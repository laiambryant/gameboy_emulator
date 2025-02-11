#include "Emulator.h"

void runEmulator(Emulator* emulator, int argc, char** argv) {
	if (!emulator->front_end) {
		emulator->front_end = create_front_end("Emulator");
		init_front_end(emulator->front_end, "Emulator");
	}
	cartridge_context* ctx = init_cart("tests\\roms\\pokemonRed.gb");
	printf("Running emulator...\n");
	while (emulator->running) {
		if (!emulator->paused) {
			emulator->ticks++;
			delay(1000);
			printf("Ticks: %d\n", emulator->ticks);
		}
		if (emulator->ticks >= 10) {
			emulator->running = 0;
		}
	}
	destroy_cart(ctx);
	free_front_end(emulator->front_end);
}

Emulator* get_emulator() {
	Emulator* emulator = (Emulator*)malloc(sizeof(Emulator));
	if (!emulator) {
		printf("Memory allocation failed\n");
		return NULL;
	}
	emulator->running = 1;
	emulator->paused = 0;
	emulator->ticks = 0;
	emulator->front_end = create_front_end("Emulator");
	init_front_end(emulator->front_end, "Emulator");
	return emulator;
}