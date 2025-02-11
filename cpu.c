#include "Cpu.h"

CPU cpu = { 0 };

CPU* get_cpu() {
	cpu.regs.pc = 0x100;
	cpu.regs.a = 0x01;
	return &cpu;
}

void destroy_cpu(CPU* cpu) {
	return;
}


void fetch_instruction(CPU* cpu) {
	cpu->curr_opcode = bus_read(cpu->regs.pc);
	cpu->curr_instr = get_instruction(cpu->curr_opcode);
}

void fetch_data(CPU* cpu) {
	cpu->memory_destination = 0;
	cpu->is_dest_mem = 0;
	switch (cpu->curr_instr->mode) {
	case AM_IMP:
		cpu->regs.pc++;
		break;
	case AM_R: 
		cpu->fetched_data = get_register(&cpu->regs, cpu->curr_instr->reg1);
		break;
	case AM_R_D8:
		cpu->fetched_data = bus_read(cpu->regs.pc++);
		cpu->regs.pc++;
		break;
	case AM_D16: {
		u16 low = cpu->fetched_data = bus_read(cpu->regs.pc);
		u8 high = cpu->fetched_data = bus_read(cpu->regs.pc + 1);
		cpu->fetched_data = (high << 8) | low;
		cpu->regs.pc += 2;
		break;
		}
	default:
		cpu->regs.pc++;
		break;
	}
	
}
static void execute() {
	instruction_func proc = instruction_get_processor(cpu.curr_instr->instruction_name);
	if (proc != NULL) 
		proc(&cpu);
}

int step(CPU* cpu) {
	if (!cpu->is_halted) {
		fetch_instruction(cpu);
		printf("Executing instruction @pc->[%04X]", cpu->regs.pc);
		fetch_data(cpu);
		printf("Instruction: [%d] %s, Addressing Mode -> [%d]\n", 
			cpu->curr_instr->instruction_name, get_instruction_name(cpu->curr_instr->instruction_name), cpu->curr_instr->mode);
		execute();
	}
	return 1;
}