#include "main.h"

int main(int argc, char* argv[]) {

	FILE* csvFile = fopen("map.data", "w+b");

	__map_values writeMeta;
	writeMeta.tsx = 32;
	writeMeta.tsy = 32;
	writeMeta.sx = 4;
	writeMeta.sy = 4;

	uint8_t dataWrite[16] = {
		1,0,0,2,
		0,1,2,0,
		0,3,4,0,
		3,0,0,4,
	};

	fwrite(&writeMeta, sizeof(writeMeta), 1, csvFile);
	fwrite(&dataWrite, sizeof(uint8_t) * 16, 1, csvFile);

	fclose(csvFile);

    return 0;
}