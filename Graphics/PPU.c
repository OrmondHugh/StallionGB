#include <stdlib.h>
#include <stdio.h>

#include "SDL.h"
#include "SDL_render.h"

#include "./PPUDefines.h"
#include "GraphicsDefines.h"
#include "../CPU/CPUDefines.h"
#include "SpriteList.h"

// Returns a PPU struct with all necessary values initialised
PPU CreateNewPPU(int8_t *memory, int8_t screenArray[144][160]) {
    PPU ppu = {
            .instructionClocks = 0,

            // The PPU registers point to values in the memory
            .lcdControl = memory + 0xFF40,
            .lcdcStatus = memory + 0xFF41,
            .scrollY = (uint8_t *) memory + 0xFF42,
            .scrollX = (uint8_t *) memory + 0xFF43,
            .lcdcY = (uint8_t *) memory + 0xFF44,
            .lyCompare = memory + 0xFF45,
            .dmaTransferStart = memory + 0xFF46,
            .backgroundPalette = memory + 0xFF47,
            .objectPalette0 = memory + 0xFF48,
            .objectPalette1 = memory + 0xFF49,
            .windowYpos = memory + 0xFF4A,
            .windowXpos = memory + 0xFF4B,

            .currentScreen = screenArray,
            //.currentScreenFull = {},

            .state = OAMREAD
    };

    return ppu;
}

void PerformPPUOperation(PPU *ppu, CPU *cpu, int8_t *memory, SDL_Renderer *ren, int8_t currentScreen[144][160]) {
    UpdatePPUState(ppu, memory);
    switch(ppu->state) {
        case OAMREAD:
            // Read sprites which should be on the line
            ppu->instructionClocks += 20;
            break;
        case PIXELTRANSFER:
            LoadBackgroundLine(ppu, memory);
			LoadSpriteLine(ppu, memory);
            // Read the background tiles, add in sprites and window and apply the scroll
            ppu->instructionClocks += 43;
            break;
        case HBLANK:
            ppu->instructionClocks += 51;
            break;
        case VBLANK:
            // Refresh the window with the newly updated screen data
			DrawScreen(ren, currentScreen);
            *ppu->lcdcY = 0;
            cpu->interruptFlag.vblank = 1;
            ppu->instructionClocks += 114;
            break;
    }
}

/**
 * Changes the state of the PPU to the next in line
 */
 // TODO update and mode flag
void UpdatePPUState(PPU *ppu, int8_t *memory) {
    if (ppu->state != VBLANK && *ppu->lcdcY >= 144) {
        ppu->state = VBLANK;
    } else {
        switch(ppu->state) {
            case OAMREAD:
                ppu->state = PIXELTRANSFER;
                break;
            case PIXELTRANSFER:
                ppu->state = HBLANK;
                break;
            case HBLANK:
                ppu->state = OAMREAD;
                break;
            case VBLANK:
                ppu->state = OAMREAD;
                break;
        }
    }
}

/**
 * Coverts the colours in the line pointed to by lcdcY to the
 * colours specified by the backgroundPalette register
 */
void ConvertBackgroundPalette(PPU *ppu) {
    int8_t shade0 = *ppu->backgroundPalette & 0b11;
    int8_t shade1 = (*ppu->backgroundPalette & 0b1100) >> 2;
    int8_t shade2 = (*ppu->backgroundPalette & 0b110000) >> 4;
    int8_t shade3 = (*ppu->backgroundPalette & 0b11000000) >> 6;

    for (int i = 0; i < 160; i++) {
        switch(ppu->currentScreen[*ppu->lcdcY][i]) {
            case(0):
                ppu->currentScreen[*ppu->lcdcY][i] = shade0;
                break;
            case(1):
                ppu->currentScreen[*ppu->lcdcY][i] = shade1;
                break;
            case(2):
                ppu->currentScreen[*ppu->lcdcY][i] = shade2;
                break;
            case(3):
                ppu->currentScreen[*ppu->lcdcY][i] = shade3;
                break;
            default:
				printf("Error decoding palette values");
                exit(1);
        }
    }
}

/**
 * Loads the background pixels on the line pointed to by the lcdcY register
 */
