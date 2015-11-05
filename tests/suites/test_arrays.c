// The MIT License (MIT)
//
// Copyright (c) 2015 Ewerton Assis <earaujoassis@gmail.com>
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the MIT license. See LICENSE for details.

#include <proto.h>

#include "utils.h"

void
test_array_creation ()
{
  proto_array_t *array;
  short int value = 10;

  describe ("Create and destroy array");
  array = proto_init_array ();
  should_be_true (array != NULL);
  should_equal (array->length, 0);
  array->push (array, &value);
  proto_del_array (array);
}

void
test_array_insert ()
{
  proto_array_t *array;
  short int value_a = 10,
    value_b = 20,
    value_c = 30,
    value_d = 40,
    value_e = 50,
    value_f = 60;

  describe ("Insert elements to array");
  array = proto_init_array ();
  should_be_true (array != NULL);
  should_equal (array->length, 0);
  array->insert (array, 0, &value_a);
  should_be_true (array->includes (array, &value_a));
  should_equal (array->at (array, 0), &value_a);
  array->insert (array, 0, &value_b);
  should_be_true (array->includes (array, &value_b));
  should_equal (array->at (array, 0), &value_b);
  should_equal (array->at (array, 1), &value_a);
  array->insert (array, 0, &value_c);
  should_be_true (array->includes (array, &value_c));
  should_equal (array->at (array, 0), &value_c);
  should_equal (array->at (array, 1), &value_b);
  should_equal (array->at (array, 2), &value_a);
  array->insert (array, 1, &value_d);
  should_be_true (array->includes (array, &value_d));
  should_equal (array->at (array, 0), &value_c);
  should_equal (array->at (array, 1), &value_d);
  should_equal (array->at (array, 2), &value_b);
  should_equal (array->at (array, 3), &value_a);
  array->insert (array, 0, &value_e);
  should_be_true (array->includes (array, &value_e));
  should_equal (array->at (array, 0), &value_e);
  should_equal (array->at (array, 1), &value_c);
  should_equal (array->at (array, 2), &value_d);
  should_equal (array->at (array, 3), &value_b);
  should_equal (array->at (array, 4), &value_a);
  array->insert (array, 1, &value_f);
  should_be_true (array->includes (array, &value_f));
  should_equal (array->at (array, 0), &value_e);
  should_equal (array->at (array, 1), &value_f);
  should_equal (array->at (array, 2), &value_c);
  should_equal (array->at (array, 3), &value_d);
  should_equal (array->at (array, 4), &value_b);
  should_equal (array->at (array, 5), &value_a);
  proto_del_array (array);
}

