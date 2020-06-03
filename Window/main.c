#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "WindowDefines.h"
#include "../FilePath.h"
#include "../Memory/MemoryDefines.h"
#include "../CPU/CPUDefines.h"
#include "../Graphics/GraphicsDefines.h"
#include "../Graphics/PPUDefines.h"
#include "../Interrupts/InterruptDefines.h"
#include "../Input/KeyboardDefines.h"
#include "../Tests/TestDefines.h"

//#define RUN_TESTS

// Array representing the Game Boy screen, holding values from 0 to 3 for each pixel
int8_t currentScreen[144][160] = {{0}};

int main(int argc, char *argv[]) {
	// Runs tests for individual funtions and displays them in the console for 2 minutes before terminating
	#ifdef RUN_TESTS
		runTests();
		return 0;
	#endif // RUN_TESTS

	// Initialisation of SDL and data structures
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
		printf("Failed to initialise SDL. Error: %s\n", SDL_GetError());
	}
	SDL_Window *win = CreateWindow("StallionGB", 144, 160);
	SDL_Renderer *ren = CreateRenderer(win);

	SDL_Event event;

    int8_t *memory = CreateNewMemory();
    PPU ppu = CreateNewPPU(memory, currentScreen);
    CPU cpu = CreateNewCPU(ppu);
    RomInfo *romInfo;
    FILE *fpRomFile = OpenRom(FILE_PATH, &memory[0x100], &romInfo);

	// Struct storing values representing whether each key (A, Up, Start ect.) is being pressed
	KeysPressed keysPressed = { 0, 0, 0, 0, 0, 0, 0, 0 };

    for (int i = 0; i < 144; i++) {
        for (int j = 0; j < 160; j++) {
            currentScreen[i][j] = 0; 
        }
    }

	int oldTime = SDL_GetTicks();
	while (1) {
		// Handle any messages which may have been sent
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;

		// Read input from the keyboard
		readKeyboard(&keysPressed);
		updateInput(keysPressed, memory);

		// Main processor loop, after window messages are dealt with
		if (cpu.state == ACTIVE) {
			int8_t currentInstruction = memory[cpu.pc];

			//printf("$90: %d $FF44: %d\n", memory[0x90], memory[0xFF44]);
			//printf("a: %d b: %d c: %d d: %d pc: %x\n", cpu.a, cpu.b, cpu.c, cpu.d, cpu.pc);
			//printf("%x, pc: %x\n", memory[cpu.pc], cpu.pc);
			//printf("PC: %d\n", cpu.pc);
			/*for (int i = 0; i < 144; i++) {
				for (int j = 0; j < 160; j++) {
					printf("%d ", currentScreen[i][j]);
				}
				printf("\n");
			}*/

			if (cpu.instructionClocks == ppu.instructionClocks) {
				cpu.instructionClocks = 0;
				ppu.instructionClocks = 0;

				DecodeOpcode(&cpu, memory, currentInstruction);

				PerformPPUOperation(&ppu, &cpu, memory, ren, currentScreen);
			} else if (cpu.instructionClocks < ppu.instructionClocks) {
				ppu.instructionClocks -= cpu.instructionClocks;
				cpu.instructionClocks = 0;

				DecodeOpcode(&cpu, memory, currentInstruction);
			} else {
				cpu.instructionClocks -= ppu.instructionClocks;
				ppu.instructionClocks = 0;

				PerformPPUOperation(&ppu, &cpu, memory, ren, currentScreen);
			}

			ProcessInterrupts(&cpu, memory);
		}
		
		// If the number of clocks corresponding to 1 frame has passed, sleep for the time difference between how long the real system would take
		int currentTime = SDL_GetTicks();
		if (cpu.totalClocks > 17556) {
			//SDL_Delay(((cpu.totalClocks / 1048576.0) * 1000) - (currentTime - oldTime) );
			/*printf("Num clocks: %d\n curr - old: %d", cpu.totalClocks, currentTime - oldTime);
			printf("Fraction: %lf", cpu.totalClocks / 1048576.0);
			printf("Sleep time: %lfms\n", ((cpu.totalClocks / 1048576.0) * 1000) - (currentTime - oldTime));*/
			oldTime = currentTime;
			cpu.totalClocks = 0;
		}
		/*if (currentTime - oldTime > 2000) {
			printf("PC: %d\n", cpu.pc);
			oldTime = currentTime;
		}*/
	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

    fclose(fpRomFile);
    free(memory);
    free(romInfo);
	return 0;
}
