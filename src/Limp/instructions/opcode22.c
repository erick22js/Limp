#include <Limp/instructions/opcode22.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode22(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// JRA
		case 0:{
			LCpu_jumpAbs(m_cpu, *m_cpu->args.regb);
		}
		break;
		
		// BRA
		case 1:{
			LCpu_push(m_cpu, m_cpu->sregs.lpc);
			LCpu_jumpAbs(m_cpu, *m_cpu->args.regb);
		}
		break;
		
		// JRAP
		case 2:{
			// Protected Mode Only
			if(LICpu_protectionThrown(m_cpu)){
				return;
			}
			
			LCpu_jumpAbs(m_cpu, *m_cpu->args.regb);
			
			m_cpu->sregs.est = setBit(m_cpu->sregs.est, LI_CPU_PM);
		}
		break;
		
		// BRAP
		case 3:{
			// Protected Mode Only
			if(LICpu_protectionThrown(m_cpu)){
				return;
			}
			
			LCpu_push(m_cpu, m_cpu->sregs.lpc);
			LCpu_jumpAbs(m_cpu, *m_cpu->args.regb);
			
			m_cpu->sregs.est = setBit(m_cpu->sregs.est, LI_CPU_PM);
		}
		break;
	}
	
}
