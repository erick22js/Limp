#include <Limp/instructions/opcode32.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode32(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// JRA
		case 0:{
			LCpu_jumpAbs(m_cpu, *m_cpu->args.rb);
		}
		break;
		
		// BRA
		case 1:{
			LCpu_push(m_cpu, m_cpu->sregs.lpc);
			LCpu_jumpAbs(m_cpu, *m_cpu->args.rb);
		}
		break;
	}
	
}