void
test_array_at ()
{
  proto_array_t *array;
  short int value_a = 10,
    value_b = 20,
    value_c = 30,
    value_d = 40,
    value_e = 50,
    value_f = 60,
    value_g = 70,
    value_h = 80,
    value_i = 90;

  describe ("Push elements to array and check their positions");
  array = proto_init_array ();
  should_be_true (array != NULL);
  should_equal (array->length, 0);
  should_equal (array->at (array, 0), NULL);
  should_equal (array->at (array, 8), NULL);
  array->push (array, &value_a);
  should_equal (array->length, 1);
  should_equal (array->at (array, 0), &value_a);
  array->push (array, &value_b);
  should_equal (array->length, 2);
  should_equal (array->at (array, 0), &value_a);
  should_equal (array->at (array, 1), &value_b);
  array->push (array, &value_c);
  should_equal (array->length, 3);
  should_equal (array->at (array, 0), &value_a);
  should_equal (array->at (array, 1), &value_b);
  should_equal (array->at (array, 2), &value_c);
  array->push (array, &value_d);
  should_equal (array->length, 4);
  should_equal (array->at (array, 0), &value_a);
  should_equal (array->at (array, 1), &value_b);
  should_equal (array->at (array, 2), &value_c);
  should_equal (array->at (array, 3), &value_d);
  array->push (array, &value_e);
  should_equal (array->length, 5);
  should_equal (array->at (array, 0), &value_a);
  should_equal (array->at (array, 1), &value_b);
  should_equal (array->at (array, 2), &value_c);
  should_equal (array->at (array, 3), &value_d);
  should_equal (array->at (array, 4), &value_e);
  array->push (array, &value_f);
  should_equal (array->length, 6);
  should_equal (array->at (array, 0), &value_a);
  should_equal (array->at (array, 1), &value_b);
  should_equal (array->at (array, 2), &value_c);
  should_equal (array->at (array, 3), &value_d);
  should_equal (array->at (array, 4), &value_e);
  should_equal (array->at (array, 5), &value_f);
  array->push (array, &value_g);
  should_equal (array->length, 7);
  should_equal (array->at (array, 0), &value_a);
  should_equal (array->at (array, 1), &value_b);
  should_equal (array->at (array, 2), &value_c);
  should_equal (array->at (array, 3), &value_d);
  should_equal (array->at (array, 4), &value_e);
  should_equal (array->at (array, 5), &value_f);
  should_equal (array->at (array, 6), &value_g);
  array->push (array, &value_h);
  should_equal (array->length, 8);
  should_equal (array->at (array, 0), &value_a);
  should_equal (array->at (array, 1), &value_b);
  should_equal (array->at (array, 2), &value_c);
  should_equal (array->at (array, 3), &value_d);
  should_equal (array->at (array, 4), &value_e);
  should_equal (array->at (array, 5), &value_f);
  should_equal (array->at (array, 6), &value_g);
  should_equal (array->at (array, 7), &value_h);
  array->push (array, &value_i);
  should_equal (array->length, 9);
  should_equal (array->at (array, 0), &value_a);
  should_equal (array->at (array, 1), &value_b);
  should_equal (array->at (array, 2), &value_c);
  should_equal (array->at (array, 3), &value_d);
  should_equal (array->at (array, 4), &value_e);
  should_equal (array->at (array, 5), &value_f);
  should_equal (array->at (array, 6), &value_g);
  should_equal (array->at (array, 7), &value_h);
  should_equal (array->at (array, 8), &value_i);
  proto_del_array (array);
}

void
test_array_del ()
{

  proto_array_t *array;
  short int value_a = 10,
    value_b = 20,
    value_c = 30,
    value_d = 40;

  describe ("Push elements to array and delete them");
  array = proto_init_array ();
  should_be_true (array != NULL);
  should_equal (array->length, 0);
  array->push (array, &value_a);
  array->push (array, &value_b);
  array->push (array, &value_c);
  should_equal (array->del (array, 1), &value_b);
  should_equal (array->index (array, &value_a), 0);
  should_equal (array->index (array, &value_c), 1);
  should_equal (array->length, 2);
  array->push (array, &value_d);
  should_equal (array->del (array, 0), &value_a);
  should_equal (array->index (array, &value_c), 0);
  should_equal (array->index (array, &value_d), 1);
  should_equal (array->length, 2);
  should_equal (array->del (array, 1), &value_d);
  should_equal (array->index (array, &value_c), 0);
  should_equal (array->length, 1);
  proto_del_array (array);
}

