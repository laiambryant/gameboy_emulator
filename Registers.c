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
	}
}

uint16_t get_register_combination(Registers* registers, Register register1, Register register2) {
    if (registers)
        return (get_register(registers, register1) << 8) | get_register(registers, register2);
    return 1;
}

uint16_t set_register_combination(Registers* registers, Register register1, Register register2, uint16_t value) {
	if (registers) {
		set_register(registers, register1, value >> 8);
		set_register(registers, register2, value & 0xFF);
		return 0;
	}
    return 1;
}

uint8_t get_register(Registers* registers, Register reg) {
    switch (reg) {
        case A: return registers->a;
        case B: return registers->b;
        case C: return registers->c;
        case D: return registers->d;
        case E: return registers->e;
        case H: return registers->h;
        case L: return registers->l;
        default: return 1; 
    }
}
uint8_t set_register(Registers* registers, Register reg, uint8_t value) {
    switch (reg) {
	case A: registers->a = value; return 0;
	case B: registers->b = value; return 0;
	case C: registers->c = value; return 0;
	case D: registers->d = value; return 0;
	case E: registers->e = value; return 0;
	case H: registers->h = value; return 0;
	case L: registers->l = value; return 0;
	default: return 1; 
    }
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
	}
}

uint8_t* get_pointer_to_register(Registers* registers, Register reg) {
	switch (reg) {
	case A: return &registers->a;
	case B: return &registers->b;
	case C: return &registers->c;
	case D: return &registers->d;
	case E: return &registers->e;
	case H: return &registers->h;
	case L: return &registers->l;
	default: return NULL;
	}
}