#ifndef EMU_API_H
#define EMU_API_H

#include <stdint.h>
#include <stdbool.h>

// ============================================================================
// Initialization & Shutdown
// ============================================================================

/**
 * Initialize the emulator core.
 * Must be called before any other functions.
 *
 * @return 0 on success, -1 on failure
 */
int emu_api_init(void);

/**
 * Shutdown and cleanup all emulator resources.
 * Safe to call even if init failed.
 */
void emu_api_shutdown(void);

// ============================================================================
// ROM Loading
// ============================================================================

/**
 * Load a Game Boy ROM from file.
 *
 * @param path Filesystem path to .gb or .gbc file
 * @return 0 on success
 *        -1 on file I/O error
 *        -2 on unsupported cartridge type
 */
int emu_api_load_rom(const char* path);

// ============================================================================
// CPU Thread Control
// ============================================================================

/**
 * Start the emulator CPU thread.
 * Thread runs cpu_run() loop until stopped.
 *
 * @return 0 on success, -1 on thread creation failure
 */
int emu_api_start(void);

/**
 * Stop the CPU thread gracefully.
 * Blocks until thread has fully stopped.
 */
void emu_api_stop(void);

/**
 * Pause/unpause emulation.
 *
 * @param paused true to pause, false to resume
 */
void emu_api_set_paused(bool paused);

// ============================================================================
// Framebuffer Access (Double-Buffered)
// ============================================================================

/**
 * Get pointer to the front buffer (safe for reading).
 * Buffer contains RGBA8888 pixels in row-major order.
 *
 * @return Pointer to uint32_t array of size [width * height]
 */
uint32_t* emu_api_get_front_buffer(void);

/**
 * Get pointer to the back buffer (used by PPU rendering).
 *
 * @return Pointer to uint32_t array of size [width * height]
 */
uint32_t* emu_api_get_back_buffer(void);

/**
 * Get framebuffer width in pixels.
 *
 * @return Width (always 160 for Game Boy)
 */
int emu_api_get_width(void);

/**
 * Get framebuffer height in pixels.
 *
 * @return Height (always 144 for Game Boy)
 */
int emu_api_get_height(void);

/**
 * Check if a new frame is ready and swap buffers if so.
 * Call this each rendering loop iteration.
 *
 * @return true if buffers were swapped (new frame available)
 *         false if no new frame since last swap
 */
bool emu_api_swap_buffers(void);

/**
 * Notify the API that a frame is complete and swap buffers.
 * Called by the PPU on the last scanline.
 */
void emu_api_frame_complete(void);

// ============================================================================
// Input
// ============================================================================

/**
 * Set the current input state.
 *
 * @param input_state 8-bit bitmask:
 *   bit 0 (0x01): A button
 *   bit 1 (0x02): B button
 *   bit 2 (0x04): Select
 *   bit 3 (0x08): Start
 *   bit 4 (0x10): Right
 *   bit 5 (0x20): Left
 *   bit 6 (0x40): Up
 *   bit 7 (0x80): Down
 */
void emu_api_set_input(uint8_t input_state);

// ============================================================================
// Timing Callbacks (Implemented in Go, called by C)
// ============================================================================

/**
 * Delay execution for specified milliseconds.
 * Implemented by Go runtime (time.Sleep).
 */
extern void go_delay_ms(uint32_t ms);

/**
 * Get elapsed milliseconds since emulator start.
 * Implemented by Go runtime (time.Since).
 *
 * @return Milliseconds as uint32_t
 */
extern uint32_t go_get_ticks_ms(void);

#endif // EMU_API_H
