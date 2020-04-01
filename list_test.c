#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"
#include "test.h"

typedef struct {
  int x;
} Test;

void test_adding_strings(void) {
  List *l = list_new(4);
  TEST_EQ(list_size(l), 0);

  list_append(l, "test");
  TEST_EQ(list_size(l), 1);
  TEST_EQ_STR(list_get(l, 0), "test");

  list_append(l, "hello");
  TEST_EQ(list_size(l), 2);

  list_free(l);
}

void test_list_in(void) {
  List *l = list_new(3);

  char *s2 = "test2";
  char *s2_ = "test2";

  list_append(l, "test1");
  list_append(l, s2);

  TEST_EQ(list_in(l, "test1"), 1);
  TEST_EQ(list_in(l, s2_), 1);
  TEST_EQ(list_in(l, "test3"), 0);

  list_free(l);
}

void test_resize(void) {
  List *l = list_new(2);

  list_append(l, "1");
  list_append(l, "2");

  TEST_EQ(list_size(l), 2);
  TEST_EQ(l->cap, 2);

  list_append(l, "3");
  TEST_EQ(list_size(l), 3);
  TEST_EQ(l->cap, 4);

  list_free(l);
}

void test_del(void) {
  List *l = list_new(4);
  TEST_EQ(l->cap, 4);

  list_append(l, "1");
  list_append(l, "2");
  list_append(l, "3");
  list_append(l, "4");

  TEST_EQ(list_size(l), 4);
  TEST_EQ(l->cap, 8);

  // Remove second element
  list_del(l, 1);

  TEST_EQ(list_size(l), 3);
  TEST_EQ(l->cap, 8);

  TEST_EQ_STR(list_get(l, 0), "1");
  TEST_EQ_STR(list_get(l, 1), "3");
  TEST_EQ_STR(list_get(l, 2), "4");
  TEST_EQ(list_get(l, 3), NULL);

  // Remove first element
  list_del(l, 0);
  TEST_EQ_STR(list_get(l, 0), "3");
  TEST_EQ_STR(list_get(l, 1), "4");
  TEST_EQ(list_get(l, 2), NULL);
  TEST_EQ(list_get(l, 3), NULL);

  // Remove last element
  list_del(l, 1);
  TEST_EQ_STR(list_get(l, 0), "3");
  TEST_EQ(list_get(l, 1), NULL);
  TEST_EQ(list_get(l, 2), NULL);
  TEST_EQ(list_get(l, 3), NULL);

  list_free(l);
}

void test_struct(void) {
  List *l = list_new(4);
  Test *t = calloc(1, sizeof(Test));
  t->x = 5;

  list_append(l, t);
  TEST_EQ(list_size(l), 1);
  TEST_EQ(list_get(l, 0), t);

  free(t);
  list_free(l);
}

int main(int argc, char *argv[])
{
    test_adding_strings();
    test_list_in();
    test_resize();
    test_del();
    test_struct();
}
