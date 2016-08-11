#include "minos.h"

int __hCountArray(void** array){
    int arrayLen = -1;
    while (array[++arrayLen] != NULL) { /* nothing */}
    return arrayLen;
}

int __minosCheckMap(MAP* map){

    return true;
}

MAP* __minosLoadMap(char* mapPath){
    MAP* newMap = malloc(sizeof(newMap));

    return newMap;
}

MAP** minosLoadMaps(char** mapPaths){
    int mapCount = __hCountArray(mapPaths);
    if(mapCount == 0){ return NULL; }
    MAP** newMaps = malloc(sizeof(MAP) * mapCount);
    for(int i = 0; i < mapCount; i++){
        newMaps[i] = __minosLoadMap(mapPaths[i]);
        // TODO: JSON? or XML? or INI?
    }
    return newMaps;
}

int minosFreeMaps(MAP** maps){
    int mapCount = __hCountArray(maps);
    if(mapCount == 0){ return -10; }
    for(int i = 0; i < mapCount; i++){ free(maps[i]); }
    return true;
}


int minosDrawMap(MAP* map){
    for(int mx = 0; mx < map->sx; mx++){
        for(int my = 0; my < map->sy; my++){
            __tile* currentTile = map->tiles + (mx + (my * 16));
            vita2d_draw_texture_part(map->tileset, mx*32, mx*32, currentTile->ox, currentTile->oy, 32, 32);
        }
    }

    return 0;
}
