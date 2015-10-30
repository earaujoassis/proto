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
  should_equal (*(int *) object->get_own_property (object, "pointer"), 200);
  deleted = (int *) object->del_own_property (object, "pointer");
  free (deleted);
  proto_del_object (object);
}

void
test_object_with_multiple_keys ()
{
  proto_object_t *object;
  int value_a = 10, value_b = 20, value_c = 30;

  describe ("Create object and assign keys");
  object = proto_init_object ();
  should_be_true (object != NULL);
  object->set_own_property (object, "a", &value_a);
  should_be_true (object->has_own_property (object, "a"));
  should_equal (*((int *) object->get_own_property (object, "a")), 10);
  object->set_own_property (object, "b", &value_b);
  should_be_true (object->has_own_property (object, "b"));
  should_equal (*((int *) object->get_own_property (object, "b")), 20);
  object->set_own_property (object, "c", &value_c);
  should_be_true (object->has_own_property (object, "c"));
  should_equal (*((int *) object->get_own_property (object, "c")), 30);
  proto_del_object (object);
}

void
test_object_with_colliding_keys ()
{
  proto_object_t *object;
  int value_a = 10, value_b = 20, value_c = 30, value_d = 40;

  describe ("Create object and assign keys");
  object = proto_init_object ();
  should_be_true (object != NULL);
  object->set_own_property (object, "computer", &value_a);
  should_be_true (object->has_own_property (object, "computer"));
  should_equal (*((int *) object->get_own_property (object, "computer")), 10);
  object->set_own_property (object, "programming", &value_b);
  should_be_true (object->has_own_property (object, "programming"));
  should_equal (*((int *) object->get_own_property (object, "programming")), 20);
  object->set_own_property (object, "testing", &value_c);
  should_be_true (object->has_own_property (object, "testing"));
  should_equal (*((int *) object->get_own_property (object, "testing")), 30);
  object->set_own_property (object, "go", &value_d);
  should_be_true (object->has_own_property (object, "go"));
  should_equal (*((int *) object->get_own_property (object, "go")), 40);
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
  should_equal (*((int *) object->get_own_property (object, "computer")), 10);
  object->set_own_property (object, "programming", &value_b);
  should_be_true (object->has_own_property (object, "programming"));
  should_equal (*((int *) object->get_own_property (object, "programming")), 20);
  object->set_own_property (object, "testing", &value_c);
  should_be_true (object->has_own_property (object, "testing"));
  should_equal (*((int *) object->get_own_property (object, "testing")), 30);
  object->set_own_property (object, "go", &value_d);
  should_be_true (object->has_own_property (object, "go"));
  should_equal (*((int *) object->get_own_property (object, "go")), 40);

  // Delete keys

  // Delete "computer"
  deleted = *(int *) object->del_own_property (object, "computer");
  should_equal (deleted, 10);
  should_be_false (object->has_own_property (object, "computer"));
  should_be_true (object->has_own_property (object, "programming"));
  should_be_true (object->has_own_property (object, "testing"));
  should_be_true (object->has_own_property (object, "go"));

  // Delete "programming"
  deleted = *(int *) object->del_own_property (object, "programming");
  should_equal (deleted, 20);
  should_be_false (object->has_own_property (object, "programming"));
  should_be_true (object->has_own_property (object, "testing"));
  should_be_true (object->has_own_property (object, "go"));

  // Delete "testing"
  deleted = *(int *) object->del_own_property (object, "testing");
  should_equal (deleted, 30);
  should_be_false (object->has_own_property (object, "testing"));
  should_be_true (object->has_own_property (object, "go"));

  // Delete "go"
  deleted = *(int *) object->del_own_property (object, "go");
  should_equal (deleted, 40);
  should_be_false (object->has_own_property (object, "go"));

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
}
