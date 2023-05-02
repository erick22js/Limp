#include <Limp/instructions/opcode3B.h>
#include <Limp/cpu.h>


void LIIsaDtb_opcode3B(LCpu *m_cpu){
	
	switch(m_cpu->args.mod){
		// XJP
		case 0:{
			Uint32 addr = *m_cpu->args.rb;
			*m_cpu->args.rb = m_cpu->sregs.epc;
			LCpu_jumpAbs(m_cpu, addr);
		}
		break;
		
		// XBR
		case 1:{
			Uint32 addr = *m_cpu->args.rb;
			*m_cpu->args.rb = m_cpu->sregs.epc;
			LCpu_push(m_cpu, m_cpu->sregs.epc);
			LCpu_jumpAbs(m_cpu, addr);
		}
		break;
	}
	
}

