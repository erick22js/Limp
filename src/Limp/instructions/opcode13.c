#include <Limp/instructions/opcode13.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode13(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// DIV
		case 0:{
			if(m_cpu->args.data){
				*m_cpu->args.rd = LIAlu_div(m_cpu, *m_cpu->args.rd, m_cpu->args.data);
			}
			else{
				LCpu_requestInterruption(m_cpu, LI_INT_ZERODIVISION);
			}
		}
		break;
		
		// MOD
		case 1:{
			if(m_cpu->args.data){
				*m_cpu->args.rd = LIAlu_mod(m_cpu, *m_cpu->args.rd, m_cpu->args.data);
			}
			else{
				LCpu_requestInterruption(m_cpu, LI_INT_ZERODIVISION);
			}
		}
		break;
	}
	
}
