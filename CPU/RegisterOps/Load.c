#include "../CPUDefines.h"
#include "../../Memory/MemoryDefines.h"

// 8-bit Loads
void ldRn(CPU *r, int8_t *reg, int8_t *memory) {
    int8_t argument = readByte(*r, memory, r->pc + 1);
    *reg = argument;

    r->instructionClocks += 2;
    r->pc += 2;
}

// Load between registers
void ldRR(CPU *r, int8_t *x, int8_t y) {
    *x = y;
    r->instructionClocks += 1;
    r->pc++;
}

void ldRHL(CPU *r, int8_t *reg, int8_t *memory) {
    int HL = DoubleRegister(r->h, r->l);
    *reg = readByte(*r, memory, HL);
    r->instructionClocks += 2;
    r->pc++;
}

void ldABC(CPU *r, int8_t *memory) {
    int BC = DoubleRegister(r->b, r->c);
    r->a = readByte(*r, memory, BC);
    r->instructionClocks += 2;
    r->pc++;
}

void ldADE(CPU *r, int8_t *memory) {
    int DE = DoubleRegister(r->d, r->e);
    r->a = readByte(*r, memory, DE);
    r->instructionClocks += 2;
    r->pc++;
}

void ldAn(CPU *r, int8_t *memory) {
    uint16_t address = DoubleRegister(readByte(*r, memory, r->pc + 1), readByte(*r, memory, r->pc + 2));
    int8_t argument = readByte(*r, memory, address);
    r->a = argument;
    r->instructionClocks += 4;
    r->pc += 3;
}

void ldHLR(CPU *r, int8_t reg, int8_t *memory) {
    // 70
    int HL = DoubleRegister(r->h, r->l);
    writeByte(*r, memory, HL, reg);
    r->instructionClocks += 2;
    r->pc++;
}

void ldHLn(CPU *r, int8_t *memory) {
    // 36
    int HL = DoubleRegister(r->h, r->l);
    int8_t argument = memory[r->pc + 1];
    writeByte(*r, memory, HL, argument);
    r->instructionClocks += 2;
    r->pc += 2;
}

void ldAnum(CPU *r, int8_t *memory) {
    // 3E
    int argument = readByte(*r, memory, r->pc + 1);
    r->a = argument;
    r->instructionClocks += 2;
    r->pc += 2;
}

void ldBCA(CPU *r, int8_t *memory) {
    // 02
    uint16_t address = DoubleRegister(r->b, r->c);
    writeByte(*r, memory, address, r->a);
    r->instructionClocks += 2;
    r->pc++;
}

void ldDEA(CPU *r, int8_t *memory) {
    // 12
    uint16_t address = DoubleRegister(r->d, r->e);
    writeByte(*r, memory, address, r->a);
    r->instructionClocks += 2;
    r->pc++;
}

void ldHLA(CPU *r, int8_t *memory) {
    // 77
    uint16_t address = DoubleRegister(r->h, r->l);
    writeByte(*r, memory, address, r->a);
    r->instructionClocks += 2;
    r->pc++;
}

void ldnnA(CPU *r, int8_t *memory) {
    // ea
    uint16_t address = DoubleRegister(readByte(*r, memory, r->pc + 1), readByte(*r, memory, r->pc + 2));
    writeByte(*r, memory, address, r->a);
    r->instructionClocks += 4;
    r->pc++;
}

void ldACAddress(CPU *r, int8_t *memory) {
    // F2
    uint16_t address = r->c + 0xFF00;
    r->a = readByte(*r, memory, address);
    r->instructionClocks += 2;
    r->pc++;
}

void ldCAddressA(CPU *r, int8_t *memory) {
    // E2
    uint16_t address = r->c + 0xFF00;
    writeByte(*r, memory, address, r->a);
    r->instructionClocks += 2;
    r->pc++;
}

