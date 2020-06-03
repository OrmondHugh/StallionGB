#ifndef STALLIONGB_BIWISEDEFINES_H
#define STALLIONGB_BIWISEDEFINES_H

#include "../CPUDefines.h"

void andA(CPU *r);
void andr(CPU *r, int8_t x);
void andHL(CPU *r, int8_t *memory);
void andn(CPU *r, int8_t *memory);

void orr(CPU *r, int8_t x);
void orHL(CPU *r, int8_t *memory);
void orn(CPU *r, int8_t *memory);

void xorA(CPU *r);
void xorr(CPU *r, int8_t x);
void xorHL(CPU *r, int8_t *memory);
void xorn(CPU *r, int8_t *memory);

void swapR(CPU *r, int8_t *reg);
void swapHL(CPU *r, int8_t *memory);

void rln(CPU *r, int8_t *reg);
void rlhl(CPU *r, int8_t *memory);
void rlcn(CPU *r, int8_t *reg);
void rlchl(CPU *r, int8_t *memory);

void rrcn(CPU *r, int8_t *reg);
void rrcHL(CPU *r, int8_t *memory);
void rrn(CPU *r, int8_t *reg);
void rrHL(CPU *r, int8_t *memory);

void sla(CPU *r, int8_t *reg);
void slaHL(CPU *r, int8_t *memory);
void sran(CPU *r, int8_t *reg);
void sraHL(CPU *r, int8_t *memory);
void srl(CPU *r, int8_t *reg);
void srlHL(CPU *r, int8_t *memory);

void bitn(CPU *r, int8_t reg, int8_t bit);
void bitHL(CPU *r, int8_t *memory, int8_t bit);
void setn(CPU *r, int8_t *reg, int8_t bit);
void setHL(CPU *r, int8_t *memory, int8_t bit);
void resn(CPU *r, int8_t *reg, int8_t bit);
void resHL(CPU *r, int8_t *memory, int8_t bit);


#endif //STALLIONGB_BIWISEDEFINES_H
