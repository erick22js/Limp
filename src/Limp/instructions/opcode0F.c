#include <Limp/instructions/opcode0F.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode0F(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// STRB
		case 0:{
			LCpu_writeMem8(m_cpu, m_cpu->args.ea, *m_cpu->args.regd);
		}
		break;
		
		// STRW
		case 1:{
			LCpu_writeMem16(m_cpu, m_cpu->args.ea, *m_cpu->args.regd);
		}
		break;
		
		// STRD
		case 2:{
			LCpu_writeMem32(m_cpu, m_cpu->args.ea, *m_cpu->args.regd);
		}
		break;
		
		// STRQ
		case 3:{
			LCpu_writeMem32(m_cpu, m_cpu->args.ea, m_cpu->args.regd[0]);
			LCpu_writeMem32(m_cpu, m_cpu->args.ea+4, m_cpu->args.regd[1]);
		}
		break;
		
		default:{
			/* TODO: Exception => Invalid Instruction */
		}
	}
	
}
