#include <Limp/instructions/opcode37.h>
#include <Limp/cpu.h>


// BLP
void LIIsaDtb_opcode37(LCpu *m_cpu){
	// Protected Mode Only
	if(LICpu_protectionThrown(m_cpu)){
		return;
	}
	
	Uint32 adr = (m_cpu->args.imm<<2)|(m_cpu->sregs.lpc&0xF0000000);
	LCpu_push(m_cpu, m_cpu->sregs.epc);
	LCpu_jumpAbs(m_cpu, adr);
	
	m_cpu->sregs.st = setBit(m_cpu->sregs.st, LI_CPU_PM);
}
