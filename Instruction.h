#pragma once
#include "Common.h"
#include "Registers.h"

typedef enum InstructionName {
    INSTR_NONE, INSTR_NOP, INSTR_LD, INSTR_INC, INSTR_DEC, INSTR_RLCA, INSTR_ADD, INSTR_RRCA,
	INSTR_STOP, INSTR_RLA, INSTR_JR, INSTR_RRA, INSTR_DAA, INSTR_CPL, INSTR_SCF, INSTR_CCF,
    INSTR_HALT, INSTR_ADC, INSTR_SUB, INSTR_SBC, INSTR_AND, INSTR_XOR, INSTR_OR, INSTR_CP,
    INSTR_POP, INSTR_JP, INSTR_PUSH, INSTR_RET, INSTR_CB, INSTR_CALL, INSTR_RETI, INSTR_LDH,
    INSTR_JPHL, INSTR_DI, INSTR_EI, INSTR_RST, INSTR_ERR, INSTR_RLC, INSTR_RRC, INSTR_RL, 
    INSTR_RR, INSTR_SLA, INSTR_SRA, INSTR_SWAP, INSTR_SRL, INSTR_BIT, INSTR_RES, INSTR_SET
} InstructionName;

typedef enum addressing_mode {
	AM_R_D16, AM_R_R, AM_MR_R, AM_R, AM_R_D8, AM_R_MR, AM_R_HLI, AM_R_HLD, AM_HLI_R, AM_HLD_R, 
    AM_R_A8 , AM_A8_R, AM_HL_SPR, AM_D16, AM_D8, AM_IMP, AM_D16_R, AM_MR_D8, AM_MR, AM_A16_R, AM_R_A16
} addressing_mode;

typedef enum register_type {
	RT_NONE, RT_A, RT_B, RT_C, RT_D, RT_E, RT_H, RT_L, 
    RT_AF, RT_BC, RT_DE, RT_HL, RT_SP, RT_PC
} register_type;

typedef enum condition_type {
	CT_NONE, CT_NZ, CT_Z, CT_NC, CT_C
} condition_type;

typedef struct Instruction {
    InstructionName instruction_name;
	Register reg1;
    Register reg2;
	addressing_mode mode;
	condition_type condition;
    u8 param;
} Instruction;

Instruction get_instruction(u8 opcode);