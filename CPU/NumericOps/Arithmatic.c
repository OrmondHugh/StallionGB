#include <stdint.h>
#include "../CPUDefines.h"
#include "../../Memory/MemoryDefines.h"

// Sets the flags in r to how they should be after an operation on a and b
void setFlagsAddition(CPU *r, int8_t a, int8_t b) {
    int result = a + b;

    // Set Zero flag
    if (result == 0) {
        r->f.zero = 1;
    } else {
        r->f.zero = 0;
    }
    // Reset subtract flag
    r->f.subtract = 0;
    // Set Half Carry flag
    if (((r->a & 0xF) + (r->b & 0xF)) > 0xF) {
        r->f.halfCarry = 1;
    } else {
        r->f.halfCarry = 0;
    }
    // Set carry flag
    if (result > 0xFF) {
        r->f.carry = 1;
    } else {
        r->f.carry = 0;
    }
}

void setFlagsSubtraction(CPU *r, int8_t a, int8_t b) {
    int result = a - b;

    if (result == 0) {
        r->f.zero = 1;
    } else {
        r->f.zero = 0;
    }
    r->f.subtract = 1;
    if ((r->a & 0xF) < (r->b & 0xF)) {
        r->f.halfCarry = 1;
    } else {
        r->f.halfCarry = 0;
    }
    if (r->a < r->b) {
        r->f.carry = 1;
    } else {
        r->f.carry = 0;
    }
}

void setFlagsAddition16bit(CPU *r, int16_t a, int16_t b) {
    int result = a + b;

    // Set Zero flag
    if (result == 0) {
        r->f.zero = 1;
    } else {
        r->f.zero = 0;
    }
    // Reset subtract flag
    r->f.subtract = 0;
    // Set Half Carry flag
    if (((r->a & 0xFFF) + (r->b & 0xF)) > 0xFFF) {
        r->f.halfCarry = 1;
    } else {
        r->f.halfCarry = 0;
    }
    // Set carry flag
    if (result > 0xFFFF) {
        r->f.carry = 1;
    } else {
        r->f.carry = 0;
    }
}

void setFlagsIncrement(CPU *r, int8_t a) {
    int result = a + 1;

    // Set Zero flag
    if (result == 0) {
        r->f.zero = 1;
    } else {
        r->f.zero = 0;
    }
    // Reset subtract flag
    r->f.subtract = 0;
    // Set Half Carry flag
    if (((r->a & 0xF) + (r->b & 0xF)) > 0xF) {
        r->f.halfCarry = 1;
    } else {
        r->f.halfCarry = 0;
    }
}

void setFlagsDecrement(CPU *r, int8_t a) {
    int result = a - 1;

    if (result == 0) {
        r->f.zero = 1;
    } else {
        r->f.zero = 0;
    }
    r->f.subtract = 1;
    if ((r->a & 0xF) < (r->b & 0xF)) {
        r->f.halfCarry = 1;
    } else {
        r->f.halfCarry = 0;
    }
}

// 8-bit addition, without taking the previous carry into account

/**
 * Add the a specified register to the value in the accumulator, storing the result in the accumulator register
 */
void addAR(CPU *r, int8_t reg) {
    int result = r->a + reg;

    setFlagsAddition(r, r->a, reg);

    r->a = result;
    r->instructionClocks += 1;
    r->pc++;
}

void addAHL(CPU *r, int8_t *memory){
    // 86
    int HL = DoubleRegister(r->h, r->l);
    int result = r->a + readByte(*r, memory, HL);

    setFlagsAddition(r, r->a, readByte(*r, memory, HL));

    r->a = result;
    r->instructionClocks += 2;
    r->pc++;
}

void addAn (CPU *r, int8_t *memory) {
    // C6
    int8_t argument = readByte(*r, memory, r->pc + 1);
    int result = r->a + argument;

    setFlagsAddition(r, r->a, argument);

    r->a = result;
    r->instructionClocks += 2;
    r->pc += 2;
}

// 8-bit addition with a carry
void adcAR(CPU *r, int8_t reg) {
    int result = r->a + reg + r->f.carry;

    setFlagsAddition(r, r->a, reg + r->f.carry);

    r->a = result;
    r->instructionClocks += 1;
    r->pc++;
}

