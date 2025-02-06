#pragma once
#include "Common.h"

typedef struct Emulator {
	int running;
	int paused;
	u64 ticks;
} Emulator;

void runEmulator();
Emulator* get_emulator();