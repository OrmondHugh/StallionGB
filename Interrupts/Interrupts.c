#include "InterruptDefines.h"
#include "../CPU/CPUDefines.h"
#include "../Memory/MemoryDefines.h"
#include "../CPU/RegisterOps/StackDefines.h"

int ProcessInterrupts(CPU *cpu, int8_t *mem) {
    // Execute any necessary interrupts if they are not disabled
    if (!cpu->interruptsEnabled) {
        return -1;
    }

    if (cpu->interruptFlag.vblank) {
        cpu->interruptsEnabled = 0;
        rstn(cpu, mem, 0x40);
        //printf("Vblank            ******************************************************\n");
        cpu->interruptFlag.vblank = 0;
        return 0;
    } else if (cpu->interruptFlag.lcdc) {
        cpu->interruptsEnabled = 0;
        rstn(cpu, mem, 0x48);
        cpu->interruptFlag.lcdc = 0;
        return 0;
    } else if (cpu->interruptFlag.timer) {
        cpu->interruptsEnabled = 0;
        rstn(cpu, mem, 0x50);
        cpu->interruptFlag.timer = 0;
        return 0;
    } else if (cpu->interruptFlag.serialTransferCompletion) {
        cpu->interruptsEnabled = 0;
        rstn(cpu, mem, 0x50);
        cpu->interruptFlag.serialTransferCompletion = 0;
        return 0;
    } else if (cpu->interruptFlag.highToLow) {
        cpu->interruptsEnabled = 0;
        rstn(cpu, mem, 0x60);
        cpu->interruptFlag.highToLow = 0;
        return 0;
    }

    return -1;
}
