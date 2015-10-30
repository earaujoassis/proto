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

proto_data_t *
proto_decimal (double data)
{
  proto_data_t *data_struct = (proto_data_t *) malloc (sizeof (proto_data_t));
  if (!data_struct)
    return NULL;
  data_struct->type = decimal_t;
  data_struct->data.decimal = data;
  return data_struct;
}

proto_data_t *
proto_integer (long data)
{
  proto_data_t *data_struct = (proto_data_t *) malloc (sizeof (proto_data_t));
  if (!data_struct)
    return NULL;
  data_struct->type = integer_t;
  data_struct->data.integer = data;
  return data_struct;
}

proto_data_t *
proto_string (char *data)
{
  proto_data_t *data_struct = (proto_data_t *) malloc (sizeof (proto_data_t));
  if (!data_struct)
    return NULL;
  data_struct->type = string_t;
  data_struct->data.string = data;
  return data_struct;
}

proto_data_t *
proto_object (void *data)
{
  proto_data_t *data_struct = (proto_data_t *) malloc (sizeof (proto_data_t));
  if (!data_struct)
    return NULL;
  data_struct->type = object_t;
  data_struct->data.object = data;
  return data_struct;
}

proto_data_t *
proto_list (void *data)
{
  proto_data_t *data_struct = (proto_data_t *) malloc (sizeof (proto_data_t));
  if (!data_struct)
    return NULL;
  data_struct->type = list_t;
  data_struct->data.list = data;
  return data_struct;
}

proto_data_t *
proto_boolean (bool data)
{
  proto_data_t *data_struct = (proto_data_t *) malloc (sizeof (proto_data_t));
  if (!data_struct)
    return NULL;
  data_struct->type = boolean_t;
  data_struct->data.boolean = data;
  return data_struct;
}

proto_data_t *
proto_function (void *(*data) (void *arguments))
{
  proto_data_t *data_struct = (proto_data_t *) malloc (sizeof (proto_data_t));
  if (!data_struct)
    return NULL;
  data_struct->type = function_t;
  data_struct->data.function = data;
  return data_struct;
}

proto_data_t *
proto_pointer (void *data)
{
  proto_data_t *data_struct = (proto_data_t *) malloc (sizeof (proto_data_t));
  if (!data_struct)
    return NULL;
  data_struct->type = pointer_t;
  data_struct->data.pointer = data;
  return data_struct;
}

void
proto_del_data (proto_data_t *data)
{
  free (data);
}

#ifndef PROTOTYPE_SIZE
#define PROTOTYPE_SIZE 20
#endif

typedef struct proto_hashmap_entry {
  const char *key;
  const void *value;
  struct proto_hashmap_entry *left;
  struct proto_hashmap_entry *right;
  bool should_free_value;
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
      (*root)->value = item->value;
      (*root)->should_free_value = item->should_free_value;
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
  proto_object_t *object = (proto_object_t *) self;
  proto_hashmap_entry_t *entry;
  unsigned long hash = proto_hash_code (key) % object->prototype_size;
  entry = (proto_hashmap_entry_t *) malloc (sizeof (proto_hashmap_entry_t));
  entry->key = key;
  entry->value = value;
  entry->left = NULL;
  entry->right = NULL;
  entry->should_free_value = false;
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
    {
      return *root;
    }
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
proto_find_minimal (proto_hashmap_entry_t *root)
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
          free (root);
          root = NULL;
        }
      else if (root->left == NULL)
        {
          proto_hashmap_entry_t *garbage = root;
          root = root->right;
          free (garbage);
        }
      else if (root->right == NULL)
        {
          proto_hashmap_entry_t *garbage = root;
          root = root->left;
          free (garbage);
        }
      else
        {
          proto_hashmap_entry_t *garbage = proto_find_minimal (root->right);
          root->value = garbage->value;
          root->should_free_value = garbage->should_free_value;
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

proto_object_t *
proto_init_object ()
{
  size_t i;
  proto_object_t *object = (proto_object_t *) malloc (sizeof (proto_object_t));
  if (!object)
    return NULL;
  object->prototype_size = PROTOTYPE_SIZE;
  object->prototype = (void **) calloc (PROTOTYPE_SIZE, sizeof (proto_hashmap_entry_t *));
  for (i = 0; i < PROTOTYPE_SIZE; i++)
    object->prototype[i] = NULL;
  object->has_own_property = &proto_has_own_property;
  object->get_own_property = &proto_get_own_property;
  object->set_own_property = &proto_set_own_property;
  object->del_own_property = &proto_del_own_property;
  object->chain = NULL; //TODO
  return object;
}

static void
proto_del_hashmap_entry (proto_hashmap_entry_t *entry)
{
  if (entry != NULL) {
    proto_del_hashmap_entry (entry->left);
    proto_del_hashmap_entry (entry->right);
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
