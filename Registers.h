#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Registers {
    uint8_t a, b, c, d, e, h, l;
} Registers;

typedef struct Flags {
    uint8_t zero, subtract, half_carry, carry;
} Flags;

typedef enum Register {
	A,B,C,D,E,H,L
} Register;

typedef enum Flag {
	ZERO, SUBTRACT, HALF_CARRY, CARRY
} Flag;

Registers* get_registers();
void init_registers(Registers* registers);
uint16_t get_register_combination(Registers* registers, Register register1, Register register2);
uint16_t set_register_combination(Registers* registers, Register register1, Register register2, uint16_t value);
uint8_t get_register(Registers* registers, Register reg);
uint8_t set_register(Registers* registers, Register reg, uint8_t value);
void print_registers(Registers* registers);
uint8_t* get_pointer_to_register(Registers* registers, Register reg);