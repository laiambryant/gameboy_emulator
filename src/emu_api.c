#include "emu_api.h"
#include "cart.h"
#include "common.h"
#include "cpu.h"
#include "emu.h"
#include "gamepad.h"
#include "ppu.h"
#include "timer.h"

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <pthread.h>
#endif

#include <string.h>

// Double buffering state
static uint32_t video_buffer_0[XRES * YRES];
static uint32_t video_buffer_1[XRES * YRES];
static uint32_t *back_buffer = video_buffer_0;
static uint32_t *front_buffer = video_buffer_1;
static volatile bool frame_ready = false;

static bool initialized = false;
#ifdef _WIN32
static HANDLE cpu_thread = NULL;
#elif __linux__
static pthread_t cpu_thread;
static bool cpu_thread_created = false;
#endif

static void *cpu_run(void *p) {
  (void)p;
  timer_init();
  cpu_init();
  ppu_init();
  emu_get_context()->running = true;
  emu_get_context()->paused = false;
  emu_get_context()->ticks = 0;
  while (emu_get_context()->running) {
    if (emu_get_context()->paused) {
      go_delay_ms(10);
      continue;
    }
    if (!cpu_step()) {
      printf("CPU Stopped\n");
      emu_get_context()->running = false;
      break;
    }
  }
  return 0;
}

int emu_api_init(void) {
  if (initialized) {
    return 0;
  }
  emu_get_context()->die = false;
  memset(video_buffer_0, 0, sizeof(video_buffer_0));
  memset(video_buffer_1, 0, sizeof(video_buffer_1));
  initialized = true;
  return 0;
}

void emu_api_shutdown(void) {
  emu_api_stop();
  initialized = false;
}

int emu_api_load_rom(const char *path) {
  if (!path) {
    return -1;
  }
  if (!cart_load((char *)path)) {
    return -1;
  }
  if (!cart_supported()) {
    return -2;
  }
  return 0;
}

int emu_api_start(void) {
  if (!initialized) {
    if (emu_api_init() != 0) {
      return -1;
    }
  }
  if (emu_get_context()->running) {
    return 0;
  }
#ifdef _WIN32
  cpu_thread =
      CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)cpu_run, NULL, 0, NULL);
  if (!cpu_thread) {
    return -1;
  }
#elif __linux__
  if (pthread_create(&cpu_thread, NULL, cpu_run, NULL) != 0) {
    return -1;
  }
  cpu_thread_created = true;
#endif
  return 0;
}

void emu_api_stop(void) {
  if (!emu_get_context()->running) {
    return;
  }
  emu_get_context()->running = false;
#ifdef _WIN32
  if (cpu_thread) {
    WaitForSingleObject(cpu_thread, INFINITE);
    CloseHandle(cpu_thread);
    cpu_thread = NULL;
  }
#elif __linux__
  if (cpu_thread_created) {
    pthread_join(cpu_thread, NULL);
    cpu_thread_created = false;
  }
#endif
}

void emu_api_set_paused(bool paused) { emu_get_context()->paused = paused; }

uint32_t *emu_api_get_front_buffer(void) { return front_buffer; }

uint32_t *emu_api_get_back_buffer(void) { return back_buffer; }

int emu_api_get_width(void) { return XRES; }

int emu_api_get_height(void) { return YRES; }

bool emu_api_swap_buffers(void) {
  if (frame_ready) {
    frame_ready = false;
    return true;
  }
  return false;
}

void emu_api_frame_complete(void) {
  uint32_t *tmp = back_buffer;
  back_buffer = front_buffer;
  front_buffer = tmp;
  frame_ready = true;
}

void emu_api_set_input(uint8_t input_state) {
  gamepad_state *state = gamepad_get_state();
  state->a = (input_state & 0x01) != 0;
  state->b = (input_state & 0x02) != 0;
  state->select = (input_state & 0x04) != 0;
  state->start = (input_state & 0x08) != 0;
  state->right = (input_state & 0x10) != 0;
  state->left = (input_state & 0x20) != 0;
  state->up = (input_state & 0x40) != 0;
  state->down = (input_state & 0x80) != 0;
}
