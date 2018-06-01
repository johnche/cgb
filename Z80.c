#include "Z80.h"

Z80* Z80_init() {
	Z80 cpu;
	return &cpu;
}

void NOP(Z80* cpu) {
	cpu->m++;
}

