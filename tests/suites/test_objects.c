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
  int value = 10;

  describe ("Create and destroy object");
  object = proto_init_object ();
  should_be_true (object != NULL);
  object->set_own_property (object, "testing", &value);
  should_be_true (object->has_own_property (object, "testing"));
  should_be_false (object->has_own_property (object, "another_key"));
  should_equal (*((int *) object->get_own_property (object, "testing")), value);
  should_equal (object->get_own_property (object, "another_key"), NULL);
  proto_del_object (object);
}

void
test_object_reassignment_of_key ()
{
  proto_object_t *object;
  int value_a = 10, value_b = 20;

  describe ("Create object and reassign a value to the same key");
  object = proto_init_object ();
  should_be_true (object != NULL);
  object->set_own_property (object, "testing", &value_a);
  should_be_true (object->has_own_property (object, "testing"));
  should_be_false (object->has_own_property (object, "another_key"));
  should_equal (*((int *) object->get_own_property (object, "testing")), value_a);
  should_equal (object->get_own_property (object, "another_key"), NULL);
  object->set_own_property (object, "testing", &value_b);
  should_equal (*((int *) object->get_own_property (object, "testing")), value_b);
  proto_del_object (object);
}

void
test_object_with_pointer ()
{
  proto_object_t *object;
  int *pointer, *deleted;

  describe ("Create object and assign a key to a pointer");
  object = proto_init_object ();
  should_be_true (object != NULL);
  pointer = (int *) malloc (sizeof (int));
  *pointer = 200;
  object->set_own_property (object, "pointer", pointer);
  should_be_true (object->has_own_property (object, "pointer"));
  should_equal ((int *) object->get_own_property (object, "pointer"), pointer);
  should_equal (*(int *) object->get_own_property (object, "pointer"), *pointer);
  deleted = (int *) object->del_own_property (object, "pointer");
  free (deleted);
  proto_del_object (object);
}

void
test_object_with_multiple_keys ()
{
  proto_object_t *object;
  int value_a = 10, value_b = 20, value_c = 30;

  describe ("Create object and assign multiple keys");
  object = proto_init_object ();
  should_be_true (object != NULL);
  object->set_own_property (object, "a", &value_a);
  should_be_true (object->has_own_property (object, "a"));
  should_equal (*((int *) object->get_own_property (object, "a")), value_a);
  object->set_own_property (object, "b", &value_b);
  should_be_true (object->has_own_property (object, "b"));
  should_equal (*((int *) object->get_own_property (object, "b")), value_b);
  object->set_own_property (object, "c", &value_c);
  should_be_true (object->has_own_property (object, "c"));
  should_equal (*((int *) object->get_own_property (object, "c")), value_c);
  proto_del_object (object);
}

void
test_object_with_colliding_keys ()
{
  proto_object_t *object;
  int value_a = 10, value_b = 20, value_c = 30, value_d = 40;

  describe ("Create object and assign colliding keys");
  object = proto_init_object ();
  should_be_true (object != NULL);
  object->set_own_property (object, "computer", &value_a);
  should_be_true (object->has_own_property (object, "computer"));
  should_equal (*((int *) object->get_own_property (object, "computer")), value_a);
  object->set_own_property (object, "programming", &value_b);
  should_be_true (object->has_own_property (object, "programming"));
  should_equal (*((int *) object->get_own_property (object, "programming")), value_b);
  object->set_own_property (object, "testing", &value_c);
  should_be_true (object->has_own_property (object, "testing"));
  should_equal (*((int *) object->get_own_property (object, "testing")), value_c);
  object->set_own_property (object, "go", &value_d);
  should_be_true (object->has_own_property (object, "go"));
  should_equal (*((int *) object->get_own_property (object, "go")), value_d);
  proto_del_object (object);
}

void
test_object_deletion_of_key ()
{
  proto_object_t *object;
  int value_a = 10, value_b = 20, value_c = 30, value_d = 40, deleted;

  describe ("Create object, assign keys and delete them");
  object = proto_init_object ();
  should_be_true (object != NULL);
  object->set_own_property (object, "computer", &value_a);
  should_be_true (object->has_own_property (object, "computer"));
  should_equal (*((int *) object->get_own_property (object, "computer")), value_a);
  object->set_own_property (object, "programming", &value_b);
  should_be_true (object->has_own_property (object, "programming"));
  should_equal (*((int *) object->get_own_property (object, "programming")), value_b);
  object->set_own_property (object, "testing", &value_c);
  should_be_true (object->has_own_property (object, "testing"));
  should_equal (*((int *) object->get_own_property (object, "testing")), value_c);
  object->set_own_property (object, "go", &value_d);
  should_be_true (object->has_own_property (object, "go"));
  should_equal (*((int *) object->get_own_property (object, "go")), value_d);

  // Delete keys

  // Delete "computer"
  deleted = *(int *) object->del_own_property (object, "computer");
  should_equal (deleted, value_a);
  should_be_false (object->has_own_property (object, "computer"));
  should_be_true (object->has_own_property (object, "programming"));
  should_be_true (object->has_own_property (object, "testing"));
  should_be_true (object->has_own_property (object, "go"));

  // Delete "programming"
  deleted = *(int *) object->del_own_property (object, "programming");
  should_equal (deleted, value_b);
  should_be_false (object->has_own_property (object, "programming"));
  should_be_true (object->has_own_property (object, "testing"));
  should_be_true (object->has_own_property (object, "go"));

  // Delete "testing"
  deleted = *(int *) object->del_own_property (object, "testing");
  should_equal (deleted, value_c);
  should_be_false (object->has_own_property (object, "testing"));
  should_be_true (object->has_own_property (object, "go"));

  // Delete "go"
  deleted = *(int *) object->del_own_property (object, "go");
  should_equal (deleted, value_d);
  should_be_false (object->has_own_property (object, "go"));

  proto_del_object (object);
}

void
test_object_chain_calls ()
{
  proto_object_t *object_a, *object_b, *object_c;
  int value = 10;

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
  should_equal (*(int *) object_a->chain (object_a, "b.c.value"), value);
  should_equal (object_a->chain (object_a, "b.c"), (void *) object_c);
  should_equal (object_a->chain (object_a, "b"), (void *) object_b);
  should_equal (*(int *) object_b->chain (object_b, "c.value"), value);
  should_equal (object_b->chain (object_b, "c"), (void *) object_c);
  should_equal (*(int *) object_c->chain (object_c, "value"), value);
  proto_del_object (object_a);
  proto_del_object (object_b);
  proto_del_object (object_c);
}

static void *
mock_function (void *arguments)
{
  int value = *(int *) arguments;
  int *sum = malloc (sizeof (int));
  *sum = value + 10;
  return sum;
}

void
test_object_execute_function ()
{
  proto_object_t *object;
  int value = 10, *sum;

  describe ("Create objects, assign a function to a key and then execute it");
  object = proto_init_object ();
  object->set_own_property (object, "function", &mock_function);
  should_equal (object->get_own_property (object, "function"), &mock_function);
  sum = (int *) object->execute_property (object, "function", &value);
  should_equal (*sum, value + 10);
  free (sum);
  proto_del_object (object);
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
  test_object_chain_calls ();
  test_object_execute_function ();
}
