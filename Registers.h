#pragma once
#include "Common.h"

typedef struct Registers {
    u8 a, b, c, d, e, h, l;
	u16 sp, pc;
} Registers;

typedef struct Flags {
	u8 zero, subtract, half_carry, carry;
} Flags;

typedef enum Register {
	R_NONE, R_A, R_B, R_C, R_D, R_E, R_H, R_L,
	R_AF, R_BC, R_DE, R_HL, R_SP, R_PC
} Register;

typedef enum Flag {
	ZERO, SUBTRACT, HALF_CARRY, CARRY
} Flag;

Registers* get_registers();
void init_registers(Registers* registers);
u16 get_register_combination(Registers* registers, Register register1, Register register2);
u16 set_register_combination(Registers* registers, Register register1, Register register2, u16 value);
u16 get_register(Registers* registers, Register reg);
void set_register(Registers* registers, Register reg, u8 value);
void print_registers(Registers* registers);
u8* get_pointer_to_register(Registers* registers, Register reg);