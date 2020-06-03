#include "../CPUDefines.h"
#include "BitwiseDefines.h"
#include "../../Memory/MemoryDefines.h"

// AND operations
void andA(CPU *r){
    // A7
    r->f.zero = r->a == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 1;
    r->f.carry = 0;

    r->instructionClocks += 1;
    r->pc++;
}

void andr(CPU *r, int8_t x){
    int8_t result = r->a & x;

    r->f.zero = result ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 1;
    r->f.carry = 0;

    r->a = result;
    r->instructionClocks += 1;
    r->pc++;
}
void andHL(CPU *r, int8_t *memory){
    // A6
    int8_t argument = readByte(*r, memory, DoubleRegister(r->h, r->l));
    int8_t result = r->a & argument;

    r->f.zero = result ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 1;
    r->f.carry = 0;

    r->a = result;
    r->instructionClocks += 2;
    r->pc++;
}

void andn(CPU *r, int8_t *memory){
    // E6
    int8_t argument = readByte(*r, memory, r->pc + 1);
    int8_t result = r->a & argument;

    r->f.zero = result ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 1;
    r->f.carry = 0;

    r->a = result;
    r->instructionClocks += 2;
    r->pc++;
}

// OR operations
void orr(CPU *r, int8_t x) {
    int8_t result = r->a | x;
    r->f.zero = result == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = 0;

    r->a = result;
    r->instructionClocks += 1;
    r->pc++;
}

void orHL(CPU *r, int8_t *memory) {
    // B6
    int8_t argument = readByte(*r, memory, DoubleRegister(r->h, r->l));
    int8_t result = r->a | argument;
    r->f.zero = result == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = 0;

    r->a = result;
    r->instructionClocks += 2;
    r->pc++;
}

void orn(CPU *r, int8_t *memory) {
    // B6
    int8_t argument = readByte(*r, memory, r->pc + 1);
    int8_t result = r->a | argument;
    r->f.zero = result == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = 0;

    r->a = result;
    r->instructionClocks += 2;
    r->pc++;
}

// XOR operations
void xorA(CPU *r) {
    // B7
    r->f.zero = 1;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = 0;

    r->a = 0;
    r->instructionClocks += 1;
    r->pc++;
}

void xorr(CPU *r, int8_t x) {
    int8_t result = r->a ^ x;
    r->f.zero = result == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = 0;

    r->a = result;
    r->instructionClocks += 1;
    r->pc++;
}

void xorHL(CPU *r, int8_t *memory) {
    // B6
    int8_t argument = readByte(*r, memory, DoubleRegister(r->h, r->l));
    int8_t result = r->a ^ argument;
    r->f.zero = result == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = 0;

    r->a = result;
    r->instructionClocks += 2;
    r->pc++;
}

void xorn(CPU *r, int8_t *memory) {
    // B6
    int8_t argument = readByte(*r, memory, r->pc + 1);
    int8_t result = r->a ^ argument;
    r->f.zero = result == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = 0;

    r->a = result;
    r->instructionClocks += 2;
    r->pc++;
}

// Swaps
void swapR(CPU *r, int8_t *reg) {
    int8_t argument = *reg;
    int8_t nibbleOne = (argument & 0xF0) >> 4;
    int8_t nibbleTwo = (argument & 0xF) << 4;

    int8_t swapped = nibbleOne | nibbleTwo;

    r->f.zero = swapped == 0 ? 1 : 0;
    r->f.carry = 0;
    r->f.halfCarry = 0;
    r->f.subtract = 0;

    r->CB = 0;

    *reg = swapped;
    r->instructionClocks += 2;
    r->pc++;
}

void swapHL(CPU *r, int8_t *memory) {
    // CB 36
    int16_t HL = DoubleRegister(r->h, r->l);
    int8_t argument = readByte(*r, memory, HL);
    int8_t nibbleOne = (argument & 0xF0) >> 4;
    int8_t nibbleTwo = (argument & 0xF) << 4;

    int8_t swapped = nibbleOne | nibbleTwo;

    r->f.zero = swapped == 0 ? 1 : 0;
    r->f.carry = 0;
    r->f.halfCarry = 0;
    r->f.subtract = 0;

    r->CB = 0;

    r->b = swapped;
    r->instructionClocks += 4;
    r->pc++;
}

