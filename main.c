#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "MMU.h"
#include "Z80.h"

int main(int argc, char** argv) {
	if (argc == 2) {
		initMMU();
		loadCartridge(argv[1]);
		Z80* cpu = Z80_init();
		Z80_printCPUState(cpu);
		cpuDispatcher(cpu);
		return 0;
	}

	printf("Missing argument. Exiting.\n");
	return 1;
}

