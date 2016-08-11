#ifndef MINOS_H
#define MINOS_H

#include <stdlib.h>
#include <stdbool.h>
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
    int sx;
    int sy;
} __tile;

struct __map{
    vita2d_texture* tileset;
    int id;
    int* data;
    __tile* tiles;
    int tsx;
    int tsy;
    int sx;
    int sy;
};
typedef struct __map MAP;

struct __command{
    int button;
    int action;
};
typedef struct __command minosCommand;

/*************************************/


/*************************************/
/** variables **/

/*************************************/


/*************************************/
/** functions **/
minosCommand* minosInputHandler(SceCtrlData* pad);
void minosCommandHandler(minosCommand* command);
MAP** minosLoadMaps(char** mapPaths);
int minosDrawMap(MAP* map);
int minosFreeMaps(MAP** maps);
/*************************************/

#endif
