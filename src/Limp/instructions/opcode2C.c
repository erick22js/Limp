#include <Limp/instructions/opcode2C.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode2C(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// FMUL
		case 0:{
			*(Float32*)m_cpu->args.rd *= *(Float32*)&m_cpu->args.data;
		}
		break;
		
		// FDIV
		case 1:{
			*(Float32*)m_cpu->args.rd /= *(Float32*)&m_cpu->args.data;
		}
		break;
	}
	
}
