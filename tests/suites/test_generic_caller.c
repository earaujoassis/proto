// The MIT License (MIT)
//
// Copyright (c) 2015 Ewerton Assis <earaujoassis@gmail.com>
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the MIT license. See LICENSE for details.

#include <proto.h>

#include "utils.h"

void *
reduce_integers (const void *arguments)
{
  size_t i;
  proto_array_t *arguments_list = (proto_array_t *) arguments;
  long *total = (long *) malloc (sizeof (long));
  *total = 0;

  for (i = 0; i < arguments_list->length; i++)
    *total += TYPED_VALUE ((proto_data_t *) arguments_list->at (arguments_list, i), long);
  return total;
}

void *
reduce_doubles (const void *arguments)
{
  size_t i;
  proto_array_t *arguments_list = (proto_array_t *) arguments;
  double *total = (double *) malloc (sizeof (double));
  *total = 0;

  for (i = 0; i < arguments_list->length; i++)
    *total += TYPED_VALUE ((proto_data_t *) arguments_list->at (arguments_list, i), double);
  return total;
}

void
test_generic_caller ()
{
  void *return_value;

  describe ("Should make a call to a generic function with the given arguments");
  return_value = proto_generic_caller ("%i %i %i %i %i", &reduce_integers,
    (long) 1, (long) 2, (long) 3, (long) 4, (long) 5);
  should_equal (*(long *) return_value, 15);
  free (return_value);

  describe ("Should make a call to a generic function with the given arguments");
  return_value = proto_generic_caller ("%d %d %d %d %d", &reduce_doubles,
    (double) 1.1, (double) 2.2, (double) 3.3, (double) 4.4, (double) 5.5);
  should_equal (*(double *) return_value, 16.5);
  free (return_value);
}

void
run_tests ()
{
  test_generic_caller ();
}
