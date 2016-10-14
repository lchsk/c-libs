#include <stdio.h>

#include <criterion/criterion.h>

#include "../map.h"

typedef struct {
    char *msg;
    int count;
} test_t;

Test(xs_map, different_types)
{
    map_t *map = map_new();

    cr_assert_eq(map_len(map), 0);

    /* Test string */

    map_put(map, "Bugs", "Bunny");
    cr_assert_str_eq(map_get(map, "Bugs"), "Bunny");

    cr_assert_eq(map_len(map), 1);

    map_put(map, "Bugs Bunny", "bugs bunny");
    cr_assert_str_eq(map_get(map, "Bugs Bunny"), "bugs bunny");

    cr_assert_eq(map_len(map), 2);

    /* Test int */

    int *year = malloc(sizeof(int));
    *year = 1940;
    map_put(map, "year", year);

    int *check_year = map_get(map, "year");

    cr_assert_eq(*check_year, *year);

    cr_assert_eq(map_len(map), 3);

    /* Test structure */

    test_t *test = malloc(sizeof(test_t));
    test->count = 42;
    test->msg = strdup("Bugs Bunny");

    map_put(map, "bugs_test", test);

    test_t *check_test = map_get(map, "bugs_test");

    cr_assert_eq(check_test->count, test->count);
    cr_assert_str_eq(check_test->msg, test->msg);

    cr_assert_eq(map_len(map), 4);

    map_free(map);

    cr_assert_eq(*year, 1940);
    cr_assert_eq(*check_year, 1940);

    cr_assert_eq(check_test->count, 42);
    cr_assert_eq(test->count, 42);
    cr_assert_str_eq(check_test->msg, "Bugs Bunny");
    cr_assert_str_eq(test->msg, "Bugs Bunny");
}

Test(xs_map, get)
{
    map_t *map = map_new();

    char *val = map_get(map, "Bugs Bunny");

    cr_assert_null(val);

    cr_assert_eq(map_in(map, "Bugs Bunny"), 0);

    map_put(map, "Bugs Bunny", "Bugs Bunny");

    cr_assert_eq(map_in(map, "Bugs Bunny"), 1);

    map_free(map);
}

Test(xs_map, del)
{
    map_t *map = map_new();

    cr_assert_eq(map_len(map), 0);

    map_put(map, "Bugs", "Bunny");

    cr_assert_eq(map_len(map), 1);

    map_del(map, "Bugs");

    cr_assert_eq(map_len(map), 0);

    map_free(map);
}

Test(xs_map, auto_resize)
{
    map_t *map = map_new();

    cr_assert_eq(map_len(map), 0);

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

    cr_assert_eq(map_len(map), items);

    for (int i = 0; i < items; i++) {
        snprintf(tmp, sizeof(tmp), "Testy McTest %d", i);

        char *value = map_get(map, tmp);

        cr_assert_str_eq(value, tmp);
    }

    map_free(map);
}
