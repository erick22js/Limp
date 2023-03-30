#include <Limp/instructions/opcode19.h>
#include <Limp/cpu.h>


// NOT
void LIIsaDtb_opcode19_func00(LCpu *m_cpu){
	*m_cpu->args.regd = ~(*m_cpu->args.regd);
}

// SETB
void LIIsaDtb_opcode19_func01(LCpu *m_cpu){
	*m_cpu->args.regd = setBit(*m_cpu->args.regd, m_cpu->args.imm);
}

// CLRB
void LIIsaDtb_opcode19_func02(LCpu *m_cpu){
	*m_cpu->args.regd = clrBit(*m_cpu->args.regd, m_cpu->args.imm);
}

// SWAP
void LIIsaDtb_opcode19_func03(LCpu *m_cpu){
	Uint32 data = *m_cpu->args.regd;
	Uint8 *buffer = &data;
	Uint8 swap[4] = {
		[0] = buffer[3],
		[1] = buffer[2],
		[2] = buffer[1],
		[3] = buffer[0]
	};
	*m_cpu->args.regd = *(Uint32*)swap;
}

// SWAPB
void LIIsaDtb_opcode19_func04(LCpu *m_cpu){
	Uint32 data = *m_cpu->args.regd;
	Uint32 swap = 
		(getBit(data, 0)<<31) | (getBit(data, 1)<<30) | (getBit(data, 2)<<29) | (getBit(data, 3)<<28) | 
		(getBit(data, 4)<<27) | (getBit(data, 5)<<26) | (getBit(data, 6)<<25) | (getBit(data, 7)<<24) | 
		(getBit(data, 8)<<23) | (getBit(data, 9)<<22) | (getBit(data, 10)<<21)| (getBit(data, 11)<<20)| 
		(getBit(data, 12)<<19)| (getBit(data, 13)<<18)| (getBit(data, 14)<<17)| (getBit(data, 15)<<16)| 
		(getBit(data, 16)<<15)| (getBit(data, 17)<<14)| (getBit(data, 18)<<13)| (getBit(data, 19)<<12)| 
		(getBit(data, 20)<<11)| (getBit(data, 21)<<10)| (getBit(data, 22)<<9) | (getBit(data, 23)<<8) | 
		(getBit(data, 24)<<7) | (getBit(data, 25)<<6) | (getBit(data, 26)<<5) | (getBit(data, 27)<<4) | 
		(getBit(data, 28)<<3) | (getBit(data, 29)<<2) | (getBit(data, 30)<<1) | (getBit(data, 31)<<0);
	*m_cpu->args.regd = swap;
}


extern void (*LIIsaDtb_opcode19[64])(LCpu *m_cpu) = {
	[0x00] = LIIsaDtb_opcode19_func00,
	[0x01] = LIIsaDtb_opcode19_func01,
	[0x02] = LIIsaDtb_opcode19_func02,
	[0x03] = LIIsaDtb_opcode19_func03,
	[0x04] = LIIsaDtb_opcode19_func04,
	[0x05] = LIIsaDtb_undefined,
	[0x06] = LIIsaDtb_undefined,
	[0x07] = LIIsaDtb_undefined,
	[0x08] = LIIsaDtb_undefined,
	[0x09] = LIIsaDtb_undefined,
	[0x0A] = LIIsaDtb_undefined,
	[0x0B] = LIIsaDtb_undefined,
	[0x0C] = LIIsaDtb_undefined,
	[0x0D] = LIIsaDtb_undefined,
	[0x0E] = LIIsaDtb_undefined,
	[0x0F] = LIIsaDtb_undefined,
	
	[0x10] = LIIsaDtb_undefined,
	[0x11] = LIIsaDtb_undefined,
	[0x12] = LIIsaDtb_undefined,
	[0x13] = LIIsaDtb_undefined,
	[0x14] = LIIsaDtb_undefined,
	[0x15] = LIIsaDtb_undefined,
	[0x16] = LIIsaDtb_undefined,
	[0x17] = LIIsaDtb_undefined,
	[0x18] = LIIsaDtb_undefined,
	[0x19] = LIIsaDtb_undefined,
	[0x1A] = LIIsaDtb_undefined,
	[0x1B] = LIIsaDtb_undefined,
	[0x1C] = LIIsaDtb_undefined,
	[0x1D] = LIIsaDtb_undefined,
	[0x1E] = LIIsaDtb_undefined,
	[0x1F] = LIIsaDtb_undefined,
	
	[0x20] = LIIsaDtb_undefined,
	[0x21] = LIIsaDtb_undefined,
	[0x22] = LIIsaDtb_undefined,
	[0x23] = LIIsaDtb_undefined,
	[0x24] = LIIsaDtb_undefined,
	[0x25] = LIIsaDtb_undefined,
	[0x26] = LIIsaDtb_undefined,
	[0x27] = LIIsaDtb_undefined,
	[0x28] = LIIsaDtb_undefined,
	[0x29] = LIIsaDtb_undefined,
	[0x2A] = LIIsaDtb_undefined,
	[0x2B] = LIIsaDtb_undefined,
	[0x2C] = LIIsaDtb_undefined,
	[0x2D] = LIIsaDtb_undefined,
	[0x2E] = LIIsaDtb_undefined,
	[0x2F] = LIIsaDtb_undefined,
	
	[0x30] = LIIsaDtb_undefined,
	[0x31] = LIIsaDtb_undefined,
	[0x32] = LIIsaDtb_undefined,
	[0x33] = LIIsaDtb_undefined,
	[0x34] = LIIsaDtb_undefined,
	[0x35] = LIIsaDtb_undefined,
	[0x36] = LIIsaDtb_undefined,
	[0x37] = LIIsaDtb_undefined,
	[0x38] = LIIsaDtb_undefined,
	[0x39] = LIIsaDtb_undefined,
	[0x3A] = LIIsaDtb_undefined,
	[0x3B] = LIIsaDtb_undefined,
	[0x3C] = LIIsaDtb_undefined,
	[0x3D] = LIIsaDtb_undefined,
	[0x3E] = LIIsaDtb_undefined,
	[0x3F] = LIIsaDtb_undefined,
};