void adcHL(CPU *r, int8_t * memory) {
    // 8E
    int HL = DoubleRegister(r->h, r->l);
    int result = r->a + readByte(*r, memory, HL) + r->f.carry;

    setFlagsAddition(r, r->a, readByte(*r, memory, HL) + r->f.carry);

    r->a = result;
    r->instructionClocks += 2;
    r->pc++;
}

void adcAn(CPU *r, int8_t *memory) {
    // CE
    int8_t argument = readByte(*r, memory, r->pc + 1);
    int result = r->a + argument + r->f.carry;

    setFlagsAddition(r, r->a, argument + r->f.carry);

    r->a = result;
    r->instructionClocks += 2;
    r->pc += 2;
}

// 8-bit subtraction without a carry

void subAR(CPU *r, int8_t reg) {
    int result = r->a - reg;

    setFlagsSubtraction(r, r->a, reg);

    r->a = result;
    r->instructionClocks += 1;
    r->pc++;
}

void subAA(CPU *r) {
    // 97
    // This operation always returns 0
    r->f.zero = 1;
    r->f.subtract = 1;
    r->f.halfCarry = 0;
    r->f.carry = 0;

    r->a = 0;
    r->instructionClocks += 1;
    r->pc++;
}

void subAHL(CPU *r, int8_t *memory) {
    // 96
    int HL = DoubleRegister(r->h, r->l);
    int result = r->a - readByte(*r, memory, HL);

    setFlagsSubtraction(r, r->a, readByte(*r, memory, HL));

    r->a = result;
    r->instructionClocks += 2;
    r->pc++;
}

void subAn(CPU *r, int8_t *memory) {
    // D6
    int8_t argument = readByte(*r, memory, r->pc + 1);
    int result = r->a - argument;

    setFlagsSubtraction(r, r->a, r->d);

    r->a = result;
    r->instructionClocks += 2;
    r->pc += 2;
}

// Subtract with a carry
void sbcAR(CPU *r, int8_t reg) {
    int8_t argument = reg + r->f.carry;
    int8_t result = r->a - argument;

    setFlagsSubtraction(r, r->a, argument);

    r->a = result;
    r->instructionClocks += 1;
    r->pc++;
}

void sbcAHL(CPU *r, int8_t *memory) {
    // 98
    int HL = DoubleRegister(r->h, r->l);
    int8_t argument = readByte(*r, memory, HL) + r->f.carry;
    int result = r->a - argument;

    setFlagsSubtraction(r, r->a, argument);

    r->a = result;
    r->instructionClocks += 2;
    r->pc++;
}

void sbcAn(CPU *r, int8_t *memory) {
    // DE
    int8_t argument = readByte(*r, memory, r->pc + 1) + r->f.carry;
    int result = r->a - argument;

    setFlagsSubtraction(r, r->a, r->d);

    r->a = result;
    r->instructionClocks += 2;
    r->pc += 2;
}

// Compare
void cpR(CPU *r, int8_t *reg) {
    setFlagsSubtraction(r, r->a, *reg);

    r->instructionClocks += 1;
    r->pc++;
}

void cpHL(CPU *r, int8_t *memory) {
    // BE
    int8_t argument = readByte(*r, memory, DoubleRegister(r->h, r->l));
    setFlagsSubtraction(r, r->a, argument);

    r->instructionClocks += 2;
    r->pc++;
}

void cpn(CPU *r, int8_t *memory) {
    // FE
    int8_t argument = readByte(*r, memory, r->pc + 1);
    setFlagsSubtraction(r, r->a, argument);

    r->instructionClocks += 2;
    r->pc += 2;
}

// Increment/Decrement registers
void incR(CPU *r, int8_t *reg) {
    int result = *reg + 1;
    setFlagsIncrement(r, *reg);

    *reg = result;
    r->instructionClocks += 1;
    r->pc++;
}

void incHL(CPU *r, int8_t *memory) {
    // 34
    int8_t argument = readByte(*r, memory, DoubleRegister(r->h, r->l));
    int result = argument + 1;

    setFlagsIncrement(r, argument);

    writeByte(*r, memory, DoubleRegister(r->h, r->l), result);
    r->instructionClocks += 3;
    r->pc++;
}

void decR(CPU *r, int8_t *reg) {
    //printf("C: %d\n", r->c);
    //printf("D: %d\n", r->d);
    //printf("B: %d\n", r->b);
    int result = *reg - 1;

    setFlagsDecrement(r, *reg);

    *reg = result;
    r->instructionClocks += 1;
    r->pc++;
}

