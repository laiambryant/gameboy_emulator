#include "Cpu.h"

CPU cpu = { 0 };

CPU* get_cpu() {
	return &cpu;
}

void destroy_cpu(CPU* cpu) {
	return;
}

void setFlagSubtract(CPU* cpu, InstructionName instruction_name){
	if (instruction_name == INSTR_SUB 
			|| instruction_name == INSTR_SBC 
			|| instruction_name == INSTR_CP)
		cpu->fl.subtract = ONE;
}
void setFlagZero(CPU* cpu, u16 result) {
	if (result == ZERO_HEX)
		cpu->fl.zero = ONE;
	else cpu->fl.zero = ZERO_HEX;
}
void setFlagCarry(CPU* cpu, u16 result) {
	if (result - 1 > MAX_16_BIT)
		cpu->fl.carry = ONE;
	else cpu->fl.carry = ZERO_HEX;
}
void setFlagHalfCarry(CPU* cpu, u16 result) {
	result = result << 8;
	if(MAX_8_BIT);
}
void checkFlags8(CPU* cpu, u16 result, InstructionName instruction_name) {
	setFlagCarry(cpu, result);
	setFlagZero(cpu, result);
	setFlagSubtract(cpu, instruction_name);
	setFlagHalfCarry(cpu, result);
}
void checkFlags16(CPU* cpu, u32 result, InstructionName instruction_name) {
	setFlagCarry(cpu, result);
	setFlagZero(cpu, result);
	setFlagSubtract(cpu, instruction_name);
	setFlagHalfCarry(cpu, result);
}

void fetch_instruction(CPU* cpu) {
	cpu->curr_opcode = bus_read(cpu->regs.pc);
	cpu->curr_instr = get_instruction(cpu->curr_opcode);
}
void fetch_data(CPU* cpu) {
	cpu->memory_destination = 0;
	cpu->is_dest_mem = 0;
	switch (cpu->curr_instr.mode) {
	case AM_IMP: 
		return;
	case AM_R: 
		cpu->fetched_data = get_register(&cpu->regs, cpu->curr_instr.reg1);
	case AM_R_D8:
		cpu->fetched_data = bus_read(cpu->regs.pc++);
		cpu->regs.pc++;
		return;
	case AM_D16: {
		u16 low = cpu->fetched_data = bus_read(cpu->regs.pc);
		u8 high = cpu->fetched_data = bus_read(cpu->regs.pc + 1);
		cpu->fetched_data = (high << 8) | low;
		cpu->regs.pc += 2;
		}
	default:
		printf("Unknown Addressing Mode -> [%d] \n", cpu->curr_instr.instruction_name);
	}
	
}
void execute(CPU* cpu) {
	printf("Not Executing...\n");
}

int step(CPU* cpu) {
	if (!cpu->is_halted) {
		fetch_instruction(cpu);
		fetch_data(cpu);
		execute(cpu);
	}
	return 0;
}