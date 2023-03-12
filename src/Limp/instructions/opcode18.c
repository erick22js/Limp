#include <Limp/instructions/opcode18.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode18(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// AND
		case 0:{
			*m_cpu->args.regd = LIAlu_and(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
		
		// OR
		case 1:{
			*m_cpu->args.regd = LIAlu_or(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
		
		// XOR
		case 2:{
			*m_cpu->args.regd = LIAlu_xor(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
		
		// NAND
		case 3:{
			*m_cpu->args.regd = LIAlu_nand(m_cpu, *m_cpu->args.regd, m_cpu->args.data);
		}
		break;
	}
	
}
