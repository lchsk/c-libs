#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "map.h"

typedef struct {
    char *msg;
    int count;
} Test;

#define eq(val1, val2) assert(val1 == val2)
#define null(val) assert(val == NULL)
#define str_eq(str1, str2) assert(strcmp(str1, str2) == 0)

void test_different_types()
{
    Map *map = map_new(5);

    eq(map_len(map), 0);

    /* Test string */

    map_set(map, "Bugs", "Bunny");
    str_eq(map_get(map, "Bugs"), "Bunny");

    eq(map_len(map), 1);

    map_set(map, "Bugs Bunny", "bugs bunny");
    str_eq(map_get(map, "Bugs Bunny"), "bugs bunny");

    eq(map_len(map), 2);

    /* Test int */

    int *year = malloc(sizeof(int));
    *year = 1940;
    map_set(map, "year", year);

    int *check_year = map_get(map, "year");

    eq(*check_year, *year);

    eq(map_len(map), 3);

    /* Test structure */

    Test *test = malloc(sizeof(test));
    test->count = 42;
    test->msg = strdup("Bugs Bunny");

    map_set(map, "bugs_test", test);

    Test *check_test = map_get(map, "bugs_test");

    eq(check_test->count, test->count);
    str_eq(check_test->msg, test->msg);

    eq(map_len(map), 4);

    map_free(map);

    eq(*year, 1940);
    eq(*check_year, 1940);

    eq(check_test->count, 42);
    eq(test->count, 42);
    str_eq(check_test->msg, "Bugs Bunny");
    str_eq(test->msg, "Bugs Bunny");
}

void test_get()
{
    Map *map = map_new(4);

    char *val = map_get(map, "Bugs Bunny");

    null(val);

    eq(map_in(map, "Bugs Bunny"), 0);

    map_set(map, "Bugs Bunny", "Bugs Bunny");

    eq(map_in(map, "Bugs Bunny"), 1);

    map_free(map);
}

void test_del()
{
    Map *map = map_new(8);

    eq(map_len(map), 0);

    /* Test string */

    map_set(map, "Bugs", "Bunny");

    eq(map_len(map), 1);

    map_del(map, "Bugs");

    eq(map_len(map), 0);

    /* Check items that do not exist */
    map_del(map, "Bugs");

    eq(map_len(map), 0);

    map_del(map, "Bunny");

    eq(map_len(map), 0);

    /* Test structure */

    Test *test = malloc(sizeof(test));
    test->count = 42;
    test->msg = strdup("Bugs Bunny");

    map_set(map, "Bugs", test);

    eq(map_len(map), 1);

    Test *check_test = map_get(map, "Bugs");

    eq(check_test->count, test->count);
    str_eq(check_test->msg, test->msg);

    map_del(map, "Bugs");

    eq(map_len(map), 0);

    free(test);
    map_free(map);
}

void test_auto_resize()
{
    Map *map = map_new(12);

    eq(map_len(map), 0);

    char tmp[100];

    int items = 15000;
    char **strings = malloc(items * sizeof(char*));

    for (int i = 0; i < items; i++) {
        strings[i] = malloc(100);
    }

    for (int i = 0; i < items; i++) {
        snprintf(strings[i], 1000, "Testy McTest %d", i);

        map_set(map, strings[i], strings[i]);
    }

    eq(map_len(map), items);

    for (int i = 0; i < items; i++) {
        snprintf(tmp, sizeof(tmp), "Testy McTest %d", i);

        char *value = map_get(map, tmp);

        str_eq(value, tmp);
    }

    map_free(map);
}

int main(int argc, char *argv[])
{
    test_different_types();
    test_get();
    test_del();
    test_auto_resize();
}
