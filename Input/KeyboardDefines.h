#ifndef STALLIONGB_KEYBOARDDEFINES_H
#define STALLIONGB_KEYBOARDDEFINES_H

#include "SDL.h"

typedef struct KeysPressed {
	_Bool A, B, Up, Left, Down, Right, Start, Select;
} KeysPressed;

void readKeyboard(KeysPressed *keysPressed);
void updateInput(KeysPressed keysPressed, int8_t *memory);

#endif