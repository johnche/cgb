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
	uint16_t pc; // Program counter
	uint16_t sp; // Stack pointer

	// Clock for last instruction
	unsigned int m;
	unsigned int t;
} Z80;

uint16_t getPair(uint8_t r1, uint8_t r2) {
	return ((uint16_t) r1 << 8) | (uint16_t) r2;
}

void setPair(uint8_t* r1, uint8_t* r2, uint16_t value) {
	*r1 = value >> 8;
	*r2 = value & 255;
}

uint16_t getAF(Z80* cpu) { return getPair(cpu->a, cpu->f); }
uint16_t getBC(Z80* cpu) { return getPair(cpu->b, cpu->c); }
uint16_t getDE(Z80* cpu) { return getPair(cpu->d, cpu->e); }
uint16_t getHL(Z80* cpu) { return getPair(cpu->h, cpu->l); }
void setAF(Z80* cpu, uint16_t value) { setPair(&cpu->a, &cpu->f, value); }
void setBC(Z80* cpu, uint16_t value) { setPair(&cpu->b, &cpu->c, value); }
void setDE(Z80* cpu, uint16_t value) { setPair(&cpu->d, &cpu->e, value); }
void setHL(Z80* cpu, uint16_t value) { setPair(&cpu->h, &cpu->l, value); }

