#include <Limp/instructions/opcode28.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode28(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// XOR
		case 0:{
			*m_cpu->args.rd = LIAlu_xor(m_cpu, *m_cpu->args.rd, m_cpu->args.data);
		}
		break;
		
		// NAND
		case 1:{
			*m_cpu->args.rd = LIAlu_nand(m_cpu, *m_cpu->args.rd, m_cpu->args.data);
		}
		break;
	}
	
}
