#pragma once
#include "Common.h"
#include "front_end.h"
#ifndef CARTRIDGE
#define	CARTRIDGE
#include "Cartridge.h"
#endif 
#include "Cpu.h"

typedef struct Emulator {
	int running;
	int paused;
	u64 ticks;
	FrontEnd* front_end;
} Emulator;


void runEmulator(Emulator* emulator, int argc, char** argv);
Emulator* get_emulator();