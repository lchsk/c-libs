#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "map.h"

static unsigned long hash(unsigned char *str);
static int map_index(map_t *map, char *key, char **keys);
static void resize(map_t *map);

map_t *map_new()
{
    map_t *map = calloc(1, sizeof(map_t));

    map->keys = calloc(XS_INITIAL_MAP_SIZE, sizeof(char *));
    map->values = calloc(XS_INITIAL_MAP_SIZE, sizeof(void *));
    map->size = XS_INITIAL_MAP_SIZE;
    map->len = 0;

    return map;
}

void map_put(map_t *map, char *key, void *value)
{
    resize(map);

    int i = map_index(map, key, map->keys);

    map->keys[i] = key;
    map->values[i] = value;
    map->len++;
}

void map_del(map_t *map, char *key)
{
    int i = map_index(map, key, map->keys);

    map->values[i] = NULL;
    map->keys[i] = NULL;
    map->len--;
}

void *map_get(map_t *map, char *key)
{
    int i = map_index(map, key, map->keys);

    return map->values[i];
}

unsigned map_len(map_t *map)
{
    return map->len;
}

unsigned map_in(map_t *map, char *key)
{
    return map_get(map, key) ? 1 : 0;
}

void map_free(map_t *map)
{
    free(map->keys);
    free(map->values);

    free(map);
}

/* djb2 (Bernstein) */
static unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

static int map_index(map_t *map, char *key, char **keys)
{
    int i = hash(key) % map->size;

    while (keys[i] && strcmp(keys[i], key) != 0)
        i = (i + 1) % map->size;

    return i;
}

static void resize(map_t *map)
{
    if (map->len >= map->size * XS_MAP_RESIZE_FACTOR) {
        map->size = map->size * 2;

        char **keys = calloc(map->size, sizeof(char *));
        void **values = calloc(map->size, sizeof(void *));

        for (int i = 0; i < map->size / 2; i++) {
            char *key = map->keys[i];
            void *value = map->values[i];

            if (key && value) {
                int index = map_index(map, key, keys);

                keys[index] = key;
                values[index] = value;
            }
        }

        free(map->keys);
        free(map->values);

        map->keys = keys;
        map->values = values;
    }
}
