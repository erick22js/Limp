#include <Limp/instructions/opcode04.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode04(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// POPR
		case 0:{
			*m_cpu->args.regd = LCpu_pop(m_cpu);
		}
		break;
		
		// POPP
		case 1:{
			while(m_cpu->args.regd >= m_cpu->args.regb){
				*m_cpu->args.regd = LCpu_pop(m_cpu);
				m_cpu->args.regd--;
			}
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
	
}

