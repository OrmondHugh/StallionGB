#include "KeyboardDefines.h"
#include "SDL.h"

/*
* Reads input from the physical keyboard and represents it's state in keysPressed
*/
void readKeyboard(KeysPressed *keysPressed) {
	const uint8_t *keyboardState =  SDL_GetKeyboardState(NULL);

	keysPressed->A = keyboardState[SDL_SCANCODE_Z];
	keysPressed->B = keyboardState[SDL_SCANCODE_X];

	keysPressed->Up = keyboardState[SDL_SCANCODE_UP];
	keysPressed->Down = keyboardState[SDL_SCANCODE_DOWN];
	keysPressed->Left = keyboardState[SDL_SCANCODE_LEFT];
	keysPressed->Right = keyboardState[SDL_SCANCODE_RIGHT];

	keysPressed->Start = keyboardState[SDL_SCANCODE_SPACE];
	keysPressed->Select = keyboardState[SDL_SCANCODE_KP_ENTER];
}

/*
* Updates the I/O register at 0xFF00 with the values corresponding to those in keysPressed
 */
void updateInput(KeysPressed keysPressed, int8_t *memory) {
	// May be a source of problem when multiple keys are pressed
	// Eg. holding right + start together is equivilent to holding A
	// I havn't been able to find specic documentation about this so far

	// This function does not yet deal with the relevant I/O interrupt when a value
	// here changes from High to Low

	memory[0xFF00] = 0x0;

	if (keysPressed.A) {
		memory[0xFF00] |= 0b00100000;
		memory[0xFF00] |= 0b00000001;
	}

	if (keysPressed.B) {
		memory[0xFF00] |= 0b00100000;
		memory[0xFF00] |= 0b00000010;
	}

	if (keysPressed.Select) {
		memory[0xFF00] |= 0b00100000;
		memory[0xFF00] |= 0b00000100;
	}

	if (keysPressed.Start) {
		memory[0xFF00] |= 0b00100000;
		memory[0xFF00] |= 0b00001000;
	}

	if (keysPressed.Right) {
		memory[0xFF00] |= 0b00010000;
		memory[0xFF00] |= 0b00000001;
	}

	if (keysPressed.Left) {
		memory[0xFF00] |= 0b00010000;
		memory[0xFF00] |= 0b00000010;
	}

	if (keysPressed.Up) {
		memory[0xFF00] |= 0b00010000;
		memory[0xFF00] |= 0b00000100;
	}

	if (keysPressed.Right) {
		memory[0xFF00] |= 0b00010000;
		memory[0xFF00] |= 0b00000010;
	}
}