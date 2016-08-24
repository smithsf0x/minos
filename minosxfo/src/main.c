#include "main.h"

int main() {
    vita2d_pgf *pgf;
    SceCtrlData pad;
    MAP** mapList;
    int state = 1;
    long deltaTime;

    char* mapPaths[] = {
        "ux0:data/minos/maps/test"
    };

    memset(&pad, 0, sizeof(pad));

    vita2d_init();
	vita2d_set_clear_color(RGBA8(120, 120, 120, 0xFF));

    pgf = vita2d_load_default_pgf();
    mapList = minosLoadMaps(mapPaths);
    MAP* currentMap = mapList + 0;

    while(state >= 1){
        sceCtrlPeekBufferPositive(0, &pad, 1);

        if (pad.buttons & SCE_CTRL_START){
            state = 0;
        }

        vita2d_start_drawing();
		vita2d_clear_screen();

        //minosDrawMap(currentMap);

		vita2d_draw_rectangle(20, 20, 400, 250, RGBA8(255, 0, 0, 255));
		vita2d_draw_rectangle(680, 350, 100, 150, RGBA8(0, 0, 255, 255));
		vita2d_draw_fill_circle(200, 420, 100, RGBA8(0, 255,0 ,255));

		vita2d_draw_line(500, 30, 800, 300, RGBA8(255, 0, 255, 255));

		vita2d_pgf_draw_text(pgf, 0, 0, RGBA8(100,255,100,255), 2, "test");

		vita2d_end_drawing();
		vita2d_swap_buffers();
    }

	vita2d_fini();
	vita2d_free_pgf(pgf);

	sceKernelExitProcess(0);
	return 0;
}
