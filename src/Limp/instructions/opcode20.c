#include <Limp/instructions/opcode20.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode20(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// JA
		case 0:{
			LCpu_jumpAbs(m_cpu, m_cpu->args.imm<<2);
		}
		break;
		
		// BA
		case 1:{
			LCpu_push(m_cpu, m_cpu->sregs.epc);
			LCpu_jumpAbs(m_cpu, m_cpu->args.imm<<2);
		}
		break;
		
		// JR
		case 2:{
			LCpu_jumpRel(m_cpu, m_cpu->args.imm<<2);
		}
		break;
		
		// BR
		case 3:{
			LCpu_push(m_cpu, m_cpu->sregs.lpc);
			LCpu_jumpRel(m_cpu, m_cpu->args.imm<<2);
		}
		break;
	}
	
}
