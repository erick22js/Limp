#include <Limp/instructions/opcode08.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode08(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// PSH
		case 0:{
			LCpu_push(m_cpu, m_cpu->args.data);
		}
		break;
		
		// PSHR
		case 1:{
			LCpu_push(m_cpu, *m_cpu->args.rb);
		}
		break;
	}
	
}
