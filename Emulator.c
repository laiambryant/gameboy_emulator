#include "Emulator.h"
#include "front_end.h"	

void runEmulator(int argc, char** argv) {
	printf("Running emulator...\n");
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
	return emulator;
}