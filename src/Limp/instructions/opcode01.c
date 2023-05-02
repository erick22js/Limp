#include <Limp/instructions/opcode01.h>
#include <Limp/cpu.h>


// HALT
void LIIsaDtb_opcode01_func00(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_stop(m_cpu);
}

void LIIsaDtb_opcode01_func01(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	m_cpu->hs.wait = TRUE;
	
	switch(m_cpu->args.mod){
		// WAIT
		case 0:{
			m_cpu->hs.waits = FALSE;
			m_cpu->hs.waiti = 0;
		}
		break;
		
		// WAITI
		case 1:{
			m_cpu->hs.waits = TRUE;
			m_cpu->hs.waiti = m_cpu->args.imm;
		}
		break;
		
		// WAITR
		case 2:{
			m_cpu->hs.waits = TRUE;
			m_cpu->hs.waiti = *m_cpu->args.rb;
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
	
}

// IN
void LIIsaDtb_opcode01_func02(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	*m_cpu->args.rd = LCpu_in(m_cpu, *m_cpu->args.rp);
}

void LIIsaDtb_opcode01_func03(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	switch(m_cpu->args.mod){
		// OUT
		case 0:{
			LCpu_out(m_cpu, *m_cpu->args.rp, *m_cpu->args.rb);
		}
		break;
		
		// OUTI
		case 1:{
			LCpu_out(m_cpu, *m_cpu->args.rp, m_cpu->args.imm);
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
}

// CP0RR
void LIIsaDtb_opcode01_func04(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	*m_cpu->args.rd = LCpu_co_readReg(m_cpu, 0, *m_cpu->args.rp);
}

// CP1RR
void LIIsaDtb_opcode01_func05(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	*m_cpu->args.rd = LCpu_co_readReg(m_cpu, 1, *m_cpu->args.rp);
}

// CP2RR
void LIIsaDtb_opcode01_func06(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	*m_cpu->args.rd = LCpu_co_readReg(m_cpu, 2, *m_cpu->args.rp);
}

// CP3RR
void LIIsaDtb_opcode01_func07(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	*m_cpu->args.rd = LCpu_co_readReg(m_cpu, 3, *m_cpu->args.rp);
}

// CP0WR
void LIIsaDtb_opcode01_func08(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_writeReg(m_cpu, 0, *m_cpu->args.rp, *m_cpu->args.rb);
}

// CP1WR
void LIIsaDtb_opcode01_func09(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_writeReg(m_cpu, 1, *m_cpu->args.rp, *m_cpu->args.rb);
}

// CP2WR
void LIIsaDtb_opcode01_func0A(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_writeReg(m_cpu, 2, *m_cpu->args.rp, *m_cpu->args.rb);
}

// CP3WR
void LIIsaDtb_opcode01_func0B(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_writeReg(m_cpu, 3, *m_cpu->args.rp, *m_cpu->args.rb);
}

// CP0DI
void LIIsaDtb_opcode01_func0C(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_disable(m_cpu, 0);
}

// CP1DI
void LIIsaDtb_opcode01_func0D(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_disable(m_cpu, 1);
}

// CP2DI
void LIIsaDtb_opcode01_func0E(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_disable(m_cpu, 2);
}

// CP3DI
void LIIsaDtb_opcode01_func0F(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_disable(m_cpu, 3);
}

// CP0EN
void LIIsaDtb_opcode01_func10(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_enable(m_cpu, 0);
}

// CP1EN
void LIIsaDtb_opcode01_func11(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_enable(m_cpu, 1);
}

// CP2EN
void LIIsaDtb_opcode01_func12(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_enable(m_cpu, 2);
}

// CP3EN
void LIIsaDtb_opcode01_func13(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_enable(m_cpu, 3);
}

// CP0CHKST
void LIIsaDtb_opcode01_func14(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	*m_cpu->args.rd = LCpu_co_checkState(m_cpu, 0);
}

// CP1CHKST
void LIIsaDtb_opcode01_func15(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	*m_cpu->args.rd = LCpu_co_checkState(m_cpu, 1);
}

// CP2CHKST
void LIIsaDtb_opcode01_func16(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	*m_cpu->args.rd = LCpu_co_checkState(m_cpu, 2);
}

// CP3CHKST
void LIIsaDtb_opcode01_func17(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	*m_cpu->args.rd = LCpu_co_checkState(m_cpu, 3);
}

// CP0CMD
void LIIsaDtb_opcode01_func18(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_command(m_cpu, 0, *m_cpu->args.rb);
}

// CP1CMD
void LIIsaDtb_opcode01_func19(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_command(m_cpu, 1, *m_cpu->args.rb);
}

// CP2CMD
void LIIsaDtb_opcode01_func1A(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_command(m_cpu, 2, *m_cpu->args.rb);
}

// CP3CMD
void LIIsaDtb_opcode01_func1B(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_co_command(m_cpu, 3, *m_cpu->args.rb);
}

void LIIsaDtb_opcode01_func1C(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	Bool updtd = LCpu_inUpdtd(m_cpu, *m_cpu->args.rd);
	m_cpu->sregs.st = setVBit(m_cpu->sregs.st, LI_CPU_OF, updtd);
	
	switch(m_cpu->args.mod){
		// INUP
		case 0:{}
		break;
		
		// INUS
		case 1:{
			if(updtd){
				LCpu_in(m_cpu, *m_cpu->args.rd);
			}
		}
		break;
	}
}

void LIIsaDtb_opcode01_func1D(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	switch(m_cpu->args.mod){
		// MVTIT
		case 0:{
			m_cpu->sregs.it = *m_cpu->args.rb;
		}
		break;
		
		// MVFIT
		case 1:{
			*m_cpu->args.rd = m_cpu->sregs.it;
		}
		break;
	}
}

void LIIsaDtb_opcode01_func1E(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	switch(m_cpu->args.mod){
		// MVTST
		case 0:{
			m_cpu->sregs.st = *m_cpu->args.rb;
		}
		break;
		
		// MVFST
		case 1:{
			*m_cpu->args.rd = m_cpu->sregs.st;
		}
		break;
	}
}

void LIIsaDtb_opcode01_func1F(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	switch(m_cpu->args.mod){
		// MVTSIV
		case 0:{
			m_cpu->sregs.ssiv = *m_cpu->args.rb;
		}
		break;
		
		// MVFSIV
		case 1:{
			*m_cpu->args.rd = m_cpu->sregs.ssiv;
		}
		break;
	}
}


extern void (*LIIsaDtb_opcode01[64])(LCpu *m_cpu) = {
	[0x00] = LIIsaDtb_opcode01_func00,
	[0x01] = LIIsaDtb_opcode01_func01,
	[0x02] = LIIsaDtb_opcode01_func02,
	[0x03] = LIIsaDtb_opcode01_func03,
	[0x04] = LIIsaDtb_opcode01_func04,
	[0x05] = LIIsaDtb_opcode01_func05,
	[0x06] = LIIsaDtb_opcode01_func06,
	[0x07] = LIIsaDtb_opcode01_func07,
	[0x08] = LIIsaDtb_opcode01_func08,
	[0x09] = LIIsaDtb_opcode01_func09,
	[0x0A] = LIIsaDtb_opcode01_func0A,
	[0x0B] = LIIsaDtb_opcode01_func0B,
	[0x0C] = LIIsaDtb_opcode01_func0C,
	[0x0D] = LIIsaDtb_opcode01_func0D,
	[0x0E] = LIIsaDtb_opcode01_func0E,
	[0x0F] = LIIsaDtb_opcode01_func0F,
	
	[0x10] = LIIsaDtb_opcode01_func10,
	[0x11] = LIIsaDtb_opcode01_func11,
	[0x12] = LIIsaDtb_opcode01_func12,
	[0x13] = LIIsaDtb_opcode01_func13,
	[0x14] = LIIsaDtb_opcode01_func14,
	[0x15] = LIIsaDtb_opcode01_func15,
	[0x16] = LIIsaDtb_opcode01_func16,
	[0x17] = LIIsaDtb_opcode01_func17,
	[0x18] = LIIsaDtb_opcode01_func18,
	[0x19] = LIIsaDtb_opcode01_func19,
	[0x1A] = LIIsaDtb_opcode01_func1A,
	[0x1B] = LIIsaDtb_opcode01_func1B,
	[0x1C] = LIIsaDtb_opcode01_func1C,
	[0x1D] = LIIsaDtb_opcode01_func1D,
	[0x1E] = LIIsaDtb_opcode01_func1E,
	[0x1F] = LIIsaDtb_opcode01_func1F,
	
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
