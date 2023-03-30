#include <Limp/instructions/opcode21.h>
#include <Limp/cpu.h>


// RET
void LIIsaDtb_opcode21_func00(LCpu *m_cpu){
	Uint32 addr = LCpu_pop(m_cpu);
	LCpu_jumpAbs(m_cpu, addr);
}

// IRET
void LIIsaDtb_opcode21_func01(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	LICpu_int_return(m_cpu);
}

// ENTER
void LIIsaDtb_opcode21_func02(LCpu *m_cpu){
	Uint32 stacksize;
	
	switch(m_cpu->args.mod){
		case 0:{
			stacksize = m_cpu->args.imm<<2;
		}
		break;
		
		case 1:{
			stacksize = *m_cpu->args.regp;
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
	
	LCpu_push(m_cpu, m_cpu->regs.n.efp);
	
	m_cpu->regs.n.esp -= 4;
	m_cpu->regs.n.efp = m_cpu->regs.n.esp;
	m_cpu->regs.n.esp -= stacksize;
	
	LCpu_push(m_cpu, m_cpu->regs.n.efp);
}

// LEAVE
void LIIsaDtb_opcode21_func03(LCpu *m_cpu){
	m_cpu->regs.n.esp = LCpu_pop(m_cpu);
	
	m_cpu->regs.n.esp += 4;
	m_cpu->regs.n.efp = LCpu_pop(m_cpu);
}

// INT
void LIIsaDtb_opcode21_func04(LCpu *m_cpu){
	LIPInterruption intr = {
		.selector = m_cpu->args.imm
	};
	LCpu_requestInterruption(m_cpu, intr);
}


extern void (*LIIsaDtb_opcode21[64])(LCpu *m_cpu) = {
	[0x00] = LIIsaDtb_opcode21_func00,
	[0x01] = LIIsaDtb_opcode21_func01,
	[0x02] = LIIsaDtb_opcode21_func02,
	[0x03] = LIIsaDtb_opcode21_func03,
	[0x04] = LIIsaDtb_opcode21_func04,
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
