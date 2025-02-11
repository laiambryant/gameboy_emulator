#pragma once
#include "Registers.h"
#include "memory_bus.h"
#include "Common.h"
#include "Instruction.h"
#include "bus.h"

#define reg cpu->regs
#define CPU_FLAG_Z BIT(cpu.regs.f, 7)
#define CPU_FLAG_C BIT(cpu.regs.f, 4)

typedef struct CPU {
    Registers regs;
    Flags fl;
    u16 fetched_data;
    u16 memory_destination;
	u8 curr_opcode;
	u8 is_halted;
    u8 is_stepping;
    u8 is_dest_mem;
    u8 int_master_enabled;
    u16 pc;
	Instruction* curr_instr;
    u8 cycles;
} CPU;

typedef void (*instruction_func)(CPU* cpu);

// CPU functions
CPU* get_cpu();
// Destroys the CPU
void destroy_cpu(CPU* cpu);
int step(CPU* cpu);
//Fetches the current instruction
void fetch_instruction(CPU* cpu);
//Fetches the data for the current instruction
void fetch_data(CPU* cpu);
//Executes the current instruction
void execute();
//TODO: Implement
void cycles(u8 cycle);
instruction_func instruction_get_processor(InstructionName type);
char* get_instruction_name(u8 opcode);