# gameboy_emulator

A Game Boy emulator powered by a C core with a Go (Ebiten) frontend.

## Useful information

The emulator supports keyboard input and currently focuses on the main window. The debug window will return in a future phase.

![alt text](<resources/images/pkmn red gif.gif>)

## Build prerequisites

### Windows
- Go 1.21+
- MinGW-w64 or MSYS2 (gcc) for cgo
  - MSYS2 recommended: https://www.msys2.org/
  - Install gcc: `pacman -S mingw-w64-x86_64-gcc`
- Environment variables:
  ```bash
  set CGO_ENABLED=1
  set CC=gcc
  ```

### Linux
- Go 1.21+
- GCC (`sudo apt install build-essential`)

## Build

```bash
go build -o gameboy.exe .
```

## Run

```bash
gameboy.exe path/to/rom.gb
```

Supports MBC1 and MBC3 cartridges. Tested on The Legend of Zelda Link's Awakening and Pokemon Red.

## References

This project would not have been possible without the following resources:

- https://gbdev.io/pandocs/
- https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
- https://archive.org/details/GameBoyProgManVer1.1/page/n85/mode/2up
- https://github.com/rockytriton

## Further improvements

There are still more things that could be implemented: 

- Mapping more memory modes
- GBC support
- Save states
- Speedup
- Custom resolutions
- etc.

Feel free to iterate over this software should you want to

Should you want to run it on windows you can find the vscode project on the "windows" branch