void
test_array_index ()
{
  proto_array_t *array;
  short int value_a = 10,
    value_b = 20,
    value_c = 30,
    value_d = 40,
    value_e = 50,
    value_f = 60;

  describe ("Insert elements to array and check their indexes");
  array = proto_init_array ();
  should_be_true (array != NULL);
  should_equal (array->length, 0);
  array->insert (array, 0, &value_a);
  should_be_true (array->includes (array, &value_a));
  should_equal (array->index (array, &value_a), 0);
  array->insert (array, 0, &value_b);
  should_be_true (array->includes (array, &value_b));
  should_equal (array->index (array, &value_b), 0);
  should_equal (array->index (array, &value_a), 1);
  array->insert (array, 0, &value_c);
  should_be_true (array->includes (array, &value_c));
  should_equal (array->index (array, &value_c), 0);
  should_equal (array->index (array, &value_b), 1);
  should_equal (array->index (array, &value_a), 2);
  array->insert (array, 1, &value_d);
  should_be_true (array->includes (array, &value_d));
  should_equal (array->index (array, &value_c), 0);
  should_equal (array->index (array, &value_d), 1);
  should_equal (array->index (array, &value_b), 2);
  should_equal (array->index (array, &value_a), 3);
  array->insert (array, 0, &value_e);
  should_be_true (array->includes (array, &value_e));
  should_equal (array->index (array, &value_e), 0);
  should_equal (array->index (array, &value_c), 1);
  should_equal (array->index (array, &value_d), 2);
  should_equal (array->index (array, &value_b), 3);
  should_equal (array->index (array, &value_a), 4);
  array->insert (array, 1, &value_f);
  should_be_true (array->includes (array, &value_f));
  should_equal (array->index (array, &value_e), 0);
  should_equal (array->index (array, &value_f), 1);
  should_equal (array->index (array, &value_c), 2);
  should_equal (array->index (array, &value_d), 3);
  should_equal (array->index (array, &value_b), 4);
  should_equal (array->index (array, &value_a), 5);
  proto_del_array (array);
}

void
test_array_push ()
{
  proto_array_t *array;
  short int value_a = 10,
    value_b = 20,
    value_c = 30,
    value_d = 40,
    value_e = 50;

  describe ("Push elements to array");
  array = proto_init_array ();
  should_be_true (array != NULL);
  should_equal (array->length, 0);
  array->push (array, &value_a);
  should_equal (array->at (array, array->length - 1), &value_a);
  array->push (array, &value_b);
  should_equal (array->at (array, array->length - 1), &value_b);
  array->push (array, &value_c);
  should_equal (array->at (array, array->length - 1), &value_c);
  array->push (array, &value_d);
  should_equal (array->at (array, array->length - 1), &value_d);
  array->push (array, &value_e);
  should_equal (array->at (array, array->length - 1), &value_e);
  proto_del_array (array);
}

void
test_array_pop ()
{
  proto_array_t *array;
  short int value_a = 10,
    value_b = 20,
    value_c = 30,
    value_d = 40,
    value_e = 50;

  describe ("Push elements to array and pop them out");
  array = proto_init_array ();
  should_be_true (array != NULL);
  should_equal (array->length, 0);
  array->push (array, &value_a);
  array->push (array, &value_b);
  array->push (array, &value_c);
  array->push (array, &value_d);
  array->push (array, &value_e);
  should_equal (array->pop (array), &value_e);
  should_equal (array->pop (array), &value_d);
  should_equal (array->pop (array), &value_c);
  should_equal (array->pop (array), &value_b);
  should_equal (array->pop (array), &value_a);
  proto_del_array (array);
}

void
test_array_unshift ()
{
  proto_array_t *array;
  short int value_a = 10,
    value_b = 20,
    value_c = 30,
    value_d = 40,
    value_e = 50;

  describe ("Unshift elements to array");
  array = proto_init_array ();
  should_be_true (array != NULL);
  should_equal (array->length, 0);
  array->unshift (array, &value_a);
  should_equal (array->at (array, 0), &value_a);
  array->unshift (array, &value_b);
  should_equal (array->at (array, 0), &value_b);
  array->unshift (array, &value_c);
  should_equal (array->at (array, 0), &value_c);
  array->unshift (array, &value_d);
  should_equal (array->at (array, 0), &value_d);
  array->unshift (array, &value_e);
  should_equal (array->at (array, 0), &value_e);
  proto_del_array (array);
}

