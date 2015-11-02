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

#ifndef ARRAY_ITEMS_SIZE
#define ARRAY_ITEMS_SIZE 4
#endif

/*
 * It uses the same strategy defined in Python implementation of lists.
 * Allocation expansion follows: 4, 8, 16, 25, 35, 46, 58, 72, 88, ...
 */
static short int
proto_array_resize (proto_array_t *array,
                    size_t newsize)
{
  void **items;
  size_t new_allocated, allocated = array->allocated;

  if (allocated >= newsize && newsize >= (allocated >> 1))
    return 0;
  new_allocated = (newsize >> 3) + (newsize < 9 ? 3 : 6);
  new_allocated += newsize;
  items = realloc (array->items, new_allocated * sizeof (void *));
  if (!items)
    return -1;
  array->items = items;
  array->allocated = new_allocated;
  return 0;
}

static void
proto_insert (void *self,
              size_t position,
              const void *element)
{
  if (self == NULL)
    return;
  size_t i;
  proto_array_t *array = (proto_array_t *) self;

  if (position > array->length)
    return;
  if (proto_array_resize (array, array->length + 1) == -1)
    return;
  for (i = array->length; i > position; i--)
    array->items[i] = array->items[i - 1];
  array->items[i] = (void *) element;
  array->length++;
}

static bool
proto_includes (const void *self,
                const void *element)
{
  if (self == NULL)
    return NULL;
  size_t i;
  proto_array_t *array = (proto_array_t *) self;

  for (i = 0; i < array->length; i++)
    if (array->items[i] == element)
      return true;
  return false;
}

static const void *
proto_at (const void *self,
          size_t position)
{
  if (self == NULL)
    return NULL;
  proto_array_t *array = (proto_array_t *) self;

  if (array->length > position)
    return array->items[position];
  return NULL;
}

static const void *
proto_del (void *self,
           size_t position)
{
  if (self == NULL)
    return NULL;
  proto_array_t *array = (proto_array_t *) self;
  size_t length = array->length;
  const void *value;

  if (length > position)
    {
      value = array->items[position];
      if (position == length - 1)
        array->items[position] = NULL;
      else
        {
          size_t i;

          for (i = position; i < length - 1; i++)
            array->items[i] = array->items[i + 1];
          array->items[i] = NULL;
        }
      array->length--;
      return value;
    }
  return NULL;
}

static size_t
proto_index (const void *self,
             const void *element)
{
  if (self == NULL)
    return -1;
  size_t i;
  proto_array_t *array = (proto_array_t *) self;

  for (i = 0; i < array->length; i++)
    if (array->items[i] == element)
      return i;
  return -1;
}

static void
proto_push (void *self,
            const void *element)
{
  if (self == NULL)
    return;
  proto_array_t *array = (proto_array_t *) self;

  if (proto_array_resize (array, array->length + 1) == -1)
    return;
  array->items[array->length++] = (void *) element;
}

static const void *
proto_pop (void *self)
{
  if (self == NULL)
    return NULL;
  const void *value;
  proto_array_t *array = (proto_array_t *) self;

  value = array->items[--array->length];
  array->items[array->length] = NULL;
  return value;
}

static void
proto_unshift (void *self,
               const void *element)
{
  if (self == NULL)
    return;
  proto_array_t *array = (proto_array_t *) self;

  array->insert (array, 0, element);
}

static const void *
proto_shift (void *self)
{
  if (self == NULL)
    return NULL;
  proto_array_t *array = (proto_array_t *) self;

  return array->del (array, 0);
}

static const void *
proto_first (const void *self)
{
  if (self == NULL)
    return NULL;
  proto_array_t *array = (proto_array_t *) self;

  return array->at (array, 0);
}

static const void *
proto_last (const void *self)
{
  if (self == NULL)
    return NULL;
  proto_array_t *array = (proto_array_t *) self;

  return array->at (array, array->length - 1);
}

proto_array_t *
proto_init_array ()
{
  size_t i;
  proto_array_t *array = (proto_array_t *) malloc (sizeof (proto_array_t));

  if (!array)
    return NULL;
  array->allocated = ARRAY_ITEMS_SIZE;
  array->length = 0;
  array->items = (void **) calloc (ARRAY_ITEMS_SIZE, sizeof (void *));
  if (!array->items)
    {
      free (array);
      return NULL;
    }
  for (i = 0; i < ARRAY_ITEMS_SIZE; i++)
    array->items[i] = NULL;
  array->insert = &proto_insert;
  array->includes = &proto_includes;
  array->at = &proto_at;
  array->del = &proto_del;
  array->index = &proto_index;
  array->push = &proto_push;
  array->pop = &proto_pop;
  array->unshift = &proto_unshift;
  array->shift = &proto_shift;
  array->first = &proto_first;
  array->last = &proto_last;
  return array;
}

void
proto_del_array (proto_array_t *array)
{
  free (array->items);
  free (array);
}
