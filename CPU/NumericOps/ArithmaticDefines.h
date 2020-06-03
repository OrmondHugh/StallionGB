#ifndef STALLIONGB_ARITHMATICDEFINES_H
#define STALLIONGB_ARITHMATICDEFINES_H

#include "../CPUDefines.h"

void addAR(CPU *r, int8_t reg);
void addAHL(CPU *r, int8_t *memory);
void addAn(CPU *r, int8_t *memory);
void adcAR(CPU *r, int8_t reg);
void adcAn(CPU *r, int8_t *memory);
void adcHL(CPU *r, int8_t * memory);

void subAR(CPU *r, int8_t reg);
void subAA(CPU *r);
void subAHL(CPU *r, int8_t *memory);
void subAn(CPU *r, int8_t *memory);
void sbcAR(CPU *r, int8_t reg);
void sbcAHL(CPU *r, int8_t *memory);
void sbcAn(CPU *r, int8_t *memory);

void cpR(CPU *r, int8_t *reg);
void cpHL(CPU *r, int8_t *memory);
void cpn(CPU *r, int8_t *memory);

void incR(CPU *r, int8_t *reg);
void incHL(CPU *r, int8_t *memory);

void decR(CPU *r, int8_t *reg);
void decHL(CPU *r, int8_t *memory);

void addHLBC16bit(CPU *r);
void addHLDE16bit(CPU *r);
void addHLHL16bit(CPU *r);
void addHLSP16bit(CPU *r);
void addSPn(CPU *r, int8_t *memory);

void incBC(CPU *r);
void incDE(CPU *r);
void incHLreg(CPU *r);
void incSP(CPU *r);

void decBC(CPU *r);
void decDE(CPU *r);
void decHLreg(CPU *r);
void decSP(CPU *r);

#endif //STALLIONGB_ARITHMATICDEFINES_H
