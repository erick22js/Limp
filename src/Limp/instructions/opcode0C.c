#include <Limp/instructions/opcode0C.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode0C(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// STSI
		case 0:{
			LCpu_writeMem32(m_cpu, *m_cpu->args.rd, *m_cpu->args.rb);
			(*m_cpu->args.rd)++;
			(*m_cpu->args.ro)++;
		}
		break;
		
		// STSD
		case 1:{
			LCpu_writeMem32(m_cpu, *m_cpu->args.rd, *m_cpu->args.rb);
			(*m_cpu->args.rd)++;
			(*m_cpu->args.ro)--;
		}
		break;
	}
	
}

