#include "Cpu.h"

CPU* get_cpu() {
	CPU* cpu = (CPU*)malloc(sizeof(CPU));
	if (!cpu) {
		printf("Memory allocation failed\n");
		return NULL;
	}
	cpu->regs = get_registers();
	cpu->fl = (Flags*)malloc(sizeof(Flags));
	cpu->pc = ZERO_HEX;
	cpu->bus = (memory_bus*)malloc(sizeof(memory_bus));
	return cpu;
}

void destroy_cpu(CPU* cpu) {
	if (cpu) {
		free(cpu->regs);
		free(cpu->fl);
		free(cpu->bus);
		free(cpu);
	}
}

void ADD(CPU* cpu, Register source, Register target) {
	u16 result = *get_pointer_to_register(reg, source) + *get_pointer_to_register(reg, target);
	checkFlags8(cpu, result, INSTR_ADD);
	*get_pointer_to_register(reg, target) = result;
}
void ADD_A(CPU* cpu, Register target) {
	u16 result = reg->a + *get_pointer_to_register(reg, target);
	checkFlags8(cpu, result, INSTR_ADD_A);
	*get_pointer_to_register(reg, target) = (u8) result;
}
void ADD_COMPOUND(CPU* cpu, Register source, Register compound1, Register compound2) {
	u32 result = get_register_combination(
		reg,
		compound1,
		compound2
	) + get_register(reg, source);
	checkFlags16(cpu, result, INSTR_ADD_COMPOUND);
	set_register_combination(reg,compound1,compound2,result);
}

void ADC(CPU* cpu, Register target) {
	u16 result = reg->a + *get_pointer_to_register(reg, target) + cpu->fl->carry;
	checkFlags8(cpu, result, INSTR_ADC);
	reg->a =result ;
}
void SUB(CPU* cpu, Register target) {
	u16 result = reg->a - *get_pointer_to_register(reg, target);
	checkFlags8(cpu, result, INSTR_SUB);
	reg->a = result;
}
void SBC(CPU* cpu, Register target) {
	uint16_t result = reg->a - *get_pointer_to_register(reg, target) - cpu->fl->carry;
	checkFlags8(cpu, result, INSTR_SBC);
	reg->a = result;
}
void AND(CPU* cpu, Register target) {
	u16 result = reg->a & *get_pointer_to_register(reg, target);
	checkFlags8(cpu, result, INSTR_AND);
	reg->a = result;
}
void OR(CPU* cpu, Register target) {
	u16 result = reg->a | *get_pointer_to_register(reg, target);
	checkFlags8(cpu, result, INSTR_OR);
	reg->a = result;
}
void XOR(CPU* cpu, Register target) {
	u16 result = reg->a ^ *get_pointer_to_register(reg, target);
	checkFlags8(cpu, result, INSTR_XOR);
	reg->a = reg->a ^ *get_pointer_to_register(reg, target);
}
void CP(CPU* cpu, Register target) {
	u16 result = reg->a - *get_pointer_to_register(reg, target) - cpu->fl->carry;
	checkFlags8(cpu, result, INSTR_SBC);
}
void INC(CPU* cpu, Register target) {
	u16 result = *get_pointer_to_register(reg, target) + ONE;
	checkFlags8(cpu, result, INSTR_INC);
	*get_pointer_to_register(reg, target) = result;
}
void DEC(CPU* cpu, Register target) {
	u16 result = *get_pointer_to_register(reg, target) - ONE;
	checkFlags8(cpu, result, INSTR_DEC);
	*get_pointer_to_register(reg, target) = result;
}
void CCF(CPU* cpu) {
	cpu->fl->carry = cpu->fl->carry ^ ONE;
}
void SCF(CPU* cpu) {
	cpu->fl->carry = ONE;
}
void RRA(CPU* cpu) {
	u8 new_carry = reg->a & ONE;
	reg->a = reg->a >> ONE;
	cpu->fl->carry = new_carry;
}
void RLA(CPU* cpu) {
	u8 new_carry = reg->a & ONE;
	reg->a = reg->a << ONE;
	cpu->fl->carry = new_carry;
}
void RRCA(CPU* cpu) {
	reg->a = reg->a >> ONE;
}
void RRLA(CPU* cpu) {
	reg->a = reg->a << ONE;
}
void CPL(CPU* cpu) {
	reg->a = ~reg->a;
}
void BIT(CPU* cpu, u8 bit, Register target) {
	u8 register_value = *get_pointer_to_register(reg, target);
	(register_value & (ONE << bit)) >> bit;
}
void RESET(CPU* cpu, u8 bit, Register target) {
	u8 result = *get_pointer_to_register(reg, target) & ~(ONE << bit);
	*get_pointer_to_register(reg, target) = result;
}
void SET(CPU* cpu, u8 bit, Register target) {
	u8 result = *get_pointer_to_register(reg, target) | (ONE << bit);
	*get_pointer_to_register(reg, target) = result;
}
void SRL(CPU* cpu, Register target) {
	*get_pointer_to_register(reg, target) = *get_pointer_to_register(reg, target) >> ONE;
}
void RR(CPU* cpu, Register target) {
	*get_pointer_to_register(reg, target) = *get_pointer_to_register(reg, target) >> ONE;
}
void RL(CPU* cpu, Register target) {
	*get_pointer_to_register(reg, target) = *get_pointer_to_register(reg, target) << ONE;
}
void RRC(CPU* cpu, Register target) {
	*get_pointer_to_register(reg, target) = *get_pointer_to_register(reg, target) << ONE;
}
void RLC(CPU* cpu, Register target) {
	*get_pointer_to_register(reg, target) = *get_pointer_to_register(reg, target) << ONE;
}
void SRA(CPU* cpu, Register target) {
	*get_pointer_to_register(reg, target) = *get_pointer_to_register(reg, target) >> ONE;
}
void SLA(CPU* cpu, Register target) {
	*get_pointer_to_register(reg, target) = *get_pointer_to_register(reg, target) << ONE;
}
void SWAP(CPU* cpu, Register target1, Register target2) {
	u8 temp = *get_pointer_to_register(reg, target1);
	*get_pointer_to_register(reg, target1) = *get_pointer_to_register(reg, target2);
	*get_pointer_to_register(reg, target2) = temp;
}
void setFlagSubtract(CPU* cpu, InstructionName instruction_name){
	if (instruction_name == INSTR_SUB 
			|| instruction_name == INSTR_SBC 
			|| instruction_name == INSTR_CP)
		cpu->fl->subtract = ONE;
}
void setFlagZero(CPU* cpu, u16 result) {
	if (result == ZERO_HEX)
		cpu->fl->zero = ONE;
	else cpu->fl->zero = ZERO_HEX;
}
void setFlagCarry(CPU* cpu, u16 result) {
	if (result - 1 > MAX_16_BIT)
		cpu->fl->carry = ONE;
	else cpu->fl->carry = ZERO_HEX;
}
void setFlagHalfCarry(CPU* cpu, u16 result) {
	result = result << 8;
	if(MAX_8_BIT);
}
void checkFlags8(CPU* cpu, u16 result, InstructionName instruction_name) {
	setFlagCarry(cpu, result);
	setFlagZero(cpu, result);
	setFlagSubtract(cpu, instruction_name);
	setFlagHalfCarry(cpu, result);
}
void checkFlags16(CPU* cpu, u32 result, InstructionName instruction_name) {
	setFlagCarry(cpu, result);
	setFlagZero(cpu, result);
	setFlagSubtract(cpu, instruction_name);
	setFlagHalfCarry(cpu, result);
}