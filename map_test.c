#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "map.h"

typedef struct {
    char *msg;
    int count;
} test_t;

#define xs_eq(val1, val2) assert(val1 == val2)
#define xs_null(val) assert(val == NULL)
#define xs_str_eq(str1, str2) assert(strcmp(str1, str2) == 0)

void test_different_types()
{
    map_t *map = map_new();

    xs_eq(map_len(map), 0);

    /* Test string */

    map_put(map, "Bugs", "Bunny");
    xs_str_eq(map_get(map, "Bugs"), "Bunny");

    xs_eq(map_len(map), 1);

    map_put(map, "Bugs Bunny", "bugs bunny");
    xs_str_eq(map_get(map, "Bugs Bunny"), "bugs bunny");

    xs_eq(map_len(map), 2);

    /* Test int */

    int *year = malloc(sizeof(int));
    *year = 1940;
    map_put(map, "year", year);

    int *check_year = map_get(map, "year");

    xs_eq(*check_year, *year);

    xs_eq(map_len(map), 3);

    /* Test structure */

    test_t *test = malloc(sizeof(test_t));
    test->count = 42;
    test->msg = strdup("Bugs Bunny");

    map_put(map, "bugs_test", test);

    test_t *check_test = map_get(map, "bugs_test");

    xs_eq(check_test->count, test->count);
    xs_str_eq(check_test->msg, test->msg);

    xs_eq(map_len(map), 4);

    map_free(map);

    xs_eq(*year, 1940);
    xs_eq(*check_year, 1940);

    xs_eq(check_test->count, 42);
    xs_eq(test->count, 42);
    xs_str_eq(check_test->msg, "Bugs Bunny");
    xs_str_eq(test->msg, "Bugs Bunny");
}

void test_get()
{
    map_t *map = map_new();

    char *val = map_get(map, "Bugs Bunny");

    xs_null(val);

    xs_eq(map_in(map, "Bugs Bunny"), 0);

    map_put(map, "Bugs Bunny", "Bugs Bunny");

    xs_eq(map_in(map, "Bugs Bunny"), 1);

    map_free(map);
}

void test_del()
{
    map_t *map = map_new();

    xs_eq(map_len(map), 0);

    /* Test string */

    map_put(map, "Bugs", "Bunny");

    xs_eq(map_len(map), 1);

    map_del(map, "Bugs");

    xs_eq(map_len(map), 0);

    /* Check items that do not exist */
    map_del(map, "Bugs");

    xs_eq(map_len(map), 0);

    map_del(map, "Bunny");

    xs_eq(map_len(map), 0);

    /* Test structure */

    test_t *test = malloc(sizeof(test_t));
    test->count = 42;
    test->msg = strdup("Bugs Bunny");

    map_put(map, "Bugs", test);

    xs_eq(map_len(map), 1);

    test_t *check_test = map_get(map, "Bugs");

    xs_eq(check_test->count, test->count);
    xs_str_eq(check_test->msg, test->msg);

    map_del(map, "Bugs");

    xs_eq(map_len(map), 0);

    free(test);
    map_free(map);
}

void test_auto_resize()
{
    map_t *map = map_new();

    xs_eq(map_len(map), 0);

    char tmp[100];

    int items = 15000;
    char **strings = malloc(items * sizeof(char*));

    for (int i = 0; i < items; i++) {
        strings[i] = malloc(100);
    }

    for (int i = 0; i < items; i++) {
        snprintf(strings[i], 1000, "Testy McTest %d", i);

        map_put(map, strings[i], strings[i]);
    }

    xs_eq(map_len(map), items);

    for (int i = 0; i < items; i++) {
        snprintf(tmp, sizeof(tmp), "Testy McTest %d", i);

        char *value = map_get(map, tmp);

        xs_str_eq(value, tmp);
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
