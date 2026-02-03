#include "emu.h"
#include "timer.h"
#include "ppu.h"
#include "dma.h"
#include "interrupts.h"

static emu_context ctx = {0};

emu_context* emu_get_context() {
    return &ctx;
}

void emu_cycles(int cpu_cycles) {
    for (int i = 0; i < cpu_cycles; i++) {
        for (int n = 0; n < 4; n++) {
            ctx.ticks++;
            timer_tick();
            ppu_tick();
        }

        dma_tick();
    }
}