void lddAHL(CPU *r, int8_t *memory) {
    // 3A
    uint16_t address = DoubleRegister(r->h, r->l);
    r->a = readByte(*r, memory, address);
    address--;
    r->h = (address & 0xFF00) >> 8;
    r->l = address & 0xFF;
    r->instructionClocks += 2;
    r->pc++;
}

void lddHLA(CPU *r, int8_t *memory) {
    // 32
    uint16_t address = DoubleRegister(r->h, r->l);
    writeByte(*r, memory, address, r->a);
    address--;
    r->h = address & 0xFF00 >> 8;;
    r->l = address & 0xFF;
    r->instructionClocks += 8;
    r->pc++;
}

void ldiAHL(CPU *r, int8_t *memory) {
    // 2A
    uint16_t address = DoubleRegister(r->h, r->l);
    r->a = readByte(*r, memory, address);
    address++;
    r->h = address & 0xFF00 >> 8;;
    r->l = address & 0xFF;
    r->instructionClocks += 2;
    r->pc++;
}

void ldiHLA(CPU *r, int8_t *memory) {
    // 22
    uint16_t address = DoubleRegister(r->h, r->l);
    writeByte(*r, memory, address, r->a);
    address++;
    r->h = address & 0xFF00 >> 8;;
    r->l = address & 0xFF;
    r->instructionClocks += 8;
    r->pc++;
}

void ldhnA(CPU *r, int8_t *memory) {
    // E0
    int address = 0xFF00 + readByte(*r, memory, r->pc + 1);
    writeByte(*r, memory, address, r->a);
    r->instructionClocks += 3;
    r->pc += 2;
}

void ldhAn(CPU *r, int8_t *memory) {
    // F0
    int address = 0xFF00 + readByte(*r, memory, r->pc + 1);
    r->a = readByte(*r, memory, address);
    r->instructionClocks += 3;
    r->pc += 2;
}

void ldBCnn(CPU *r, int8_t *memory) {
    // 01
    r->b = readByte(*r, memory, r->pc + 1);
    r->c = readByte(*r, memory, r->pc + 2);
    r->instructionClocks += 3;
    r->pc += 3;
}

void ldDEnn(CPU *r, int8_t *memory) {
    // 11
    r->d = readByte(*r, memory, r->pc + 1);
    r->e = readByte(*r, memory, r->pc + 2);
    r->instructionClocks += 3;
    r->pc += 3;
}

void ldHLnn(CPU *r, int8_t *memory) {
    // 21
    r->h = readByte(*r, memory, r->pc + 1);
    r->l = readByte(*r, memory, r->pc + 2);
    r->instructionClocks += 3;
    r->pc += 3;
}

void ldSPnn(CPU *r, int8_t *memory) {
    // 31
    uint16_t argument = DoubleRegister(readByte(*r, memory, r->pc + 1), readByte(*r, memory, r->pc + 2));
    r->sp = argument;
    r->instructionClocks += 3;
    r->pc += 3;
}

void ldSPHL(CPU *r) {
    // F9
    uint16_t HL = DoubleRegister(r->h, r->l);
    r->sp = HL;
    r->instructionClocks += 2;
    r->pc++;
}

void ldHLSPn(CPU *r, int8_t *memory) {
    // F8
    int result = r->sp + readByte(*r, memory, r->pc + 1);

    r->f.zero = 0;
    r->f.subtract = 0;
    if ( (r->sp & 0x0F00) + (readByte(*r, memory, r->pc + 1)) > 0xF00) {
        r->f.halfCarry = 1;
    } else {
        r->f.halfCarry = 0;
    }
    if (result > 0xFF) {
        r->f.carry = 1;
    } else {
        r->f.carry = 0;
    }
    r->instructionClocks += 3;
    r->pc += 2;
}

void ldnnSP(CPU *r, int8_t *memory) {
    // 08
    int address = DoubleRegister(readByte(*r, memory, r->pc + 1), readByte(*r, memory, r->pc + 2));
    writeByte(*r, memory, address, r->sp);
    r->instructionClocks += 5;
    r->pc += 3;
}