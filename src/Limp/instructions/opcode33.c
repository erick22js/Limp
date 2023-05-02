#include <Limp/instructions/opcode33.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode33(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// JRR
		case 0:{
			LCpu_jumpRel(m_cpu, *m_cpu->args.rb);
		}
		break;
		
		// BRR
		case 1:{
			LCpu_push(m_cpu, m_cpu->sregs.lpc);
			LCpu_jumpRel(m_cpu, *m_cpu->args.rb);
		}
		break;
	}
	
}

