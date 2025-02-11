#include "Instruction.h"

Instruction instructions[0x100] = {
	[0x00]={INSTR_NOP, AM_IMP},
	[0x05]={INSTR_DEC, AM_R, RT_B},
	[0x0E]={INSTR_LD, AM_R_D8, RT_C},
	[0xAF]={INSTR_XOR, AM_R, RT_A},
	[0xC3]={INSTR_JP, AM_D16}
};

Instruction* get_instruction(u8 opcode) {
	return &instructions[opcode];
}