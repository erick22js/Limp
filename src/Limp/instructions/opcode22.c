#include <Limp/instructions/opcode22.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode22(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// CVWD
		case 0:{
			*m_cpu->args.rd = castS16T32(*m_cpu->args.rb);
		}
		break;
		
		// CVWDI
		case 1:{
			*m_cpu->args.rd = castS16T32(m_cpu->args.imm);
		}
		break;
	}
	
}
