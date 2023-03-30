#include <Limp/instructions/opcode35.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode35(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// MVFR
		case 0:{
			*m_cpu->args.regd = LCpu_readExReg(m_cpu, m_cpu->args.imm);
		}
		break;
		
		// MVTR
		case 1:{
			LCpu_writeExReg(m_cpu, m_cpu->args.imm, *m_cpu->args.regb);
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
	
}

