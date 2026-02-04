package emulator

// #cgo CFLAGS: -I${SRCDIR}/../../include
// #cgo windows CFLAGS: -DTHREADS -D_WIN32
// #cgo linux CFLAGS: -DTHREADS -D__linux__
// #cgo LDFLAGS: -L${SRCDIR}/../../build -lgbcore
// #cgo linux LDFLAGS: -lpthread
//
// #include "emu_api.h"
// #include "cart.h"
// #include "bus.h"
// #include "cpu.h"
// #include "ppu.h"
// #include "timer.h"
// #include "dma.h"
// #include "interrupts.h"
// #include "io.h"
// #include "lcd.h"
// #include "ram.h"
// #include "stack.h"
// #include "gamepad.h"
// #include "dbg.h"
// #include "emu.h"
// #include "ppu_sm.h"
// #include <stdlib.h>
//
// // Forward declarations for Go exports
// extern void go_delay_ms(uint32_t ms);
// extern uint32_t go_get_ticks_ms(void);
import "C"

import (
	"errors"
	"fmt"
	"runtime"
	"unsafe"
)

type Emulator struct {
	running bool
}

type InputState struct {
	A, B, Start, Select   bool
	Up, Down, Left, Right bool
}

func New(romPath string) (*Emulator, error) {
	if ret := C.emu_api_init(); ret != 0 {
		return nil, errors.New("failed to initialize emulator core")
	}
	cPath := C.CString(romPath)
	defer C.free(unsafe.Pointer(cPath))
	ret := C.emu_api_load_rom(cPath)
	if ret != 0 {
		C.emu_api_shutdown()
		switch ret {
		case -1:
			return nil, fmt.Errorf("failed to load ROM: file error (%s)", romPath)
		case -2:
			return nil, fmt.Errorf("unsupported cartridge type in ROM: %s", romPath)
		default:
			return nil, fmt.Errorf("unknown error loading ROM: %s", romPath)
		}
	}
	return &Emulator{running: false}, nil
}

func (e *Emulator) Start() error {
	if e.running {
		return errors.New("emulator already running")
	}
	if ret := C.emu_api_start(); ret != 0 {
		return errors.New("failed to start CPU thread")
	}
	e.running = true
	return nil
}

func (e *Emulator) Stop() {
	if e.running {
		C.emu_api_stop()
		e.running = false
	}
}

func (e *Emulator) SwapBuffers() bool {
	return bool(C.emu_api_swap_buffers())
}

func (e *Emulator) Framebuffer() []byte {
	ptr := C.emu_api_get_front_buffer()
	w := int(C.emu_api_get_width())
	h := int(C.emu_api_get_height())
	size := w * h * 4
	fb := unsafe.Slice((*byte)(unsafe.Pointer(ptr)), size)
	runtime.KeepAlive(ptr)
	return fb
}

func (e *Emulator) SetInput(state InputState) {
	var mask C.uint8_t
	if state.A {
		mask |= 0x01
	}
	if state.B {
		mask |= 0x02
	}
	if state.Select {
		mask |= 0x04
	}
	if state.Start {
		mask |= 0x08
	}
	if state.Right {
		mask |= 0x10
	}
	if state.Left {
		mask |= 0x20
	}
	if state.Up {
		mask |= 0x40
	}
	if state.Down {
		mask |= 0x80
	}
	C.emu_api_set_input(mask)
}

func (e *Emulator) SetPaused(paused bool) {
	C.emu_api_set_paused(C.bool(paused))
}

func (e *Emulator) Close() {
	e.Stop()
	C.emu_api_shutdown()
}
