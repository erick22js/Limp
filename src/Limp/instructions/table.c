#include <Limp/instructions/table.h>
#include <Limp/cpu.h>



/**
	BASE INSTRUCTIONS
*/


void LIIsaFmt_ir(LCpu *m_cpu, LIPSignal signal){
	Bool s = (m_cpu->args.selector = LIDFmt_IR_selector(m_cpu->sregs.efd));
	m_cpu->args.mod = LIDFmt_IR_mod(m_cpu->sregs.efd);
	
	Uint32 im = LIDFmt_IR_im(m_cpu->sregs.efd);
	m_cpu->args.im = im;
	
	Uint32 regof = s?8:0;
	m_cpu->args.regd = LIDFmt_IR_regd(m_cpu->sregs.efd);
	m_cpu->args.rd = &m_cpu->regs.u[m_cpu->args.regd+regof];
	m_cpu->args.regb = LIDFmt_IR_regb(m_cpu->sregs.efd);
	m_cpu->args.rb = &m_cpu->regs.u[m_cpu->args.regb+regof];
	
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
}

void LIIsaFmt_ami(LCpu *m_cpu, LIPSignal signal){
	Bool s = (m_cpu->args.selector = LIDFmt_AMI_selector(m_cpu->sregs.efd));
	m_cpu->args.mod = LIDFmt_AMI_mod(m_cpu->sregs.efd);
	
	Uint32 adrm = LIDFmt_AMI_adrm(m_cpu->sregs.efd);
	m_cpu->args.adrm = adrm;
	
	Uint32 dsize = LIDFmt_AMI_dsize(m_cpu->sregs.efd);
	m_cpu->args.dsize = dsize;
	
	Uint32 regof = s?8:0;
	m_cpu->args.regd = LIDFmt_AMI_regd(m_cpu->sregs.efd);
	Uint32 *regd = &m_cpu->regs.u[m_cpu->args.regd+regof];
	m_cpu->args.rd = regd;
	/* Only for address calculation is not allowed registers from others sets */
	m_cpu->args.regi = LIDFmt_AMI_regi(m_cpu->sregs.efd);
	Uint32 *regi = &m_cpu->regs.u[m_cpu->args.regi];
	m_cpu->args.ri = regi;
	m_cpu->args.regb = LIDFmt_AMI_regb(m_cpu->sregs.efd);
	Uint32 *regb = &m_cpu->regs.u[m_cpu->args.regb];
	m_cpu->args.rb = regb;
	
	Uint32 imm;
	Uint32 immd;
	
	/* Check for extra immediate fetching */
	if(LIDFmt_AMI_f(m_cpu->sregs.efd)){
		m_cpu->args.imm = LCpu_fetch(m_cpu);
		imm = m_cpu->args.imm;
		immd = m_cpu->args.imm;
	}
	else{
		m_cpu->args.imm = LIDFmt_AMI_imm(m_cpu->sregs.efd);
		imm = castS8T32(m_cpu->args.imm);
		immd = m_cpu->args.imm;
	}
	
	/* Loading the immediate for instruction base on addressing mode */
	Uint32 ea = 0;
	Bool readmem_adr = !signal&LPROCS_ONLYADDRESS;
	switch(adrm){
		case 0:{
			m_cpu->args.data = immd;
			readmem_adr = FALSE;
		}
		break;
		case 1:{
			/* The register is from asked set */
			regb = &m_cpu->regs.u[m_cpu->args.regb+regof];
			m_cpu->args.rb = regb;
			/* Retrieves the register data */
			ea = regb;
			m_cpu->args.data = *regb;
			readmem_adr = FALSE;
		}
		break;
		case 2:{
			ea = imm<<dsize;
		}
		break;
		case 3:{
			ea = *regb;
		}
		break;
		case 4:{
			ea = *regb + (imm<<dsize);
		}
		break;
		case 5:{
			ea = *regb + *regi;
		}
		break;
		case 6:{
			ea = *regb + *regi + (imm<<dsize);
		}
		break;
		case 7:{
			ea = *regb + (*regi)*imm;
		}
		break;
		case 8:{
			*regb += 1;
			ea = *regb;
		}
		break;
		case 9:{
			*regb -= 1;
			ea = *regb;
		}
		break;
		case 10:{
			ea = *regb;
			*regb += 1;
		}
		break;
		case 11:{
			ea = *regb;
			*regb -= 1;
		}
		break;
		case 12:{
			ea = *regb + *regi;
			*regi += 1;
		}
		break;
		case 13:{
			ea = *regb + *regi;
			*regi -= 1;
		}
		break;
		case 14:{
			ea = *regb + *regi + (imm<<dsize);
			*regi += 1;
		}
		break;
		default:{
			ea = *regb + *regi + (imm<<dsize);
			*regi -= 1;
		}
	}
	if(readmem_adr){
		switch(dsize){
			case 0:{
				m_cpu->args.data = LCpu_readMem8(m_cpu, ea);
			}
			break;
			case 1:{
				m_cpu->args.data = LCpu_readMem16(m_cpu, ea);
			}
			break;
			case 2:
			case 3:{
				m_cpu->args.data = LCpu_readMem32(m_cpu, ea);
			}
			break;
		}
	}
	
	m_cpu->args.ea = ea;
}

