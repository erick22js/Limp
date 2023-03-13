#include <Limp/instructions/table.h>
#include <Limp/cpu.h>



/**
	BASE INSTRUCTIONS
*/


void LIIsaFmt_ir(LCpu *m_cpu, LIPSignal signal){
	m_cpu->args.mod = LIDFmt_IR_mod(m_cpu->sregs.efd);
	
	Uint32 im = LIDFmt_IR_im(m_cpu->sregs.efd);
	m_cpu->args.im = im;
	
	/* Loading the immediate for instruction */
	switch(im){
		case 0:{
			m_cpu->args.imm = LIDFmt_IR_imm(m_cpu->sregs.efd);
		}
		break;
		case 1:{
			m_cpu->args.imm = LIDFmt_IR_imm(m_cpu->sregs.efd)<<16;
		}
		break;
		case 2:{
			m_cpu->args.imm = castS16T32(LIDFmt_IR_imm(m_cpu->sregs.efd));
		}
		break;
		default:{
			m_cpu->args.imm = LCpu_fetch(m_cpu);
		}
		break;
	}
	
	m_cpu->args.regd = &m_cpu->regs.u[LIDFmt_IR_regd(m_cpu->sregs.efd)];
	m_cpu->args.regb = &m_cpu->regs.u[LIDFmt_IR_regb(m_cpu->sregs.efd)];
}

void LIIsaFmt_ami(LCpu *m_cpu, LIPSignal signal){
	m_cpu->args.mod = LIDFmt_AMI_mod(m_cpu->sregs.efd);
	
	Uint32 adrm = LIDFmt_AMI_adrm(m_cpu->sregs.efd);
	m_cpu->args.adrm = adrm;
	
	Uint32 dsize = LIDFmt_AMI_dsize(m_cpu->sregs.efd);
	m_cpu->args.dsize = dsize;
	
	Uint32 *regd = &m_cpu->regs.u[LIDFmt_AMI_regd(m_cpu->sregs.efd)];
	m_cpu->args.regd = regd;
	Uint32 *regi = &m_cpu->regs.u[LIDFmt_AMI_regi(m_cpu->sregs.efd)];
	m_cpu->args.regi = regi;
	Uint32 *regb = &m_cpu->regs.u[LIDFmt_AMI_regb(m_cpu->sregs.efd)];
	m_cpu->args.regb = regb;
	
	/* Check for extra immediate fetching */
	if(LIDFmt_AMI_f(m_cpu->sregs.efd)){
		m_cpu->args.imm = LCpu_fetch(m_cpu);
	}
	else{
		m_cpu->args.imm = LIDFmt_AMI_imm(m_cpu->sregs.efd);
	}
	
	Uint32 imm = m_cpu->args.imm;
	
	/* Loading the immediate for instruction base on addressing mode */
	Uint32 ea = 0;
	switch(adrm){
		case 0:{
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = imm;
			}
		}
		break;
		case 1:{
			ea = regb;
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = *regb;
			}
		}
		break;
		case 2:{
			ea = imm<<dsize;
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
		}
		break;
		case 3:{
			ea = *regb;
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
		}
		break;
		case 4:{
			ea = *regb + (imm<<dsize);
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
		}
		break;
		case 5:{
			ea = *regb + *regi;
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
		}
		break;
		case 6:{
			ea = *regb + *regi + (imm<<dsize);
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
		}
		break;
		case 7:{
			ea = *regb + (*regi)*imm;
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
		}
		break;
		case 8:{
			*regb += 1;
			ea = *regb;
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
		}
		break;
		case 9:{
			*regb -= 1;
			ea = *regb;
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
		}
		break;
		case 10:{
			ea = *regb;
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
			*regb += 1;
		}
		break;
		case 11:{
			ea = *regb;
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
			*regb -= 1;
		}
		break;
		case 12:{
			ea = *regb + *regi;
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
			*regi += 1;
		}
		break;
		case 13:{
			ea = *regb + *regi;
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
			*regi -= 1;
		}
		break;
		case 14:{
			ea = *regb + *regi + (imm<<dsize);
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
			*regi += 1;
		}
		break;
		default:{
			ea = *regb + *regi + (imm<<dsize);
			if(!signal&LPROCS_ONLYADDRESS){
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
			*regi -= 1;
		}
	}
	m_cpu->args.ea = ea;
}

void LIIsaFmt_si(LCpu *m_cpu, LIPSignal signal){
	m_cpu->args.mod = LIDFmt_SI_mod(m_cpu->sregs.efd);
	
	Uint32 func = LIDFmt_SI_func(m_cpu->sregs.efd);
	m_cpu->args.func = m_cpu->args.subfuncs[func];
	
	m_cpu->args.regd = &m_cpu->regs.u[LIDFmt_SI_regd(m_cpu->sregs.efd)];
	m_cpu->args.regp = &m_cpu->regs.u[LIDFmt_SI_regp(m_cpu->sregs.efd)];
	m_cpu->args.regb = &m_cpu->regs.u[LIDFmt_SI_regb(m_cpu->sregs.efd)];
	
	/* Check for extra immediate fetching */
	if(LIDFmt_SI_f(m_cpu->sregs.efd)){
		m_cpu->args.imm = LCpu_fetch(m_cpu);
	}
	else{
		m_cpu->args.imm = LIDFmt_SI_imm(m_cpu->sregs.efd);
	}
}

