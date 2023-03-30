#include <Limp/instructions/opcode32.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode32(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// MV
		case 0:{
			*m_cpu->args.regd = *m_cpu->args.regb;
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
	
}
