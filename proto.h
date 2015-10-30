// The MIT License (MIT)
//
// Copyright (c) 2015 Ewerton Assis <earaujoassis@gmail.com>
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the MIT license. See LICENSE for details.

#ifndef __proto_datastructures_h__
#define __proto_datastructures_h__

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum {
  decimal_t,
  integer_t,
  string_t,
  object_t,
  list_t,
  boolean_t,
  function_t,
  pointer_t
} proto_type_t;

typedef union {
  double decimal;
  long integer;
  char *string;
  void *object;
  void *list;
  bool boolean;
  void *(*function) (void *arguments);
  void *pointer;
} proto_variable_t;

typedef struct {
  proto_type_t type;
  proto_variable_t data;
} proto_data_t;

typedef struct {
  bool (*has_own_property) (const void *self, const char *key);
  const void *(*get_own_property) (const void *self, const char *key);
  void (*set_own_property) (void *self, const char *key, const void *value);
  const void *(*del_own_property) (void *self, const char *key);
  const void *(*chain) (void *self, const char *keys);
  size_t prototype_size;
  void **prototype;
} proto_object_t;

proto_data_t *
proto_decimal (double data);

proto_data_t *
proto_integer (long data);

proto_data_t *
proto_string (char *data);

proto_data_t *
proto_object (void *data);

proto_data_t *
proto_list (void *data);

proto_data_t *
proto_boolean (bool data);

proto_data_t *
proto_function (void *(*data) (void *arguments));

proto_data_t *
proto_pointer (void *data);

void
proto_del_data (proto_data_t *data);

proto_object_t *
proto_init_object ();

void
proto_del_object (proto_object_t *object);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __proto_datastructures_h__
