// The MIT License (MIT)
//
// Copyright (c) 2015 Ewerton Assis <earaujoassis@gmail.com>
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the MIT license. See LICENSE for details.

#include <proto.h>

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
  should_equal (data->data.string, "Testing");
  proto_del_data (data);

  describe ("Create proto_data_t for object");
  object = proto_init_object ();
  should_be_true (object != NULL);
  data = proto_object (object);
  should_equal (data->type, object_t);
  should_equal (data->data.object, object);
  proto_del_data (data);
  proto_del_object (object);

  skip ("Create proto_data_t for list");

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
run_tests ()
{
  test_data_types ();
}
