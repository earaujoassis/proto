// The MIT License (MIT)
//
// Copyright (c) 2015 Ewerton Assis <earaujoassis@gmail.com>
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the MIT license. See LICENSE for details.

#include <proto.h>

#include "utils.h"

void
test_object_creation ()
{
  proto_object_t *object;
  short int value = 10;

  describe ("Create and destroy object");
  object = proto_init_object ();
  should_be_true (object != NULL);
  object->set_own_property (object, "testing", &value);
  should_be_true (object->has_own_property (object, "testing"));
  should_be_false (object->has_own_property (object, "another_key"));
  should_equal (*((short int *) object->get_own_property (object, "testing")), value);
  should_equal (object->get_own_property (object, "another_key"), NULL);
  proto_del_object (object);
}

void
test_object_reassignment_of_key ()
{
  proto_object_t *object;
  short int value_a = 10, value_b = 20;

  describe ("Create object and reassign a value to the same key");
  object = proto_init_object ();
  should_be_true (object != NULL);
  object->set_own_property (object, "testing", &value_a);
  should_be_true (object->has_own_property (object, "testing"));
  should_be_false (object->has_own_property (object, "another_key"));
  should_equal (*((short int *) object->get_own_property (object, "testing")), value_a);
  should_equal (object->get_own_property (object, "another_key"), NULL);
  object->set_own_property (object, "testing", &value_b);
  should_equal (*((short int *) object->get_own_property (object, "testing")), value_b);
  proto_del_object (object);
}

void
test_object_with_pointer ()
{
  proto_object_t *object;
  short int *pointer, *deleted;

  describe ("Create object and assign a key to a pointer");
  object = proto_init_object ();
  should_be_true (object != NULL);
  pointer = (short int *) malloc (sizeof (short int));
  *pointer = 200;
  object->set_own_property (object, "pointer", pointer);
  should_be_true (object->has_own_property (object, "pointer"));
  should_equal ((short int *) object->get_own_property (object, "pointer"), pointer);
  should_equal (*(short int *) object->get_own_property (object, "pointer"), *pointer);
  deleted = (short int *) object->del_own_property (object, "pointer");
  free (deleted);
  proto_del_object (object);
}

void
test_object_with_multiple_keys ()
{
  proto_object_t *object;
  short int value_a = 10, value_b = 20, value_c = 30;

  describe ("Create object and assign multiple keys");
  object = proto_init_object ();
  should_be_true (object != NULL);
  object->set_own_property (object, "a", &value_a);
  should_be_true (object->has_own_property (object, "a"));
  should_equal (*((short int *) object->get_own_property (object, "a")), value_a);
  object->set_own_property (object, "b", &value_b);
  should_be_true (object->has_own_property (object, "b"));
  should_equal (*((short int *) object->get_own_property (object, "b")), value_b);
  object->set_own_property (object, "c", &value_c);
  should_be_true (object->has_own_property (object, "c"));
  should_equal (*((short int *) object->get_own_property (object, "c")), value_c);
  proto_del_object (object);
}

void
test_object_with_colliding_keys ()
{
  proto_object_t *object;
  short int value_a = 10, value_b = 20, value_c = 30, value_d = 40;

  describe ("Create object and assign colliding keys");
  object = proto_init_object ();
  should_be_true (object != NULL);
  object->set_own_property (object, "computer", &value_a);
  should_be_true (object->has_own_property (object, "computer"));
  should_equal (*((short int *) object->get_own_property (object, "computer")), value_a);
  object->set_own_property (object, "programming", &value_b);
  should_be_true (object->has_own_property (object, "programming"));
  should_equal (*((short int *) object->get_own_property (object, "programming")), value_b);
  object->set_own_property (object, "testing", &value_c);
  should_be_true (object->has_own_property (object, "testing"));
  should_equal (*((short int *) object->get_own_property (object, "testing")), value_c);
  object->set_own_property (object, "go", &value_d);
  should_be_true (object->has_own_property (object, "go"));
  should_equal (*((short int *) object->get_own_property (object, "go")), value_d);
  proto_del_object (object);
}