// Rotations
void rln(CPU *r, int8_t *reg) {
    int result = (*reg << 1) | r->f.carry;

    r->f.zero = result & 0xFF ? 0 : 1;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = r->a >> 7;

    *reg = result;
    r->instructionClocks += 1;
    r->pc++;
    r->CB = 0;
}

void rlcn(CPU *r, int8_t *reg) {
    int result = (*reg << 1) | (*reg >> 7);

    r->f.zero = result & 0xFF ? 0 : 1;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = *reg >> 7;

    *reg = result;
    r->pc++;
    r->instructionClocks += 2;
    r->CB = 0;
}

void rlchl(CPU *r, int8_t *memory) {
    // CB 06
    int HL = DoubleRegister(r->h, r->l);
    int argument = readByte(*r, memory, HL);
    int result = (argument << 1) | (argument >> 7);

    r->f.zero = result & 0xFF ? 0 : 1;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = argument >> 7;

    writeByte(*r, memory, HL, result);
    r->pc++;
    r->instructionClocks += 4;
    r->CB = 0;
}

void rlhl(CPU *r, int8_t *memory) {
    // CB 06
    int HL = DoubleRegister(r->h, r->l);
    int argument = readByte(*r, memory, HL);
    int result = (argument << 1) | (r->f.carry);

    r->f.zero = result & 0xFF ? 0 : 1;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = argument >> 7;

    writeByte(*r, memory, HL, result);
    r->pc++;
    r->instructionClocks += 4;
    r->CB = 0;
}

void rrcn(CPU *r, int8_t *reg) {
    int result = ((*reg & 1) << 7) | (*reg >> 1);

    r->f.zero = result == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = *reg & 1;

    *reg = result;
    r->pc++;
    r->instructionClocks += 2;
    r->CB = 0;
}

void rrcHL(CPU *r, int8_t *memory) {
    int HL = DoubleRegister(r->h, r->l);
    int8_t reg = readByte(*r, memory, HL);
    int result = ((reg & 1) << 7) | (reg >> 1);

    r->f.zero = result == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = reg & 1;

    writeByte(*r, memory, HL, result);
    r->pc++;
    r->instructionClocks += 4;
    r->CB = 0;
}

void rrn(CPU *r, int8_t *reg) {
    int result = ((r->f.carry) << 7) | (*reg >> 1);

    r->f.zero = result == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = *reg & 1;

    *reg = result;
    r->pc++;
    r->instructionClocks += 2;
    r->CB = 0;
}

void rrHL(CPU *r, int8_t *memory) {
    int HL = DoubleRegister(r->h, r->l);
    int8_t reg = readByte(*r, memory, HL);
    int result = ((r->f.carry) << 7) | (reg >> 1);

    r->f.zero = result == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;
    r->f.carry = reg & 1;

    writeByte(*r, memory, HL, result);
    r->pc++;
    r->instructionClocks += 4;
    r->CB = 0;
}

// Shifts
void sla(CPU *r, int8_t *reg) {
    r->f.carry = *reg & 0b10000000 ? 1 : 0;

    *reg <<= 1;
    r->f.zero = *reg == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;

    r->pc++;
    r->instructionClocks += 2;
    r->CB = 0;
}

void slaHL(CPU *r, int8_t *memory) {
    // CB 26
    int HL = DoubleRegister(r->h, r->l);
    int8_t reg = readByte(*r, memory, HL);
    r->f.carry = reg & 0b10000000 ? 1 : 0;

    reg <<= 1;
    r->f.zero = reg == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;

    writeByte(*r, memory, HL, reg);
    r->pc++;
    r->instructionClocks += 4;
    r->CB = 0;
}


