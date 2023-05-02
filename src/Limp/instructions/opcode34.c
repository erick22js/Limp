#include <Limp/instructions/opcode34.h>
#include <Limp/cpu.h>


// JL
void LIIsaDtb_opcode34(LCpu *m_cpu){
	Uint32 adr = (m_cpu->args.imm<<2)|(m_cpu->sregs.lpc&0xF0000000);
	LCpu_jumpAbs(m_cpu, adr);
}
