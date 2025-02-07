#include "tests.h"
#include "Emulator.h"

int main(int argc, char** argv) {

	test_registers();
	test_adds();
	Emulator* emulator = get_emulator();
	runEmulator(emulator, argc, argv);
	return 0;

}

