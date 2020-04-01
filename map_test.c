#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "map.h"
#include "test.h"

typedef struct {
    char *msg;
    int count;
} Test;

void test_different_types()
{
    Map *map = map_new(5);

    TEST_EQ(map_size(map), 0);

    /* Test string */

    map_set(map, "Bugs", "Bunny");
    TEST_EQ_STR(map_get(map, "Bugs"), "Bunny");

    TEST_EQ(map_size(map), 1);

    map_set(map, "Bugs Bunny", "bugs bunny");
    TEST_EQ_STR(map_get(map, "Bugs Bunny"), "bugs bunny");

    TEST_EQ(map_size(map), 2);

    /* Test int */

    int *year = calloc(1, sizeof(int));
    *year = 1940;
    map_set(map, "year", year);

    int *check_year = map_get(map, "year");

    TEST_EQ(*check_year, *year);

    TEST_EQ(map_size(map), 3);

    /* Test structure */

    Test *test = calloc(1, sizeof(Test));
    test->count = 42;
    test->msg = strdup("Bugs Bunny");

    map_set(map, "bugs_test", test);

    Test *check_test = map_get(map, "bugs_test");

    TEST_EQ(check_test->count, test->count);
    TEST_EQ_STR(check_test->msg, test->msg);

    TEST_EQ(map_size(map), 4);

    map_free(map);

    TEST_EQ(*year, 1940);
    TEST_EQ(*check_year, 1940);

    TEST_EQ(check_test->count, 42);
    TEST_EQ(test->count, 42);
    TEST_EQ_STR(check_test->msg, "Bugs Bunny");
    TEST_EQ_STR(test->msg, "Bugs Bunny");

    free(test->msg);
    free(test);
    free(year);
}

void test_get()
{
    Map *map = map_new(4);
    char *val = map_get(map, "Bugs Bunny");

    TEST_NULL(val);

    TEST_EQ(map_in(map, "Bugs Bunny"), 0);

    map_set(map, "Bugs Bunny", "Bugs Bunny");

    TEST_EQ(map_in(map, "Bugs Bunny"), 1);

    map_free(map);
}

void test_del()
{
    Map *map = map_new(8);

    TEST_EQ(map_size(map), 0);

    /* Test string */

    map_set(map, "Bugs", "Bunny");

    TEST_EQ(map_size(map), 1);

    map_del(map, "Bugs");

    TEST_EQ(map_size(map), 0);

    /* Check items that do not exist */
    map_del(map, "Bugs");

    TEST_EQ(map_size(map), 0);

    map_del(map, "Bunny");

    TEST_EQ(map_size(map), 0);

    /* Test structure */

    Test *test = calloc(1, sizeof(Test));
    test->count = 42;
    test->msg = strdup("Bugs Bunny");

    map_set(map, "Bugs", test);

    TEST_EQ(map_size(map), 1);

    Test *check_test = map_get(map, "Bugs");

    TEST_EQ(check_test->count, test->count);
    TEST_EQ_STR(check_test->msg, test->msg);

    map_del(map, "Bugs");

    TEST_EQ(map_size(map), 0);

    free(test->msg);
    free(test);
    map_free(map);
}

void test_auto_resize()
{
    Map *map = map_new(12);

    TEST_EQ(map_size(map), 0);

    char tmp[100];

    int items = 15000;
    char **strings = calloc(items, sizeof(char*));

    for (int i = 0; i < items; i++) {
        strings[i] = calloc(100, sizeof(char));
    }

    for (int i = 0; i < items; i++) {
        snprintf(strings[i], 100, "Testy McTest %d", i);

        map_set(map, strings[i], strings[i]);
    }

    TEST_EQ(map_size(map), items);

    for (int i = 0; i < items; i++) {
        snprintf(tmp, sizeof(tmp), "Testy McTest %d", i);

        char *value = map_get(map, tmp);

        TEST_EQ_STR(value, tmp);
    }

    for (int i = 0; i < items; i++) {
        free(strings[i]);
    }

    free(strings);
    map_free(map);
}

int main(int argc, char *argv[])
{
    test_different_types();
    test_get();
    test_del();
    test_auto_resize();
}
