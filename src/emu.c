#include <stdio.h>
#ifdef _WIN32
#define THREADS
#include <Windows.h>
#elif __linux__
#define THREADS
#include <pthread.h>
#endif 

#include "emu.h"
#include "cart.h"
#include "cpu.h"
#include "ui.h"
#include "timer.h"
#include "dma.h"
#include "ppu.h"

static emu_context ctx;

emu_context* emu_get_context() {
    return &ctx;
}

void* cpu_run(void* p) {
    timer_init();
    cpu_init();
    ppu_init();

    ctx.running = true;
    ctx.paused = false;
    ctx.ticks = 0;

    while (ctx.running) {
        if (ctx.paused) {
            delay(10);
            continue;
        }

        if (!cpu_step()) {
            printf("CPU Stopped\n");
            return 0;
        }
    }

    return 0;
}

int emu_run(int argc, char** argv) {
    
    if (!cart_load(argv[1])) {
        printf("Failed to load ROM file: %s\n", argv[1]);
        return -2;
    }

    printf("Cart loaded..\n");

    ui_init();

    #ifdef _WIN32
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)cpu_run, NULL, 0, NULL);
    #elif __linux__
    pthread_t cpu_thread;
    pthread_create(&cpu_thread, NULL, cpu_run, NULL);
    #endif

    u32 prev_frame = 0;

    while (!ctx.die) {
        ui_handle_events();

        if (prev_frame != ppu_get_context()->current_frame) {
            ui_update();
        }

        prev_frame = ppu_get_context()->current_frame;
    }

    return 0;
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
