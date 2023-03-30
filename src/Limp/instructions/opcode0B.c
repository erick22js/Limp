#include <Limp/instructions/opcode0B.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode0B(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// PSHAS
		case 0:{
			LCpu_push(m_cpu, m_cpu->sregs.est&0x0000FFFF);
		}
		break;
		
		// PSHSS
		case 1:{
			// Protected Mode Only
			if(LICpu_protectionThrown(m_cpu)){
				return;
			}
			
			LCpu_push(m_cpu, m_cpu->sregs.est&0xFFFF0000);
		}
		break;
		
		// PSHS
		case 2:{
			// Protected Mode Only
			if(LICpu_protectionThrown(m_cpu)){
				return;
			}
			
			LCpu_push(m_cpu, m_cpu->sregs.est);
		}
		break;
		
		default:{
			LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		}
	}
	
}

