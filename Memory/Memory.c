#include <stdlib.h>
#include <stdint.h>
#include "MemoryDefines.h"
#include "../FilePath.h"
#include "../CPU/CPUDefines.h"

const int ADDRESS_SPACE_SIZE = 0x10000;

/**
 * Creates an array to represent the Gameboy's memory and initialises it with the boot ROM
 */
int8_t *CreateNewMemory() {
    int8_t *memory = calloc(ADDRESS_SPACE_SIZE, 1);

    for (int i = 0; i <= 0xFF; i++) {
        memory[i] = BOOT_ROM[i];
    }

    return memory;
}

int8_t readByte(CPU cpu, int8_t *mem, uint16_t address) {
    /*if (address >= 0xFE00 && address <= 0xFE9F) { // If the address is in OAM ram
        if (*cpu.ppuState == HBLANK || *cpu.ppuState == VBLANK) {
            return mem[address];
        }
    } else if (address >= 0x8000 && address < 0xA000) { // If the address is in VRAM
        if (*cpu.ppuState != PIXELTRANSFER) {
            return mem[address];
        }
    }

    return 0xFF;*/

    return mem[address];
}

void writeByte(CPU cpu, int8_t *mem, uint16_t address, int8_t content) {
    if (address >= 0xFE00 && address <= 0xFE9F) { // If the address is in OAM ram
        if (*cpu.ppuState == HBLANK || *cpu.ppuState == VBLANK) {
            mem[address] = content;
        }
    } else if (address >= 0x8000 && address < 0xA000) { // If the address is in VRAM
        if (*cpu.ppuState != PIXELTRANSFER) {
            mem[address] = content;
        }
	} else {
		mem[address] = content;
	}
}
