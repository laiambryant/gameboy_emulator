package emulator

// #include <stdint.h>
import "C"

import "time"

var startTime = time.Now()

//export go_delay_ms
func go_delay_ms(ms C.uint32_t) {
	time.Sleep(time.Duration(ms) * time.Millisecond)
}

//export go_get_ticks_ms
func go_get_ticks_ms() C.uint32_t {
	elapsed := time.Since(startTime).Milliseconds()
	return C.uint32_t(elapsed)
}
