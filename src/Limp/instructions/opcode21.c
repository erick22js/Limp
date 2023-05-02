#include <Limp/instructions/opcode21.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode21(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// CVBW
		case 0:{
			*m_cpu->args.rd = castS8T16(*m_cpu->args.rb);
		}
		break;
		
		// CVBD
		case 1:{
			*m_cpu->args.rd = castS8T32(*m_cpu->args.rb);
		}
		break;
	}
	
}
