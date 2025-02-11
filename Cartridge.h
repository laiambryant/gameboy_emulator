#pragma once
#include "Common.h"

typedef struct rom_header {
    u8 entry[4];
    u8 logo[0x30];
    char title[16];
    u16 new_lic_code;
    u8 sgb_flag;
    u8 type;
    u8 rom_size;
    u8 ram_size;
    u8 dest_code;
    u8 lic_code;
    u8 version;
    u8 checksum;
    u16 global_checksum;
} rom_header;

typedef struct cartridge_context {
    char filename[1024];
    u32 rom_size;
    u8* rom_data;
    rom_header* header;
} cartridge_context;

cartridge_context* init_cart(char* cartridge_path);
int cart_load(cartridge_context* ctx, char* cart);
void print_debug(cartridge_context* ctx);
int read_rom(cartridge_context* ctx, char* cart);
void destroy_cart(cartridge_context* ctx);
u8 cart_read( u16 address);
void cart_write( u16 address, u8 data);