void
test_array_shift ()
{
  proto_array_t *array;
  short int value_a = 10,
    value_b = 20,
    value_c = 30,
    value_d = 40,
    value_e = 50;

  describe ("Unshift elements to array and shift them out");
  array = proto_init_array ();
  should_be_true (array != NULL);
  should_equal (array->length, 0);
  array->unshift (array, &value_a);
  array->unshift (array, &value_b);
  array->unshift (array, &value_c);
  array->unshift (array, &value_d);
  array->unshift (array, &value_e);
  should_equal (array->shift (array), &value_e);
  should_equal (array->shift (array), &value_d);
  should_equal (array->shift (array), &value_c);
  should_equal (array->shift (array), &value_b);
  should_equal (array->shift (array), &value_a);
  proto_del_array (array);
}

void
test_array_stress ()
{
  proto_array_t *array;
  short int *pointer;
  size_t i;

  describe ("Stress an array instance");
  array = proto_init_array ();
  for (i = 0; i < 100; i++)
    {
      pointer = (short int *) malloc (sizeof (short int));
      *pointer = (short int) i + 1;
      array->push (array, pointer);
    }
  should_equal (array->length, 100);
  should_equal (*(short int *) array->first (array), 1);
  should_equal (*(short int *) array->at (array, 24), 25);
  should_equal (*(short int *) array->at (array, 49), 50);
  should_equal (*(short int *) array->at (array, 74), 75);
  should_equal (*(short int *) array->last (array), 100);
  for (i = 0; i < 100; i++)
    free ((short int *) array->pop (array));
  proto_del_array (array);
}

void
test_array_concat ()
{
  proto_array_t *array, *another;
  short int value_a = 1,
    value_b = 2,
    value_c = 3,
    value_d = 4;

  describe ("Concat one array into another");
  array = proto_init_array ();
  array->push (array, &value_a);
  array->push (array, &value_b);
  should_equal (array->length, 2);
  another = proto_init_array ();
  another->push (another, &value_c);
  another->push (another, &value_d);
  should_equal (another->length, 2);
  array->concat (array, another);
  should_equal (array->length, 4);
  should_equal (*(short int *) array->first (array), 1);
  should_equal (*(short int *) array->at (array, 1), 2);
  should_equal (*(short int *) array->at (array, 2), 3);
  should_equal (*(short int *) array->last (array), 4);
  should_equal (another->length, 2);
  proto_del_array (another);
  proto_del_array (array);
}

void
test_array_reverse ()
{
  proto_array_t *array, *reversed;
  short int value_a = 1,
    value_b = 2,
    value_c = 3,
    value_d = 4,
    value_e = 5;

  describe ("Reverse an array");
  array = proto_init_array ();
  should_be_true (array != NULL);
  should_equal (array->length, 0);
  reversed = array->reverse (array);
  should_be_true (reversed != NULL);
  should_equal (reversed->length, 0);
  proto_del_array (reversed);
  array->push (array, &value_a);
  array->push (array, &value_b);
  array->push (array, &value_c);
  array->push (array, &value_d);
  array->push (array, &value_e);
  should_equal (array->length, 5);
  should_equal (*(short int *) array->first (array), 1);
  should_equal (*(short int *) array->at (array, 2), 3);
  should_equal (*(short int *) array->last (array), 5);
  reversed = array->reverse (array);
  should_be_true (reversed != NULL);
  should_equal (reversed->length, 5);
  should_equal (*(short int *) reversed->first (reversed), 5);
  should_equal (*(short int *) reversed->at (reversed, 2), 3);
  should_equal (*(short int *) reversed->last (reversed), 1);
  proto_del_array (reversed);
  proto_del_array (array);
}

void
run_tests ()
{
  test_array_creation ();
  test_array_insert ();
  test_array_at ();
  test_array_del ();
  test_array_index ();
  test_array_push ();
  test_array_pop ();
  test_array_unshift ();
  test_array_shift ();
  test_array_stress ();
  test_array_concat ();
  test_array_reverse ();
}
