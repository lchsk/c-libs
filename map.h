#ifndef XS_MAP_H
#define XS_MAP_H

#define XS_INITIAL_MAP_SIZE (16)

typedef struct {
    int size;
    int len;
    void **keys;
    void **values;
} map_t;

map_t *map_new();

void map_put(map_t *map, void *key, void *value);

void *map_get(map_t *map, void *key);

void map_free(map_t *map);

#endif
