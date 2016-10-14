#ifndef XS_MAP_H
#define XS_MAP_H

#define XS_INITIAL_MAP_SIZE (16)

#define XS_MAP_RESIZE_FACTOR (0.666)

typedef struct {
    int size;
    int len;
    char **keys;
    void **values;
} map_t;

map_t *map_new();

void map_put(map_t *map, char *key, void *value);

void map_del(map_t *map, char *key);

void *map_get(map_t *map, char *key);

unsigned map_in(map_t *map, char *key);

unsigned map_len(map_t *map);

void map_free(map_t *map);

#endif
