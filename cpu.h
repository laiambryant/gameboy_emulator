#pragma once
#include "Registers.h"
#include "memory_bus.h"
#define reg cpu->registers


typedef struct CPU {
	Registers* registers;
	Flags* flags;
	uint16_t pc;
	memory_bus* bus;
} CPU;

//Initializes the CPU
CPU* get_cpu();
//Destroys the CPU
void destroy_cpu(CPU* cpu);
//ADD (add) - add the value stored in the source register with the value in the target register
void ADD(CPU* cpu, Register source, Register target);
//ADD (add) - add the value stored in a specific register with the value in the A register
void ADD_A(CPU* cpu, Register source);
//ADD (add) - add the value stored in a register to the compound register composed of two registers (e.g. HL)
void ADD_COMPOUND(CPU* cpu, Register compound1, Register compound2, Register source);
//ADC (add with carry) - just like ADD except that the value of the carry flag is also added to the number
void ADC(CPU* cpu, Register target);
//SUB (subtract) - subtract the value stored in a specific register with the value in the A register
void SUB(CPU* cpu, Register target);
//SBC (subtract with carry) - just like ADD except that the value of the carry flag is also subtracted from the number
void SBC(CPU* cpu, Register target);
//AND (logical and) - do a bitwise and on the value in a specific register and the value in the A register
void AND(CPU* cpu, Register target);
//OR (logical or) - do a bitwise or on the value in a specific register and the value in the A register
void OR(CPU* cpu, Register target);
//XOR (logical xor) - do a bitwise xor on the value in a specific register and the value in the A register
void XOR(CPU* cpu, Register target);
//CP (compare) - just like SUB except the result of the subtraction is not stored back into A
void CP(CPU* cpu, Register target);
//INC (increment) - increment the value in a specific register by 1
void INC(CPU* cpu, Register target);
//DEC (decrement) - decrement the value in a specific register by 1
void DEC(CPU* cpu, Register target);
//CCF (complement carry flag) - toggle the value of the carry flag
void CCF(CPU* cpu);
//SCF (set carry flag) - set the carry flag to true
void SCF(CPU* cpu);
//RRA (rotate right A register) - bit rotate A register right through the carry flag
void RRA(CPU* cpu);
//RLA (rotate left A register) - bit rotate A register left through the carry flag
void RLA(CPU* cpu);
//RRCA (rotate right A register) - bit rotate A register right (not through the carry flag)
void RRCA(CPU* cpu);
//RRLA (rotate left A register) - bit rotate A register left (not through the carry flag)
void RRLA(CPU* cpu);
//CPL (complement) - toggle every bit of the A register
void CPL(CPU* cpu);
//BIT (bit test) - test to see if a specific bit of a specific register is set
void BIT(CPU* cpu, uint8_t bit, Register target);
//RESET (bit reset) - set a specific bit of a specific register to 0
void RESET(CPU* cpu, uint8_t bit, Register target);
//SET (bit set) - set a specific bit of a specific register to 1
void SET(CPU* cpu, uint8_t bit, Register target);
//SRL (shift right logical) - bit shift a specific register right by 1
void SRL(CPU* cpu, Register target);
//RR (rotate right) - bit rotate a specific register right by 1 through the carry flag
void RR(CPU* cpu, Register target);
//RL (rotate left) - bit rotate a specific register left by 1 through the carry flag
void RL(CPU* cpu, Register target);
//RRC (rorate right) - bit rotate a specific register right by 1 (not through the carry flag)
void RRC(CPU* cpu, Register target);
//RLC (rorate left) - bit rotate a specific register left by 1 (not through the carry flag)
void RLC(CPU* cpu, Register target);
//SRA (shift right arithmetic) - arithmetic shift a specific register right by 1
void SRA(CPU* cpu, Register target);
//SLA (shift left arithmetic) - arithmetic shift a specific register left by 1
void SLA(CPU* cpu, Register target);
//SWAP (swap nibbles) - switch upper and lower nibble of a specific register
void SWAP(CPU* cpu, Register targets);