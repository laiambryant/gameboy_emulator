#include "cpu_proc.h"


static void proc_none(CPU* ctx) {
    printf("INVALID INSTRUCTION!\n");
    exit(-7);
}

static void proc_nop(CPU* ctx) {

}

static void proc_di(CPU* ctx) {
    ctx->int_master_enabled = 0;
}

static void proc_ld(CPU* ctx) {
    //TODO...
}

void cpu_set_flags(CPU* ctx, char z, char n, char h, char c) {
    if (z != -1) {
        BIT_SET(ctx->regs.f, 7, z);
    }

    if (n != -1) {
        BIT_SET(ctx->regs.f, 6, n);
    }

    if (h != -1) {
        BIT_SET(ctx->regs.f, 5, h);
    }

    if (c != -1) {
        BIT_SET(ctx->regs.f, 4, c);
    }
}

static void proc_xor(CPU* ctx) {
    ctx->regs.a ^= ctx->fetched_data & 0xFF;
    cpu_set_flags(ctx, ctx->regs.a == 0, 0, 0, 0);
}


static u8 check_cond(CPU* ctx) {
    u8 z = ctx->fl.zero;
    u8 c = ctx->fl.carry;

    switch (ctx->curr_instr->condition) {
    case CT_NONE: return 1;
    case CT_C: return c;
    case CT_NC: return !c;
    case CT_Z: return z;
    case CT_NZ: return !z;
    }

    return 0;
}

static void proc_jp(CPU* ctx) {
    if (check_cond(ctx)) {
        ctx->regs.pc = ctx->fetched_data;
    }
}

static instruction_func processors[] = {
    [INSTR_NONE] = proc_none,
    [INSTR_NOP] = proc_nop,
    [INSTR_LD] = proc_ld,
    [INSTR_JP] = proc_jp,
    [INSTR_DI] = proc_di,
    [INSTR_XOR] = proc_xor
};

instruction_func instruction_get_processor(InstructionName type) {
    printf("Getting processor for instruction: %d\n", type);
    return processors[type];
}

char* get_instruction_name(InstructionName type) {
    switch (type) {
	case INSTR_NOP: return "NOP";
	case INSTR_JP: return "JP a16";
	case INSTR_DI: return "DI";
    case INSTR_LD: return "LD C, d8";
	case INSTR_XOR: return "XOR A";
    default: return "UNKNOWN";
    }
}