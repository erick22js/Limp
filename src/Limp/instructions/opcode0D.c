#include <Limp/instructions/opcode0D.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode0D(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// MMSI
		case 0:{
			Uint32 data = LCpu_readMem32(m_cpu, *m_cpu->args.rb);
			LCpu_writeMem32(m_cpu, *m_cpu->args.rd, data);
			(*m_cpu->args.rb)++;
			(*m_cpu->args.rd)++;
			(*m_cpu->args.ro)++;
		}
		break;
		
		// MMSD
		case 1:{
			Uint32 data = LCpu_readMem32(m_cpu, *m_cpu->args.rb);
			LCpu_writeMem32(m_cpu, *m_cpu->args.rd, data);
			(*m_cpu->args.rb)++;
			(*m_cpu->args.rd)++;
			(*m_cpu->args.ro)--;
		}
		break;
	}
	
}
