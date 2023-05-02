#include <Limp/instructions/opcode38.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode38(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// JR
		case 0:{
			LCpu_jumpRel(m_cpu, m_cpu->args.imm<<2);
		}
		break;
		
		// BR
		case 1:{
			LCpu_push(m_cpu, m_cpu->sregs.lpc);
			LCpu_jumpRel(m_cpu, m_cpu->args.imm<<2);
		}
		break;
	}
	
}
