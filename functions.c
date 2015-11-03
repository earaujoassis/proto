// The MIT License (MIT)
//
// Copyright (c) 2015 Ewerton Assis <earaujoassis@gmail.com>
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the MIT license. See LICENSE for details.

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "proto.h"

void *
proto_generic_caller (const char *arguments,
                      void *(*function) (const void *arguments), ...)
{
  size_t i;
  char current_char;
  void *return_value;
  va_list args;
  proto_array_t *arguments_list = proto_init_array ();

  va_start (args, function);
  i = 0;
  current_char = arguments[i];
  while (current_char != '\0')
    {
      if (current_char == '%')
        {
          current_char = arguments[++i];
          switch (current_char)
            {
              case 'd':
                arguments_list->push (arguments_list, T_DECIMAL (va_arg (args, double)));
                break;
              case 'i':
                arguments_list->push (arguments_list, T_INTEGER (va_arg (args, long)));
                break;
              case 's':
                arguments_list->push (arguments_list, T_STRING (va_arg (args, char *)));
                break;
              case 'o':
                arguments_list->push (arguments_list, T_OBJECT (va_arg (args, void *)));
                break;
              case 'a':
                arguments_list->push (arguments_list, T_ARRAY (va_arg (args, void *)));
                break;
              case 'b':
                arguments_list->push (arguments_list, T_BOOLEAN (va_arg (args, bool)));
                break;
              case 'f':
                arguments_list->push (arguments_list, T_FUNCTION (va_arg (args, void *)));
                break;
              case 'p':
                arguments_list->push (arguments_list, T_POINTER (va_arg (args, void *)));
                break;
            }
        }
      current_char = arguments[++i];
    }
  va_end (args);
  return_value = function (arguments_list);
  while (arguments_list->length)
    free ((void *) arguments_list->pop (arguments_list));
  proto_del_array (arguments_list);
  return return_value;
}
