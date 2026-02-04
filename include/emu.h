#pragma once

#include "common.h"

typedef struct {
  bool paused;
  bool running;
  bool die;
  u64 ticks;
} emu_context;

emu_context *emu_get_context();
void emu_cycles(int cpu_cycles);
