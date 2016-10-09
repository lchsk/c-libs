#include <stdio.h>
#include <stdlib.h>

#include "map.h"

/* Todo
- in, length

*/

map_t *map_new() {
    map_t *map = calloc(1, sizeof(map_t));

    map->keys = calloc(XS_INITIAL_MAP_SIZE, sizeof(void *));
    map->values = calloc(XS_INITIAL_MAP_SIZE, sizeof(void *));
    map->size = XS_INITIAL_MAP_SIZE;
    map->len = 0;

    return map;
}

int map_index(map_t *map, void *key, void **keys) {
    int i = (int) key % map->size;

    /* i = 0; */

    printf("Initial i: %d\n", i);

    while (keys[i] && keys[i] != key)
        i = (i + 1) % map->size;

    printf("Actual i: %d\n", i);

    return i;
}

void map_put(map_t *map, void *key, void *value) {
    printf("map  size: %d, len: %d\n", map->size, map->len);

    if (3.0 / 2.0 * map->len >= map->size) {

        printf("Resizing...\n");
        map->size = map->size * 2;

        void** keys2 = calloc(map->size * 2, sizeof(void *));
        void** values2 = calloc(map->size * 2, sizeof(void *));

        for (int i = 0; i < map->size / 2; i++) {

            printf("before cp, ind: %d\n", i);
            char *key2 = map->keys[i];
            char *value2 = map->values[i];

            printf("cp %s=%s\n", key2, value2);
            int index = map_index(map, key2, keys2);
            keys2[index] = key2;
            values2[index] = value2;
        }

        free(map->keys);
        free(map->values);

        map->keys = keys2;
        map->values = values2;
    }
    
    int i = map_index(map, key, map->keys);

    printf("currently at %d = %s\n", i,  map->keys[i]);

    printf("adding: %s=%s at %d\n", key, value, i);

    map->keys[i] = key;
    map->values[i] = value;
    map->len++;
}

void *map_get(map_t *map, void *key) {
    int i = map_index(map, key, map->keys);

    return map->values[i];
}

void map_free(map_t *map) {
    free(map->keys);
    free(map->values);

    free(map);
}
