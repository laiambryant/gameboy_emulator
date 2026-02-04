package emulator

func (s InputState) Bitmask() uint8 {	var mask uint8
	if s.A {
		mask |= 0x01
	}
	if s.B {
		mask |= 0x02
	}
	if s.Select {
		mask |= 0x04
	}
	if s.Start {
		mask |= 0x08
	}
	if s.Right {
		mask |= 0x10
	}
	if s.Left {
		mask |= 0x20
	}
	if s.Up {
		mask |= 0x40
	}
	if s.Down {
		mask |= 0x80
	}
	return mask
}
