#include <Limp/instructions/opcode0C.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode0C(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// PSHI
		case 0:{
			LCpu_push(m_cpu, m_cpu->args.imm);
		}
		break;
		
		// PSHR
		case 1:{
			LCpu_push(m_cpu, *m_cpu->args.regb);
		}
		break;
		
		// PSHP
		case 2:{
			while(m_cpu->args.regb <= m_cpu->args.regd){
				LCpu_push(m_cpu, *m_cpu->args.regb);
				m_cpu->args.regb++;
			}
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
	
}

