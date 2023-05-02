#include <Limp/instructions/opcode0B.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode0B(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// STRD
		case 0:{
			LCpu_writeMem32(m_cpu, m_cpu->args.ea, *m_cpu->args.rd);
		}
		break;
		
		// STRQ
		case 1:{
			LCpu_writeMem32(m_cpu, m_cpu->args.ea, m_cpu->args.rd[0]);
			LCpu_writeMem32(m_cpu, m_cpu->args.ea+4, m_cpu->args.rd[1]);
		}
		break;
	}
	
}
