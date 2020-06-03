#include "CPUDefines.h"
#include "../Memory/MemoryDefines.h"

CPU CreateNewCPU(PPU ppu) {
    CPU a = {.f={0,0,0,0},
             .pc=0,
             .CB=0,
             .state=ACTIVE,
             .instructionClocks=0,
             .interruptsEnabled=1,
             .interruptFlag={0,0,0,0,0},
             .ppuState=&ppu.state
    };

    return a;
}

// Returns the value of the Flag register struct as an 8 bit number, as it would be in the real CPU
uint8_t getF(Flag f) {
    uint8_t flag = 0x00;
    if (f.zero == 1) {
        flag &= 0b10000000;
    }
    if (f.subtract == 1) {
        flag &= 0b1000000;
    }
    if (f.halfCarry == 1) {
        flag &= 0b100000;
    }
    if (f.carry == 1) {
        flag &= 0b10000;
    }

    return flag;
}