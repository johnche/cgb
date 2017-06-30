struct Z80 {
	struct clock {
		unsigned int m;
		unsigned int t;
	}
	
	struct register {
		// 8-bit registers
		unsigned int a, b, c, d, e, h, l, f;
		
		// 16-bit registers
		unsigned int pc; // Program counter
		unsigned int sp; // Stack pointer

		// Clock for last instruction
		unsigned int m;
		unsigned int t;
	}
}
