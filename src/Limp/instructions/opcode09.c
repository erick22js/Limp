#include <Limp/instructions/opcode0D.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode09(LCpu *m_cpu){
	Uint32 dtmem = LCpu_readMem32(m_cpu, m_cpu->args.ea);
	
	switch(m_cpu->args.mod){
		// CMPEQST
		case 0:{
			if(dtmem==m_cpu->regs.n.dx){
				LCpu_writeMem32(m_cpu, m_cpu->args.ea, *m_cpu->args.rd);
			}
			LIAlu_sub(m_cpu, dtmem, m_cpu->regs.n.dx, FALSE);
		}
		break;
		
		// CMPNEST
		case 1:{
			if(dtmem!=m_cpu->regs.n.dx){
				LCpu_writeMem32(m_cpu, m_cpu->args.ea, *m_cpu->args.rd);
			}
			LIAlu_sub(m_cpu, dtmem, m_cpu->regs.n.dx, FALSE);
		}
		break;
	}
	
}
