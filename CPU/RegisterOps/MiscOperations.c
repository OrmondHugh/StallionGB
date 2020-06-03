#include "MiscOpDefines.h"
#include "../../Memory/MemoryDefines.h"

// Uncatagorised ops
void DAA(CPU *r) {
    // 27
    int8_t nibbleOne = (r->a & 0xF0) >> 4;
    int8_t nibbleTwo = r->a & 0xF;

    if (r->a == 0) {
        r->f.zero = 1;
    } else {
        r->f.zero = 0;
    }

    if (nibbleTwo > 9 || r->f.halfCarry) {
        r->a += 0x6;
    }
    if (nibbleOne > 9 || r->f.carry) {
        if (r->a + 0x60 > 0xFF) {
            r->f.carry = 1;
        }
        r->a += 0x60;
    } else {
        r->f.carry = 0;
    }

    r->instructionClocks += 1;
    r->pc++;
}

void CPL(CPU *r) {
    // 2F
    r->a ^= r->a;

    r->f.subtract = 0;
    r->f.halfCarry = 0;

    r->instructionClocks += 1;
    r->pc++;
}

void CCF(CPU *r) {
    // 3F
    r->f.carry ^= r->f.carry;

    r->f.subtract = 0;
    r->f.halfCarry = 0;

    r->instructionClocks += 1;
    r->pc++;
}

void SCF(CPU *r) {
    // 37
    r->f.carry = 1;

    r->f.subtract = 0;
    r->f.halfCarry = 0;

    r->instructionClocks += 1;
    r->pc++;
}

// Jumps
void jp(CPU *r, int8_t *memory) {
    // C3
    int a = readByte(*r, memory, r->pc + 1);
    int b = readByte(*r, memory, r->pc + 2);
    uint16_t argument = (b << 8) | a;

    r->instructionClocks += 3;
    r->pc = argument;
}

void jpnz(CPU *r, int8_t *memory) {
    // C2
    if (r->f.subtract == 0) {
        jp(r, memory);
    } else {
        r->pc += 3;
    }

    r->instructionClocks += 3;
}

void jpz(CPU *r, int8_t *memory) {
    // CA
    if (r->f.subtract != 0) {
        jp(r, memory);
    } else {
        r->pc += 3;
    }
    r->instructionClocks += 3;
}

void jpnc(CPU *r, int8_t *memory) {
    // D2
    if (r->f.carry == 0) {
        jp(r, memory);
    } else {
        r->pc += 3;
    }

    r->instructionClocks += 3;
}

void jpc(CPU *r, int8_t *memory) {
    // DA
    if (r->f.carry != 0) {
        jp(r, memory);
    } else {
        r->pc += 3;
    }

    r->instructionClocks += 3;
}

void jphl(CPU *r, int8_t *memory) {
    // E9
    int16_t HL = DoubleRegister(r->h, r->l);

    r->instructionClocks += 1;
    r->pc = HL;
}

void jrn(CPU *r, int8_t *memory) {
    // 18
    int8_t argument = readByte(*r, memory, r->pc + 1);

    r->instructionClocks += 2;
    r->pc += 2 + argument;
}

void jrnzn(CPU *r, int8_t *memory) {
    // 20
    if (r->f.zero == 0) {
        int8_t argument = readByte(*r, memory, r->pc + 1);
        r->pc += argument;
    }
    r->instructionClocks += 2;
    r->pc += 2;
}

void jrzn(CPU *r, int8_t *memory) {
    // 28
    if (r->f.zero != 0) {
        int8_t argument = readByte(*r, memory, r->pc + 1);
        r->pc += argument;
    }
    r->instructionClocks += 2;
    r->pc += 2;
}

void jrncn(CPU *r, int8_t *memory) {
    // 30
    if (r->f.carry == 0) {
        int8_t argument = readByte(*r, memory, r->pc + 1);
        r->pc += argument;
    }
    r->instructionClocks += 2;
    r->pc += 2;
}

void jrcn(CPU *r, int8_t *memory) {
    // 38
    if (r->f.carry != 0) {
        int8_t argument = readByte(*r, memory, r->pc + 1);
        r->pc += argument;
    }
    r->instructionClocks += 2;
    r->pc += 2;
}

// Interrupt master enable/disable
void DI(CPU *r) {
    // F3
    r->interruptsEnabled = 0;
    r->instructionClocks += 1;
    r->pc++;
}

void EI(CPU *r) {
    // FB
    r->interruptsEnabled = 1;
    r->instructionClocks += 1;
    r->pc++;
}