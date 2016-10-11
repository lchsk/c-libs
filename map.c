#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "map.h"

/* Todo
- in, length, remove

*/

/* djb2 (Bernstein) */
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

map_t *map_new() {
    map_t *map = calloc(1, sizeof(map_t));

    map->keys = calloc(XS_INITIAL_MAP_SIZE, sizeof(char *));
    map->values = calloc(XS_INITIAL_MAP_SIZE, sizeof(void *));
    map->size = XS_INITIAL_MAP_SIZE;
    map->len = 0;

    return map;
}

int map_index(map_t *map, char *key, char **keys) {
    int i = hash(key) % map->size;

    while (keys[i] && strcmp(keys[i], key) != 0)
        i = (i + 1) % map->size;

    return i;
}

void map_put(map_t *map, char *key, void *value) {

    if (3.0 / 2.0 * map->len >= map->size) {

        map->size = map->size * 2;

        char **keys2 = calloc(map->size * 2, sizeof(char *));
        void **values2 = calloc(map->size * 2, sizeof(void *));

        for (int i = 0; i < map->size / 2; i++) {

            char *key2 = map->keys[i];
            void *value2 = map->values[i];

            if (key2 && value2) {
                int index = map_index(map, key2, keys2);

                keys2[index] = key2;
                values2[index] = value2;
            }
        }

        free(map->keys);
        free(map->values);

        map->keys = keys2;
        map->values = values2;
    }
    
    int i = map_index(map, key, map->keys);

    map->keys[i] = key;
    map->values[i] = value;
    map->len++;
}

void *map_get(map_t *map, char *key) {
    int i = map_index(map, key, map->keys);

    return map->values[i];
}

unsigned map_len(map_t *map)
{
    return map->len;
}

void map_free(map_t *map) {
    free(map->keys);
    free(map->values);

    free(map);
}
