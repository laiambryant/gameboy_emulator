#include "tests.h"
#include "Emulator.h"

int main(int argc, char** argv) {

	test_registers();
	test_adds();
	runEmulator(argc, argv);
	return 0;

}

