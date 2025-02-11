#pragma once
#include "Registers.h"
#include "memory_bus.h"
#include "Common.h"
#include "Instruction.h"
#include "bus.h"

#define reg cpu->regs

typedef struct CPU {
    Registers regs;
    Flags fl;
    u16 fetched_data;
    u16 memory_destination;
	u8 curr_opcode;
	u8 is_halted;
    u8 is_stepping;
    u8 is_dest_mem;
    u16 pc;
	Instruction curr_instr;
    memory_bus* bus;
} CPU;


// CPU functions
CPU* get_cpu();
// Destroys the CPU
void destroy_cpu(CPU* cpu);
// Sets flag bit to 1 if the result of an operation is overflowing
void setFlagSubtract(CPU* cpu, InstructionName instruction_name);
// Sets flag bit to 1 if the result of an operation is zero
void setFlagZero(CPU* cpu, u16 result);
// Sets flag bit to 1 if the result of an operation is carrying
void setFlagCarry(CPU* cpu, u16 result);
// Sets flag bit to 1 if the result of an operation is half carrying
void setFlagHalfCarry(CPU* cpu, u16 result);
// Performs all flag checks for 8 bit operations
void checkFlags8(CPU* cpu, u16 result, InstructionName instruction_name);
// Performs all flag checks for 16 bit operations
void checkFlags16(CPU* cpu, u32 result, InstructionName instruction_name);
int step(CPU* cpu);
void fetch_instruction(CPU* cpu);
void fetch_data(CPU* cpu);
void execute(CPU* cpu);