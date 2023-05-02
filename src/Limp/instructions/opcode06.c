#include <Limp/instructions/opcode06.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode06(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// LDMB
		case 0:{
			*m_cpu->args.rd = LCpu_readMem8(m_cpu, m_cpu->args.ea);
		}
		break;
		
		// LDMW
		case 1:{
			*m_cpu->args.rd = LCpu_readMem16(m_cpu, m_cpu->args.ea);
		}
		break;
	}
	
}
