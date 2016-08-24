#ifndef MINOS_H
#define MINOS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <psp2/io/fcntl.h>
#include <vita2d.h>


  /*************************************/
 /*               minos               */
/*************************************/

/*************************************/
/** includes **/

/*************************************/


/*************************************/
/** defines **/

#define MINOS_DRAW_BUFFER_TYPE  int
#define MINOS_DRAW_BUFFER_X     2048
#define MINOS_DRAW_BUFFER_Y     2048

#define DEBUGA

/*************************************/


/*************************************/
/** enumeration **/

/*************************************/


/*************************************/
/** structs / typedef **/

typedef struct __tile{
    int id;
    int ox;
    int oy;
} __tile;

struct __map_values{
    uint8_t tsx;
    uint8_t tsy;
    uint8_t sx;
    uint8_t sy;
};
typedef struct __map_values __map_values;

struct __map_info{
    __map_values values;
    uint8_t* data;
};
typedef struct __map_info MAP_INFO;

struct __map{
    vita2d_texture* tileset;
    int tilesetx;
    int tilesety;
    int id;
    uint8_t* data;
    __tile* tiles;
    uint8_t tsx;
    uint8_t tsy;
    uint8_t sx;
    uint8_t sy;
};
typedef struct __map MAP;

struct __command{
    int button;
    int action;
};
typedef struct __command minosCommand;

struct __camera{
    float scale;
    float x;
    float y;
    int sx;
    int sy;
};
typedef struct __camera CAMERA;

/*************************************/


/*************************************/
/** variables **/
int __minosLogFd;
/*************************************/


/*************************************/
/** functions **/

int minosLogInit(char* filePath);
int minosLog( char* string);
int minosLogClose();

minosCommand* minosInputHandler(SceCtrlData* pad);
void minosCommandHandler(minosCommand* command);
MAP_INFO* __minosGetMapInfo(char* mapPathData);
MAP* __minosLoadMap(char* mapPath);
MAP** minosLoadMaps(char** mapPaths);
int minosDrawMap(MAP* map);
int minosFreeMaps(MAP** maps);
/*************************************/

#endif
