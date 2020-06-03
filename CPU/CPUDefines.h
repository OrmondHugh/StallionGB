#ifndef STALLIONGB_CPUFUNCS_H
#define STALLIONGB_CPUFUNCS_H

#include <stdint.h>
#include "../Graphics/PPUDefines.h"
#include "Processors.h"

// Concatenates the value of two resisters together to get the value of a 16-bit register, such as HL
#define DoubleRegister(x, y) (((x << 8) | y) & 0xFFFF)

CPU CreateNewCPU(PPU);

uint8_t getF(Flag f);

void setFlagsAddition(CPU *r, int8_t a, int8_t b);

void DecodeOpcode(CPU *cpu, int8_t *memory, int8_t op);

#endif //STALLIONGB_CPUFUNCS_H
