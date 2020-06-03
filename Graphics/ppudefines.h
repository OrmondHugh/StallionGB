#ifndef STALLIONGB_PPUDEFINES_H
#define STALLIONGB_PPUDEFINES_H

#include <stdint.h>
#include "../CPU/Processors.h"

#include "SDL.h"

PPU CreateNewPPU(int8_t *memory, int8_t screenArray[144][160]);

void PerformPPUOperation(PPU *ppu, CPU *cpu, int8_t *memory, SDL_Renderer *ren, int8_t currentScreen[144][160]);
void UpdatePPUState(PPU *ppu);
int8_t ConvertSpritePalette(int8_t paletteNum, int8_t value, int8_t *memory);
void DrawScreen(SDL_Renderer *ren, int8_t currentScreen[144][160]);
void LoadBackgroundLine(PPU *ppu, int8_t *memory);
int8_t combineColourBytes(int8_t lineByteA, int8_t lineByteB, int n);
void LoadSpriteLine(PPU *ppu, int8_t *memory);

#endif