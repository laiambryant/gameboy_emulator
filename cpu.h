#pragma once
#include "Registers.h"
#include "memory_bus.h"
#include "Common.h"

#define reg cpu->regs

typedef struct CPU {
    Registers* regs;
    Flags* fl;
    u16 pc;
    memory_bus* bus;
} CPU;

//Instructions
typedef enum InstructionName {
    INSTR_ADD, INSTR_ADD_A, INSTR_ADD_COMPOUND, INSTR_ADC, INSTR_SUB,
    INSTR_SBC, INSTR_AND, INSTR_OR, INSTR_XOR, INSTR_CP, INSTR_INC,
    INSTR_DEC, INSTR_CCF, INSTR_SCF, INSTR_RRA, INSTR_RLA, INSTR_RRCA,
    INSTR_RRLA, INSTR_CPL, INSTR_BIT, INSTR_RESET, INSTR_SET, INSTR_SRL,
    INSTR_RR, INSTR_RL, INSTR_RRC, INSTR_RLC, INSTR_SRA, INSTR_SLA, INSTR_SWAP
} InstructionName;

typedef struct Instruction {
    void* operation;
    InstructionName instruction_name;
} Instruction;

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
void BIT(CPU* cpu, u8 bit, Register target);
//RESET (bit reset) - set a specific bit of a specific register to 0
void RESET(CPU* cpu, u8 bit, Register target);
//SET (bit set) - set a specific bit of a specific register to 1
void SET(CPU* cpu, u8 bit, Register target);
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