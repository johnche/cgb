#pragma once
#include <stdint.h>

typedef struct cpu_clock {
	unsigned int m;
	unsigned int t;
} Clock;

typedef struct CPU{
	Clock clock;

	// 8-bit registers
	uint8_t a, b, c, d, e, h, l, f;

	// 16-bit registers
	unsigned int pc; // Program counter
	unsigned int sp; // Stack pointer

	// Clock for last instruction
	unsigned int m;
	unsigned int t;
} Z80;

