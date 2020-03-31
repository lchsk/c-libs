#ifndef MAP_H
#define MAP_H

typedef struct {
    int size;
    int len;
    char **keys;
    void **values;
} Map;

Map *map_new(int initial_size);
void map_free(Map *map);

void map_set(Map *map, char *key, void *value);
void *map_get(Map *map, char *key);

void map_del(Map *map, char *key);
const int map_in(Map *map, char *key);
const int map_len(Map *map);

#endif
