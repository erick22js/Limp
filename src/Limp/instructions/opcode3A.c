#include <Limp/instructions/opcode3A.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode3A(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// JRAP
		case 0:{
			// Protected Mode Only
			if(LICpu_protectionThrown(m_cpu)){
				return;
			}
			
			LCpu_jumpAbs(m_cpu, *m_cpu->args.rb);
			
			m_cpu->sregs.st = setBit(m_cpu->sregs.st, LI_CPU_PM);
		}
		break;
		
		// BRAP
		case 1:{
			// Protected Mode Only
			if(LICpu_protectionThrown(m_cpu)){
				return;
			}
			
			LCpu_push(m_cpu, m_cpu->sregs.lpc);
			LCpu_jumpAbs(m_cpu, *m_cpu->args.rb);
			
			m_cpu->sregs.st = setBit(m_cpu->sregs.st, LI_CPU_PM);
		}
		break;
	}
	
}
