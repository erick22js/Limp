#include <Limp/instructions/opcode23.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode23(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// MV
		case 0:{
			*m_cpu->args.rd = *m_cpu->args.rb;
		}
		break;
		
		// XCHG
		case 1:{
			Uint32 temp = *m_cpu->args.rb;
			*m_cpu->args.rb = *m_cpu->args.rd;
			*m_cpu->args.rd = temp;
		}
		break;
	}
}
