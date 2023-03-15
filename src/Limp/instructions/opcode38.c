#include <Limp/instructions/opcode38.h>
#include <Limp/cpu.h>


// STC
void LIIsaDtb_opcode38_func00(LCpu *m_cpu){
	m_cpu->sregs.est = setBit(m_cpu->sregs.est, LI_CPU_CF);
}

// CLC
void LIIsaDtb_opcode38_func01(LCpu *m_cpu){
	m_cpu->sregs.est = clrBit(m_cpu->sregs.est, LI_CPU_CF);
}

// TGC
void LIIsaDtb_opcode38_func02(LCpu *m_cpu){
	m_cpu->sregs.est = togBit(m_cpu->sregs.est, LI_CPU_CF);
}

// STB
void LIIsaDtb_opcode38_func03(LCpu *m_cpu){
	m_cpu->sregs.est = setBit(m_cpu->sregs.est, LI_CPU_BF);
}

// CLB
void LIIsaDtb_opcode38_func04(LCpu *m_cpu){
	m_cpu->sregs.est = clrBit(m_cpu->sregs.est, LI_CPU_BF);
}

// TGB
void LIIsaDtb_opcode38_func05(LCpu *m_cpu){
	m_cpu->sregs.est = togBit(m_cpu->sregs.est, LI_CPU_BF);
}

// STV
void LIIsaDtb_opcode38_func06(LCpu *m_cpu){
	m_cpu->sregs.est = setBit(m_cpu->sregs.est, LI_CPU_VF);
}

// CLV
void LIIsaDtb_opcode38_func07(LCpu *m_cpu){
	m_cpu->sregs.est = clrBit(m_cpu->sregs.est, LI_CPU_VF);
}

// TGV
void LIIsaDtb_opcode38_func08(LCpu *m_cpu){
	m_cpu->sregs.est = togBit(m_cpu->sregs.est, LI_CPU_VF);
}

// STZ
void LIIsaDtb_opcode38_func09(LCpu *m_cpu){
	m_cpu->sregs.est = setBit(m_cpu->sregs.est, LI_CPU_ZF);
}

// CLZ
void LIIsaDtb_opcode38_func0A(LCpu *m_cpu){
	m_cpu->sregs.est = clrBit(m_cpu->sregs.est, LI_CPU_ZF);
}

// TGZ
void LIIsaDtb_opcode38_func0B(LCpu *m_cpu){
	m_cpu->sregs.est = togBit(m_cpu->sregs.est, LI_CPU_ZF);
}

// STN
void LIIsaDtb_opcode38_func0C(LCpu *m_cpu){
	m_cpu->sregs.est = setBit(m_cpu->sregs.est, LI_CPU_NF);
}

// CLN
void LIIsaDtb_opcode38_func0D(LCpu *m_cpu){
	m_cpu->sregs.est = clrBit(m_cpu->sregs.est, LI_CPU_NF);
}

// TGN
void LIIsaDtb_opcode38_func0E(LCpu *m_cpu){
	m_cpu->sregs.est = togBit(m_cpu->sregs.est, LI_CPU_NF);
}

// STO
void LIIsaDtb_opcode38_func0F(LCpu *m_cpu){
	m_cpu->sregs.est = setBit(m_cpu->sregs.est, LI_CPU_OF);
}

// CLO
void LIIsaDtb_opcode38_func10(LCpu *m_cpu){
	m_cpu->sregs.est = clrBit(m_cpu->sregs.est, LI_CPU_OF);
}

// TGO
void LIIsaDtb_opcode38_func11(LCpu *m_cpu){
	m_cpu->sregs.est = togBit(m_cpu->sregs.est, LI_CPU_OF);
}

// ENBI
void LIIsaDtb_opcode38_func12(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	m_cpu->sregs.est = setBit(m_cpu->sregs.est, LI_CPU_EI);
}

// DSBI
void LIIsaDtb_opcode38_func13(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	m_cpu->sregs.est = clrBit(m_cpu->sregs.est, LI_CPU_EI);
}

// ENBV
void LIIsaDtb_opcode38_func14(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	m_cpu->sregs.est = setBit(m_cpu->sregs.est, LI_CPU_VM);
}

// DSBV
void LIIsaDtb_opcode38_func15(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	m_cpu->sregs.est = clrBit(m_cpu->sregs.est, LI_CPU_VM);
}


extern void (*LIIsaDtb_opcode38[64])(LCpu *m_cpu) = {
	[0x00] = LIIsaDtb_opcode38_func00,
	[0x01] = LIIsaDtb_opcode38_func01,
	[0x02] = LIIsaDtb_opcode38_func02,
	[0x03] = LIIsaDtb_opcode38_func03,
	[0x04] = LIIsaDtb_opcode38_func04,
	[0x05] = LIIsaDtb_opcode38_func05,
	[0x06] = LIIsaDtb_opcode38_func06,
	[0x07] = LIIsaDtb_opcode38_func07,
	[0x08] = LIIsaDtb_opcode38_func08,
	[0x09] = LIIsaDtb_opcode38_func09,
	[0x0A] = LIIsaDtb_opcode38_func0A,
	[0x0B] = LIIsaDtb_opcode38_func0B,
	[0x0C] = LIIsaDtb_opcode38_func0C,
	[0x0D] = LIIsaDtb_opcode38_func0D,
	[0x0E] = LIIsaDtb_opcode38_func0E,
	[0x0F] = LIIsaDtb_opcode38_func0F,
	
	[0x10] = LIIsaDtb_opcode38_func10,
	[0x11] = LIIsaDtb_opcode38_func11,
	[0x12] = LIIsaDtb_opcode38_func12,
	[0x13] = LIIsaDtb_opcode38_func13,
	[0x14] = LIIsaDtb_opcode38_func14,
	[0x15] = LIIsaDtb_opcode38_func15,
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
