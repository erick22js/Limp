#include <Limp/instructions/opcode10.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode1C(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// FADD
		case 0:{
			*(Float32*)m_cpu->args.rd += *(Float32*)&m_cpu->args.data;
		}
		break;
		
		// FSUB
		case 1:{
			*(Float32*)m_cpu->args.rd -= *(Float32*)&m_cpu->args.data;
		}
		break;
	}
	
}
