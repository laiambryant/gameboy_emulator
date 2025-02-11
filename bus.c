#include "bus.h"

u8 bus_read( u16 addr) {
	if (addr >= ROM_BANK_0_START && addr <= ROM_BANK_0_END) {
		return cart_read(addr);
	}
	if (addr >= ROM_BANK_1_START && addr <= ROM_BANK_1_END) {
		return 0;
	}
	if (addr >= CHR_RAM_START && addr <= CHR_RAM_END) {
		return 0;
	}
	if (addr >= CARTRIDGE_RAM_START && addr <= CARTRIDGE_RAM_END) {
		return 0;
	}
	if (addr >= RAM_BANK_0_START && addr <= RAM_BANK_0_END) {
		return 0;
	}
	if (addr >= RAM_BANK_1_7_START && addr <= RAM_BANK_1_7_END) {
		return 0;
	}
	if (addr >= ECHO_RAM_START && addr <= ECHO_RAM_END) {
		return 0;
	}
	if (addr >= OAM_START && addr <= OAM_END) {
		return 0;
	}
	if (addr >= UNUSED_START && addr <= UNUSED_END) {
		return 0;
	}
	if (addr >= IO_REGISTERS_START && addr <= IO_REGISTERS_END) {
		return 0;
	}
	if (addr >= ZERO_PAGE_START && addr <= ZERO_PAGE_END) {
		return 0;
	}
	return 0;
}

void bus_write( u16 addr, u8 data) {
	if (addr >= ROM_BANK_0_START && addr <= ROM_BANK_0_END) {
		cart_write( addr, data);
		return;
	}
	if (addr >= ROM_BANK_1_START && addr <= ROM_BANK_1_END) {
		return;
	}
	if (addr >= CHR_RAM_START && addr <= CHR_RAM_END) {
		return;
	}
	if (addr >= CARTRIDGE_RAM_START && addr <= CARTRIDGE_RAM_END) {
		return;
	}
	if (addr >= RAM_BANK_0_START && addr <= RAM_BANK_0_END) {
		return;
	}
	if (addr >= RAM_BANK_1_7_START && addr <= RAM_BANK_1_7_END) {
		return;
	}
	if (addr >= ECHO_RAM_START && addr <= ECHO_RAM_END) {
		return;
	}
	if (addr >= OAM_START && addr <= OAM_END) {
		return;
	}
	if (addr >= UNUSED_START && addr <= UNUSED_END) {
		return;
	}
	if (addr >= IO_REGISTERS_START && addr <= IO_REGISTERS_END) {
		return;
	}
	if (addr >= ZERO_PAGE_START && addr <= ZERO_PAGE_END) {
		return;
	}
	return;
}