#include <Limp/instructions/opcode36.h>
#include <Limp/cpu.h>


// JLP
void LIIsaDtb_opcode36(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	Uint32 adr = (m_cpu->args.imm<<2)|(m_cpu->sregs.lpc&0xF0000000);
	LCpu_jumpAbs(m_cpu, adr);
	
	m_cpu->sregs.st = setBit(m_cpu->sregs.st, LI_CPU_PM);
}
