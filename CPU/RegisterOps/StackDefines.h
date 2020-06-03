#ifndef STALLIONGB_STACKDEFINES_H
#define STALLIONGB_STACKDEFINES_H

#include "../CPUDefines.h"

void pushAF(CPU *r, int8_t *memory);
void pushBC(CPU *r, int8_t *memory);
void pushDE(CPU *r, int8_t *memory);
void pushHL(CPU *r, int8_t *memory);
void popAF(CPU *r, int8_t *memory);
void popBC(CPU *r, int8_t *memory);
void popDE(CPU *r, int8_t *memory);
void popHL(CPU *r, int8_t *memory);

void call(CPU *r, int8_t *memory);
void callnz(CPU *r, int8_t *memory);
void callz(CPU *r, int8_t *memory);
void callnc(CPU *r, int8_t *memory);
void callc(CPU *r, int8_t *memory);

void rstn(CPU *r, int8_t *memory, int16_t argument);

void ret(CPU *r, int8_t *memory);
void retnz(CPU *r, int8_t *memory);
void retz(CPU *r, int8_t *memory);
void retnc(CPU *r, int8_t *memory);
void retc(CPU *r, int8_t *memory);
void reti(CPU *r, int8_t *memory);

#endif //STALLIONGB_STACKDEFINES_H
