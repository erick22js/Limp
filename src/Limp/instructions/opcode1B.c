#include <Limp/instructions/opcode1B.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode1B(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// LSHF
		case 0:{
			*m_cpu->args.regd = LIAlu_lshf(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
		
		// RSHF
		case 1:{
			*m_cpu->args.regd = LIAlu_rshf(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
		
		// LROT
		case 2:{
			*m_cpu->args.regd = LIAlu_lrot(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
		
		// RROT
		case 3:{
			*m_cpu->args.regd = LIAlu_rrot(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
	}
	
}
