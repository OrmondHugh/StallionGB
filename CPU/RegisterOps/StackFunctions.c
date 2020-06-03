#include "../../Memory/MemoryDefines.h"
#include "../CPUDefines.h"

void pushAF(CPU *r, int8_t *memory) {
    // F5
    writeByte(*r, memory, r->sp - 1, getF(r->f));
    writeByte(*r, memory, r->sp - 2, r->a);
    r->sp -= 2;
    r->instructionClocks += 4;
    r->pc++;
}

void pushBC(CPU *r, int8_t *memory) {
    // C5
    writeByte(*r, memory, r->sp - 1, r->c);
    writeByte(*r, memory, r->sp - 2, r->b);
    r->sp -= 2;
    r->instructionClocks += 4;
    r->pc++;
}

void pushDE(CPU *r, int8_t *memory) {
    // D5
    writeByte(*r, memory, r->sp - 1, r->e);
    writeByte(*r, memory, r->sp - 2, r->d);
    r->sp -= 2;
    r->instructionClocks += 4;
    r->pc++;
}

void pushHL(CPU *r, int8_t *memory) {
    // E5
    writeByte(*r, memory, r->sp - 1, r->l);
    writeByte(*r, memory, r->sp - 2, r->h);
    r->sp -= 2;
    r->instructionClocks += 4;
    r->pc++;
}

void popAF(CPU *r, int8_t *memory) {
    // F1
    r->a = readByte(*r, memory, r->sp);
    int8_t f = readByte(*r, memory, r->sp + 1);

    // Construct a corresponding flag struct from the register value
    Flag flag = {0,0,0,0};
    if (f & 0b10000000) {
        flag.zero = 1;
    }
    if (f & 0b1000000) {
        flag.subtract = 1;
    }
    if (f & 0b100000) {
        flag.halfCarry = 1;
    }
    if (f & 0b10000) {
        flag.carry = 1;
    }

    r->sp += 2;
    r->f = flag;
    r->instructionClocks += 3;
    r->pc++;
}

void popBC(CPU *r, int8_t *memory) {
    // C1
    r->b = readByte(*r, memory, r->sp);
    r->c = readByte(*r, memory, r->sp + 1);

    r->sp += 2;
    r->instructionClocks += 3;
    r->pc++;
}

void popDE(CPU *r, int8_t *memory) {
    // D1
    r->d = readByte(*r, memory, r->sp);
    r->e = readByte(*r, memory, r->sp + 1);

    r->sp += 2;
    r->instructionClocks += 3;
    r->pc++;
}

void popHL(CPU *r, int8_t *memory) {
    // E1
    r->h = readByte(*r, memory, r->sp);
    r->l = readByte(*r, memory, r->sp + 1);

    r->sp += 2;
    r->instructionClocks += 3;
    r->pc++;
}

// Calls
void call(CPU *r, int8_t *memory) {
    // CD
    // Push next instruction to the stack
    int8_t b = (r->pc + 3) & 0xFF;
    int8_t a = ( (r->pc + 3) & 0xFF00 ) >> 8;
    writeByte(*r, memory, r->sp - 1, b);
    writeByte(*r, memory, r->sp - 2, a);
    r->sp -= 2;

    // Jump to the specified argument
    int x = readByte(*r, memory, r->pc + 1);
    int y = readByte(*r, memory, r->pc + 2);
    uint16_t argument = (y << 8) | (x & 0xFF);
    r->instructionClocks += 3;
    r->pc = argument;
}

void callnz(CPU *r, int8_t *memory) {
    // C4
    if (r->f.subtract == 0) {
        int b = (r->pc + 3) & 0xFF;
        int a = ((r->pc + 3) & 0xFF00) >> 8;
        writeByte(*r, memory, r->sp - 1, b);
        writeByte(*r, memory, r->sp - 2, a);
        r->sp -= 2;

        int x = readByte(*r, memory, r->pc + 1);
        int y = readByte(*r, memory, r->pc + 2);
        uint16_t argument = (y << 8) | (x & 0xFF);
        r->pc = argument;
    } else {
        r->pc += 3;
    }
    r->instructionClocks += 2;
}

