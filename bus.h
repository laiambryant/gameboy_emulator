#pragma once
#include "Common.h"
#ifndef CARTRIDGE
#define	CARTRIDGE
#include "Cartridge.h"
#endif 


#define ROM_BANK_0_START 0x0000
#define ROM_BANK_0_END 0x3FFF
#define ROM_BANK_1_START 0x4000
#define ROM_BANK_1_END 0x7FFF
#define CHR_RAM_START 0x8000
#define CHR_RAM_END 0x9FFF
#define CARTRIDGE_RAM_START 0xA000
#define CARTRIDGE_RAM_END 0xBFFF
#define RAM_BANK_0_START 0xC000
#define RAM_BANK_0_END 0xCFFF
#define RAM_BANK_1_7_START 0xD000
#define RAM_BANK_1_7_END 0xDFFF
#define ECHO_RAM_START 0xE000
#define ECHO_RAM_END 0xFDFF
#define OAM_START 0xFE00
#define OAM_END 0xFE9F
#define UNUSED_START 0xFEA0
#define UNUSED_END 0xFEFF
#define IO_REGISTERS_START 0xFF00
#define IO_REGISTERS_END 0xFF7F
#define ZERO_PAGE_START 0xFF80
#define ZERO_PAGE_END 0xFFFE

u8 bus_read(u16 addr);
void bus_write(u16 addr, u8 data);