#include "tests.h"

void test_registers() {
	Registers* registers = get_registers();
	print_registers(registers);
	set_register(registers, A, 0x12);
	print_registers(registers);
	assert(get_register(registers, A) == 0x12);
	set_register_combination(registers, A, B, 0x6634);
	print_registers(registers);
	assert(get_register_combination(registers, A, B) == 0x6634);
	assert(get_register(registers, A) == 0x66);
	assert(get_register(registers, B) == 0x34);
	free(registers);
}

void test_adds() {
	CPU* cpu = get_cpu();
	set_register(cpu->regs, A, 0x12);
	set_register_combination(cpu->regs, H, L, 0x1212);
	ADD_COMPOUND(cpu, A, H, L);
	print_registers(cpu->regs);
	assert(get_register(cpu->regs, L) == 0x24);
	assert(get_register_combination(cpu->regs, H, L) == 0x1224);
	destroy_cpu(cpu);
}
