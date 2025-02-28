# gameboy_emulator

A game Boy emulator written in C and running on SDL3.

## Useful information

The emulator supports controllers and includes also a debug window that shows all the sprites currently loaded in memory.

![alt text](<resources/images/pkmn red gif.gif>)

To run it on your own device you must have SDL3 installed. My makefile expects you to have an SDL/build folder containing SDL3. At the time i am writing this the current version is the 3.2.4. You can download SDL [here](https://www.libsdl.org/).

To build just run 
``` bash
make
```
 while in the root directory and to run just run 

``` bash
make run
```

You can pass Supports MBC1, MBC2 And MBC3 cartridges. Tested on The Legend of Zelda Link's Awakening and Pokemon Red

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