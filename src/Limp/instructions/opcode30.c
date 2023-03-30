#include <Limp/instructions/opcode30.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode30(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// MOV
		case 0:{
			*m_cpu->args.regd = *m_cpu->args.regb;
		}
		break;
		
		// MOVI
		case 1:{
			*m_cpu->args.regd = m_cpu->args.imm;
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
	
}

