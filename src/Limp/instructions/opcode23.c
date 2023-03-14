#include <Limp/instructions/opcode23.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode23(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// JRR
		case 0:{
			LCpu_jumpRel(m_cpu, *m_cpu->args.regb);
		}
		break;
		
		// BRR
		case 1:{
			LCpu_push(m_cpu, m_cpu->sregs.lpc);
			LCpu_jumpRel(m_cpu, *m_cpu->args.regb);
		}
		break;
		
		// XJP
		case 2:{
			Uint32 addr = *m_cpu->args.regb;
			*m_cpu->args.regb = m_cpu->sregs.epc;
			LCpu_jumpAbs(m_cpu, addr);
		}
		break;
		
		// XBR
		case 3:{
			Uint32 addr = *m_cpu->args.regb;
			*m_cpu->args.regb = m_cpu->sregs.epc;
			LCpu_push(m_cpu, m_cpu->sregs.epc);
			LCpu_jumpAbs(m_cpu, addr);
		}
		break;
	}
	
}
