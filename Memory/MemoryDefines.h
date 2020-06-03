#ifndef STALLIONGB_MEMORYFUNCS_H
#define STALLIONGB_MEMORYFUNCS_H

#include <stdint.h>
#include <stdio.h>
#include "../CPU/CPUDefines.h"

typedef struct RomInfo {
    char gameTitle[16];
    // If the game is intended for a Game Boy Colour, or if it is for a super game boy
    _Bool colour, super;
    int8_t cartrigeType;
    int numROMBanks;
    uint16_t checksum;
    _Bool checksumPassed;
} RomInfo;

FILE *OpenRom(const char *location, int8_t *romMemoryLocation, RomInfo **info);
int8_t *CreateNewMemory();
int8_t readByte(CPU cpu, int8_t *mem, uint16_t address);
void writeByte(CPU cpu, int8_t *mem, uint16_t address, int8_t content);

#endif //STALLIONGB_MEMORYFUNCS_H
