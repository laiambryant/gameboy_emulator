#include "bus.h"
#include "cart.h"
#include "ram.h"
#include "io.h"
#include "cpu.h"
#include "ppu.h"
#include "dma.h"

u8 bus_read(u16 address) {    if (address < 0x8000) {
        return cart_read(address);
    } else if (address < 0xA000) {
        return ppu_vram_read(address);
    } else if (address < 0xC000) {
        return cart_read(address);
    } else if (address < 0xE000) {
        return wram_read(address);
    } else if (address < 0xFE00) {
        return 0;
    } else if (address < 0xFEA0) {
        if (dma_transferring()) {
            return 0xFF;
        }
        return ppu_oam_read(address);
    } else if (address < 0xFF00) {
        return 0;
    } else if (address < 0xFF80) {
        return io_read(address);
    } else if (address == 0xFFFF) {
        return cpu_get_ie_register();
    }
    return hram_read(address);
}

void bus_write(u16 address, u8 value) {    if (address < 0x8000) {
        cart_write(address, value);
    } else if (address < 0xA000) {
        ppu_vram_write(address, value);
    } else if (address < 0xC000) {
        cart_write(address, value);
    } else if (address < 0xE000) {
        wram_write(address, value);
    } else if (address < 0xFE00) {
    } else if (address < 0xFEA0) {
        if (dma_transferring()) {
            return;
        }
        ppu_oam_write(address, value);
    } else if (address < 0xFF00) {
    } else if (address < 0xFF80) {
        io_write(address, value);
    } else if (address == 0xFFFF) {
        cpu_set_ie_register(value);
    } else {
        hram_write(address, value);
    }
}

u16 bus_read16(u16 address) {    u16 lo = bus_read(address);
    u16 hi = bus_read(address + 1);
    return lo | (hi << 8);
}

void bus_write16(u16 address, u16 value) {    bus_write(address + 1, (value >> 8) & 0xFF);
    bus_write(address, value & 0xFF);
}