void LIIsaFmt_adi(LCpu *m_cpu, LIPSignal signal){
	m_cpu->args.mod = LIDFmt_ADI_mod(m_cpu->sregs.efd);
	m_cpu->args.cond = LIDFmt_ADI_cond(m_cpu->sregs.efd);
	m_cpu->args.rego = &m_cpu->regs.u[LIDFmt_ADI_rego(m_cpu->sregs.efd)];
	m_cpu->args.imm = LIDFmt_ADI_imm(m_cpu->sregs.efd);
	
	if(!LICpu_condition(m_cpu)){
		m_cpu->args.func = LIIsaDtb_nop;
	}
}

void LIIsaFmt_cdi(LCpu *m_cpu, LIPSignal signal){
	m_cpu->args.mod = LIDFmt_CDI_mod(m_cpu->sregs.efd);
	m_cpu->args.cond = LIDFmt_CDI_cond(m_cpu->sregs.efd);
	
	m_cpu->args.regd = &m_cpu->regs.u[LIDFmt_CDI_regd(m_cpu->sregs.efd)];
	m_cpu->args.rego = &m_cpu->regs.u[LIDFmt_CDI_rego(m_cpu->sregs.efd)];
	m_cpu->args.regb = &m_cpu->regs.u[LIDFmt_CDI_regb(m_cpu->sregs.efd)];
	
	/* Check for extra immediate fetching */
	if(LIDFmt_CDI_f(m_cpu->sregs.efd)){
		m_cpu->args.imm = LCpu_fetch(m_cpu);
	}
	else{
		m_cpu->args.imm = LIDFmt_CDI_imm(m_cpu->sregs.efd);
	}
	
	if(!LIDFmt_CDI_gap_(m_cpu->sregs.efd)){
		m_cpu->args.func = LIIsaDtb_nop;
		LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
		return;
	}
	
	if(!LICpu_condition(m_cpu)){
		m_cpu->args.func = LIIsaDtb_nop;
	}
}

void LIIsaFmt_jl(LCpu *m_cpu, LIPSignal signal){
	m_cpu->args.imm = LIDFmt_JL_imm(m_cpu->sregs.efd);
}


void LIIsaDtb_undefined(LCpu *m_cpu){
	printf("# Undefined Instruction #\n");
	LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
}

void LIIsaDtb_nop(LCpu *m_cpu){
	printf("# No Operation Instruction #\n");
}



/**
	TABLE INSTRUCTIONS
*/

LIInstDescriptor LIIsa_table[64] = {
	[0x00] = {LIIsaFmt_jl, LIIsaDtb_nop, LPROCS_NONE, NULL},
	[0x01] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x02] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x03] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x04] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x05] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x06] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x07] = {LIIsaFmt_ami, LIIsaDtb_opcode07, LPROCS_ONLYADDRESS, NULL},
	[0x08] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x09] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x0A] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x0B] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x0C] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x0D] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x0E] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x0F] = {LIIsaFmt_ami, LIIsaDtb_opcode0F, LPROCS_ONLYADDRESS, NULL},
	
	[0x10] = {LIIsaFmt_ami, LIIsaDtb_opcode10, LPROCS_NONE, NULL},
	[0x11] = {LIIsaFmt_ami, LIIsaDtb_opcode11, LPROCS_NONE, NULL},
	[0x12] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x13] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x14] = {LIIsaFmt_si, NULL, LPROCS_NONE, LIIsaDtb_opcode14},
	[0x15] = {LIIsaFmt_ami, LIIsaDtb_opcode15, LPROCS_NONE, NULL},
	[0x16] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x17] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x18] = {LIIsaFmt_ami, LIIsaDtb_opcode18, LPROCS_NONE, NULL},
	[0x19] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x1A] = {LIIsaFmt_ami, LIIsaDtb_opcode1A, LPROCS_NONE, NULL},
	[0x1B] = {LIIsaFmt_ami, LIIsaDtb_opcode1B, LPROCS_NONE, NULL},
	[0x1C] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x1D] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x1E] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x1F] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	
	[0x20] = {LIIsaFmt_adi, LIIsaDtb_opcode20, LPROCS_NONE, NULL},
	[0x21] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x22] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x23] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x24] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x25] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x26] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x27] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x28] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x29] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x2A] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x2B] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x2C] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x2D] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x2E] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x2F] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	
	[0x30] = {LIIsaFmt_ir, LIIsaDtb_opcode30, LPROCS_NONE, NULL},
	[0x31] = {LIIsaFmt_ir, LIIsaDtb_opcode31, LPROCS_NONE, NULL},
	[0x32] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x33] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x34] = {LIIsaFmt_si, NULL, LPROCS_NONE, LIIsaDtb_opcode34},
	[0x35] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x36] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x37] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x38] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x39] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x3A] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x3B] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x3C] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x3D] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x3E] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x3F] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
};

