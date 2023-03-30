#include <Limp/instructions/opcode03.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode03(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// POPAS
		case 0:{
			m_cpu->sregs.est = (m_cpu->sregs.est&0xFFFF0000)|(LCpu_pop(m_cpu)&0x0000FFFF);
		}
		break;
		
		// POPSS
		case 1:{
			// Protected Mode Only
			if(LICpu_protectionThrown(m_cpu)){
				return;
			}
			
			m_cpu->sregs.est = (m_cpu->sregs.est&0x0000FFFF)|(LCpu_pop(m_cpu)&0xFFFF0000);
		}
		break;
		
		// POPS
		case 2:{
			// Protected Mode Only
			if(LICpu_protectionThrown(m_cpu)){
				return;
			}
			
			m_cpu->sregs.est = LCpu_pop(m_cpu);
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
	
}

