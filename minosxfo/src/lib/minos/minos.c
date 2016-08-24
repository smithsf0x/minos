#include "minos.h"
//TODO: error checking...
//TODO: logging/printing log

int minosLogInit(char* filePath){
    if(!(__minosLogFd = sceIoOpen(filePath, SCE_O_WRONLY|SCE_O_CREAT, 0777))) {
 	      return -1;
    };
    char initText[] = "\nInit log ... \n";

    sceIoWrite(__minosLogFd,initText, strlen(initText));
    return 0;
}

int minosLog(char* string){
    size_t len = strlen(string);
    return sceIoWrite(__minosLogFd,string, len);
}

int minosLogClose(){
    sceIoClose(__minosLogFd);
    return 0;
}

int __hCountArray(void* array){
    int arrayLen = -1;
    while(array[++arrayLen] != NULL) { /* nothing */ }
    return arrayLen;
}
int __hCountArrayMap(MAP** array){
    int arrayLen = -1;
    while (array[++arrayLen] != NULL) { /* nothing */}
    return arrayLen;
}
int __hCountArrayChar(char** array){
    int arrayLen = -1;
    while (array[++arrayLen] != NULL) { /* nothing */}
    return arrayLen;
}

int __minosCheckMap(MAP* map){

    return true;
}

__tile* __minosCalcTiles(MAP* map){
    __tile* tiles = malloc(sizeof(tiles) * map->sx * map->sy);
    int tsx = map->tsx;
    int tsy = map->tsy;
    for (int y = 0; y <  map->sy; y++) {
        for (int x = 0; x <  map->sx; x++) {
            int select = (y * map->sx) + x;
            __tile newTile;
            newTile.id = map->data[select];
            newTile.oy = tsy * (newTile.id/map->tilesetx);
            newTile.ox = tsx * (newTile.id%map->tilesetx);
            tiles[select] = newTile;
        }
    }
    return tiles;
}

MAP_INFO* __minosGetMapInfo(char* mapPathData){
    int fd;
    if(!(fd = sceIoOpen(mapPathData, SCE_O_RDONLY|SCE_O_NBLOCK, 0777))){
        sceIoClose(fd);
        return NULL;
    }
    __map_values values;
    if(sceIoRead(fd, &values, sizeof(values)) != sizeof(values)){
        sceIoClose(fd);
        return NULL;
    }
    size_t dataSize = (sizeof(uint8_t)*values.sx*values.sy);
    uint8_t* data = malloc( sizeof(uint8_t)*dataSize);
    size_t readSize = sceIoRead(fd, data, sizeof(uint8_t)*dataSize);


    MAP_INFO* mapInfo = malloc(sizeof(MAP_INFO));
    mapInfo->values = values;
    mapInfo->data = data;
    sceIoClose(fd);
    return mapInfo;
}

MAP* __minosLoadMap(char* mapPath){
    size_t mapPathSize = strlen(mapPath);
    char mapPathData[mapPathSize + 10];
    mapPathData[0] = '\0';
    char mapPathPng[mapPathSize + 14];
    mapPathPng[0] = '\0';

    strcat(mapPathData, mapPath);
    strcat(mapPathData, "/map.data\0");
    strcat(mapPathPng, mapPath);
    strcat(mapPathPng, "/tileset.png\0");

    MAP* newMap = malloc(sizeof(MAP));

    MAP_INFO* mapInfo;
    __tile* mapTiles;

    mapInfo = __minosGetMapInfo(mapPathData);
    if(mapInfo == NULL){
        return NULL;
    }

    newMap->tsx = mapInfo->values.tsx;
    newMap->tsy = mapInfo->values.tsy;
    newMap->sx = mapInfo->values.sx;
    newMap->sy = mapInfo->values.sy;
    newMap->data = mapInfo->data;
    newMap->tileset = vita2d_load_PNG_file(mapPathPng);
    newMap->tilesetx = vita2d_texture_get_width(newMap->tileset) / newMap->tsx;
    newMap->tilesety = vita2d_texture_get_height(newMap->tileset) / newMap->tsy;

    mapTiles = __minosCalcTiles(newMap);
    newMap->tiles = mapTiles;
    return newMap;
}

MAP** minosLoadMaps(char** mapPaths){
    int mapCount = __hCountArrayChar(mapPaths);
    if(mapCount == 0){ return NULL; }
    MAP** newMaps = malloc(sizeof(MAP) * mapCount);
    for(int i = 0; i < mapCount; i++){
        newMaps[i] = __minosLoadMap(mapPaths[i]);
        if(newMaps[i] == NULL){
            return NULL;
        }
    }
    return newMaps;
}

int minosFreeMaps(MAP** maps){
    int mapCount = __hCountArrayMap(maps);
    if(mapCount == 0){ return -10; }
    for(int i = 0; i < mapCount; i++){ free(maps[i]); }
    return true;
}


int minosDrawMap(MAP* map){
    for(int my = 0; my < map->sy; my++){
        for(int mx = 0; mx < map->sx; mx++){
            __tile* currentTile = map->tiles + (mx + (my * map->sx));
            vita2d_draw_texture_part(map->tileset, mx*map->tsx, my*map->tsy, currentTile->ox, currentTile->oy, map->tsx, map->tsy);
        }
    }
    return 0;
}

long minosGetDeltaTime(){
    static struct timeval currentTime;
    static struct timeval currentTimeOld;
    currentTimeOld = currentTime;
	gettimeofday(&currentTime, NULL);

	return (currentTime.tv_sec * (int)1e6 + currentTime.tv_usec) - (currentTimeOld.tv_sec * (int)1e6 + currentTimeOld.tv_usec);
}
