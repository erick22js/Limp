#include <Limp/instructions/opcode24.h>
#include <Limp/cpu.h>


// JL
void LIIsaDtb_opcode24(LCpu *m_cpu){
	Uint32 adr = (m_cpu->args.imm<<2)|(m_cpu->sregs.lpc&0xF0000000);
	LCpu_jumpAbs(m_cpu, adr);
}
