#include <Limp/instructions/opcode07.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode07(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// STRB
		case 0:{
			*m_cpu->args.regd = LCpu_readMem8(m_cpu, m_cpu->args.ea);
		}
		break;
		
		// STRW
		case 1:{
			*m_cpu->args.regd = LCpu_readMem16(m_cpu, m_cpu->args.ea);
		}
		break;
		
		// STRD
		case 2:{
			*m_cpu->args.regd = LCpu_readMem32(m_cpu, m_cpu->args.ea);
		}
		break;
		
		// STRQ
		case 3:{
			m_cpu->args.regd[0] = LCpu_readMem32(m_cpu, m_cpu->args.ea);
			m_cpu->args.regd[1] = LCpu_readMem32(m_cpu, m_cpu->args.ea+4);
		}
		break;
		
		default:{
			/* TODO: Exception => Invalid Instruction */
		}
	}
	
}