void decHL(CPU *r, int8_t *memory) {
    // 35
    int8_t argument = readByte(*r, memory, DoubleRegister(r->h, r->l));
    int8_t result = argument - 1;

    setFlagsDecrement(r, argument);

    writeByte(*r, memory, DoubleRegister(r->h, r->l), result);
    r->instructionClocks += 3;
    r->pc++;
}

// 16 bit Arithmetic
void addHLBC16bit(CPU *r) {
    // 09
    int16_t HL = DoubleRegister(r->h, r->l);
    int16_t argument = DoubleRegister(r->b, r->c);
    int result = HL + argument;

    setFlagsAddition16bit(r, HL, argument);

    r->h = (result & 0xFF00) >> 8;
    r->l = result & 0xFF;
    r->instructionClocks += 2;
    r->pc++;
}

void addHLDE16bit(CPU *r) {
    // 19
    int16_t HL = DoubleRegister(r->h, r->l);
    int16_t argument = DoubleRegister(r->d, r->e);
    int result = HL + argument;

    setFlagsAddition16bit(r, HL, argument);

    r->h = (result & 0xFF00) >> 8;
    r->l = result & 0xFF;
    r->instructionClocks += 2;
    r->pc++;
}

void addHLHL16bit(CPU *r) {
    // 29
    int16_t HL = DoubleRegister(r->h, r->l);
    int result = HL + HL;

    setFlagsAddition16bit(r, HL, HL);

    r->h = (result & 0xFF00) >> 8;
    r->l = result & 0xFF;
    r->instructionClocks += 2;
    r->pc++;
}

void addHLSP16bit(CPU *r) {
    // 39
    int16_t HL = DoubleRegister(r->h, r->l);
    int result = HL + r->sp;

    setFlagsAddition16bit(r, HL, r->sp);

    r->h = (result & 0xFF00) >> 8;
    r->l = result & 0xFF;
    r->instructionClocks += 2;
    r->pc++;
}

void addSPn(CPU *r, int8_t *memory) {
    // E8
    int16_t argument = readByte(*r, memory, r->pc + 1);
    int result = r->sp + argument;

    setFlagsAddition16bit(r, r->sp, argument);

    r->sp = result;
    r->instructionClocks += 4;
    r->pc += 2;
}

// 16-bit increment
void incBC(CPU *r) {
    // 03
    uint16_t reg = DoubleRegister(r->b, r->c);
    reg -= 1;

    r->b = (reg & 0xFF00) >> 8;
    r->c = reg & 0xFF;
    r->instructionClocks += 2;
    r->pc++;
}

void incDE(CPU *r) {
    // 13
    uint16_t reg = DoubleRegister(r->d, r->e);
    reg -= 1;

    r->d = (reg & 0xFF00) >> 8;
    r->e = reg & 0xFF;
    r->instructionClocks += 2;
    r->pc++;
}

void incHLreg(CPU *r) {
    // 23
    uint16_t reg = DoubleRegister(r->h, r->l);
    reg -= 1;

    r->h = (reg & 0xFF00) >> 8;
    r->l = reg & 0xFF;
    r->instructionClocks += 2;
    r->pc++;
}

void incSP(CPU *r) {
    // 33
    r->sp -= 1;
    r->instructionClocks += 2;
    r->pc++;
}

// 16-bit decrement
void decBC(CPU *r) {
    // 0B
    uint16_t reg = DoubleRegister(r->b, r->c);
    reg -= 1;

    r->b = (reg & 0xFF00) >> 8;
    r->c = reg & 0xFF;
    r->instructionClocks += 2;
    r->pc++;
}

void decDE(CPU *r) {
    // 1B
    uint16_t reg = DoubleRegister(r->d, r->e);
    reg -= 1;

    r->d = (reg & 0xFF00) >> 8;
    r->e = reg & 0xFF;
    r->instructionClocks += 2;
    r->pc++;
}

void decHLreg(CPU *r) {
    // 2B
    uint16_t reg = DoubleRegister(r->h, r->l);
    reg -= 1;

    r->h = (reg & 0xFF00) >> 8;
    r->l = reg & 0xFF;
    r->instructionClocks += 2;
    r->pc++;
}

void decSP(CPU *r) {
    // 3B
    r->sp -= 1;
    r->instructionClocks += 2;
    r->pc++;
}
