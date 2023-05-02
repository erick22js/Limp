#include <Limp/instructions/opcode0A.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode0A(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// STRB
		case 0:{
			LCpu_writeMem8(m_cpu, m_cpu->args.ea, *m_cpu->args.rd);
		}
		break;
		
		// STRW
		case 1:{
			LCpu_writeMem16(m_cpu, m_cpu->args.ea, *m_cpu->args.rd);
		}
		break;
	}
	
}