void sran(CPU *r, int8_t *reg) {
    r->f.carry = *reg & 1 ? 1 : 0;

    int8_t oldMSB = *reg & 0b10000000;
    *reg >>= 1;
    *reg |= oldMSB;

    r->f.zero = *reg == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;

    r->pc++;
    r->instructionClocks += 2;
    r->CB = 0;
}

void sraHL(CPU *r, int8_t *memory) {
    // CB 2E
    int HL = DoubleRegister(r->h, r->l);
    int8_t reg = readByte(*r, memory, HL);
    r->f.carry = reg & 1 ? 1 : 0;

    int8_t oldMSB = reg & 0b10000000;
    reg >>= 1;
    reg |= oldMSB;

    r->f.zero = reg == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;

    writeByte(*r, memory, HL, reg);
    r->pc++;
    r->instructionClocks += 4;
    r->CB = 0;
}

void srl(CPU *r, int8_t *reg) {
    r->f.carry = *reg & 1 ? 1 : 0;

    *reg >>= 1;
    *reg &= 0b01111111;

    r->f.zero = *reg == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;

    r->pc++;
    r->instructionClocks += 2;
    r->CB = 0;
}

void srlHL(CPU *r, int8_t *memory) {
    // CN 3E
    int HL = DoubleRegister(r->h, r->l);
    int8_t reg = readByte(*r, memory, HL);
    r->f.carry = reg & 1 ? 1 : 0;

    reg >>= 1;
    reg &= 0b01111111;

    r->f.zero = reg == 0 ? 1 : 0;
    r->f.subtract = 0;
    r->f.halfCarry = 0;

    writeByte(*r, memory, HL, reg);
    r->pc++;
    r->instructionClocks += 4;
    r->CB = 0;
}

// Bit ops
/**
 * Test a bit in a register
 * reg: The register to be checked
 * bit: The bit of the register being tested (LSB - 0, MSB - 7)
 */
void bitn(CPU *r, int8_t reg, int8_t bit) {
    int8_t tester = 1 << bit;
    int8_t result = reg & tester;

    r->f.zero = result ? 0 : 1;

    r->f.subtract = 0;
    r->f.halfCarry = 1;

    r->pc++;
    r->instructionClocks += 2;
    r->CB = 0;
}

void bitHL(CPU *r, int8_t *memory, int8_t bit) {
    uint16_t HL = DoubleRegister(r->h, r->l);
    int8_t reg = readByte(*r, memory, HL);

    int8_t tester = 1 << bit;
    int8_t result = reg & tester;

    if (result) {
        r->f.zero = 0;
    } else {
        r->f.zero = 1;
    }

    r->f.subtract = 0;
    r->f.halfCarry = 1;

    r->pc++;
    r->instructionClocks += 4;
    r->CB = 0;
}

void setn(CPU *r, int8_t *reg, int8_t bit) {
    int8_t tester = 1 << bit;
    *reg |= tester;

    r->pc++;
    r->instructionClocks += 2;
    r->CB = 0;
}

void setHL(CPU *r, int8_t *memory, int8_t bit) {
    uint16_t HL = DoubleRegister(r->h, r->l);
    int8_t reg = readByte(*r, memory, HL);

    int8_t tester = 1 << bit;
    int8_t result = reg | tester;
    writeByte(*r, memory, HL, result);

    r->pc++;
    r->instructionClocks += 3;
    r->CB = 0;
}

void resn(CPU *r, int8_t *reg, int8_t bit) {
    int8_t tester = 0xFF ^ (1 << bit);;
    *reg &= tester;

    r->pc++;
    r->instructionClocks += 2;
    r->CB = 0;
}

void resHL(CPU *r, int8_t *memory, int8_t bit) {
    uint16_t HL = DoubleRegister(r->h, r->l);
    int8_t reg = readByte(*r, memory, HL);

    int8_t tester = 0xFF ^ (1 << bit);
    int8_t result = reg & tester;
    writeByte(*r, memory, HL, result);

    r->pc++;
    r->instructionClocks += 4;
    r->CB = 0;
}
