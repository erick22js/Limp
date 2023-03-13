#include <Limp/instructions/opcode18.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode1A(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// TEST
		case 0:{
			LIAlu_test(m_cpu, m_cpu->args.data);
		}
		break;
		
		// BIT
		case 1:{
			LIAlu_and(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
	
}
