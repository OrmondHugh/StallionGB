#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "MemoryDefines.h"

FILE *OpenRom(const char *location, int8_t *romMemoryLocation, RomInfo **info) {
	FILE *p = NULL;
	fopen_s(&p, "C:\\Users\\Hugh\\Documents\\GB Roms\\Tetris.gb", "r");

    // Read the start of the ROM to get basic info
    int8_t *buffer = malloc(0x60);
    fread(buffer, 1, 0x50, p);
    rewind(p);

    *info = malloc(sizeof(RomInfo));

    for (int i = 0; i < 16; i++) {
        (*info)->gameTitle[i] = buffer[0x34+i];
    }
    (*info)->colour = buffer[0x43] == 0x80 ? 1 : 0;
    (*info)->super = buffer[0x46];
    (*info)->cartrigeType = buffer[0x47];
    if (buffer[0x48] <= 6) {
        (*info)->numROMBanks = 2^(buffer[0x48] + 1);
    } else if (buffer[0x48] == 0x52) {
        (*info)->numROMBanks = 72;
    } else if (buffer[0x48] == 0x53) {
        (*info)->numROMBanks = 80;
    } else {
        (*info)->numROMBanks = 96;
    }
    (*info)->checksum = (buffer[0x4E] << 8) & buffer[0x4F];
    free(buffer);

    long fileSize;
    fseek(p, 0L, SEEK_END);
    fileSize = ftell(p);
    rewind(p);

    // Limit the amount of the ROM transferred to memory as not to spill out of the 2 banks
    if (fileSize > 0xFFFF9C) {
        fileSize = 0xFFFF9C;
    }

    fread(romMemoryLocation, 1, fileSize, p);

    return p;
}
