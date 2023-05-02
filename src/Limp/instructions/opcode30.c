#include <Limp/instructions/opcode30.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode30(LCpu *m_cpu){
	
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
	}
	
}

