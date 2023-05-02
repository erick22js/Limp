#include <Limp/instructions/opcode10.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode10(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// ADD
		case 0:{
			*m_cpu->args.rd = LIAlu_add(m_cpu, *m_cpu->args.rd, m_cpu->args.data, FALSE);
		}
		break;
		
		// ADC
		case 1:{
			*m_cpu->args.rd = LIAlu_add(m_cpu, *m_cpu->args.rd, m_cpu->args.data, TRUE);
		}
		break;
	}
	
}
