#include <Limp/instructions/opcode14.h>
#include <Limp/cpu.h>


// INC
void LIIsaDtb_opcode14_func00(LCpu *m_cpu){
	*m_cpu->args.regd += 1;
	
	m_cpu->sregs.est = setVBit(m_cpu->sregs.est, LI_CPU_CF, !(*m_cpu->args.regd));
	m_cpu->sregs.est = setVBit(m_cpu->sregs.est, LI_CPU_ZF, !(*m_cpu->args.regd));
}

// DEC
void LIIsaDtb_opcode14_func01(LCpu *m_cpu){
	m_cpu->sregs.est = setVBit(m_cpu->sregs.est, LI_CPU_BF, !(*m_cpu->args.regd));
	
	*m_cpu->args.regd -= 1;
	
	m_cpu->sregs.est = setVBit(m_cpu->sregs.est, LI_CPU_ZF, !(*m_cpu->args.regd));
}

// NEG
void LIIsaDtb_opcode14_func02(LCpu *m_cpu){
	*m_cpu->args.regd = -(*m_cpu->args.regd);
}

// MADD
void LIIsaDtb_opcode14_func03(LCpu *m_cpu){
	Uint32 mul = LIAlu_mul(m_cpu, *m_cpu->args.regd, *m_cpu->args.regb);
	Uint32 add = LIAlu_add(m_cpu, mul, *m_cpu->args.regp, FALSE);
	*m_cpu->args.regd = add;
}

// MSUB
void LIIsaDtb_opcode14_func04(LCpu *m_cpu){
	Uint32 mul = LIAlu_mul(m_cpu, *m_cpu->args.regd, *m_cpu->args.regb);
	Uint32 sub = LIAlu_sub(m_cpu, mul, *m_cpu->args.regp, FALSE);
	*m_cpu->args.regd = sub;
}

// MADC
void LIIsaDtb_opcode14_func05(LCpu *m_cpu){
	Uint32 mul = LIAlu_mul(m_cpu, *m_cpu->args.regd, *m_cpu->args.regb);
	Uint32 add = LIAlu_add(m_cpu, mul, *m_cpu->args.regp, TRUE);
	*m_cpu->args.regd = add;
}

// MSBB
void LIIsaDtb_opcode14_func06(LCpu *m_cpu){
	Uint32 mul = LIAlu_mul(m_cpu, *m_cpu->args.regd, *m_cpu->args.regb);
	Uint32 sub = LIAlu_sub(m_cpu, mul, *m_cpu->args.regp, TRUE);
	*m_cpu->args.regd = sub;
}

// LDIV
void LIIsaDtb_opcode14_func07(LCpu *m_cpu){
	*m_cpu->args.regd = LIAlu_ldiv(m_cpu, *m_cpu->args.regd, *m_cpu->args.regb);
}


extern void (*LIIsaDtb_opcode14[64])(LCpu *m_cpu) = {
	[0x00] = LIIsaDtb_opcode14_func00,
	[0x01] = LIIsaDtb_opcode14_func01,
	[0x02] = LIIsaDtb_opcode14_func02,
	[0x03] = LIIsaDtb_opcode14_func03,
	[0x04] = LIIsaDtb_opcode14_func04,
	[0x05] = LIIsaDtb_opcode14_func05,
	[0x06] = LIIsaDtb_opcode14_func06,
	[0x07] = LIIsaDtb_opcode14_func07,
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
