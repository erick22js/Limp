#include <Limp/instructions/opcode25.h>
#include <Limp/cpu.h>


// BL
void LIIsaDtb_opcode25(LCpu *m_cpu){
	Uint32 adr = (m_cpu->args.imm<<2)|(m_cpu->sregs.lpc&0xF0000000);
	LCpu_push(m_cpu, m_cpu->sregs.epc);
	LCpu_jumpAbs(m_cpu, adr);
}
