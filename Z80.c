#include "Z80.h"
#include "MMU.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

uint16_t getPair(uint8_t r1, uint8_t r2) {
	return ((uint16_t) r1 << 8) | (uint16_t) r2;
}

void setPair(uint8_t* r1, uint8_t* r2, uint16_t value) {
	*r1 = value & 0x00FF;
	*r2 = (value & 0xFF00) >> 8;
}

uint16_t getAF(Z80* cpu) { return getPair(cpu->a, cpu->f); }
uint16_t getBC(Z80* cpu) { return getPair(cpu->b, cpu->c); }
uint16_t getDE(Z80* cpu) { return getPair(cpu->d, cpu->e); }
uint16_t getHL(Z80* cpu) { return getPair(cpu->h, cpu->l); }
void setAF(Z80* cpu, uint16_t value) { setPair(&cpu->a, &cpu->f, value); }
void setBC(Z80* cpu, uint16_t value) { setPair(&cpu->b, &cpu->c, value); }
void setDE(Z80* cpu, uint16_t value) { setPair(&cpu->d, &cpu->e, value); }
void setHL(Z80* cpu, uint16_t value) { setPair(&cpu->h, &cpu->l, value); }

bool getBit(uint8_t value, uint8_t index) { return (value >> index) & 1; }
bool isZERO_FLAG(Z80* cpu)		{ return getBit(cpu->f, 7); }
bool isSUBTRACT_FLAG(Z80* cpu)	{ return getBit(cpu->f, 6); }
bool isHALFCARRY_FLAG(Z80* cpu)	{ return getBit(cpu->f, 5); }
bool isCARRY_FLAG(Z80* cpu)		{ return getBit(cpu->f, 4); }

uint8_t fetchByte(Z80* cpu) {
	uint8_t retval = readByte(cpu->pc);
	cpu->pc += 1;
	return retval;
}

uint16_t fetchShort(Z80* cpu) {
	uint16_t retval = readShort(cpu->pc);
	cpu->pc += 2;
	return retval;
}

Z80* Z80_init() {
	Z80* cpu = calloc(1, sizeof(Z80));
	return cpu;
}

void Z80_printCPUState(Z80* cpu) {
	printf("8-bit Register states:\n");
	printf("A: %d, B: %d, C: %d, D: %d, ", cpu->a, cpu->b, cpu->c, cpu->d);
	printf("E: %d, H: %d, L: %d, F: %d\n", cpu->e, cpu->h, cpu->l, cpu->d);
	printf("16-bit Register states:\n");
	printf("AF: %d, BC: %d, DE: %d, HL: %d\n", getAF(cpu), getBC(cpu), getDE(cpu), getHL(cpu));
	printf("Clock:\n");
	printf("m: %d, t: %d\n", cpu->clock.m, cpu->clock.t);
	printf("Intermediate clock:\n");
	printf("m: %d, t: %d\n", cpu->m, cpu->t);
}

/* m is a machine cycle, which are 4 clock cycles */

void NOP(Z80* cpu) { cpu->m = 1; }

/* 8-bit loads */
// LD r,n
void LD_A_n(Z80* cpu, uint8_t n) { cpu->a = n; cpu->m = 2; }
void LD_B_n(Z80* cpu, uint8_t n) { cpu->b = n; cpu->m = 2; }
void LD_C_n(Z80* cpu, uint8_t n) { cpu->c = n; cpu->m = 2; }
void LD_D_n(Z80* cpu, uint8_t n) { cpu->d = n; cpu->m = 2; }
void LD_E_n(Z80* cpu, uint8_t n) { cpu->e = n; cpu->m = 2; }
void LD_H_n(Z80* cpu, uint8_t n) { cpu->h = n; cpu->m = 2; }
void LD_L_n(Z80* cpu, uint8_t n) { cpu->l = n; cpu->m = 2; }

// LD r,nn
void LD_A_nn(Z80* cpu, uint16_t nn) { cpu->a = nn; cpu->m = 4; }

