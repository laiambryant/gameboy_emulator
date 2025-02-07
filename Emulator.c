#include "Emulator.h"

void runEmulator(Emulator* emulator, int argc, char** argv) {
	if (!emulator->front_end) {
		emulator->front_end = create_front_end("Emulator");
		init_front_end(emulator->front_end, "Emulator");
	}
	printf("Running emulator...\n");
	while (emulator->running) {
		if (!emulator->paused) {
			emulator->ticks++;
			delay(10);
			printf("Ticks: %d\n", emulator->ticks);
			if (!cart_load("")) {
				emulator->running = 1;
			}
		}
	}
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