#include <Limp/instructions/opcode34.h>
#include <Limp/cpu.h>


// STEQ
void LIIsaDtb_opcode34_func00(LCpu *m_cpu){
	if((*m_cpu->args.regb)==(*m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STNE
void LIIsaDtb_opcode34_func01(LCpu *m_cpu){
	if((*m_cpu->args.regb)!=(*m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STLT
void LIIsaDtb_opcode34_func02(LCpu *m_cpu){
	if((Sint32)(*m_cpu->args.regb)<(Sint32)(*m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STGT
void LIIsaDtb_opcode34_func03(LCpu *m_cpu){
	if((Sint32)(*m_cpu->args.regb)>(Sint32)(*m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STLE
void LIIsaDtb_opcode34_func04(LCpu *m_cpu){
	if((Sint32)(*m_cpu->args.regb)<=(Sint32)(*m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STGE
void LIIsaDtb_opcode34_func05(LCpu *m_cpu){
	if((Sint32)(*m_cpu->args.regb)>=(Sint32)(*m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STBL
void LIIsaDtb_opcode34_func06(LCpu *m_cpu){
	if((*m_cpu->args.regb)<(*m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STAB
void LIIsaDtb_opcode34_func07(LCpu *m_cpu){
	if((*m_cpu->args.regb)>(*m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STBE
void LIIsaDtb_opcode34_func08(LCpu *m_cpu){
	if((*m_cpu->args.regb)<=(*m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STAE
void LIIsaDtb_opcode34_func09(LCpu *m_cpu){
	if((*m_cpu->args.regb)>=(*m_cpu->args.regp)){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STEZI
void LIIsaDtb_opcode34_func0A(LCpu *m_cpu){
	if((*m_cpu->args.regb)==0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STNZI
void LIIsaDtb_opcode34_func0B(LCpu *m_cpu){
	if((*m_cpu->args.regb)!=0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STLTZI
void LIIsaDtb_opcode34_func0C(LCpu *m_cpu){
	if((Sint32)(*m_cpu->args.regb)<0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STGTZI
void LIIsaDtb_opcode34_func0D(LCpu *m_cpu){
	if((Sint32)(*m_cpu->args.regb)>0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STLEZI
void LIIsaDtb_opcode34_func0E(LCpu *m_cpu){
	if((Sint32)(*m_cpu->args.regb)<=0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STGEZI
void LIIsaDtb_opcode34_func0F(LCpu *m_cpu){
	if((Sint32)(*m_cpu->args.regb)>=0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STBLZI
void LIIsaDtb_opcode34_func10(LCpu *m_cpu){
	if((*m_cpu->args.regb)<0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STABZI
void LIIsaDtb_opcode34_func11(LCpu *m_cpu){
	if((*m_cpu->args.regb)>0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STBEZI
void LIIsaDtb_opcode34_func12(LCpu *m_cpu){
	if((*m_cpu->args.regb)<=0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STAEZI
void LIIsaDtb_opcode34_func13(LCpu *m_cpu){
	if((*m_cpu->args.regb)>=0){
		*m_cpu->args.regd = m_cpu->args.imm;
	}
}

// STEZ
void LIIsaDtb_opcode34_func14(LCpu *m_cpu){
	if((*m_cpu->args.regb)==0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// STNZ
void LIIsaDtb_opcode34_func15(LCpu *m_cpu){
	if((*m_cpu->args.regb)!=0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// STLTZ
void LIIsaDtb_opcode34_func16(LCpu *m_cpu){
	if((Sint32)(*m_cpu->args.regb)<0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// STGTZ
void LIIsaDtb_opcode34_func17(LCpu *m_cpu){
	if((Sint32)(*m_cpu->args.regb)>0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// STLEZ
void LIIsaDtb_opcode34_func18(LCpu *m_cpu){
	if((Sint32)(*m_cpu->args.regb)<=0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// STGEZ
void LIIsaDtb_opcode34_func19(LCpu *m_cpu){
	if((Sint32)(*m_cpu->args.regb)>=0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// STBLZ
void LIIsaDtb_opcode34_func1A(LCpu *m_cpu){
	if((*m_cpu->args.regb)<0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// STABZ
void LIIsaDtb_opcode34_func1B(LCpu *m_cpu){
	if((*m_cpu->args.regb)>0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// STBEZ
void LIIsaDtb_opcode34_func1C(LCpu *m_cpu){
	if((*m_cpu->args.regb)<=0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}

// STAEZ
void LIIsaDtb_opcode34_func1D(LCpu *m_cpu){
	if((*m_cpu->args.regb)>=0){
		*m_cpu->args.regd = *m_cpu->args.regp;
	}
}


extern void (*LIIsaDtb_opcode34[64])(LCpu *m_cpu) = {
	[0x00] = LIIsaDtb_opcode34_func00,
	[0x01] = LIIsaDtb_opcode34_func01,
	[0x02] = LIIsaDtb_opcode34_func02,
	[0x03] = LIIsaDtb_opcode34_func03,
	[0x04] = LIIsaDtb_opcode34_func04,
	[0x05] = LIIsaDtb_opcode34_func05,
	[0x06] = LIIsaDtb_opcode34_func06,
	[0x07] = LIIsaDtb_opcode34_func07,
	[0x08] = LIIsaDtb_opcode34_func08,
	[0x09] = LIIsaDtb_opcode34_func09,
	[0x0A] = LIIsaDtb_opcode34_func0A,
	[0x0B] = LIIsaDtb_opcode34_func0B,
	[0x0C] = LIIsaDtb_opcode34_func0C,
	[0x0D] = LIIsaDtb_opcode34_func0D,
	[0x0E] = LIIsaDtb_opcode34_func0E,
	[0x0F] = LIIsaDtb_opcode34_func0F,
	
	[0x10] = LIIsaDtb_opcode34_func10,
	[0x11] = LIIsaDtb_opcode34_func11,
	[0x12] = LIIsaDtb_opcode34_func12,
	[0x13] = LIIsaDtb_opcode34_func13,
	[0x14] = LIIsaDtb_opcode34_func14,
	[0x15] = LIIsaDtb_opcode34_func15,
	[0x16] = LIIsaDtb_opcode34_func16,
	[0x17] = LIIsaDtb_opcode34_func17,
	[0x18] = LIIsaDtb_opcode34_func18,
	[0x19] = LIIsaDtb_opcode34_func19,
	[0x1A] = LIIsaDtb_opcode34_func1A,
	[0x1B] = LIIsaDtb_opcode34_func1B,
	[0x1C] = LIIsaDtb_opcode34_func1C,
	[0x1D] = LIIsaDtb_opcode34_func1D,
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
