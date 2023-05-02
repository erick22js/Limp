#include <Limp/instructions/opcode12.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode12(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// MUL
		case 0:{
			*m_cpu->args.rd = LIAlu_mul(m_cpu, *m_cpu->args.rd, m_cpu->args.data);
		}
		break;
		
		// HMUL
		case 1:{
			*m_cpu->args.rd = LIAlu_hmul(m_cpu, *m_cpu->args.rd, m_cpu->args.data);
		}
		break;
	}
	
}