void LIIsaFmt_si(LCpu *m_cpu, LIPSignal signal){
	Bool s = (m_cpu->args.selector = LIDFmt_SI_selector(m_cpu->sregs.efd));
	m_cpu->args.mod = LIDFmt_SI_mod(m_cpu->sregs.efd);
	
	Uint32 func = LIDFmt_SI_func(m_cpu->sregs.efd);
	m_cpu->args.func = m_cpu->args.subfuncs[func];
	
	Uint32 regof = s?8:0;
	m_cpu->args.regd = LIDFmt_SI_regd(m_cpu->sregs.efd);
	m_cpu->args.rd = &m_cpu->regs.u[m_cpu->args.regd+regof];
	m_cpu->args.regp = LIDFmt_SI_regp(m_cpu->sregs.efd);
	m_cpu->args.rp = &m_cpu->regs.u[m_cpu->args.regp+regof];
	m_cpu->args.regb = LIDFmt_SI_regb(m_cpu->sregs.efd);
	m_cpu->args.rb = &m_cpu->regs.u[m_cpu->args.regb+regof];
	
	/* Check for extra immediate fetching */
	if(LIDFmt_SI_f(m_cpu->sregs.efd)){
		m_cpu->args.imm = LCpu_fetch(m_cpu);
	}
	else{
		m_cpu->args.imm = LIDFmt_SI_imm(m_cpu->sregs.efd);
	}
}

void LIIsaFmt_adi(LCpu *m_cpu, LIPSignal signal){
	Bool s = (m_cpu->args.selector = LIDFmt_ADI_selector(m_cpu->sregs.efd));
	m_cpu->args.mod = LIDFmt_ADI_mod(m_cpu->sregs.efd);
	m_cpu->args.cond = LIDFmt_ADI_cond(m_cpu->sregs.efd);
	Uint32 regof = s?8:0;
	m_cpu->args.rego = LIDFmt_ADI_rego(m_cpu->sregs.efd);
	m_cpu->args.ro = &m_cpu->regs.u[m_cpu->args.rego+regof];
	m_cpu->args.imm = castS16T32(LIDFmt_ADI_imm(m_cpu->sregs.efd));
	
	if(!LICpu_condition(m_cpu)){
		m_cpu->args.func = LIIsaDtb_nop;
	}
}

