#include <Limp/instructions/opcode03.h>
#include <Limp/cpu.h>


// POPAS
void LIIsaDtb_opcode03_func00(LCpu *m_cpu){
	m_cpu->sregs.st = (m_cpu->sregs.st&0xFFFF0000)|(LCpu_pop(m_cpu)&0x0000FFFF);
}

// POPSS
void LIIsaDtb_opcode03_func01(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	m_cpu->sregs.st = (m_cpu->sregs.st&0x0000FFFF)|(LCpu_pop(m_cpu)&0xFFFF0000);
}

// POPS
void LIIsaDtb_opcode03_func02(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	m_cpu->sregs.st = LCpu_pop(m_cpu);
}

// PSHAS
void LIIsaDtb_opcode03_func03(LCpu *m_cpu){
	LCpu_push(m_cpu, m_cpu->sregs.st&0x0000FFFF);
}

// PSHSS
void LIIsaDtb_opcode03_func04(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_push(m_cpu, m_cpu->sregs.st&0xFFFF0000);
}

// PSHS
void LIIsaDtb_opcode03_func05(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	LCpu_push(m_cpu, m_cpu->sregs.st);
}


void (*LIIsaDtb_opcode03[64])(LCpu *m_cpu) = {
	[0x00] = LIIsaDtb_opcode03_func00,
	[0x01] = LIIsaDtb_opcode03_func01,
	[0x02] = LIIsaDtb_opcode03_func02,
	[0x03] = LIIsaDtb_opcode03_func03,
	[0x04] = LIIsaDtb_opcode03_func04,
	[0x05] = LIIsaDtb_opcode03_func05,
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

