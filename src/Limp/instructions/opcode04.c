#include <Limp/instructions/opcode04.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode04(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// POPR
		case 0:{
			*m_cpu->args.rd = LCpu_pop(m_cpu);
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
	
}

