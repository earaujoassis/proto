// The MIT License (MIT)
//
// Copyright (c) 2015 Ewerton Assis <earaujoassis@gmail.com>
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the MIT license. See LICENSE for details.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proto.h"

#ifndef OBJECT_PROTOTYPE_SIZE
#define OBJECT_PROTOTYPE_SIZE 20
#endif

typedef struct proto_hashmap_entry {
  const char *key;
  const void *value;
  struct proto_hashmap_entry *left;
  struct proto_hashmap_entry *right;
  bool is_internal_object;
} proto_hashmap_entry_t;

static unsigned long
proto_hash_code (const char *str)
{
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

static void
proto_btree_insert (proto_hashmap_entry_t **root,
                    proto_hashmap_entry_t *item)
{
  if ((*root) == NULL)
    {
      *root = item;
      return;
    }
  int strcmp_value = strcmp (item->key, (*root)->key);

  if (!strcmp_value)
    {
      // Reassign value to object
      if ((*root)->is_internal_object)
        proto_del_object ((*root)->value);
      (*root)->value = item->value;
      (*root)->is_internal_object = false;
    }
  if (strcmp_value < 0)
    proto_btree_insert (&(*root)->left, item);
   else // strcmp_value > 0
    proto_btree_insert (&(*root)->right, item);
}

static void
proto_set_own_property (void *self,
                        const char *key,
                        const void *value)
{
  if (key == NULL)
    return;
  proto_object_t *object = (proto_object_t *) self;
  proto_hashmap_entry_t *entry;
  unsigned long hash = proto_hash_code (key) % object->prototype_size;
  char *key_copy;

  entry = (proto_hashmap_entry_t *) malloc (sizeof (proto_hashmap_entry_t));
  if (!entry)
    return;
  key_copy = (char *) calloc (strlen (key) + 1, sizeof (char *));
  if (!key_copy)
    {
      free (entry);
      return;
    }
  strcpy (key_copy, key);
  entry->key = key_copy;
  entry->value = value;
  entry->left = NULL;
  entry->right = NULL;
  entry->is_internal_object = false;
  proto_btree_insert ((proto_hashmap_entry_t **) &object->prototype[hash], entry);
}

static proto_hashmap_entry_t *
proto_btree_retrieve (proto_hashmap_entry_t **root,
                      const char *key)
{
  if ((*root) == NULL)
    {
      return NULL;
    }
  int strcmp_value = strcmp (key, (*root)->key);

  if (!strcmp_value)
    return *root;
  if (strcmp_value < 0)
    return proto_btree_retrieve (&(*root)->left, key);
   else // strcmp_value > 0
    return proto_btree_retrieve (&(*root)->right, key);
}

static const void *
proto_get_own_property (const void *self,
                        const char *key)
{
  proto_object_t *object = (proto_object_t *) self;
  unsigned long hash = proto_hash_code (key) % object->prototype_size;
  proto_hashmap_entry_t *entry = proto_btree_retrieve ((proto_hashmap_entry_t **) &object->prototype[hash], key);

  if (entry == NULL)
    return NULL;
  return entry->value;
}

static bool
proto_has_own_property (const void *self,
                        const char *key)
{
  proto_object_t *object = (proto_object_t *) self;
  unsigned long hash = proto_hash_code (key) % object->prototype_size;
  proto_hashmap_entry_t *entry = proto_btree_retrieve ((proto_hashmap_entry_t **) &object->prototype[hash], key);

  if (entry == NULL)
    return false;
  return true;
}

static proto_hashmap_entry_t *
proto_btree_find_minimal (proto_hashmap_entry_t *root)
{
  proto_hashmap_entry_t *tmp = root;

  while (tmp->left != NULL)
    tmp = tmp->left;
  return tmp;
}

static proto_hashmap_entry_t *
proto_btree_delete (proto_hashmap_entry_t *root,
                    const char *key)
{
  if (root == NULL)
    return root;
  int strcmp_value = strcmp (key, root->key);

  if (strcmp_value < 0)
    root->left = proto_btree_delete (root->left, key);
  else if (strcmp_value > 0)
    root->right = proto_btree_delete (root->right, key);
  else
    {
      if (root->left == NULL && root->right == NULL)
        {
          free (root->key);
          free (root);
          root = NULL;
        }
      else if (root->left == NULL)
        {
          proto_hashmap_entry_t *garbage = root;
          root = root->right;
          free (garbage->key);
          free (garbage);
        }
      else if (root->right == NULL)
        {
          proto_hashmap_entry_t *garbage = root;
          root = root->left;
          free (garbage->key);
          free (garbage);
        }
      else
        {
          proto_hashmap_entry_t *garbage = proto_btree_find_minimal (root->right);
          root->value = garbage->value;
          root->is_internal_object = garbage->is_internal_object;
          root->right = proto_btree_delete (root->right, key);
        }
    }
  return root;
}

static void
proto_print_btree (const proto_hashmap_entry_t *root)
{
  int value;

  if (root == NULL)
    {
      printf (" n ");
      return;
    }
  value = *(int *) root->value;
  proto_print_btree (root->left);
  printf (" %d ", value);
  proto_print_btree (root->right);
}

static const void *
proto_del_own_property (void *self,
                        const char *key)
{
  const void *value;
  proto_object_t *object = (proto_object_t *) self;
  unsigned long hash = proto_hash_code (key) % object->prototype_size;
  proto_hashmap_entry_t *entry = proto_btree_retrieve ((proto_hashmap_entry_t **) &object->prototype[hash], key);

  if (entry == NULL)
    return NULL;
  value = entry->value;
  object->prototype[hash] = proto_btree_delete ((proto_hashmap_entry_t *) object->prototype[hash], key);
  return value;
}

static void
proto_set_chain (void *self,
                 const char *keys,
                 const void *new_value)
{
  proto_object_t *object, *new_object;
  proto_hashmap_entry_t *entry;
  size_t key_max_length = strlen (keys), pos_keys_chain, pos_current_key;
  char *current_key, *previous_key, current_char;
  unsigned long hash;
  const void *value = self;

  if (key_max_length == 0)
    return;
  previous_key = NULL;
  current_key = (char *) calloc (key_max_length + 1, sizeof (char));
  for (pos_current_key = 0, pos_keys_chain = 0, current_char = keys[0]; \
    pos_keys_chain < key_max_length || current_char != '\0'; \
    current_char = keys[++pos_keys_chain])
    {
      if (current_char == '.')
        {
          if (previous_key != NULL)
            {
              object = (proto_object_t *) value;
              new_object = proto_init_object ();
              object->set_own_property (object, previous_key, new_object);
              hash = proto_hash_code (previous_key) % object->prototype_size;
              entry = proto_btree_retrieve ((proto_hashmap_entry_t **) &object->prototype[hash], previous_key);
              entry->is_internal_object = true;
              value = new_object;
              free (previous_key);
              previous_key = NULL;
            }
          object = (proto_object_t *) value;
          current_key[pos_current_key] = '\0';
          if (object->has_own_property (object, current_key))
            value = object->get_own_property (object, current_key);
          else
            {
              previous_key = (char *) calloc (pos_current_key + 1, sizeof (char));
              strcpy (previous_key, current_key);
            }
          pos_current_key = 0;
        }
      else
        current_key[pos_current_key++] = current_char;
    }
  if (previous_key != NULL)
    {
      object = (proto_object_t *) value;
      new_object = proto_init_object ();
      object->set_own_property (object, previous_key, new_object);
      hash = proto_hash_code (previous_key) % object->prototype_size;
      entry = proto_btree_retrieve ((proto_hashmap_entry_t **) &object->prototype[hash], previous_key);
      entry->is_internal_object = true;
      value = new_object;
      free (previous_key);
      previous_key = NULL;
    }
  if (key_max_length > 0 && pos_current_key > 0)
    {
      object = (proto_object_t *) value;
      current_key[pos_current_key] = '\0';
      object->set_own_property (object, current_key, new_value);
    }
  free (current_key);
}

static const void *
proto_get_chain (const void *self,
                 const char *keys)
{
  proto_object_t *object;
  size_t key_max_length = strlen (keys), pos_keys_chain, pos_current_key;
  char current_key[key_max_length + 1], current_char;
  const void *value = self;

  if (key_max_length == 0)
    return NULL;
  for (pos_current_key = 0, pos_keys_chain = 0, current_char = keys[0]; \
    pos_keys_chain < key_max_length || current_char != '\0'; \
    current_char = keys[++pos_keys_chain])
    {
      if (current_char == '.')
        {
          object = (proto_object_t *) value;
          current_key[pos_current_key] = '\0';
          if (object->has_own_property (object, current_key))
            value = object->get_own_property (object, current_key);
          pos_current_key = 0;
        }
      else
        current_key[pos_current_key++] = current_char;
    }
  if (key_max_length > 0 && pos_current_key > 0)
    {
      object = (proto_object_t *) value;
      current_key[pos_current_key] = '\0';
      if (object->has_own_property (object, current_key))
        value = object->get_own_property (object, current_key);
      else
        value = NULL;
    }
  return value;
}

static bool
proto_has_chain (const void *self,
                 const char *keys)
{
  proto_object_t *object = (proto_object_t *) self;

  if (object->get_chain (object, keys) != NULL)
    return true;
  return false;
}

static const void *
proto_execute_property (void *self,
                        const char *key,
                        const void *arguments)
{
  proto_object_t *object = (proto_object_t *) self;
  void *(*function) (const void *arguments);

  if (object->has_own_property (object, key)) {
    function = object->get_own_property (object, key);
    return (const void *) function (arguments);
  }
  return NULL;
}

static void
proto_set_super (void *self,
                 const void *reference)
{
  proto_object_t *object = (proto_object_t *) self;
  object->super = (proto_object_t *) reference;
}

static char **
proto_btree_keys (size_t *number_of_keys,
                  char **keys,
                  const proto_hashmap_entry_t *root)
{
  if (root == NULL)
    return keys;
  keys = proto_btree_keys (number_of_keys, keys, root->left);
  keys = proto_btree_keys (number_of_keys, keys, root->right);
  *number_of_keys = (*number_of_keys) + 1;
  keys = (char **) realloc (keys, (*number_of_keys) * sizeof (char *));
  keys[(*number_of_keys) - 1] = root->key;
  return keys;
}

static void
proto_merge (void *self,
             const void *reference)
{
  const proto_object_t *another = (const proto_object_t *) reference;
  proto_object_t *object = (proto_object_t *) self;
  proto_hashmap_entry_t *root;
  size_t number_of_keys, prototype_size, i, j;
  char **keys, *key;

  prototype_size = another->prototype_size;
  for (i = 0; i < prototype_size; i++)
    {
      keys = NULL;
      number_of_keys = 0;
      root = another->prototype[i];
      keys = proto_btree_keys (&number_of_keys, keys, root);
      if (keys != NULL)
        {
          for (j = 0; j < number_of_keys; j++)
            {
              key = keys[j];
              const void *value = another->get_own_property (another, key);
              object->set_own_property (object, key, value);
            }
          free (keys);
        }
    }
}

proto_object_t *
proto_init_object ()
{
  size_t i;
  proto_object_t *object = (proto_object_t *) malloc (sizeof (proto_object_t));

  if (!object)
    return NULL;
  object->super = NULL;
  object->prototype_size = OBJECT_PROTOTYPE_SIZE;
  object->prototype = (void **) calloc (OBJECT_PROTOTYPE_SIZE, sizeof (proto_hashmap_entry_t *));
  if (!object->prototype)
    {
      free (object);
      return NULL;
    }
  for (i = 0; i < OBJECT_PROTOTYPE_SIZE; i++)
    object->prototype[i] = NULL;
  object->set_own_property = &proto_set_own_property;
  object->get_own_property = &proto_get_own_property;
  object->has_own_property = &proto_has_own_property;
  object->del_own_property = &proto_del_own_property;
  object->set_chain = &proto_set_chain;
  object->get_chain = &proto_get_chain;
  object->has_chain = &proto_has_chain;
  object->execute_property = &proto_execute_property;
  object->set_super = &proto_set_super;
  object->merge = &proto_merge;
  return object;
}

static void
proto_del_hashmap_entry (proto_hashmap_entry_t *entry)
{
  if (entry != NULL) {
    proto_del_hashmap_entry (entry->left);
    proto_del_hashmap_entry (entry->right);
    if (entry->is_internal_object)
      proto_del_object (entry->value);
    free (entry->key);
    free (entry);
  }
}

void
proto_del_object (proto_object_t *object)
{
  size_t i;
  proto_hashmap_entry_t **prototype = (proto_hashmap_entry_t **) object->prototype;

  for (i = 0; i < object->prototype_size; i++)
    {
      proto_hashmap_entry_t *entry = prototype[i];
      proto_del_hashmap_entry (entry);
    }
  free (prototype);
  free (object);
}
