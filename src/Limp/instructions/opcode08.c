#include <Limp/instructions/opcode08.h>
#include <Limp/cpu.h>


// IN
void LIIsaDtb_opcode08_func00(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	*m_cpu->args.regd = LCpu_in(m_cpu, *m_cpu->args.regp);
}

void LIIsaDtb_opcode08_func01(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	switch(m_cpu->args.mod){
		// OUT
		case 0:{
			LCpu_out(m_cpu, *m_cpu->args.regp, *m_cpu->args.regb);
		}
		break;
		
		// OUTI
		case 1:{
			LCpu_out(m_cpu, *m_cpu->args.regp, m_cpu->args.imm);
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
}

// CPRR
void LIIsaDtb_opcode08_func02(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	*m_cpu->args.regd = LCpu_co_readReg(m_cpu, m_cpu->args.mod, *m_cpu->args.regp);
}

// CPWR
void LIIsaDtb_opcode08_func03(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_writeReg(m_cpu, m_cpu->args.mod, *m_cpu->args.regp, *m_cpu->args.regb);
}

// CPDI
void LIIsaDtb_opcode08_func04(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_disable(m_cpu, m_cpu->args.mod);
}

// CPEN
void LIIsaDtb_opcode08_func05(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_enable(m_cpu, m_cpu->args.mod);
}

// CPCHKST
void LIIsaDtb_opcode08_func06(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	*m_cpu->args.regd = LCpu_co_checkState(m_cpu, m_cpu->args.mod);
}

// CPCMD
void LIIsaDtb_opcode08_func07(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_command(m_cpu, m_cpu->args.mod, *m_cpu->args.regb);
}

void LIIsaDtb_opcode08_func08(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	Bool updtd = LCpu_inUpdtd(m_cpu, *m_cpu->args.regd);
	m_cpu->sregs.est = setVBit(m_cpu->sregs.est, LI_CPU_OF, updtd);
	
	switch(m_cpu->args.mod){
		// INUP
		case 0:{}
		break;
		
		// INUS
		case 1:{
			if(updtd){
				LCpu_in(m_cpu, *m_cpu->args.regd);
			}
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
}

void LIIsaDtb_opcode08_func09(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	switch(m_cpu->args.mod){
		// MVTIT
		case 0:{
			m_cpu->sregs.it = *m_cpu->args.regb;
		}
		break;
		
		// MVFIT
		case 1:{
			*m_cpu->args.regd = m_cpu->sregs.it;
		}
		break;
		
		// MVTST
		case 2:{
			m_cpu->sregs.est = *m_cpu->args.regb;
		}
		break;
		
		// MVFST
		case 3:{
			*m_cpu->args.regd = m_cpu->sregs.est;
		}
		break;
	}
}


extern void (*LIIsaDtb_opcode08[64])(LCpu *m_cpu) = {
	[0x00] = LIIsaDtb_opcode08_func00,
	[0x01] = LIIsaDtb_opcode08_func01,
	[0x02] = LIIsaDtb_opcode08_func02,
	[0x03] = LIIsaDtb_opcode08_func03,
	[0x04] = LIIsaDtb_opcode08_func04,
	[0x05] = LIIsaDtb_opcode08_func05,
	[0x06] = LIIsaDtb_opcode08_func06,
	[0x07] = LIIsaDtb_opcode08_func07,
	[0x08] = LIIsaDtb_opcode08_func08,
	[0x09] = LIIsaDtb_opcode08_func09,
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
