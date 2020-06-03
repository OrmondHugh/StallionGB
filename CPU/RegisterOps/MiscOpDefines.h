//
// Created by Hugh on 12/06/2018.
//

#ifndef STALLIONGB_MISCOPDEFINES_H
#define STALLIONGB_MISCOPDEFINES_H

#include "../CPUDefines.h"

void DAA(CPU *r);
void CPL(CPU *r);
void CCF(CPU *r);
void SCF(CPU *r);

void jp(CPU *r, int8_t *memory);
void jpnz(CPU *r, int8_t *memory);
void jpz(CPU *r, int8_t *memory);
void jpnc(CPU *r, int8_t *memory);
void jpc(CPU *r, int8_t *memory);
void jphl(CPU *r, int8_t *memory);
void jrn(CPU *r, int8_t *memory);
void jrnzn(CPU *r, int8_t *memory);
void jrzn(CPU *r, int8_t *memory);
void jrncn(CPU *r, int8_t *memory);
void jrcn(CPU *r, int8_t *memory);

void DI(CPU *r);
void EI(CPU *r);

#endif //STALLIONGB_MISCOPDEFINES_H