// LD nn,r
void LD_nn_A(Z80* cpu, uint16_t* nn) { *nn = cpu->a; cpu->m = 4; }

// LD r1,r2
void LD_A_A(Z80* cpu) { cpu->m = 1; }
void LD_A_B(Z80* cpu) { cpu->a = cpu->b; cpu->m = 1; }
void LD_A_C(Z80* cpu) { cpu->a = cpu->c; cpu->m = 1; }
void LD_A_D(Z80* cpu) { cpu->a = cpu->d; cpu->m = 1; }
void LD_A_E(Z80* cpu) { cpu->a = cpu->e; cpu->m = 1; }
void LD_A_H(Z80* cpu) { cpu->a = cpu->h; cpu->m = 1; }
void LD_A_L(Z80* cpu) { cpu->a = cpu->l; cpu->m = 1; }
void LD_A_BC(Z80* cpu) { cpu->a = getBC(cpu); cpu->m = 2; }
void LD_A_DE(Z80* cpu) { cpu->a = getDE(cpu); cpu->m = 2; }
void LD_A_HL(Z80* cpu) { cpu->a = getHL(cpu); cpu->m = 2; }

void LD_B_A(Z80* cpu) { cpu->b = cpu->a; cpu->m = 1; }
void LD_B_B(Z80* cpu) { cpu->m = 1; }
void LD_B_C(Z80* cpu) { cpu->b = cpu->c; cpu->m = 1; }
void LD_B_D(Z80* cpu) { cpu->b = cpu->d; cpu->m = 1; }
void LD_B_E(Z80* cpu) { cpu->b = cpu->e; cpu->m = 1; }
void LD_B_H(Z80* cpu) { cpu->b = cpu->h; cpu->m = 1; }
void LD_B_L(Z80* cpu) { cpu->b = cpu->l; cpu->m = 1; }
void LD_B_HL(Z80* cpu) { cpu->b = getHL(cpu) >> 8; cpu->m = 2; }

void LD_C_A(Z80* cpu) { cpu->c = cpu->a; cpu->m = 1; }
void LD_C_B(Z80* cpu) { cpu->c = cpu->c; cpu->m = 1; }
void LD_C_C(Z80* cpu) { cpu->m = 1; }
void LD_C_D(Z80* cpu) { cpu->c = cpu->d; cpu->m = 1; }
void LD_C_E(Z80* cpu) { cpu->c = cpu->e; cpu->m = 1; }
void LD_C_H(Z80* cpu) { cpu->c = cpu->h; cpu->m = 1; }
void LD_C_L(Z80* cpu) { cpu->c = cpu->l; cpu->m = 1; }
void LD_C_HL(Z80* cpu) { cpu->c = getHL(cpu) >> 8; cpu->m = 2; }

void LD_D_A(Z80* cpu) { cpu->d = cpu->a; cpu->m = 1; }
void LD_D_B(Z80* cpu) { cpu->d = cpu->b; cpu->m = 1; }
void LD_D_C(Z80* cpu) { cpu->d = cpu->c; cpu->m = 1; }
void LD_D_D(Z80* cpu) { cpu->m = 1; }
void LD_D_E(Z80* cpu) { cpu->d = cpu->e; cpu->m = 1; }
void LD_D_H(Z80* cpu) { cpu->d = cpu->h; cpu->m = 1; }
void LD_D_L(Z80* cpu) { cpu->d = cpu->l; cpu->m = 1; }
void LD_D_HL(Z80* cpu) { cpu->d = getHL(cpu) >> 8; cpu->m = 2; }

void LD_E_A(Z80* cpu) { cpu->e = cpu->a; cpu->m = 1; }
void LD_E_B(Z80* cpu) { cpu->e = cpu->b; cpu->m = 1; }
void LD_E_C(Z80* cpu) { cpu->e = cpu->c; cpu->m = 1; }
void LD_E_D(Z80* cpu) { cpu->e = cpu->d; cpu->m = 1; }
void LD_E_E(Z80* cpu) { cpu->m = 1; }
void LD_E_H(Z80* cpu) { cpu->e = cpu->h; cpu->m = 1; }
void LD_E_L(Z80* cpu) { cpu->e = cpu->l; cpu->m = 1; }
void LD_E_HL(Z80* cpu) { cpu->e = getHL(cpu) >> 8; cpu->m = 2; }

