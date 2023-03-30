#include <Limp/instructions/opcode31.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode31(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// CVBW
		case 0:{
			*m_cpu->args.regd = castS8T16(*m_cpu->args.regb);
		}
		break;
		
		// CVBD
		case 1:{
			*m_cpu->args.regd = castS8T32(*m_cpu->args.regb);
		}
		break;
		
		// CVWD
		case 2:{
			*m_cpu->args.regd = castS16T32(*m_cpu->args.regb);
		}
		break;
		
		// CVWDI
		case 3:{
			*m_cpu->args.regd = castS16T32(m_cpu->args.imm);
		}
		break;
	}
	
}

