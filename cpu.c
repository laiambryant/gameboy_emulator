#pragma once
#include "cpu.h"

CPU* get_cpu() {
	CPU* cpu = (CPU*)malloc(sizeof(CPU));
	if (!cpu) {
		printf("Memory allocation failed\n");
		return NULL;
	}
	cpu->registers = get_registers();
	cpu->flags = (Flags*)malloc(sizeof(Flags));
	cpu->pc = 0;
	cpu->bus = (memory_bus*)malloc(sizeof(memory_bus));
	return cpu;
}

void destroy_cpu(CPU* cpu) {
	if (cpu) {
		free(cpu->registers);
		free(cpu->flags);
		free(cpu->bus);
		free(cpu);
	}
}

void ADD(CPU* cpu, Register source, Register target){
	*get_pointer_to_register(reg, target) = *get_pointer_to_register(reg, source) + *get_pointer_to_register(reg, target);
}
void ADD_A(CPU* cpu,  Register target) {
	*get_pointer_to_register(reg, target) = reg->a + *get_pointer_to_register(reg, target);
}
void ADD_COMPOUND(CPU* cpu, Register source, Register compound1, Register compound2){
	set_register_combination(
		reg,
		compound1,
		compound2,
		get_register_combination(
			reg,
			compound1,
			compound2
		) + get_register(reg, source)
	);
}
void ADC(CPU* cpu, Register target){
	reg->a = reg->a + *get_pointer_to_register(reg, target) + cpu->flags->carry;
}
void SUB(CPU* cpu, Register target){
	reg->a = reg->a - cpu->registers->b;
}
void SBC(CPU* cpu, Register target){

}
void AND(CPU* cpu, Register target){

}
void OR(CPU* cpu, Register target){

}
void XOR(CPU* cpu, Register target){

}
void CP(CPU* cpu, Register target){

}
void INC(CPU* cpu, Register target){

}
void DEC(CPU* cpu, Register target){

}
void CCF(CPU* cpu){

}
void SCF(CPU* cpu){

}
void RRA(CPU* cpu){

}
void RLA(CPU* cpu){

}
void RRCA(CPU* cpu){

}
void RRLA(CPU* cpu){

}
void CPL(CPU* cpu){

}
void BIT(CPU* cpu, uint8_t bit, Register target){

}
void RESET(CPU* cpu, uint8_t bit, Register target){

}
void SET(CPU* cpu, uint8_t bit, Register target){

}
void SRL(CPU* cpu, Register target){

}
void RR(CPU* cpu, Register target){

}
void RL(CPU* cpu, Register target){

}
void RRC(CPU* cpu, Register target){

}
void RLC(CPU* cpu, Register target){

}
void SRA(CPU* cpu, Register target){

}
void SLA(CPU* cpu, Register target){

}
void SWAP(CPU* cpu, Register target){

}


