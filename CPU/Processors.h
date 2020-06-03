#ifndef STALLIONGB_PROCESSORS_H
#define STALLIONGB_PROCESSORS_H

#include <stdint.h>

typedef enum PPUState {HBLANK, VBLANK, OAMREAD, PIXELTRANSFER} PPUState;

typedef struct PPU {
    int instructionClocks;

    // Resisters in the memory for the PPU
    int8_t *lcdControl;
    int8_t *lcdcStatus;
    uint8_t *scrollX, *scrollY;
    uint8_t *lcdcY;
    int8_t *lyCompare;
    int8_t *dmaTransferStart;   // Possibly unnecessary here?
    int8_t *backgroundPalette, *objectPalette0, *objectPalette1;
    int8_t *windowYpos, *windowXpos;

    //int8_t spriteArray[10]; Should be of some kind of sprite struct
    int8_t currentScreen[144][160];

    PPUState state;
} PPU;

typedef struct Flag {
    _Bool zero, subtract, halfCarry, carry;
} Flag;

typedef enum CPUState {ACTIVE, SLEEP, STOPPED} CPUState;

typedef struct InterruptFlags {
    _Bool vblank, lcdc, timer, serialTransferCompletion, highToLow;
} InterruptFlags;

typedef struct CPU {
    // 8-bit registers
    int8_t a, b, c, d, e, h, l;
    Flag f;

    // 16-bit registers
    uint16_t pc, sp;

    CPUState state;

    int instructionClocks;
	int totalClocks;

    // Flag representing if the CB prefix has been used
    _Bool CB;

    _Bool interruptsEnabled;
    InterruptFlags interruptFlag;

    PPUState *ppuState;
} CPU;

#endif //STALLIONGB_PROCESSORS_H