void LD_H_A(Z80* cpu) { cpu->e = cpu->a; cpu->m = 1; }
void LD_H_B(Z80* cpu) { cpu->e = cpu->b; cpu->m = 1; }
void LD_H_C(Z80* cpu) { cpu->e = cpu->c; cpu->m = 1; }
void LD_H_D(Z80* cpu) { cpu->e = cpu->d; cpu->m = 1; }
void LD_H_E(Z80* cpu) { cpu->e = cpu->e; cpu->m = 1; }
void LD_H_H(Z80* cpu) { cpu->m = 1; }
void LD_H_L(Z80* cpu) { cpu->e = cpu->l; cpu->m = 1; }
void LD_H_HL(Z80* cpu) { cpu->e = getHL(cpu) >> 8; cpu->m = 2; }

void LD_L_A(Z80* cpu) { cpu->l = cpu->a; cpu->m = 1; }
void LD_L_B(Z80* cpu) { cpu->l = cpu->b; cpu->m = 1; }
void LD_L_C(Z80* cpu) { cpu->l = cpu->c; cpu->m = 1; }
void LD_L_D(Z80* cpu) { cpu->l = cpu->d; cpu->m = 1; }
void LD_L_E(Z80* cpu) { cpu->l = cpu->e; cpu->m = 1; }
void LD_L_H(Z80* cpu) { cpu->l = cpu->h; cpu->m = 1; }
void LD_L_L(Z80* cpu) { cpu->m = 1; }
void LD_L_HL(Z80* cpu) { cpu->l = getHL(cpu) >> 8; cpu->m = 2; }

void LD_BC_A(Z80* cpu) { setBC(cpu, cpu->a); cpu->m = 2; }
void LD_DE_A(Z80* cpu) { setDE(cpu, cpu->a); cpu->m = 2; }

void LD_HL_A(Z80* cpu) { setHL(cpu, cpu->a); cpu->m = 1; }
void LD_HL_B(Z80* cpu) { setHL(cpu, cpu->b); cpu->m = 2; }
void LD_HL_C(Z80* cpu) { setHL(cpu, cpu->c); cpu->m = 2; }
void LD_HL_D(Z80* cpu) { setHL(cpu, cpu->d); cpu->m = 2; }
void LD_HL_E(Z80* cpu) { setHL(cpu, cpu->e); cpu->m = 2; }
void LD_HL_H(Z80* cpu) { setHL(cpu, cpu->h); cpu->m = 2; }
void LD_HL_L(Z80* cpu) { setHL(cpu, cpu->l); cpu->m = 2; }
void LD_HL_n(Z80* cpu, uint8_t n) { setHL(cpu, n); cpu->m = 3; }


