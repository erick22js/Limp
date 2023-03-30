#include <Limp/instructions/opcode26.h>
#include <Limp/cpu.h>


// JLP
void LIIsaDtb_opcode26(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	Uint32 adr = (m_cpu->args.imm<<2)|(m_cpu->sregs.lpc&0xF0000000);
	LCpu_jumpAbs(m_cpu, adr);
	
	m_cpu->sregs.est = setBit(m_cpu->sregs.est, LI_CPU_PM);
}