void
test_object_deletion_of_key ()
{
  proto_object_t *object;
  short int value_a = 10, value_b = 20, value_c = 30, value_d = 40, deleted;

  describe ("Create object, assign keys and delete them");
  object = proto_init_object ();
  should_be_true (object != NULL);
  object->set_own_property (object, "computer", &value_a);
  should_be_true (object->has_own_property (object, "computer"));
  should_equal (*((short int *) object->get_own_property (object, "computer")), value_a);
  object->set_own_property (object, "programming", &value_b);
  should_be_true (object->has_own_property (object, "programming"));
  should_equal (*((short int *) object->get_own_property (object, "programming")), value_b);
  object->set_own_property (object, "testing", &value_c);
  should_be_true (object->has_own_property (object, "testing"));
  should_equal (*((short int *) object->get_own_property (object, "testing")), value_c);
  object->set_own_property (object, "go", &value_d);
  should_be_true (object->has_own_property (object, "go"));
  should_equal (*((short int *) object->get_own_property (object, "go")), value_d);

  // Delete keys

  // Delete "computer"
  deleted = *(short int *) object->del_own_property (object, "computer");
  should_equal (deleted, value_a);
  should_be_false (object->has_own_property (object, "computer"));
  should_be_true (object->has_own_property (object, "programming"));
  should_be_true (object->has_own_property (object, "testing"));
  should_be_true (object->has_own_property (object, "go"));

  // Delete "programming"
  deleted = *(short int *) object->del_own_property (object, "programming");
  should_equal (deleted, value_b);
  should_be_false (object->has_own_property (object, "programming"));
  should_be_true (object->has_own_property (object, "testing"));
  should_be_true (object->has_own_property (object, "go"));

  // Delete "testing"
  deleted = *(short int *) object->del_own_property (object, "testing");
  should_equal (deleted, value_c);
  should_be_false (object->has_own_property (object, "testing"));
  should_be_true (object->has_own_property (object, "go"));

  // Delete "go"
  deleted = *(short int *) object->del_own_property (object, "go");
  should_equal (deleted, value_d);
  should_be_false (object->has_own_property (object, "go"));

  proto_del_object (object);
}

void
test_object_get_chain_calls ()
{
  proto_object_t *object_a, *object_b, *object_c;
  short int value = 10;

  describe ("Create three objects, assign keys for each object, in a chain, and then call it");
  object_a = proto_init_object ();
  object_b = proto_init_object ();
  object_c = proto_init_object ();
  object_a->set_own_property (object_a, "b", object_b);
  object_b->set_own_property (object_b, "c", object_c);
  object_c->set_own_property (object_c, "value", &value);
  should_be_true (object_a->has_own_property (object_a, "b"));
  should_be_true (object_b->has_own_property (object_b, "c"));
  should_be_true (object_c->has_own_property (object_c, "value"));
  should_equal (*(short int *) object_a->get_chain (object_a, "b.c.value"), value);
  should_equal (object_a->get_chain (object_a, "b.c"), (void *) object_c);
  should_equal (object_a->get_chain (object_a, "b"), (void *) object_b);
  should_equal (*(short int *) object_b->get_chain (object_b, "c.value"), value);
  should_equal (object_b->get_chain (object_b, "c"), (void *) object_c);
  should_equal (*(short int *) object_c->get_chain (object_c, "value"), value);
  proto_del_object (object_a);
  proto_del_object (object_b);
  proto_del_object (object_c);
}

void
test_object_set_chain_calls ()
{
  proto_object_t *object, *object_a, *object_b, *object_c;
  short int value = 10;

  describe ("Create object and assign keys in a chain and then call them");
  object = proto_init_object ();
  object->set_chain (object, "a.b.c.value", &value);
  should_be_true (object->has_own_property (object, "a"));
  object_a = object->get_own_property (object, "a");
  should_be_true (object_a->has_own_property (object_a, "b"));
  object_b = object_a->get_own_property (object_a, "b");
  should_be_true (object_b->has_own_property (object_b, "c"));
  object_c = object_b->get_own_property (object_b, "c");
  should_be_true (object_c->has_own_property (object_c, "value"));
  should_equal (*(short int *) object->get_chain (object, "a.b.c.value"), value);
  should_equal (*(short int *) object_a->get_chain (object_a, "b.c.value"), value);
  should_equal (*(short int *) object_b->get_chain (object_b, "c.value"), value);
  should_equal (*(short int *) object_c->get_chain (object_c, "value"), value);
  proto_del_object (object);
}

