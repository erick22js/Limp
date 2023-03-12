#include <Limp/instructions/opcode11.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode11(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// MUL
		case 0:{
			*m_cpu->args.regd = LIAlu_mul(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
		
		// HMUL
		case 1:{
			*m_cpu->args.regd = LIAlu_hmul(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
		
		// DIV
		case 2:{
			*m_cpu->args.regd = LIAlu_div(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
		
		// MOD
		case 3:{
			*m_cpu->args.regd = LIAlu_mod(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
	}
	
}