void LIIsaFmt_cdi(LCpu *m_cpu, LIPSignal signal){
	Bool s = (m_cpu->args.selector = LIDFmt_CDI_selector(m_cpu->sregs.efd));
	m_cpu->args.mod = LIDFmt_CDI_mod(m_cpu->sregs.efd);
	m_cpu->args.cond = LIDFmt_CDI_cond(m_cpu->sregs.efd);
	
	Bool os = (m_cpu->args.selector = LIDFmt_CDI_oselector(m_cpu->sregs.efd));
	
	Uint32 regof = s?8:0;
	Uint32 oregof = os?8:0;
	m_cpu->args.regd = LIDFmt_CDI_regd(m_cpu->sregs.efd);
	m_cpu->args.rd = &m_cpu->regs.u[m_cpu->args.regd+regof];
	m_cpu->args.rego = LIDFmt_CDI_rego(m_cpu->sregs.efd);
	m_cpu->args.ro = &m_cpu->regs.u[m_cpu->args.rego+oregof];
	m_cpu->args.regb = LIDFmt_CDI_regb(m_cpu->sregs.efd);
	m_cpu->args.rb = &m_cpu->regs.u[m_cpu->args.regb+regof];
	
	/* Check for extra immediate fetching */
	if(LIDFmt_CDI_f(m_cpu->sregs.efd)){
		m_cpu->args.imm = LCpu_fetch(m_cpu);
	}
	else{
		m_cpu->args.imm = LIDFmt_CDI_imm(m_cpu->sregs.efd);
	}
	
	if(!LICpu_condition(m_cpu)){
		m_cpu->args.func = LIIsaDtb_nop;
	}
}

void LIIsaFmt_jl(LCpu *m_cpu, LIPSignal signal){
	m_cpu->args.imm = LIDFmt_JL_imm(m_cpu->sregs.efd);
}


void LIIsaDtb_undefined(LCpu *m_cpu){
	LCpu_requestInterruption(m_cpu, LI_INT_INVALIDOPC);
}

void LIIsaDtb_nop(LCpu *m_cpu){}



/**
	TABLE INSTRUCTIONS
*/

