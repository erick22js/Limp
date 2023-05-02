#include <Limp/instructions/opcode11.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode11(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// SUB
		case 0:{
			*m_cpu->args.rd = LIAlu_sub(m_cpu, *m_cpu->args.rd, m_cpu->args.data, FALSE);
		}
		break;
		
		// SBB
		case 1:{
			*m_cpu->args.rd = LIAlu_sub(m_cpu, *m_cpu->args.rd, m_cpu->args.data, TRUE);
		}
		break;
	}
	
}
