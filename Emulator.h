#pragma once
#include "Common.h"
#include "front_end.h"
#include "Cartridge.h"

typedef struct Emulator {
	int running;
	int paused;
	u64 ticks;
	FrontEnd* front_end;
} Emulator;

static Emulator* emulator_ctx ;

void runEmulator(Emulator* emulator, int argc, char** argv);
Emulator* get_emulator();