LIInstDescriptor LIIsa_table[64] = {
	[0x00] = {LIIsaFmt_jl, LIIsaDtb_nop, LPROCS_NONE, NULL},
	[0x01] = {LIIsaFmt_si, NULL, LPROCS_NONE, LIIsaDtb_opcode01},
	[0x02] = {LIIsaFmt_si, NULL, LPROCS_NONE, LIIsaDtb_opcode02},
	[0x03] = {LIIsaFmt_si, NULL, LPROCS_NONE, LIIsaDtb_opcode03},
	[0x04] = {LIIsaFmt_ir, LIIsaDtb_opcode04, LPROCS_NONE, NULL},
	[0x05] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x06] = {LIIsaFmt_ami, LIIsaDtb_opcode06, LPROCS_ONLYADDRESS, NULL},
	[0x07] = {LIIsaFmt_ami, LIIsaDtb_opcode07, LPROCS_ONLYADDRESS, NULL},
	[0x08] = {LIIsaFmt_ami, LIIsaDtb_opcode08, LPROCS_NONE, NULL},
	[0x09] = {LIIsaFmt_ami, LIIsaDtb_opcode09, LPROCS_ONLYADDRESS, NULL},
	[0x0A] = {LIIsaFmt_ami, LIIsaDtb_opcode0A, LPROCS_ONLYADDRESS, NULL},
	[0x0B] = {LIIsaFmt_ami, LIIsaDtb_opcode0B, LPROCS_ONLYADDRESS, NULL},
	[0x0C] = {LIIsaFmt_cdi, LIIsaDtb_opcode0C, LPROCS_NONE, NULL},
	[0x0D] = {LIIsaFmt_cdi, LIIsaDtb_opcode0D, LPROCS_NONE, NULL},
	[0x0E] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x0F] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	
	[0x10] = {LIIsaFmt_ami, LIIsaDtb_opcode10, LPROCS_NONE, NULL},
	[0x11] = {LIIsaFmt_ami, LIIsaDtb_opcode11, LPROCS_NONE, NULL},
	[0x12] = {LIIsaFmt_ami, LIIsaDtb_opcode12, LPROCS_NONE, NULL},
	[0x13] = {LIIsaFmt_ami, LIIsaDtb_opcode13, LPROCS_NONE, NULL},
	[0x14] = {LIIsaFmt_si, NULL, LPROCS_NONE, LIIsaDtb_opcode14},
	[0x15] = {LIIsaFmt_ami, LIIsaDtb_opcode15, LPROCS_NONE, NULL},
	[0x16] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x17] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x18] = {LIIsaFmt_ami, LIIsaDtb_opcode18, LPROCS_NONE, NULL},
	[0x19] = {LIIsaFmt_si, NULL, LPROCS_NONE, LIIsaDtb_opcode19},
	[0x1A] = {LIIsaFmt_ami, LIIsaDtb_opcode1A, LPROCS_NONE, NULL},
	[0x1B] = {LIIsaFmt_ami, LIIsaDtb_opcode1B, LPROCS_NONE, NULL},
	[0x1C] = {LIIsaFmt_ami, LIIsaDtb_opcode1C, LPROCS_NONE, NULL},
	[0x1D] = {LIIsaFmt_si, NULL, LPROCS_NONE, LIIsaDtb_opcode1D},
	[0x1E] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x1F] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	
	[0x20] = {LIIsaFmt_ir, LIIsaDtb_opcode20, LPROCS_NONE, NULL},
	[0x21] = {LIIsaFmt_ir, LIIsaDtb_opcode21, LPROCS_NONE, NULL},
	[0x22] = {LIIsaFmt_ir, LIIsaDtb_opcode22, LPROCS_NONE, NULL},
	[0x23] = {LIIsaFmt_cdi, LIIsaDtb_opcode23, LPROCS_NONE, NULL},
	[0x24] = {LIIsaFmt_si, NULL, LPROCS_NONE, LIIsaDtb_opcode24},
	[0x25] = {LIIsaFmt_si, NULL, LPROCS_NONE, LIIsaDtb_opcode25},
	[0x26] = {LIIsaFmt_ir, LIIsaDtb_opcode26, LPROCS_NONE, NULL},
	[0x27] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x28] = {LIIsaFmt_ami, LIIsaDtb_opcode28, LPROCS_NONE, NULL},
	[0x29] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x2A] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x2B] = {LIIsaFmt_ami, LIIsaDtb_opcode2B, LPROCS_NONE, NULL},
	[0x2C] = {LIIsaFmt_ami, LIIsaDtb_opcode2C, LPROCS_NONE, NULL},
	[0x2D] = {LIIsaFmt_si, NULL, LPROCS_NONE, LIIsaDtb_opcode2D},
	[0x2E] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x2F] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	
	[0x30] = {LIIsaFmt_adi, LIIsaDtb_opcode30, LPROCS_NONE, NULL},
	[0x31] = {LIIsaFmt_si, NULL, LPROCS_NONE, LIIsaDtb_opcode31},
	[0x32] = {LIIsaFmt_cdi, LIIsaDtb_opcode32, LPROCS_NONE, NULL},
	[0x33] = {LIIsaFmt_cdi, LIIsaDtb_opcode33, LPROCS_NONE, NULL},
	[0x34] = {LIIsaFmt_jl, LIIsaDtb_opcode34, LPROCS_NONE, NULL},
	[0x35] = {LIIsaFmt_jl, LIIsaDtb_opcode35, LPROCS_NONE, NULL},
	[0x36] = {LIIsaFmt_jl, LIIsaDtb_opcode36, LPROCS_NONE, NULL},
	[0x37] = {LIIsaFmt_jl, LIIsaDtb_opcode37, LPROCS_NONE, NULL},
	[0x38] = {LIIsaFmt_adi, LIIsaDtb_opcode38, LPROCS_NONE, NULL},
	[0x39] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x3A] = {LIIsaFmt_cdi, LIIsaDtb_opcode3A, LPROCS_NONE, NULL},
	[0x3B] = {LIIsaFmt_cdi, LIIsaDtb_opcode3B, LPROCS_NONE, NULL},
	[0x3C] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_ONLYADDRESS, NULL},
	[0x3D] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_ONLYADDRESS, NULL},
	[0x3E] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
	[0x3F] = {LIIsaFmt_jl, LIIsaDtb_undefined, LPROCS_NONE, NULL},
};

