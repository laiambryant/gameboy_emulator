#include "Registers.h"

Registers* get_registers() {
	Registers* registers = (Registers*)malloc(sizeof(Registers));
	if (!registers) {
		printf("Memory allocation failed\n");
		return NULL;
	}
	init_registers(registers);
	return registers;
}

void init_registers(Registers* registers) {
	if (registers) {
		registers->a = 0;
		registers->b = 0;
		registers->c = 0;
		registers->d = 0;
		registers->e = 0;
		registers->h = 0;
		registers->l = 0;
		registers->sp = 0;
		registers->pc = 0;
	}
}

u16 get_register_combination(Registers* registers, Register register1, Register register2) {
    if (registers)
        return (get_register(registers, register1) << 8) | get_register(registers, register2);
    return 1;
}

u16 set_register_combination(Registers* registers, Register register1, Register register2, u16 value) {
	if (registers) {
		set_register(registers, register1, value >> 8);
		set_register(registers, register2, value & 0xFF);
		return 0;
	}
    return 1;
}

u16 get_register(Registers* registers, Register reg) {
    switch (reg) {
        case R_A: return registers->a;
        case R_B: return registers->b;
        case R_C: return registers->c;
        case R_D: return registers->d;
        case R_E: return registers->e;
        case R_H: return registers->h;
        case R_L: return registers->l;
		case R_BC: return get_register_combination(registers, R_B, R_C);
		case R_DE: return get_register_combination(registers, R_D, R_E);
		case R_HL: return get_register_combination(registers, R_H, R_L);
        case R_SP : return registers->sp;
		case R_PC : return registers->pc;
        default: return 1; 
    }
}
void set_register(Registers* registers, Register reg, u16 value) {
    switch (reg) {
	case R_A: registers->a = value; break;
	case R_B: registers->b = value; break;
	case R_C: registers->c = value; break;
	case R_D: registers->d = value; break;
	case R_E: registers->e = value; break;
	case R_H: registers->h = value; break;
	case R_L: registers->l = value; break;
	case R_BC: set_register_combination(registers, R_B, R_C, value); break;
	case R_DE: set_register_combination(registers, R_D, R_E, value); break;
	case R_HL: set_register_combination(registers, R_H, R_L, value); break;
	case R_SP: registers->sp = value; break;
	case R_PC: registers->pc = value; break;
	default: break;
    }
}
u16 getAFregister() {

}

void print_registers(Registers* registers) {
	if (registers) {
		printf("A: %d\n", registers->a);
		printf("B: %d\n", registers->b);
		printf("C: %d\n", registers->c);
		printf("D: %d\n", registers->d);
		printf("E: %d\n", registers->e);
		printf("H: %d\n", registers->h);
		printf("L: %d\n", registers->l);
		printf("SP: %d\n", registers->sp);
		printf("PC: %d\n", registers->pc);
	}
}

u8* get_pointer_to_register(Registers* registers, Register reg) {
	switch (reg) {
	case R_A: return &registers->a;
	case R_B: return &registers->b;
	case R_C: return &registers->c;
	case R_D: return &registers->d;
	case R_E: return &registers->e;
	case R_H: return &registers->h;
	case R_L: return &registers->l;
	case R_SP: return &registers->sp;
	case R_PC: return &registers->pc;
	default: return NULL;
	}
}