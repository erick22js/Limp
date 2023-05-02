#include <Limp/instructions/opcode26.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode26(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// MVFC
		case 0:{
			*m_cpu->args.rd = LCpu_readCache(m_cpu, m_cpu->args.imm);
		}
		break;
		
		// MVTC
		case 1:{
			LCpu_writeCache(m_cpu, m_cpu->args.imm, *m_cpu->args.rb);
		}
		break;
	}
	
}
