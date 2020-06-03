#include <stdint.h>
#include "CPUDefines.h"
#include "RegisterOps/LoadDefines.h"
#include "NumericOps/ArithmaticDefines.h"
#include "RegisterOps/MiscOpDefines.h"
#include "RegisterOps/StackDefines.h"
#include "NumericOps/BitwiseDefines.h"

// Finds the relevant function for the opcode and executes the function
void DecodeOpcode(CPU *cpu, int8_t *memory, int8_t op) {

    int8_t nibbleOne = (op & 0xF0) >> 4;
    int8_t nibbleTwo = op & 0xF;

    switch (nibbleOne) {
        case(0x0):
            switch(nibbleTwo) {
                case(0x0):
                    if (cpu->CB) {
                        rlcn(cpu, &cpu->b);
                    } else {
                        cpu->instructionClocks += 1;
                        cpu->pc++;
                    }
                    break;
                case(0x1):
                    cpu->CB ? rlcn(cpu, &cpu->c) : ldBCnn(cpu, memory);
                    break;
                case(0x2):
                    cpu->CB ? rlcn(cpu, &cpu->d) : ldBCA(cpu, memory);
                    break;
                case(0x3):
                    cpu->CB ? rlcn(cpu, &cpu->e) : incBC(cpu);
                    break;
                case(0x4):
                    cpu->CB ? rlcn(cpu, &cpu->h) : incR(cpu, &cpu->b);
                    break;
                case(0x5):
                    cpu->CB ? rlcn(cpu, &cpu->l) : decR(cpu, &cpu->b);
                    break;
                case(0x6):
                    cpu->CB ? rlchl(cpu, memory) : ldRn(cpu, &cpu->b,memory);
                    break;
                case(0x7):
                    rlcn(cpu, &cpu->a);
                    break;
                case(0x8):
                    cpu->CB ? rrcn(cpu, &cpu->b) : ldnnSP(cpu, memory);
                    break;
                case(0x9):
                    cpu->CB ? rrcn(cpu, &cpu->c) : addHLBC16bit(cpu);
                    break;
                case(0xA):
                    cpu->CB ? rrcn(cpu, &cpu->d) : ldABC(cpu, memory);
                    break;
                case(0xB):
                    cpu->CB ? rrcn(cpu, &cpu->e) : decBC(cpu);
                    break;
                case(0xC):
                    cpu->CB ? rrcn(cpu, &cpu->h) : incR(cpu, &cpu->c);
                    break;
                case(0xD):
                    cpu->CB ? rrcn(cpu, &cpu->l) : decR(cpu, &cpu->c);
                    break;
                case(0xE):
                    cpu->CB ? rrcHL(cpu, memory) : ldRn(cpu, &cpu->c,memory);
                    break;
                case(0xF):
                    rrcn(cpu, &cpu->a);
                    break;
            }
            break;
        case(0x1):
            switch(nibbleTwo) {
                case(0x0):
                    rln(cpu, &cpu->b); // STOP
                    break;
                case(0x1):
                    cpu->CB ? rln(cpu, &cpu->c) : ldDEnn(cpu, memory);
                    break;
                case(0x2):
                    cpu->CB ? rln(cpu, &cpu->d) : ldDEA(cpu, memory);
                    break;
                case(0x3):
                    cpu->CB ? rln(cpu, &cpu->e) : incDE(cpu);
                    break;
                case(0x4):
                    cpu->CB ? rln(cpu, &cpu->h) : incR(cpu, &cpu->d);
                    break;
                case(0x5):
                    cpu->CB ? rln(cpu, &cpu->l) : decR(cpu, &cpu->d);
                    break;
                case(0x6):
                    cpu->CB ? rlhl(cpu, memory) : ldRn(cpu, &cpu->d,memory);
					break;	// ha
                case(0x7):
                    rln(cpu, &cpu->a);
                    break;
                case(0x8):
                    cpu->CB ? rrn(cpu, &cpu->b) : jrn(cpu, memory);
                    break;
                case(0x9):
                    cpu->CB ? rrn(cpu, &cpu->c) : addHLDE16bit(cpu);
                    break;
                case(0xA):
                    cpu->CB ? rrn(cpu, &cpu->d) : ldADE(cpu, memory);
                    break;
                case(0xB):
                    cpu->CB ? rrn(cpu, &cpu->e) : decDE(cpu);
                    break;
                case(0xC):
                    cpu->CB ? rrn(cpu, &cpu->h) : incR(cpu, &cpu->e);
                    break;
                case(0xD):
                    cpu->CB ? rrn(cpu, &cpu->l) : decR(cpu, &cpu->e);
                    break;
                case(0xE):
                    cpu->CB ? rrHL(cpu, memory) : ldRn(cpu, &cpu->e,memory);
                    break;
                case(0xF):
                    rrn(cpu, &cpu->a);
                    break;
            }
            break;
        case(0x2):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? sla(cpu, &cpu->b) : jrnzn(cpu, memory);
                    break;
                case(0x1):
                    cpu->CB ? sla(cpu, &cpu->c) : ldHLnn(cpu, memory);
                    break;
                case(0x2):
                    cpu->CB ? sla(cpu, &cpu->d) : ldiHLA(cpu, memory);
                    break;
                case(0x3):
                    cpu->CB ? sla(cpu, &cpu->e) : incHLreg(cpu);
                    break;
                case(0x4):
                    cpu->CB ? sla(cpu, &cpu->h) : incR(cpu, &cpu->h);
                    break;
                case(0x5):
                    cpu->CB ? sla(cpu, &cpu->l) : decR(cpu, &cpu->h);
                    break;
                case(0x6):
                    cpu->CB ? slaHL(cpu, memory) : ldRn(cpu, &cpu->h,memory);
					break;
                case(0x7):
                    cpu->CB ? sla(cpu, &cpu->a) : DAA(cpu);
                    break;
                case(0x8):
                    cpu->CB ? sran(cpu, &cpu->b) : jrzn(cpu, memory);
                    break;
                case(0x9):
                    cpu->CB ? sran(cpu, &cpu->c) : addHLHL16bit(cpu);
                    break;
                case(0xA):
                    cpu->CB ? sran(cpu, &cpu->d) : ldiAHL(cpu, memory);
                    break;
                case(0xB):
                    cpu->CB ? sran(cpu, &cpu->e) : decHLreg(cpu);
                    break;
                case(0xC):
                    cpu->CB ? sran(cpu, &cpu->h) : incR(cpu, &cpu->l);
                    break;
                case(0xD):
                    cpu->CB ? sran(cpu, &cpu->l) : decR(cpu, &cpu->l);
                    break;
                case(0xE):
                    cpu->CB ? sraHL(cpu, memory) : ldRn(cpu, &cpu->l,memory);
                    break;
                case(0xF):
                    cpu->CB ? sran(cpu, &cpu->a) : CPL(cpu);
                    break;
            }
            break;
        case(0x3):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? swapR(cpu, &cpu->b) : jrncn(cpu, memory);
                    break;
                case(0x1):
                    cpu->CB ? swapR(cpu, &cpu->c) : ldSPnn(cpu, memory);
                    break;
                case(0x2):
                    cpu->CB ? swapR(cpu, &cpu->d) : lddHLA(cpu, memory);
                    break;
                case(0x3):
                    cpu->CB ? swapR(cpu, &cpu->e) : incSP(cpu);
                    break;
                case(0x4):
                    cpu->CB ? swapR(cpu, &cpu->h) : incHL(cpu, memory);
                    break;
                case(0x5):
                    cpu->CB ? swapR(cpu, &cpu->l) : decHL(cpu, memory);
                    break;
                case(0x6):
                    cpu->CB ? swapHL(cpu, memory) : ldHLn(cpu, memory);
					break;
                case(0x7):
                    cpu->CB ? swapR(cpu, &cpu->a) : SCF(cpu);
                    break;
                case(0x8):
                    cpu->CB ? srl(cpu, &cpu->b) : jrcn(cpu, memory);
                    break;
                case(0x9):
                    cpu->CB ? srl(cpu, &cpu->c) : addHLSP16bit(cpu);
                    break;
                case(0xA):
                    cpu->CB ? srl(cpu, &cpu->d) : lddAHL(cpu, memory);
                    break;
                case(0xB):
                    cpu->CB ? srl(cpu, &cpu->e) : decSP(cpu);
                    break;
                case(0xC):
                    cpu->CB ? srl(cpu, &cpu->h) : incR(cpu, &cpu->a);
                    break;
                case(0xD):
                    cpu->CB ? srl(cpu, &cpu->l) : decR(cpu, &cpu->a);
                    break;
                case(0xE):
                    cpu->CB ? srlHL(cpu, memory) : ldAnum(cpu, memory);
                    break;
                case(0xF):
                    cpu->CB ? srl(cpu, &cpu->a) : CCF(cpu);
                    break;
            }
            break;
        case(0x4):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? bitn(cpu, cpu->b, 0) : ldRR(cpu, &cpu->b, cpu->b);
                    break;
                case(0x1):
                    cpu->CB ? bitn(cpu, cpu->c, 0) : ldRR(cpu, &cpu->b, cpu->c);
                    break;
                case(0x2):
                    cpu->CB ? bitn(cpu, cpu->d, 0) : ldRR(cpu, &cpu->b, cpu->d);
                    break;
                case(0x3):
                    cpu->CB ? bitn(cpu, cpu->e, 0) : ldRR(cpu, &cpu->b, cpu->e);;
                    break;
                case(0x4):
                    cpu->CB ? bitn(cpu, cpu->h, 0) : ldRR(cpu, &cpu->b, cpu->h);
                    break;
                case(0x5):
                    cpu->CB ? bitn(cpu, cpu->l, 0) : ldRR(cpu, &cpu->b, cpu->l);
                    break;
                case(0x6):
                    cpu->CB ? bitHL(cpu, memory, 0) : ldRHL(cpu, &cpu->b, memory);
					break;
                case(0x7):
                    cpu->CB ? bitn(cpu, cpu->a, 0) : ldRR(cpu, &cpu->b, cpu->a);
                    break;
                case(0x8):
                    cpu->CB ? bitn(cpu, cpu->b, 1) : ldRR(cpu, &cpu->c, cpu->b);
                    break;
                case(0x9):
                    cpu->CB ? bitn(cpu, cpu->c, 1) : ldRR(cpu, &cpu->c, cpu->c);
                    break;
                case(0xA):
                    cpu->CB ? bitn(cpu, cpu->d, 1) : ldRR(cpu, &cpu->c, cpu->d);
                    break;
                case(0xB):
                    cpu->CB ? bitn(cpu, cpu->e, 1) : ldRR(cpu, &cpu->c, cpu->e);
                    break;
                case(0xC):
                    cpu->CB ? bitn(cpu, cpu->h, 1) : ldRR(cpu, &cpu->c, cpu->h);
                    break;
                case(0xD):
                    cpu->CB ? bitn(cpu, cpu->l, 1) : ldRR(cpu, &cpu->c, cpu->l);
                    break;
                case(0xE):
                    cpu->CB ? bitHL(cpu, memory, 1) : ldRHL(cpu, &cpu->c, memory);
                    break;
                case(0xF):
                    cpu->CB ? bitn(cpu, cpu->a, 1) : ldRR(cpu, &cpu->c, cpu->a);
                    break;
            }
            break;
        case(0x5):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? bitn(cpu, cpu->b, 2) : ldRR(cpu, &cpu->d, cpu->b);
                    break;
                case(0x1):
                    cpu->CB ? bitn(cpu, cpu->c, 2) : ldRR(cpu, &cpu->d, cpu->c);
                    break;
                case(0x2):
                    cpu->CB ? bitn(cpu, cpu->d, 2) : ldRR(cpu, &cpu->d, cpu->d);
                    break;
                case(0x3):
                    cpu->CB ? bitn(cpu, cpu->e, 2) : ldRR(cpu, &cpu->d, cpu->e);
                    break;
                case(0x4):
                    cpu->CB ? bitn(cpu, cpu->h, 2) : ldRR(cpu, &cpu->d, cpu->h);
                    break;
                case(0x5):
                    cpu->CB ? bitn(cpu, cpu->l, 2) : ldRR(cpu, &cpu->d, cpu->l);
                    break;
                case(0x6):
                    cpu->CB ? bitHL(cpu, memory, 2) : ldRHL(cpu, &cpu->d, memory);
					break;
                case(0x7):
                    cpu->CB ? bitn(cpu, cpu->a, 2) : ldRR(cpu, &cpu->d, cpu->a);
                    break;
                case(0x8):
                    cpu->CB ? bitn(cpu, cpu->b, 3) : ldRR(cpu, &cpu->e, cpu->b);
                    break;
                case(0x9):
                    cpu->CB ? bitn(cpu, cpu->c, 3) : ldRR(cpu, &cpu->e, cpu->c);
                    break;
                case(0xA):
                    cpu->CB ? bitn(cpu, cpu->d, 3) : ldRR(cpu, &cpu->e, cpu->d);
                    break;
                case(0xB):
                    cpu->CB ? bitn(cpu, cpu->e, 3) : ldRR(cpu, &cpu->e, cpu->e);
                    break;
                case(0xC):
                    cpu->CB ? bitn(cpu, cpu->h, 3) : ldRR(cpu, &cpu->e, cpu->h);
                    break;
                case(0xD):
                    cpu->CB ? bitn(cpu, cpu->l, 3) : ldRR(cpu, &cpu->e, cpu->l);
                    break;
                case(0xE):
                    cpu->CB ? bitHL(cpu, memory, 3) : ldRHL(cpu, &cpu->e, memory);
                    break;
                case(0xF):
                    cpu->CB ? bitn(cpu, cpu->a, 3) : ldRR(cpu, &cpu->e, cpu->a);
                    break;
            }
            break;
        case(0x6):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? bitn(cpu, cpu->b, 4) : ldRR(cpu, &cpu->h, cpu->b);
                    break;
                case(0x1):
                    cpu->CB ? bitn(cpu, cpu->c, 4) : ldRR(cpu, &cpu->h, cpu->c);
                    break;
                case(0x2):
                    cpu->CB ? bitn(cpu, cpu->d, 4) : ldRR(cpu, &cpu->h, cpu->d);
                    break;
                case(0x3):
                    cpu->CB ? bitn(cpu, cpu->e, 4) : ldRR(cpu, &cpu->h, cpu->e);
                    break;
                case(0x4):
                    cpu->CB ? bitn(cpu, cpu->h, 4) : ldRR(cpu, &cpu->h, cpu->h);
                    break;
                case(0x5):
                    cpu->CB ? bitn(cpu, cpu->l, 4) : ldRR(cpu, &cpu->h, cpu->l);
                    break;
                case(0x6):
                    cpu->CB ? bitHL(cpu, memory, 4) : ldRHL(cpu, &cpu->h, memory);
					break;
                case(0x7):
                    cpu->CB ? bitn(cpu, cpu->a, 4) : ldRR(cpu, &cpu->h, cpu->a);
                    break;
                case(0x8):
                    cpu->CB ? bitn(cpu, cpu->b, 5) : ldRR(cpu, &cpu->l, cpu->b);
                    break;
                case(0x9):
                    cpu->CB ? bitn(cpu, cpu->c, 5) : ldRR(cpu, &cpu->l, cpu->c);
                    break;
                case(0xA):
                    cpu->CB ? bitn(cpu, cpu->d, 5) : ldRR(cpu, &cpu->l, cpu->d);
                    break;
                case(0xB):
                    cpu->CB ? bitn(cpu, cpu->e, 5) : ldRR(cpu, &cpu->l, cpu->e);
                    break;
                case(0xC):
                    cpu->CB ? bitn(cpu, cpu->h, 5) : ldRR(cpu, &cpu->l, cpu->h);
                    break;
                case(0xD):
                    cpu->CB ? bitn(cpu, cpu->l, 5) : ldRR(cpu, &cpu->l, cpu->l);
                    break;
                case(0xE):
                    cpu->CB ? bitHL(cpu, memory, 5) : ldRHL(cpu, &cpu->l, memory);
                    break;
                case(0xF):
                    cpu->CB ? bitn(cpu, cpu->a, 5) : ldRR(cpu, &cpu->l, cpu->a);
                    break;
            }
            break;
        case(0x7):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? bitn(cpu, cpu->b, 6) : ldHLR(cpu, cpu->b, memory);
                    break;
                case(0x1):
                    cpu->CB ? bitn(cpu, cpu->c, 6) : ldHLR(cpu, cpu->c, memory);
                    break;
                case(0x2):
                    cpu->CB ? bitn(cpu, cpu->d, 6) : ldHLR(cpu, cpu->d, memory);
                    break;
                case(0x3):
                    cpu->CB ? bitn(cpu, cpu->e, 6) : ldHLR(cpu, cpu->e, memory);
                    break;
                case(0x4):
                    cpu->CB ? bitn(cpu, cpu->h, 6) : ldHLR(cpu, cpu->h, memory);
                    break;
                case(0x5):
                    cpu->CB ? bitn(cpu, cpu->l, 6) : ldHLR(cpu, cpu->l, memory);
                    break;
                case(0x6):
                    bitHL(cpu, memory, 6); // HALT otherwise
					break;
                case(0x7):
                    cpu->CB ? bitn(cpu, cpu->a, 6) : ldHLA(cpu, memory);
                    break;
                case(0x8):
                    cpu->CB ? bitn(cpu, cpu->b, 7) : ldRR(cpu, &cpu->a, cpu->b);
                    break;
                case(0x9):
                    cpu->CB ? bitn(cpu, cpu->c, 7) : ldRR(cpu, &cpu->a, cpu->c);
                    break;
                case(0xA):
                    cpu->CB ? bitn(cpu, cpu->d, 7) : ldRR(cpu, &cpu->a, cpu->d);
                    break;
                case(0xB):
                    cpu->CB ? bitn(cpu, cpu->e, 7) : ldRR(cpu, &cpu->a, cpu->e);
                    break;
                case(0xC):
                    cpu->CB ? bitn(cpu, cpu->h, 7) : ldRR(cpu, &cpu->a, cpu->h);
                    break;
                case(0xD):
                    cpu->CB ? bitn(cpu, cpu->l, 7) : ldRR(cpu, &cpu->a, cpu->l);
                    break;
                case(0xE):
                    cpu->CB ? bitHL(cpu, memory, 7) : ldRHL(cpu, &cpu->a, memory);
                    break;
                case(0xF):
                    cpu->CB ? bitn(cpu, cpu->a, 7) : ldRR(cpu, &cpu->a, cpu->a);
                    break;
            }
            break;
        case(0x8):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? resn(cpu, &cpu->b, 0) : addAR(cpu, cpu->b);
                    break;
                case(0x1):
                    cpu->CB ? resn(cpu, &cpu->c, 0) : addAR(cpu, cpu->c);
                    break;
                case(0x2):
                    cpu->CB ? resn(cpu, &cpu->d, 0) : addAR(cpu, cpu->d);
                    break;
                case(0x3):
                    cpu->CB ? resn(cpu, &cpu->e, 0) : addAR(cpu, cpu->e);
                    break;
                case(0x4):
                    cpu->CB ? resn(cpu, &cpu->h, 0) : addAR(cpu, cpu->h);
                    break;
                case(0x5):
                    cpu->CB ? resn(cpu, &cpu->l, 0) : addAR(cpu, cpu->l);
                    break;
                case(0x6):
                    cpu->CB ? resHL(cpu, memory, 0) : addAHL(cpu, memory);
					break;
                case(0x7):
                    cpu->CB ? resn(cpu, &cpu->a, 0) : addAR(cpu, cpu->a);
                    break;
                case(0x8):
                    cpu->CB ? resn(cpu, &cpu->b, 1) : adcAR(cpu, cpu->b);
                    break;
                case(0x9):
                    cpu->CB ? resn(cpu, &cpu->c, 1) : adcAR(cpu, cpu->c);
                    break;
                case(0xA):
                    cpu->CB ? resn(cpu, &cpu->d, 1) : adcAR(cpu, cpu->d);
                    break;
                case(0xB):
                    cpu->CB ? resn(cpu, &cpu->e, 1) : adcAR(cpu, cpu->e);
                    break;
                case(0xC):
                    cpu->CB ? resn(cpu, &cpu->h, 1) : adcAR(cpu, cpu->h);
                    break;
                case(0xD):
                    cpu->CB ? resn(cpu, &cpu->l, 1) : adcAR(cpu, cpu->l);
                    break;
                case(0xE):
                    cpu->CB ? resHL(cpu, memory, 1) : adcHL(cpu, memory);
                    break;
                case(0xF):
                    cpu->CB ? resn(cpu, &cpu->a, 1) : adcAR(cpu, cpu->a);
                    break;
            }
            break;
        case(0x9):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? resn(cpu, &cpu->b, 2) : subAR(cpu, cpu->b);
                    break;
                case(0x1):
                    cpu->CB ? resn(cpu, &cpu->c, 2) : subAR(cpu, cpu->c);
                    break;
                case(0x2):
                    cpu->CB ? resn(cpu, &cpu->d, 2) : subAR(cpu, cpu->d);
                    break;
                case(0x3):
                    cpu->CB ? resn(cpu, &cpu->e, 2) : subAR(cpu, cpu->e);
                    break;
                case(0x4):
                    cpu->CB ? resn(cpu, &cpu->h, 2) : subAR(cpu, cpu->h);;
                    break;
                case(0x5):
                    cpu->CB ? resn(cpu, &cpu->l, 2) : subAR(cpu, cpu->l);
                    break;
                case(0x6):
                    cpu->CB ? resHL(cpu, memory, 2) : subAHL(cpu, memory);
					break;
                case(0x7):
                    cpu->CB ? resn(cpu, &cpu->a, 2) : subAA(cpu);
                    break;
                case(0x8):
                    cpu->CB ? resn(cpu, &cpu->b, 3) : sbcAR(cpu, cpu->b);
                    break;
                case(0x9):
                    cpu->CB ? resn(cpu, &cpu->c, 3) : sbcAR(cpu, cpu->c);
                    break;
                case(0xA):
                    cpu->CB ? resn(cpu, &cpu->d, 3) : sbcAR(cpu, cpu->d);
                    break;
                case(0xB):
                    cpu->CB ? resn(cpu, &cpu->e, 3) : sbcAR(cpu, cpu->e);
                    break;
                case(0xC):
                    cpu->CB ? resn(cpu, &cpu->h, 3) : sbcAR(cpu, cpu->h);
                    break;
                case(0xD):
                    cpu->CB ? resn(cpu, &cpu->l, 3) : sbcAR(cpu, cpu->l);
                    break;
                case(0xE):
                    cpu->CB ? resHL(cpu, memory, 3) : sbcAHL(cpu, memory);
                    break;
                case(0xF):
                    cpu->CB ? resn(cpu, &cpu->a, 3) : sbcAR(cpu, cpu->a);
                    break;
            }
            break;
        case(0xA):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? resn(cpu, &cpu->b, 4) : andr(cpu, cpu->b);
                    break;
                case(0x1):
                    cpu->CB ? resn(cpu, &cpu->c, 4) : andr(cpu, cpu->c);
                    break;
                case(0x2):
                    cpu->CB ? resn(cpu, &cpu->d, 4) : andr(cpu, cpu->d);
                    break;
                case(0x3):
                    cpu->CB ? resn(cpu, &cpu->e, 4) : andr(cpu, cpu->e);
                    break;
                case(0x4):
                    cpu->CB ? resn(cpu, &cpu->h, 4) : andr(cpu, cpu->h);
                    break;
                case(0x5):
                    cpu->CB ? resn(cpu, &cpu->l, 4) : andr(cpu, cpu->h);
                    break;
                case(0x6):
                    cpu->CB ? resHL(cpu, memory, 4) : andHL(cpu, memory);
					break;
                case(0x7):
                    cpu->CB ? resn(cpu, &cpu->a, 4) : andA(cpu);
                    break;
                case(0x8):
                    cpu->CB ? resn(cpu, &cpu->b, 5) : xorr(cpu, cpu->b);
                    break;
                case(0x9):
                    cpu->CB ? resn(cpu, &cpu->c, 5) : xorr(cpu, cpu->c);
                    break;
                case(0xA):
                    cpu->CB ? resn(cpu, &cpu->d, 5) : xorr(cpu, cpu->d);
                    break;
                case(0xB):
                    cpu->CB ? resn(cpu, &cpu->e, 5) : xorr(cpu, cpu->e);
                    break;
                case(0xC):
                    cpu->CB ? resn(cpu, &cpu->h, 5) : xorr(cpu, cpu->h);
                    break;
                case(0xD):
                    cpu->CB ? resn(cpu, &cpu->l, 5) : xorr(cpu, cpu->l);
                    break;
                case(0xE):
                    cpu->CB ? resHL(cpu, memory, 5) : xorHL(cpu, memory);
                    break;
                case(0xF):
                    cpu->CB ? resn(cpu, &cpu->a, 5) : xorA(cpu);
                    break;
            }
            break;
        case(0xB):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? resn(cpu, &cpu->b, 6) : orr(cpu, cpu->b);
                    break;
                case(0x1):
                    cpu->CB ? resn(cpu, &cpu->c, 6) : orr(cpu, cpu->c);
                    break;
                case(0x2):
                    cpu->CB ? resn(cpu, &cpu->d, 6) : orr(cpu, cpu->d);
                    break;
                case(0x3):
                    cpu->CB ? resn(cpu, &cpu->e, 6) : orr(cpu, cpu->e);
                    break;
                case(0x4):
                    cpu->CB ? resn(cpu, &cpu->h, 6) : orr(cpu, cpu->h);
                    break;
                case(0x5):
                    cpu->CB ? resn(cpu, &cpu->l, 6) : orr(cpu, cpu->l);
                    break;
                case(0x6):
                    cpu->CB ? resHL(cpu, memory, 6) : orHL(cpu, memory);
					break;
                case(0x7):
                    cpu->CB ? resn(cpu, &cpu->a, 6) : orr(cpu, cpu->a);
                    break;
                case(0x8):
                    cpu->CB ? resn(cpu, &cpu->b, 7) : cpR(cpu, &cpu->b);
                    break;
                case(0x9):
                    cpu->CB ? resn(cpu, &cpu->c, 7) : cpR(cpu, &cpu->c);
                    break;
                case(0xA):
                    cpu->CB ? resn(cpu, &cpu->d, 7) : cpR(cpu, &cpu->d);
                    break;
                case(0xB):
                    cpu->CB ? resn(cpu, &cpu->e, 7) : cpR(cpu, &cpu->e);
                    break;
                case(0xC):
                    cpu->CB ? resn(cpu, &cpu->h, 7) : cpR(cpu, &cpu->h);
                    break;
                case(0xD):
                    cpu->CB ? resn(cpu, &cpu->l, 7) : cpR(cpu, &cpu->l);
                    break;
                case(0xE):
                    cpu->CB ? resHL(cpu, memory, 7) : cpHL(cpu, memory);
                    break;
                case(0xF):
                    cpu->CB ? resn(cpu, &cpu->a, 7) : cpR(cpu, &cpu->a);
                    break;
            }
            break;
        case(0xC):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? setn(cpu, &cpu->b, 0) : retnz(cpu, memory);
                    break;
                case(0x1):
                    cpu->CB ? setn(cpu, &cpu->c, 0) : popBC(cpu, memory);
                    break;
                case(0x2):
                    cpu->CB ? setn(cpu, &cpu->d, 0) : jpnz(cpu, memory);
                    break;
                case(0x3):
                    cpu->CB ? setn(cpu, &cpu->e, 0) : jp(cpu, memory);
                    break;
                case(0x4):
                    cpu->CB ? setn(cpu, &cpu->h, 0) : callnz(cpu, memory);
                    break;
                case(0x5):
                    cpu->CB ? setn(cpu, &cpu->l, 0) : pushBC(cpu, memory);
                    break;
                case(0x6):
                    cpu->CB ? setHL(cpu, memory, 0) : addAn(cpu, memory);
					break;
                case(0x7):
                    cpu->CB ? setn(cpu, &cpu->a, 0) : rstn(cpu, memory, 0x00);
                    break;
                case(0x8):
                    cpu->CB ? setn(cpu, &cpu->b, 1) : retz(cpu, memory);
                    break;
                case(0x9):
                    cpu->CB ? setn(cpu, &cpu->c, 1) : ret(cpu, memory);
                    break;
                case(0xA):
                    cpu->CB ? setn(cpu, &cpu->d, 1) : jpz(cpu, memory);
                    break;
                case(0xB):
                    if (cpu->CB)  {
                        setn(cpu, &cpu->e, 1);
                    } else {
                        cpu->CB = 1;
                        cpu->pc++;
                    }
                    break;
                case(0xC):
                    cpu->CB ? setn(cpu, &cpu->h, 1) : callz(cpu, memory);
                    break;
                case(0xD):
                    cpu->CB ? setn(cpu, &cpu->l, 1) : call(cpu, memory);
                    break;
                case(0xE):
                    cpu->CB ? setHL(cpu, memory, 1) : adcAn(cpu, memory);
                    break;
                case(0xF):
                    cpu->CB ? setn(cpu, &cpu->a, 1) : rstn(cpu, memory, 0x08);
                    break;
            }
            break;
        case(0xD):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? setn(cpu, &cpu->b, 2) : retnc(cpu, memory);
                    break;
                case(0x1):
                    cpu->CB ? setn(cpu, &cpu->c, 2) : popDE(cpu, memory);
                    break;
                case(0x2):
                    cpu->CB ? setn(cpu, &cpu->d, 2) : jpnc(cpu, memory);
                    break;
                case(0x3):
                    // Invalid opcode
                    cpu->CB ? setn(cpu, &cpu->e, 2) : cpu->pc++;
                    break;
                case(0x4):
                    cpu->CB ? setn(cpu, &cpu->h, 2) : callnc(cpu, memory);
                    break;
                case(0x5):
                    cpu->CB ? setn(cpu, &cpu->l, 2) : pushDE(cpu, memory);
                    break;
                case(0x6):
                    cpu->CB ? setHL(cpu, memory, 2) : subAn(cpu, memory);
					break;
                case(0x7):
                    cpu->CB ? setn(cpu, &cpu->a, 2) : rstn(cpu, memory, 0x10);
                    break;
                case(0x8):
                    cpu->CB ? setn(cpu, &cpu->b, 3) : retc(cpu, memory);
                    break;
                case(0x9):
                    cpu->CB ? setn(cpu, &cpu->c, 3) : reti(cpu, memory);
                    break;
                case(0xA):
                    cpu->CB ? setn(cpu, &cpu->d, 3) : jpc(cpu, memory);
                    break;
                case(0xB):
                    // Invalid opcode
                    cpu->CB ? setn(cpu, &cpu->e, 3) : cpu->pc++;
                    break;
                case(0xC):
                    cpu->CB ? setn(cpu, &cpu->h, 3) : callc(cpu, memory);
                    break;
                case(0xD):
                    // Invalid opcode
                    cpu->CB ? setn(cpu, &cpu->l, 3) : cpu->pc++;
                    break;
                case(0xE):
                    cpu->CB ? setHL(cpu, memory, 3) : sbcAn(cpu, memory);
                    break;
                case(0xF):
                    cpu->CB ? setn(cpu, &cpu->a, 3) : rstn(cpu, memory, 0x18);
                    break;
            }
            break;
        case(0xE):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? setn(cpu, &cpu->b, 4) : ldhnA(cpu, memory);
                    break;
                case(0x1):
                    cpu->CB ? setn(cpu, &cpu->c, 4) : popHL(cpu, memory);
                    break;
                case(0x2):
                    cpu->CB ? setn(cpu, &cpu->d, 4) : ldCAddressA(cpu, memory);
                    break;
                case(0x3):
                    // Invalid opcode
                    cpu->CB ? setn(cpu, &cpu->e, 4) : cpu->pc++;
                    break;
                case(0x4):
                    // Invalid opcode
                    cpu->CB ? setn(cpu, &cpu->h, 4) : cpu->pc++;
                    break;
                case(0x5):
                    cpu->CB ? setn(cpu, &cpu->l, 4) : pushHL(cpu, memory);
                    break;
                case(0x6):
                    cpu->CB ? setHL(cpu, memory, 4) : andn(cpu, memory);
					break;
                case(0x7):
                    cpu->CB ? setn(cpu, &cpu->a, 4) : rstn(cpu, memory, 0x20);
                    break;
                case(0x8):
                    cpu->CB ? setn(cpu, &cpu->b, 5) : addSPn(cpu, memory);
                    break;
                case(0x9):
                    cpu->CB ? setn(cpu, &cpu->c, 5) : jphl(cpu, memory);
                    break;
                case(0xA):
                    cpu->CB ? setn(cpu, &cpu->d, 5) : ldnnA(cpu, memory);
                    break;
                case(0xB):
                    // Invalid Opcode
                    cpu->CB ? setn(cpu, &cpu->e, 5) : cpu->pc++;
                    break;
                case(0xC):
                    // Invalid Opcode
                    cpu->CB ? setn(cpu, &cpu->h, 5) : cpu->pc++;
                    break;
                case(0xD):
                    // Invalid Opcode
                    cpu->CB ? setn(cpu, &cpu->l, 5) : cpu->pc++;
                    break;
                case(0xE):
                    cpu->CB ? setHL(cpu, memory, 5) : xorn(cpu, memory);
                    break;
                case(0xF):
                    cpu->CB ? setn(cpu, &cpu->a, 5) : rstn(cpu, memory, 0x28);
                    break;
            }
            break;
        case(0xF):
            switch(nibbleTwo) {
                case(0x0):
                    cpu->CB ? setn(cpu, &cpu->b, 6) : ldhAn(cpu, memory);
                    break;
                case(0x1):
                    cpu->CB ? setn(cpu, &cpu->c, 6) : popAF(cpu, memory);
                    break;
                case(0x2):
                    cpu->CB ? setn(cpu, &cpu->d, 6) : ldACAddress(cpu, memory);
                    break;
                case(0x3):
                    // DI
                    cpu->CB? setn(cpu, &cpu->e, 6) : DI(cpu);
                    break;
                case(0x4):
                    // Invalid opcode
                    cpu->CB ? setn(cpu, &cpu->h, 6) : cpu->pc++;
                    break;
                case(0x5):
                    cpu->CB ? setn(cpu, &cpu->l, 6) : pushAF(cpu, memory);
                    break;
                case(0x6):
                    cpu->CB ? setHL(cpu, memory, 6) : orn(cpu, memory);
					break;
                case(0x7):
                    cpu->CB ? setn(cpu, &cpu->a, 6) : rstn(cpu, memory, 0x30);
                    break;
                case(0x8):
                    cpu->CB ? setn(cpu, &cpu->b, 7) : ldHLSPn(cpu, memory);
                    break;
                case(0x9):
                    cpu->CB ? setn(cpu, &cpu->c, 7) : ldSPHL(cpu);
                    break;
                case(0xA):
                    cpu->CB ? setn(cpu, &cpu->d, 7) : ldAn(cpu, memory);
                    break;
                case(0xB):
                    cpu->CB? setn(cpu, &cpu->e, 7) : EI(cpu);
                    break;
                case(0xC):
                    // Invalid Opcode
                    cpu->CB ? setn(cpu, &cpu->h, 7) : cpu->pc++;
                    break;
                case(0xD):
                    // Invalid Opcode
                    cpu->CB ? setn(cpu, &cpu->l, 7) : cpu->pc++;
                    break;
                case(0xE):
                    cpu->CB ? setHL(cpu, memory, 7) : cpn(cpu, memory);
                    break;
                case(0xF):
                    cpu->CB ? setn(cpu, &cpu->a, 7) : rstn(cpu, memory, 0x38);
                    break;
            }
            break;
    }

	cpu->totalClocks += cpu->instructionClocks;
}
