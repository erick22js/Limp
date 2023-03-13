#include <Limp/instructions/opcode15.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode15(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// CMP
		case 0:{
			LIAlu_sub(m_cpu, *m_cpu->args.regd, m_cpu->args.data, FALSE);
		}
		break;
		// CPB
		case 1:{
			LIAlu_sub(m_cpu, *m_cpu->args.regd, m_cpu->args.data, TRUE);
		}
		break;
		
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
	
}
