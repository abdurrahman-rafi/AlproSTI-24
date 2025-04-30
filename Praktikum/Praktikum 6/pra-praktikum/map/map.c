#include "map.h"
#include <stdio.h>

Map *create_map(int capacity){
    Map map;
    map.capacity = capacity;
    map.entries = malloc(2 * capacity);
    map.size = 0;
}

bool map_insert(Map *map, int key, const char *value){
    map->entries[map->size].key = key;
    strcpy(map->entries[map->size].value, value);
    map->size++;
}

char *map_get(const Map *map, int key){
    for(int i = 0; i<map->size; i++){
        if(map->entries[i].key == key){
            return map->entries[i].value;
        }
    }
    return NULL;
}