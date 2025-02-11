#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define ONE 0x01
#define ZERO_HEX 0x00
#define MAX_16_BIT 0xFF
#define MAX_8_BIT 0x0F
#define u64 unsigned int
#define u32 uint32_t
#define u16 uint16_t
#define u8 uint8_t

#define BIT(a, n) ((a & (1 << n)) ? 1 : 0)
#define BIT_SET(a, n, on) { if (on) a |= (1 << n); else a &= ~(1 << n);}