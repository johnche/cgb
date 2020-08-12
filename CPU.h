#pragma once
#include <stdint.h>

#define ZERO_FLAG 0x80
#define SUBTRACT_FLAG 0x40
#define HALFCARRY_FLAG 0x20
#define CARRY_FLAG 0x10

typedef struct cpu_clock {
	unsigned int m;
	unsigned int t;
} Clock;

typedef struct CPU{
	Clock clock;

	// 8-bit registers
	uint8_t a, b, c, d, e, h, l, f;

	// 16-bit registers
	uint16_t pc; // Program counter
	uint16_t sp; // Stack pointer

	// Clock for last instruction
	unsigned int m;
	unsigned int t;
} Z80;

Z80* Z80_init();
void cpuDispatcher(Z80* cpu);

