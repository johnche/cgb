#include "Z80.h"

Z80* Z80_init() {
	Z80 cpu;
	return &cpu;
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

