#include <Limp/instructions/opcode2B.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode2B(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// LROT
		case 0:{
			*m_cpu->args.rd = LIAlu_lrot(m_cpu, *m_cpu->args.rd, m_cpu->args.data);
		}
		break;
		
		// RROT
		case 1:{
			*m_cpu->args.rd = LIAlu_rrot(m_cpu, *m_cpu->args.rd, m_cpu->args.data);
		}
		break;
	}
	
}