void
test_object_set_chain_multiple_calls ()
{
  proto_object_t *object, *object_a, *object_b, *object_c;
  short int value_a = 10, value_b = 20, value_c = 30;

  describe ("Create object and assign keys in a chain and then call them");
  object = proto_init_object ();
  object->set_chain (object, "a.b.c.value_a", &value_a);
  object->set_chain (object, "a.b.c.value_b", &value_b);
  object->set_chain (object, "a.b.value_c", &value_c);
  should_be_true (object->has_own_property (object, "a"));
  object_a = object->get_own_property (object, "a");
  should_be_true (object_a->has_own_property (object_a, "b"));
  object_b = object_a->get_own_property (object_a, "b");
  should_be_true (object_b->has_own_property (object_b, "c"));
  object_c = object_b->get_own_property (object_b, "c");
  should_be_true (object_c->has_own_property (object_c, "value_a"));
  should_equal (*(short int *) object->get_chain (object, "a.b.c.value_a"), value_a);
  should_equal (*(short int *) object_a->get_chain (object_a, "b.c.value_a"), value_a);
  should_equal (*(short int *) object_b->get_chain (object_b, "c.value_a"), value_a);
  should_equal (*(short int *) object_c->get_chain (object_c, "value_a"), value_a);
  should_be_true (object_c->has_own_property (object_c, "value_b"));
  should_equal (*(short int *) object->get_chain (object, "a.b.c.value_b"), value_b);
  should_equal (*(short int *) object_a->get_chain (object_a, "b.c.value_b"), value_b);
  should_equal (*(short int *) object_b->get_chain (object_b, "c.value_b"), value_b);
  should_equal (*(short int *) object_c->get_chain (object_c, "value_b"), value_b);
  should_equal (*(short int *) object->get_chain (object, "a.b.value_c"), value_c);
  should_equal (*(short int *) object_a->get_chain (object_a, "b.value_c"), value_c);
  should_equal (*(short int *) object_b->get_chain (object_b, "value_c"), value_c);
  proto_del_object (object);
}

void
test_object_set_chain_reassignments ()
{
  proto_object_t *object;
  short int value = 10;

  describe ("Create object and assign keys in a chain and then call them");
  object = proto_init_object ();
  object->set_chain (object, "a.b.c.value", &value);
  should_equal (*(short int *) object->get_chain (object, "a.b.c.value"), value);
  object->set_chain (object, "a", &value);
  should_equal (*(short int *) object->get_chain (object, "a"), value);
  proto_del_object (object);
}

static void *
mock_function (void *arguments)
{
  short int value = *(short int *) arguments;
  short int *sum = malloc (sizeof (short int));
  *sum = value + 10;
  return sum;
}

void
test_object_execute_function ()
{
  proto_object_t *object;
  short int value = 10, *sum;

  describe ("Create objects, assign a function to a key and then execute it");
  object = proto_init_object ();
  object->set_own_property (object, "function", &mock_function);
  should_equal (object->get_own_property (object, "function"), &mock_function);
  sum = (short int *) object->execute_property (object, "function", &value);
  should_equal (*sum, value + 10);
  free (sum);
  proto_del_object (object);
}

void
test_object_merge ()
{
  proto_object_t *object_a, *object_b;
  short int value_a = 10, value_b = 20, value_c = 30, value_d = 40;

  describe ("Create two objects, assign some keys and then merge them");
  object_a = proto_init_object ();
  object_b = proto_init_object ();

  object_a->set_own_property (object_a, "d", &value_d);
  object_b->set_own_property (object_b, "a", &value_a);
  object_b->set_own_property (object_b, "b", &value_b);
  object_b->set_own_property (object_b, "c", &value_c);
  should_be_true (object_a->has_own_property (object_a, "d"));
  should_be_false (object_a->has_own_property (object_a, "a"));
  should_be_false (object_a->has_own_property (object_a, "b"));
  should_be_false (object_a->has_own_property (object_a, "c"));
  should_be_true (object_b->has_own_property (object_b, "a"));
  should_be_true (object_b->has_own_property (object_b, "b"));
  should_be_true (object_b->has_own_property (object_b, "c"));
  object_a->merge (object_a, object_b);
  should_be_true (object_a->has_own_property (object_a, "a"));
  should_be_true (object_a->has_own_property (object_a, "b"));
  should_be_true (object_a->has_own_property (object_a, "c"));
  should_be_true (object_a->has_own_property (object_a, "d"));
  should_be_true (object_b->has_own_property (object_b, "a"));
  should_be_true (object_b->has_own_property (object_b, "b"));
  should_be_true (object_b->has_own_property (object_b, "c"));
  should_be_false (object_b->has_own_property (object_b, "d"));

  proto_del_object (object_a);
  proto_del_object (object_b);
}

void
run_tests ()
{
  test_object_creation ();
  test_object_reassignment_of_key ();
  test_object_with_pointer ();
  test_object_with_multiple_keys ();
  test_object_with_colliding_keys ();
  test_object_deletion_of_key ();
  test_object_get_chain_calls ();
  test_object_set_chain_calls ();
  test_object_set_chain_multiple_calls ();
  test_object_set_chain_reassignments ();
  test_object_execute_function ();
  test_object_merge ();
}