void LoadBackgroundLine(PPU *ppu, int8_t *memory) {
	// Read what background map should be used
	uint16_t bgMapAddress = (*ppu->lcdControl & 0b1000) ? 0x9C00 : 0x9800;

	// The "coordinates" of the tile being read within the tile map
	int mapX, mapY;

	// The "coordinates" of the pixel within the tile being read
	int tileX;
	int tileY = *ppu->scrollY % 8;

	// The two bytes used to represent a line within a tile
	int8_t lineByteA, lineByteB;

	// Read from the correct tile data table based on what the LCDC register specifies
	if (*ppu->lcdControl & 0b1000) {
		uint16_t tileDataAddress = 0x8000;

		uint8_t *tileAddress;
		for (int i = 0; i < 160; i++) {
			mapX = (*ppu->scrollX + i) / 32;
			mapY = *ppu->scrollY / 32;

			tileAddress = (uint8_t *)&memory[bgMapAddress + (mapY * 32) + mapX];
			*tileAddress += tileDataAddress;

			tileX = (*ppu->scrollX + i) % 8;

			lineByteA = memory[*tileAddress + tileY];
			lineByteB = memory[*tileAddress + tileY + 1];

			//int8_t colour = ((lineByteB & (0b10000000 >> tileX)) >> (6 - tileX) | (lineByteA & (0b10000000 >> tileX) >> (7 - tileX))) && 0b11;
			int8_t colour = combineColourBytes(lineByteA, lineByteA, tileX);

			ppu->currentScreen[*ppu->lcdcY][i] = colour;
		}
	}
	else {
		uint16_t tileDataAddress = 0x9000;

		int8_t *tileAddress;
		for (int i = 0; i < 160; i++) {
			mapX = (*ppu->scrollX + i) / 32;
			mapY = *ppu->scrollY / 32;

			tileAddress = &memory[bgMapAddress + (mapY * 32) + mapX];
			*tileAddress += tileDataAddress;

			tileX = (*ppu->scrollX + i) % 8;

			lineByteA = memory[*tileAddress + tileY];		// CHECK THIS AGAIN
			lineByteB = memory[*tileAddress + tileY + 1];

			//int8_t colour = ((lineByteB & (0b10000000 >> tileX)) >> (6 - tileX) | (lineByteA & (0b10000000 >> tileX) >> (7 - tileX))) && 0b11;
			int8_t colour = combineColourBytes(lineByteA, lineByteA, tileX);

			ppu->currentScreen[*ppu->lcdcY][i] = colour;
		}
	}

	ConvertBackgroundPalette(ppu);

	*ppu->lcdcY += 1;
}


/*
* Takes 2 bytes representing 8 pixels of 1 line and returns the colour of the pixel nth as value in [0,3]
*/
int8_t combineColourBytes(int8_t lineByteA, int8_t lineByteB, int n) {
	int8_t lhs = (lineByteB & (0b10000000 >> n)) >> (7 - n);
	int8_t rhs = (lineByteA & (0b10000000 >> n)) >> (7 - n);
	
	lhs = lhs << 1;
	int8_t colour = (lhs | rhs) & 0b11;

	return colour;
}

