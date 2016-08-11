/*
 * Copyright (c) 2015 Sergi Granell (xerpi)
 */

#include "main.h"

/*
 * Symbol of the image.png file
 */
extern unsigned char _binary_image_png_start;

int main() {
    SceCtrlData pad;
    minosCommand* mainCommand;
    MAP** mapList;

    char* mapPaths[] = {
        "test",
        "asdf"
    };

    mapList = minosLoadMaps(mapPaths);
    MAP* testMap = mapList[0];
    mapList[0]->tsy = 32;
    mapList[0]->tsx = 32;
    mapList[0]->sy = 4;
    mapList[0]->sx = 8;

    __tile tileBlue, tileRed, tileGray, tileGreen;
    tileBlue.sx = 32;
    tileBlue.sy = 32;
    tileBlue.id = 0;
    tileBlue.ox = 0;
    tileBlue.oy = 0;

    tileRed.sx = 32;
    tileRed.sy = 32;
    tileRed.id = 17;
    tileRed.ox = 32;
    tileRed.oy = 32;

    tileGray.sx = 32;
    tileGray.sy = 32;
    tileGray.id = 16;
    tileGray.ox = 0;
    tileGray.oy = 32;

    tileGreen.sx = 32;
    tileGreen.sy = 32;
    tileGreen.id = 1;
    tileGreen.ox = 32;
    tileGreen.oy = 0;

    int data[32]= {
        0,0,0,0,0,0,0,0,
        0,1,1,0,0,0,0,0,
        0,0,0,16,17,0,0,0,
        0,0,0,0,0,0,0,0
    };

    testMap->data = data;

    __tile testTiles[128];
    testTiles[0] = tileBlue;
    testTiles[17] = tileRed;
    testTiles[16] = tileGray;
    testTiles[1] = tileGreen;

    testMap->tiles = testTiles;

    vita2d_pgf *pgf;
	vita2d_texture *image;

    vita2d_init();
	vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));

    pgf = vita2d_load_default_pgf();

	/*
	 * Load the statically compiled image.png file.
	 */
	image = vita2d_load_PNG_file("ux0:data/minos/tile.png");

    // do {

    // } while(1);
    while(1){
        sceCtrlPeekBufferPositive(0, &pad, 1);

		if (pad.buttons & SCE_CTRL_START)
			break;

		vita2d_start_drawing();
		vita2d_clear_screen();
        /*
        vita2d_draw_rectangle(20, 20, 400, 250, RGBA8(255, 0, 0, 255));
		vita2d_draw_rectangle(680, 350, 100, 150, RGBA8(0, 0, 255, 255));
		vita2d_draw_fill_circle(200, 420, 100, RGBA8(0, 255,0 ,255));

		vita2d_draw_line(500, 30, 800, 300, RGBA8(255, 0, 255, 255));

		vita2d_pgf_draw_text(pgf, 700, 30, RGBA8(0,255,0,255), 1.0f, "PGF Font sample!");
        */
        minosDrawMap(testMap);
        //vita2d_draw_texture(image, 0, 0);
        //vita2d_draw_texture_part(image, 2, 2, 200, 200, 100, 100);

		vita2d_end_drawing();
		vita2d_swap_buffers();
    }





    minosFreeMaps(mapList);

	/*
	 * vita2d_fini() waits until the GPU has finished rendering,
	 * then we can free the assets freely.
	 */
	vita2d_fini();
	vita2d_free_texture(image);
	vita2d_free_pgf(pgf);

	sceKernelExitProcess(0);
	return 0;
}
