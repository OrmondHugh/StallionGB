#include "../Graphics/GraphicsDefines.h"
#include <stdint.h>

/*
* Runs cases for the combineColourBytesTest function to verify soundness. Prints results.
*/
void combineColourBytesTest() {
	printf("combineColourBytesTest started\n");
	int8_t testByteA1 = 0b00000000;
	int8_t testByteA2 = 0b00000000;
	int8_t testResultA[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	int8_t testByteB1 = 0b11111111;
	int8_t testByteB2 = 0b11111111;
	int8_t testResultB[8] = {3, 3, 3, 3, 3, 3, 3, 3};

	int8_t testByteC1 = 0b11110000;
	int8_t testByteC2 = 0b10101010;
	int8_t testResultC[8] = { 3, 1, 3, 1, 2, 0, 2, 0 };

	int8_t *resultA;
	int8_t *resultB;
	int8_t *resultC;

	resultA = malloc(8);
	resultB = malloc(8);
	resultC = malloc(8);

	for (int i = 7; i >= 0; i--) {
		resultA[i] = combineColourBytes(testByteA1, testByteA2, i);
		resultB[i] = combineColourBytes(testByteB1, testByteB2, i);
		resultC[i] = combineColourBytes(testByteC1, testByteC2, i);
	}

	for (int i = 7; i >= 0; i--) {
		if (resultA[i] != testResultA[i]) {
			printf("combineColourBytesTest failed for test A. Expected value %d for pixel %d but returned %d\n", testResultA[i], i, resultA[i]);
		}
		else {
			printf("Test A #%d passed\n", i);
		}
	}

	for (int i = 7; i >= 0; i--) {
		if (resultB[i] != testResultB[i]) {
			printf("combineColourBytesTest failed for test B. Expected value %d for pixel %d but returned %d\n", testResultB[i], i, resultB[i]);
		} else {
			printf("Test B #%d passed\n", i);
		}
	}

	for (int i = 7; i >= 0; i--) {
		if (resultC[i] != testResultC[i]) {
			printf("combineColourBytesTest failed for test C. Expected value %d for pixel %d but returned %d\n", testResultC[i], i, resultC[i]);
		}
		else {
			printf("Test C #%d passed\n", i);
		}
	}
}

void ConvertSpritePaletteTest() {
	printf("\n\nConvertSpritePaletteTest Started\n");
	int8_t testPaletteA = 0b00000000;
	int8_t testPaletteB = 0b01010101;
	int8_t testPaletteC = 0b10101010;
	int8_t testPaletteD = 0b11111111;

	int8_t *testMemory;
	testMemory = malloc(0xFF49);

	testMemory[0xFF49] = testPaletteA;
	for (int i = 0; i < 4; i++) {
		int8_t result = ConvertSpritePalette(1, i, testMemory);

		if (result != 0) {
			printf("ConvertSpritePaletteTest failed for Test A on value %d. Expected %d but returned %d\n", i, 0, result);
		} else {
			printf("Test A #%d passed\n", i);
		}
	}

	testMemory[0xFF49] = testPaletteB;
	for (int i = 0; i < 4; i++) {
		int8_t result = ConvertSpritePalette(1, i, testMemory);

		if (result != 1) {
			printf("ConvertSpritePaletteTest failed for Test B on value %d. Expected %d but returned %d\n", i, 1, result);
		} else {
			printf("Test B #%d passed\n", i);
		}
	}

	testMemory[0xFF49] = testPaletteC;
	for (int i = 0; i < 4; i++) {
		int8_t result = ConvertSpritePalette(1, i, testMemory);

		if (result != 2) {
			printf("ConvertSpritePaletteTest failed for Test C on value %d. Expected %d but returned %d\n", i, 2, result);
		} else {
			printf("Test C #%d passed\n", i);
		}
	}

	testMemory[0xFF49] = testPaletteD;
	for (int i = 0; i < 4; i++) {\
		int8_t result = ConvertSpritePalette(1, i, testMemory);

		if (result != 3) {
			printf("ConvertSpritePaletteTest failed for Test D on value %d. Expected %d but returned %d\n", i, 3, result);
		} else {
			printf("Test D #%d passed\n", i);
		}
	}
	printf("ConvertSpritePaletteTest Finished\n");
}

void runTests() {
	printf("***Running Tests***\n");
	combineColourBytesTest();
	ConvertSpritePaletteTest();
	printf("***Tests Finished***\n");
	SDL_Delay(1200000);
}