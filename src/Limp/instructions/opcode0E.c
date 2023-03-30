#include <Limp/instructions/opcode0E.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode0E(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// STSI
		case 0:{
			LCpu_writeMem32(m_cpu, *m_cpu->args.regd, *m_cpu->args.regb);
			(*m_cpu->args.regd)++;
			(*m_cpu->args.rego)++;
		}
		break;
		
		// STSD
		case 1:{
			LCpu_writeMem32(m_cpu, *m_cpu->args.regd, *m_cpu->args.regb);
			(*m_cpu->args.regd)++;
			(*m_cpu->args.rego)--;
		}
		break;
		
		// MMSI
		case 2:{
			Uint32 data = LCpu_readMem32(m_cpu, *m_cpu->args.regb);
			LCpu_writeMem32(m_cpu, *m_cpu->args.regd, data);
			(*m_cpu->args.regb)++;
			(*m_cpu->args.regd)++;
			(*m_cpu->args.rego)++;
		}
		break;
		
		// MMSD
		case 3:{
			Uint32 data = LCpu_readMem32(m_cpu, *m_cpu->args.regb);
			LCpu_writeMem32(m_cpu, *m_cpu->args.regd, data);
			(*m_cpu->args.regb)++;
			(*m_cpu->args.regd)++;
			(*m_cpu->args.rego)--;
		}
		break;
	}
	
}
