#include <stdlib.h>
#include <assert.h>

#include "map.h"

static unsigned long hash(unsigned char const *str);
static const int map_index(Map *map, char *key, char **keys);
static void resize(Map *map);

// How full the map must be in order to trigger resize
static const double MAP_RESIZE_TRIGGER = 0.6;

// By what factor we're enlarging the map
static const int MAP_RESIZE_FACTOR = 2;

int _strcmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }

    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

Map *map_new(int initial_size)
{
    Map *map = malloc(sizeof(map));

    map->keys = malloc(initial_size * sizeof(char *));
    map->values = malloc(initial_size * sizeof(void *));
    map->size = initial_size;
    map->len = 0;

    return map;
}

void map_free(Map *map)
{
    if (!map) {
        return;
    }

    if (map->keys) {
        free(map->keys);
    }

    if (map->values) {
        free(map->values);
    }

    free(map);
}

void map_set(Map *map, char *key, void *value)
{
    assert(map != NULL);

    resize(map);

    const int i = map_index(map, key, map->keys);

    map->keys[i] = key;
    map->values[i] = value;
    map->len++;
}

void map_del(Map *map, char *key)
{
    assert(map != NULL);

    const int i = map_index(map, key, map->keys);

    if (map->values[i] && map->keys[i]) {
        map->values[i] = NULL;
        map->keys[i] = NULL;
        map->len--;
    }
}

void *map_get(Map *map, char *key)
{
    assert(map != NULL);

    const int i = map_index(map, key, map->keys);

    return map->values[i];
}

const int map_len(Map *map)
{
    assert(map != NULL);

    return map->len;
}

const int map_in(Map *map, char *key)
{
    assert(map != NULL);

    return map_get(map, key) ? 1 : 0;
}

/* djb2 (Bernstein) */
static unsigned long hash(unsigned char const *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

static const int map_index(Map *map, char *key, char **keys)
{
    assert(map != NULL);

    int i = hash(key) % map->size;

    while (keys[i] && _strcmp(keys[i], key) != 0)
        i = (i + 1) % map->size;

    return i;
}

static void resize(Map *map)
{
    if (map->len < map->size * MAP_RESIZE_TRIGGER) {
        return;
    }

    map->size = map->size * MAP_RESIZE_FACTOR;

    char **keys = malloc(map->size * sizeof(char *));
    void **values = malloc(map->size * sizeof(void *));

    for (int i = 0; i < map->size / MAP_RESIZE_FACTOR; i++) {
        char *key = map->keys[i];
        void *value = map->values[i];

        if (key && value) {
            const int index = map_index(map, key, keys);

            keys[index] = key;
            values[index] = value;
        }
    }

    free(map->keys);
    free(map->values);

    map->keys = keys;
    map->values = values;
}
