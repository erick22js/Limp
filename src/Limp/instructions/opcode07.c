#include <Limp/instructions/opcode07.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode07(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// LDMD
		case 0:{
			*m_cpu->args.rd = LCpu_readMem32(m_cpu, m_cpu->args.ea);
		}
		break;
		
		// LDMQ
		case 1:{
			m_cpu->args.rd[0] = LCpu_readMem32(m_cpu, m_cpu->args.ea);
			m_cpu->args.rd[1] = LCpu_readMem32(m_cpu, m_cpu->args.ea+4);
		}
		break;
	}
	
}
