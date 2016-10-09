#include <criterion/criterion.h>

#include "../map.h"

Test(xs_map, map)
{
    map_t *map = map_new(10);

    map_put(map, "Bugs", "Bunny");

    cr_assert_str_eq(map_get(map, "Bugs"),  "Bunny");

    map_free(map);
}
