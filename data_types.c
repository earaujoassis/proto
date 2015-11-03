// The MIT License (MIT)
//
// Copyright (c) 2015 Ewerton Assis <earaujoassis@gmail.com>
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the MIT license. See LICENSE for details.

#include <stdio.h>
#include <stdlib.h>

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
proto_array (void *data)
{
  proto_data_t *data_struct = (proto_data_t *) malloc (sizeof (proto_data_t));

  if (!data_struct)
    return NULL;
  data_struct->type = array_t;
  data_struct->data.array = data;
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