void dispatch(Z80* cpu, int opcode) {
	printf("Dispatch opcode: %02X\n", opcode);
	switch(opcode) {
		case 0x00: NOP(cpu); break;

		case 0x06: LD_B_n(cpu, fetchByte(cpu)); break;

		case 0x0E: LD_C_n(cpu, fetchByte(cpu)); break;

		case 0x16: LD_D_n(cpu, fetchByte(cpu)); break;

		case 0x1E: LD_E_n(cpu, fetchByte(cpu)); break;

		case 0x26: LD_H_n(cpu, fetchByte(cpu)); break;

		case 0x2E: LD_L_n(cpu, fetchByte(cpu)); break;

		case 0x36: LD_HL_n(cpu, fetchByte(cpu)); break;

		case 0x40: LD_B_B(cpu); break;
		case 0x41: LD_B_C(cpu); break;
		case 0x42: LD_B_D(cpu); break;
		case 0x43: LD_B_E(cpu); break;
		case 0x44: LD_B_H(cpu); break;
		case 0x45: LD_B_L(cpu); break;
		case 0x46: LD_B_HL(cpu); break;
		case 0x47: LD_B_A(cpu); break;
		case 0x48: LD_C_B(cpu); break;
		case 0x49: LD_C_C(cpu); break;
		case 0x4A: LD_C_D(cpu); break;
		case 0x4B: LD_C_E(cpu); break;
		case 0x4C: LD_C_H(cpu); break;
		case 0x4D: LD_C_L(cpu); break;
		case 0x4E: LD_C_HL(cpu); break;
		case 0x4F: LD_C_A(cpu); break;
		case 0x50: LD_D_B(cpu); break;
		case 0x51: LD_D_C(cpu); break;
		case 0x52: LD_D_D(cpu); break;
		case 0x53: LD_D_E(cpu); break;
		case 0x54: LD_D_H(cpu); break;
		case 0x55: LD_D_L(cpu); break;
		case 0x56: LD_D_HL(cpu); break;
		case 0x57: LD_D_A(cpu); break;
		case 0x58: LD_E_B(cpu); break;
		case 0x59: LD_E_C(cpu); break;
		case 0x5A: LD_E_D(cpu); break;
		case 0x5B: LD_E_E(cpu); break;
		case 0x5C: LD_E_H(cpu); break;
		case 0x5D: LD_E_L(cpu); break;
		case 0x5E: LD_E_HL(cpu); break;
		case 0x5F: LD_E_A(cpu); break;
		case 0x60: LD_H_B(cpu); break;
		case 0x61: LD_H_C(cpu); break;
		case 0x62: LD_H_D(cpu); break;
		case 0x63: LD_H_E(cpu); break;
		case 0x64: LD_H_H(cpu); break;
		case 0x65: LD_H_L(cpu); break;
		case 0x66: LD_H_HL(cpu); break;
		case 0x67: LD_H_A(cpu); break;
		case 0x68: LD_L_B(cpu); break;
		case 0x69: LD_L_C(cpu); break;
		case 0x6A: LD_L_D(cpu); break;
		case 0x6B: LD_L_E(cpu); break;
		case 0x6C: LD_L_H(cpu); break;
		case 0x6D: LD_L_L(cpu); break;
		case 0x6E: LD_L_HL(cpu); break;
		case 0x6F: LD_L_A(cpu); break;
		case 0x70: LD_HL_B(cpu); break;
		case 0x71: LD_HL_C(cpu); break;
		case 0x72: LD_HL_D(cpu); break;
		case 0x73: LD_HL_E(cpu); break;
		case 0x74: LD_HL_H(cpu); break;
		case 0x75: LD_HL_L(cpu); break;

		case 0x78: LD_A_B(cpu); break;
		case 0x79: LD_A_C(cpu); break;
		case 0x7A: LD_A_D(cpu); break;
		case 0x7B: LD_A_E(cpu); break;
		case 0x7C: LD_A_H(cpu);break;
		case 0x7D: LD_A_L(cpu); break;
		case 0x7F: LD_A_A(cpu); break;
		default:
			fprintf(stderr, "Missing instruction 0x%02X. Exiting..\n", opcode);
			Z80_printCPUState(cpu);
			exit(1);
	}
}

void reset(Z80* cpu) {
	cpu->a = 0;
	cpu->b = 0;
	cpu->c = 0;
	cpu->d = 0;
	cpu->e = 0;
	cpu->h = 0;
	cpu->l = 0;
	cpu->f = 0;
	cpu->m = 0;
	cpu->t = 0;
	cpu->clock.m = 0;
	cpu->clock.t = 0;
}

void updateClock(Z80* cpu) {
	cpu->clock.m += cpu->m;
	cpu->clock.t += cpu->t;
}

void cpuDispatcher(Z80* cpu) {
	while(1) {
		uint8_t opcode = fetchByte(cpu);
		dispatch(cpu, opcode);
		updateClock(cpu);
	}
}

