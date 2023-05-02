#include <Limp/instructions/opcode20.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode20(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// MOV
		case 0:{
			*m_cpu->args.rd = *m_cpu->args.rb;
		}
		break;
		
		// MOVI
		case 1:{
			*m_cpu->args.rd = m_cpu->args.imm;
		}
		break;
	}
	
}