/* 
* Adds sprite pixels on the line pointed to by the lcdcY register, after the background has been loaded
*/
void LoadSpriteLine(PPU *ppu, int8_t *memory) {
	// Attributes: FE00 - FE9F, 4 bytes long
	// Patterns: 8000 - 8FFF
	// Smaller X coordinate has priority
	// Equal X coordinate means FE00 has highest priority
	// X,Y is coodiantes of top left corner
	// Attribute blocks:
	// Byte 0,1: Y,X position
	// Byte 2: pattern num (0,255) unsigned
	// Flags: 
	// Bit 7 - Priority. 1 means only display over colour 0. 0 is normal
	// 6,5 - Y,X flip
	// 4 - Palette num

	SpriteList spriteList = { NULL, 0 };
	AddSprites(&spriteList, memory);

	SpriteData *tmp = spriteList.first;

	for (int i = 0; i < 10 && i < spriteList.spriteCount; i++) {
		tmp = tmp->next;

		int patternNum = memory[tmp->attributeLocation];
		int priority = memory[tmp->attributeLocation + 3]		& 0b10000000;
		int yFlip = memory[tmp->attributeLocation + 3]			& 0b1000000;
		int xFlip = memory[tmp->attributeLocation + 3]			& 0b100000;
		int palletNum = memory[tmp->attributeLocation + 3]		& 0b10000;

		int tileY = yFlip ? 8 - (*ppu->lcdcY % 0b1000) : (*ppu->lcdcY % 0b1000);
		 
		int8_t lineByteA = memory[0x8000 + patternNum + (tileY * 2)];
		int8_t lineByteB = memory[0x8000 + patternNum + (tileY * 2) + 1];

		if (xFlip) {
			for (int i = 8; i > 0; i--) {
				if (!(priority && (ppu->currentScreen[*ppu->lcdcY + tileY][tmp->xPos + i] != 0))) {
					int tileX = 8 - i;

					int8_t colour = combineColourBytes(lineByteA, lineByteA, tileX);

					ppu->currentScreen[*ppu->lcdcY + tileY][tmp->xPos + i] = ConvertSpritePalette(palletNum, colour, memory);
				}
			}
		} else {
			for (int i = 0; i < 8; i++) {
				// If the sprite isn't under priorty with regards to the background
				if (!(priority && (ppu->currentScreen[*ppu->lcdcY + tileY][tmp->xPos + i] != 0))) {
					int8_t colour = combineColourBytes(lineByteA, lineByteA, i);

					//printf("Colour: %d\n", colour);

					//printf("Placing colour %d at index %d, %d\n", ConvertSpritePalette(palletNum, colour, memory), *ppu->lcdcY + tileY, tmp->xPos + i);
					ppu->currentScreen[*ppu->lcdcY + tileY][tmp->xPos + i] = ConvertSpritePalette(palletNum, colour, memory);
				}
			}
		}
	}

}

int8_t ConvertSpritePalette(int8_t paletteNum, int8_t value, int8_t *memory) {
	int paletteLocation = paletteNum ? 0xFF49 : 0xFF48;

	// b = 00001011
	switch (value) {
	case(0b11):	// Return bits 7-6 of the palette data reg
		return ((memory[paletteLocation] & 0b11000000) >> 6) & 0b11;
		break;
	case(0b10): // Return bits 5-4
		return ((memory[paletteLocation] & 0b110000) >> 4) & 0b11;
		break;
	case(0b01): // Return bits 3-2
		return ((memory[paletteLocation] & 0b1100) >> 2) & 0b11;
		break;
	case(0b00): // Return bits 1-0
		return memory[paletteLocation] & 0b11;
		break;
	}

	perror("Invalid value for sprite data");
	exit(1);
}

/**
 * Draws the screen represented by currentScreen to the window
 */
void DrawScreen(SDL_Renderer *ren, int8_t currentScreen[144][160]) {
	// This technique may cause trouble with vsync enabled

	// Define a texture which will represent the screen
	SDL_Texture *texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 144, 160);

	// Array of RGBA tuples for each pixel in the 144*160 screen
	int8_t pixels[144][160][4] = { {0} };

	for (int i = 0; i < 144; i++) {
		//printf("\n");
		for (int j = 0; j < 160; j++) {
			//printf("%d ", currentScreen[i][j]);
			SDL_RenderClear(ren);

			switch (currentScreen[i][j]) {
			case(0):
				pixels[i][j][0] = 0x0F; // B
				pixels[i][j][1] = 0xBC; // G
				pixels[i][j][2] = 0x9B; // R
				pixels[i][j][3] = SDL_ALPHA_OPAQUE; // A
				break;
			case(1):
				pixels[i][j][0] = 0x0F; // B
				pixels[i][j][1] = 0xAC; // G
				pixels[i][j][2] = 0x8B; // R
				pixels[i][j][3] = SDL_ALPHA_OPAQUE; // A
				break;
			case(2):
				pixels[i][j][0] = 0x30; // B
				pixels[i][j][1] = 0x62; // G
				pixels[i][j][2] = 0x30; // R
				pixels[i][j][3] = SDL_ALPHA_OPAQUE; // A
				break;
			case(3):
				pixels[i][j][0] = 0x0F; // B
				pixels[i][j][1] = 0x38; // G
				pixels[i][j][2] = 0x0F; // R
				pixels[i][j][3] = SDL_ALPHA_OPAQUE; // A
				break;
			default:
				perror("Invalid Pixel Color Value");
				exit(1);
			}
		}
	}

	SDL_UpdateTexture(texture, NULL, &pixels[0], 144 * 4);
	SDL_RenderCopy(ren, texture, NULL, NULL);
	SDL_RenderPresent(ren);

	SDL_DestroyTexture(texture);
}