void callz(CPU *r, int8_t *memory) {
    // CC
    if (r->f.subtract != 0) {
        int b = (r->pc + 3) & 0xFF;
        int a = ((r->pc + 3) & 0xFF00) >> 8;
        writeByte(*r, memory, r->sp - 1, b);
        writeByte(*r, memory, r->sp - 2, a);
        r->sp -= 2;

        int x = readByte(*r, memory, r->pc + 1);
        int y = readByte(*r, memory, r->pc + 2);
        uint16_t argument = (y << 8) | (x & 0xFF);
        r->pc = argument;
    } else {
        r->pc += 3;
    }
    r->instructionClocks += 2;
}

void callnc(CPU *r, int8_t *memory) {
    // D4
    if (r->f.carry == 0) {
        int b = (r->pc + 3) & 0xFF;
        int a = ((r->pc + 3) & 0xFF00) >> 8;
        writeByte(*r, memory, r->sp - 1, b);
        writeByte(*r, memory, r->sp - 2, a);
        r->sp -= 2;

        int x = readByte(*r, memory, r->pc + 1);
        int y = readByte(*r, memory, r->pc + 2);
        uint16_t argument = (y << 8) | (x & 0xFF);
        r->pc = argument;
    } else {
        r->pc += 3;
    }
    r->instructionClocks += 2;
}

void callc(CPU *r, int8_t *memory) {
    // DC
    if (r->f.carry != 0) {
        int b = (r->pc + 3) & 0xFF;
        int a = ((r->pc + 3) & 0xFF00) >> 8;
        writeByte(*r, memory, r->sp - 1, b);
        writeByte(*r, memory, r->sp - 2, a);
        r->sp -= 2;

        int x = readByte(*r, memory, r->pc + 1);
        int y = readByte(*r, memory, r->pc + 2);
        uint16_t argument = (y << 8) | (x & 0xFF);
        r->pc = argument;
    } else {
        r->pc += 3;
    }
    r->instructionClocks += 2;
}

// Restarts
void rstn(CPU *r, int8_t *memory, int16_t argument) {
    int b = r->pc & 0xFF;
    int a = (r->pc & 0xFF00) >> 8;
    writeByte(*r, memory, r->sp - 1, b);
    writeByte(*r, memory, r->sp - 2, a);
    r->sp -= 2;

    r->instructionClocks += 8;
    r->pc = argument;
}

// Returns
void ret(CPU *r, int8_t *memory) {
    // C9
    int8_t x = readByte(*r, memory, r->sp);
    int8_t y = readByte(*r, memory, r->sp + 1);
    r->sp += 2;

    int16_t address = (x << 8) | y;

    r->instructionClocks += 2;
    r->pc = address;
}

void retnz(CPU *r, int8_t *memory) {
    // C0
    if (r->f.subtract == 0) {
        ret(r, memory);
    } else {
        r->pc++;
    }
    r->instructionClocks += 2;
}

void retz(CPU *r, int8_t *memory) {
    // C8
    if (r->f.subtract != 0) {
        ret(r, memory);
    } else {
        r->pc++;
    }
    r->instructionClocks += 2;
}

void retnc(CPU *r, int8_t *memory) {
    // D0
    if (r->f.carry == 0) {
        ret(r, memory);
    } else {
        r->pc++;
    }
    r->instructionClocks += 2;
}

void retc(CPU *r, int8_t *memory) {
    // D8
    if (r->f.carry != 0) {
        ret(r, memory);
    } else {
        r->pc++;
    }
    r->instructionClocks += 2;
}

void reti(CPU *r, int8_t *memory) {
    // D9
    int8_t x = readByte(*r, memory, r->sp);
    int8_t y = readByte(*r, memory, r->sp + 1);
    r->sp += 2;

    int16_t address = (x << 8) | y;

    r->interruptsEnabled = 1;
    r->instructionClocks += 2;
    r->pc = address;
}