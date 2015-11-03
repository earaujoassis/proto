// The MIT License (MIT)
//
// Copyright (c) 2015 Ewerton Assis <earaujoassis@gmail.com>
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the MIT license. See LICENSE for details.

#ifndef __proto_library_h__
#define __proto_library_h__

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef T_DECIMAL
#define T_DECIMAL(d) proto_decimal (d)
#endif
#ifndef T_INTEGER
#define T_INTEGER(d) proto_integer (d)
#endif
#ifndef T_STRING
#define T_STRING(d) proto_string (d)
#endif
#ifndef T_OBJECT
#define T_OBJECT(d) proto_object (d)
#endif
#ifndef T_ARRAY
#define T_ARRAY(d) proto_array (d)
#endif
#ifndef T_BOOLEAN
#define T_BOOLEAN(d) proto_boolean (d)
#endif
#ifndef T_FUNCTION
#define T_FUNCTION(d) proto_function (d)
#endif
#ifndef T_POINTER
#define T_POINTER(d) proto_pointer (d)
#endif
#ifndef TYPE_OF
#define TYPE_OF(v) v->type
#endif
#ifndef VALUE
#define VALUE(d) proto_data_value (d)
#endif
#ifndef TYPED_VALUE
#define TYPED_VALUE(d, mode) *(mode *) (void *) proto_data_value (d)
#endif

typedef enum {
  decimal_t  = 0x00,
  integer_t  = 0x01,
  string_t   = 0x02,
  object_t   = 0x03,
  array_t    = 0x04,
  boolean_t  = 0x05,
  function_t = 0x06,
  pointer_t  = 0x07
} proto_type_t;

typedef union {
  double decimal;
  long integer;
  char *string;
  void *object;
  void *array;
  bool boolean;
  void *(*function) (void *arguments);
  void *pointer;
} proto_typed_data_t;

typedef struct {
  proto_type_t type;
  proto_typed_data_t data;
} proto_data_t;

typedef struct {
  size_t prototype_size;
  void **prototype;
  void *super;
  void (*set_own_property) (void *self, const char *key, const void *value);
  const void *(*get_own_property) (const void *self, const char *key);
  bool (*has_own_property) (const void *self, const char *key);
  const void *(*del_own_property) (void *self, const char *key);
  const void *(*chain) (void *self, const char *keys);
  const void *(*execute_property) (void *self, const char *key, const void *arguments);
  void (*set_super) (void *self, const void *reference);
} proto_object_t;

typedef struct {
  size_t allocated;
  size_t length;
  void **items;
  void (*insert) (void *self, size_t position, const void *element);
  bool (*includes) (const void *self, const void *element);
  const void *(*at) (const void *self, size_t position);
  const void *(*del) (void *self, size_t position);
  size_t (*index) (const void *self, const void *element);
  void (*push) (void *self, const void *element);
  const void *(*pop) (void *self);
  void (*unshift) (void *self, const void *element);
  const void *(*shift) (void *self);
  const void *(*first) (const void *self);
  const void *(*last) (const void *self);
  void (*concat) (void *self, const void *list);
  void *(*reverse) (const void *self);
} proto_array_t;

proto_data_t *
proto_decimal (double data);

proto_data_t *
proto_integer (long data);

proto_data_t *
proto_string (char *data);

proto_data_t *
proto_object (void *data);

proto_data_t *
proto_array (void *data);

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

proto_array_t *
proto_init_array ();

void
proto_del_array (proto_array_t *array);

void *
proto_generic_caller (const char *arguments,
                      void *(*function) (const void *arguments), ...);

static inline void *
proto_data_value (proto_data_t *data)
{
  if (data == NULL)
    return NULL;
  switch (data->type)
    {
      case decimal_t:
        return &data->data.decimal;
        break;
      case integer_t:
        return &data->data.integer;
        break;
      case string_t:
        return data->data.string;
        break;
      case object_t:
        return data->data.object;
        break;
      case array_t:
        return data->data.array;
        break;
      case boolean_t:
        return &data->data.boolean;
        break;
      case function_t:
        return data->data.function;
        break;
      case pointer_t:
        return data->data.pointer;
        break;
    }
  return NULL;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __proto_library_h__
