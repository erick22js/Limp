#include <Limp/instructions/opcode1D.h>
#include <Limp/cpu.h>


// FSTEQ
void LIIsaDtb_opcode1D_func00(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)==(*(Float32*)m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// FSTNE
void LIIsaDtb_opcode1D_func01(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)!=(*(Float32*)m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// FSTLT
void LIIsaDtb_opcode1D_func02(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)<(*(Float32*)m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// FSTGT
void LIIsaDtb_opcode1D_func03(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)>(*(Float32*)m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// FSTLE
void LIIsaDtb_opcode1D_func04(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)<=(*(Float32*)m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// FSTGE
void LIIsaDtb_opcode1D_func05(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)>=(*(Float32*)m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// FSTEZI
void LIIsaDtb_opcode1D_func06(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)==0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// FSTNZI
void LIIsaDtb_opcode1D_func07(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)!=0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// FSTLTZI
void LIIsaDtb_opcode1D_func08(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)<0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// FSTGTZI
void LIIsaDtb_opcode1D_func09(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)>0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// FSTLEZI
void LIIsaDtb_opcode1D_func0A(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)<=0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// FSTGEZI
void LIIsaDtb_opcode1D_func0B(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)>=0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// FSTEZ
void LIIsaDtb_opcode1D_func0C(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)==0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// FSTNZ
void LIIsaDtb_opcode1D_func0D(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)!=0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// FSTLTZ
void LIIsaDtb_opcode1D_func0E(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)<0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// FSTGTZ
void LIIsaDtb_opcode1D_func0F(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)>0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// FSTLEZ
void LIIsaDtb_opcode1D_func10(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)<=0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// FSTGEZ
void LIIsaDtb_opcode1D_func11(LCpu *m_cpu){
	if((*(Float32*)m_cpu->args.regb)>=0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}


extern void (*LIIsaDtb_opcode1D[64])(LCpu *m_cpu) = {
	[0x00] = LIIsaDtb_opcode1D_func00,
	[0x01] = LIIsaDtb_opcode1D_func01,
	[0x02] = LIIsaDtb_opcode1D_func02,
	[0x03] = LIIsaDtb_opcode1D_func03,
	[0x04] = LIIsaDtb_opcode1D_func04,
	[0x05] = LIIsaDtb_opcode1D_func05,
	[0x06] = LIIsaDtb_opcode1D_func06,
	[0x07] = LIIsaDtb_opcode1D_func07,
	[0x08] = LIIsaDtb_opcode1D_func08,
	[0x09] = LIIsaDtb_opcode1D_func09,
	[0x0A] = LIIsaDtb_opcode1D_func0A,
	[0x0B] = LIIsaDtb_opcode1D_func0B,
	[0x0C] = LIIsaDtb_opcode1D_func0C,
	[0x0D] = LIIsaDtb_opcode1D_func0D,
	[0x0E] = LIIsaDtb_opcode1D_func0E,
	[0x0F] = LIIsaDtb_opcode1D_func0F,
	
	[0x10] = LIIsaDtb_opcode1D_func10,
	[0x11] = LIIsaDtb_opcode1D_func11,
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
