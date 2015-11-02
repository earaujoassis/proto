// The MIT License (MIT)
//
// Copyright (c) 2015 Ewerton Assis <earaujoassis@gmail.com>
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the MIT license. See LICENSE for details.

#include <proto.h>
#include <string.h>

#include "utils.h"

static void *
mock_function (void *arguments)
{
  return NULL;
}

void
test_data_types ()
{
  proto_data_t *data;
  proto_object_t *object;
  proto_array_t *array;

  describe ("Create proto_data_t for decimal");
  data = proto_decimal (10.0);
  should_equal(data->type, decimal_t);
  should_equal(data->data.decimal, 10.0);
  proto_del_data (data);

  describe ("Create proto_data_t for integer");
  data = proto_integer (10);
  should_equal (data->type, integer_t);
  should_equal (data->data.integer, 10);
  proto_del_data (data);

  describe ("Create proto_data_t for string");
  data = proto_string ("Testing");
  should_equal (data->type, string_t);
  should_be_true (!strcmp (data->data.string, "Testing"));
  proto_del_data (data);

  describe ("Create proto_data_t for object");
  object = proto_init_object ();
  should_be_true (object != NULL);
  data = proto_object (object);
  should_equal (data->type, object_t);
  should_equal (data->data.object, object);
  proto_del_data (data);
  proto_del_object (object);

  describe ("Create proto_data_t for array");
  array = proto_init_array ();
  should_be_true (array != NULL);
  data = proto_array (array);
  should_equal (data->type, array_t);
  should_equal (data->data.array, array);
  proto_del_data (data);
  proto_del_array (array);

  describe ("Create proto_data_t for boolean");
  data = proto_boolean (true);
  should_equal (data->type, boolean_t);
  should_equal (data->data.boolean, true);
  proto_del_data (data);

  describe ("Create proto_data_t for function");
  data = proto_function (&mock_function);
  should_equal (data->type, function_t);
  should_equal (data->data.function, &mock_function);
  proto_del_data (data);

  describe ("Create proto_data_t for pointer");
  int pointed = 10;
  data = proto_pointer (&pointed);
  should_equal (data->type, pointer_t);
  should_equal (data->data.pointer, &pointed);
  should_equal (*((int *) data->data.pointer), pointed);
  proto_del_data (data);
}

void
test_data_types_macros ()
{
  proto_data_t *data;
  proto_object_t *object;
  proto_array_t *array;

  describe ("Create proto_data_t for decimal");
  data = T_DECIMAL (10.0);
  should_equal(TYPE_OF (data), decimal_t);
  should_equal(*(double *) VALUE (data), 10.0);
  proto_del_data (data);

  describe ("Create proto_data_t for integer");
  data = T_INTEGER (10);
  should_equal (TYPE_OF (data), integer_t);
  should_equal (*(long *) VALUE (data), 10);
  proto_del_data (data);

  describe ("Create proto_data_t for string");
  data = T_STRING ("Testing");
  should_equal (TYPE_OF (data), string_t);
  should_be_true (!strcmp ((char *) VALUE (data), "Testing"));
  proto_del_data (data);

  describe ("Create proto_data_t for object");
  object = proto_init_object ();
  should_be_true (object != NULL);
  data = T_OBJECT (object);
  should_equal (TYPE_OF (data), object_t);
  should_equal (VALUE (data), object);
  proto_del_data (data);
  proto_del_object (object);

  describe ("Create proto_data_t for array");
  array = proto_init_array ();
  should_be_true (array != NULL);
  data = T_ARRAY (array);
  should_equal (TYPE_OF (data), array_t);
  should_equal (VALUE (data), array);
  proto_del_data (data);
  proto_del_array (array);

  describe ("Create proto_data_t for boolean");
  data = T_BOOLEAN (true);
  should_equal (TYPE_OF (data), boolean_t);
  should_equal (*(bool *) VALUE (data), true);
  proto_del_data (data);

  describe ("Create proto_data_t for function");
  data = T_FUNCTION (&mock_function);
  should_equal (TYPE_OF (data), function_t);
  should_equal (VALUE (data), &mock_function);
  proto_del_data (data);

  describe ("Create proto_data_t for pointer");
  int pointed = 10;
  data = T_POINTER (&pointed);
  should_equal (TYPE_OF (data), pointer_t);
  should_equal (VALUE (data), &pointed);
  should_equal (*(int *) VALUE (data), pointed);
  proto_del_data (data);
}

void
test_data_types_interchange ()
{
  skip ("Should test interchaging data types");
}

void
run_tests ()
{
  test_data_types ();
  test_data_types_macros ();
  test_data_types_interchange ();
}
