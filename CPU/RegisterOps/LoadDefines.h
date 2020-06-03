#ifndef STALLIONGB_LOADDEFINES_H
#define STALLIONGB_LOADDEFINES_H

#include "../CPUDefines.h"

void ldRn(CPU *r, int8_t *reg, int8_t *memory);
void ldRR(CPU *r, int8_t *x, int8_t y);
void ldRHL(CPU *r, int8_t *reg, int8_t *memory);

void ldABC(CPU *r, int8_t *memory);
void ldADE(CPU *r, int8_t *memory);
void ldAn(CPU *r, int8_t *memory);
void ldHLR(CPU *r, int8_t reg, int8_t *memory);
void ldHLn(CPU *r, int8_t *memory);
void ldAnum(CPU *r, int8_t *memory);
void ldBCA(CPU *r, int8_t *memory);
void ldDEA(CPU *r, int8_t *memory);
void ldHLA(CPU *r, int8_t *memory);
void ldnnA(CPU *r, int8_t *memory);
void ldACAddress(CPU *r, int8_t *memory);
void ldCAddressA(CPU *r, int8_t *memory);
void lddAHL(CPU *r, int8_t *memory);
void lddHLA(CPU *r, int8_t *memory);
void ldiAHL(CPU *r, int8_t *memory);
void ldiHLA(CPU *r, int8_t *memory);
void ldhnA(CPU *r, int8_t *memory);
void ldhAn(CPU *r, int8_t *memory);
void ldBCnn(CPU *r, int8_t *memory);
void ldDEnn(CPU *r, int8_t *memory);
void ldHLnn(CPU *r, int8_t *memory);
void ldSPnn(CPU *r, int8_t *memory);
void ldSPHL(CPU *r);
void ldHLSPn(CPU *r, int8_t *memory);
void ldnnSP(CPU *r, int8_t *memory);

#endif //STALLIONGB_LOADDEFINES_H
