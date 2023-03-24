#include <Limp/cpu.h>
#include <Limp/coproc.h>
#include <Limp/mmu.h>
#include <Limp/pci.h>


/**
	DATA
*/


/* System Predefined Interruptions */

const LIPInterruption LI_INT_PMVIOLATION = {0};
const LIPInterruption LI_INT_INVALIDOPC = {2};
const LIPInterruption LI_INT_INVDATAACCESS = {4};
const LIPInterruption LI_INT_INVCODEACCESS = {5};
const LIPInterruption LI_INT_ZERODIVISION = {7};
const LIPInterruption LI_INT_DEBUGGING = {10};



/**
	OBJECT FUNCTIONS
*/


void LCpu_init(LCpu *m_cpu, LBus *m_bus){
	memset(m_cpu, 0, sizeof(LCpu));
	
	m_cpu->io.bus = m_bus;
}



/**
	WORKING FUNCTIONS
*/


/* Memory Access */

Int LCpu_tAddress(LCpu *m_cpu, Uint32 *addr, LIPAdressAccess mode){
	if(getBit(m_cpu->sregs.est, LI_CPU_VM)){
		if(m_cpu->mmu){
			if(m_cpu->mmu->tAddr(addr, mode|m_cpu->sregs.est)){
				if(mode&LIP_ADRESSACCESS_EXECUTE){
					LCpu_requestInterruption(m_cpu, LI_INT_INVCODEACCESS);
				}
				else{
					LCpu_requestInterruption(m_cpu, LI_INT_INVDATAACCESS);
				}
				return 1;
			}
		}
	}
	return 0;
}


Uint8 LCpu_readMem8(LCpu *m_cpu, Uint32 addr){
	if(LCpu_tAddress(m_cpu, &addr, 0)){
		return 0;
	}
	return LICPU_readBus8(m_cpu, addr);
}

Uint16 LCpu_readMem16(LCpu *m_cpu, Uint32 addr){
	if(LCpu_tAddress(m_cpu, &addr, 0)){
		return 0;
	}
	return LICPU_readBus16(m_cpu, addr);
}

Uint32 LCpu_readMem32(LCpu *m_cpu, Uint32 addr){
	if(LCpu_tAddress(m_cpu, &addr, 0)){
		return 0;
	}
	return LICPU_readBus32(m_cpu, addr);
}


void LCpu_writeMem8(LCpu *m_cpu, Uint32 addr, Uint8 data){
	if(LCpu_tAddress(m_cpu, &addr, LIP_ADRESSACCESS_WRITE)){
		return 0;
	}
	LICPU_writeBus8(m_cpu, addr, data);
}

void LCpu_writeMem16(LCpu *m_cpu, Uint32 addr, Uint16 data){
	if(LCpu_tAddress(m_cpu, &addr, LIP_ADRESSACCESS_WRITE)){
		return 0;
	}
	LICPU_writeBus16(m_cpu, addr, data);
}

void LCpu_writeMem32(LCpu *m_cpu, Uint32 addr, Uint32 data){
	if(LCpu_tAddress(m_cpu, &addr, LIP_ADRESSACCESS_WRITE)){
		return 0;
	}
	LICPU_writeBus32(m_cpu, addr, data);
}


Uint32 LCpu_pop(LCpu *m_cpu){
	Uint32 addr = m_cpu->regs.n.esp;
	m_cpu->regs.n.esp += 4;
	if(LCpu_tAddress(m_cpu, &addr, 0)){
		return 0;
	}
	return LICPU_readBus32(m_cpu, addr);
}


void LCpu_push(LCpu *m_cpu, Uint32 data){
	m_cpu->regs.n.esp -= 4;
	Uint32 addr = m_cpu->regs.n.esp;
	if(LCpu_tAddress(m_cpu, &addr, LIP_ADRESSACCESS_WRITE)){
		return 0;
	}
	LICPU_writeBus32(m_cpu, addr, data);
}


Uint32 LCpu_fetch(LCpu *m_cpu){
	Uint32 addr = m_cpu->sregs.epc;
	m_cpu->sregs.epc += 4;
	if(LCpu_tAddress(m_cpu, &addr, LIP_ADRESSACCESS_EXECUTE)){
		return 0;
	}
	return (m_cpu->sregs.efd = LICPU_readBus32(m_cpu, addr));
}


/* Extra Registers */

Uint32 LCpu_readExReg(LCpu *m_cpu, Uint16 reg){
	if(m_cpu->exregs&&(reg<m_cpu->exregs_length)){
		return m_cpu->exregs[reg];
	}
	return 0;
}

void LCpu_writeExReg(LCpu *m_cpu, Uint16 reg, Uint32 data){
	if(m_cpu->exregs&&(reg<m_cpu->exregs_length)){
		m_cpu->exregs[reg] = data;
	}
}


/* External Devices Access */

Uint32 LCpu_in(LCpu *m_cpu, Uint8 port){
	if(m_cpu->io.pci){
		return LPci_cpu_read(m_cpu->io.pci, port);
	}
	return 0;
}

Bool LCpu_inUpdtd(LCpu *m_cpu, Uint8 port){
	if(m_cpu->io.pci){
		return LPci_cpu_readUpdtd(m_cpu->io.pci, port);
	}
	return FALSE;
}

void LCpu_out(LCpu *m_cpu, Uint8 port, Uint32 data){
	if(m_cpu->io.pci){
		LPci_cpu_write(m_cpu->io.pci, port, data);
	}
}


/* Coprocessor Access */

Uint32 LCpu_co_readReg(LCpu *m_cpu, Uint8 co, Uint32 reg){
	co &= 3;
	if(m_cpu->coprocs[co]){
		if(m_cpu->coprocs[co]->readReg){
			return m_cpu->coprocs[co]->readReg(reg);
		}
	}
	
	return 0;
}

void LCpu_co_writeReg(LCpu *m_cpu, Uint8 co, Uint32 reg, Uint32 data){
	co &= 3;
	if(m_cpu->coprocs[co]){
		if(m_cpu->coprocs[co]->writeReg){
			m_cpu->coprocs[co]->writeReg(reg, data);
		}
	}
}


void LCpu_co_disable(LCpu *m_cpu, Uint8 co){
	co &= 3;
	if(m_cpu->coprocs[co]){
		m_cpu->coprocs[co]->enabled = FALSE;
	}
}

void LCpu_co_enable(LCpu *m_cpu, Uint8 co){
	co &= 3;
	if(m_cpu->coprocs[co]){
		m_cpu->coprocs[co]->enabled = TRUE;
	}
}


Uint8 LCpu_co_checkState(LCpu *m_cpu, Uint8 co){
	co &= 3;
	return m_cpu->coprocs[co]? (m_cpu->coprocs[co]->enabled?1:-1) :0;
}


void LCpu_co_command(LCpu *m_cpu, Uint8 co, Uint32 cmd){
	co &= 3;
	if(m_cpu->coprocs[co]){
		if(m_cpu->coprocs[co]->receive){
			m_cpu->coprocs[co]->receive(cmd);
		}
	}
}


/* Instruction Handling */

void LICpu_decode(LCpu *m_cpu){
	Uint32 base = LIDFmt_baseOpcode(m_cpu->sregs.efd);
	
	m_cpu->args.func = LIIsa_table[base].func;
	m_cpu->args.subfuncs = LIIsa_table[base].subfuncs;
	LIIsa_table[base].decoder(m_cpu, LIIsa_table[base].flags);
}

Bool LICpu_condition(LCpu *m_cpu){
	switch(m_cpu->args.cond){
		case 0:{ /* Always */
			return TRUE;
		}
		break;
		case 1:{ /* Equal */
			return getBit(m_cpu->sregs.est, LI_CPU_ZF);
		}
		break;
		case 2:{ /* Not Equal */
			return !getBit(m_cpu->sregs.est, LI_CPU_ZF);
		}
		break;
		case 3:{ /* Lesser Than */
			return (getBit(m_cpu->sregs.est, LI_CPU_VF)!=getBit(m_cpu->sregs.est, LI_CPU_NF))&&!getBit(m_cpu->sregs.est, LI_CPU_ZF);
		}
		break;
		case 4:{ /* Greater Than */
			return (getBit(m_cpu->sregs.est, LI_CPU_VF)==getBit(m_cpu->sregs.est, LI_CPU_NF))&&!getBit(m_cpu->sregs.est, LI_CPU_ZF);
		}
		break;
		case 5:{ /* Lesser or Equal */
			return (getBit(m_cpu->sregs.est, LI_CPU_VF)!=getBit(m_cpu->sregs.est, LI_CPU_NF))||getBit(m_cpu->sregs.est, LI_CPU_ZF);
		}
		break;
		case 6:{ /* Greater or Equal */
			return (getBit(m_cpu->sregs.est, LI_CPU_VF)==getBit(m_cpu->sregs.est, LI_CPU_NF))||getBit(m_cpu->sregs.est, LI_CPU_ZF);
		}
		break;
		case 7:{ /* Below Than */
			return getBit(m_cpu->sregs.est, LI_CPU_BF)&&!getBit(m_cpu->sregs.est, LI_CPU_ZF);
		}
		break;
		case 8:{ /* Above Than */
			return !getBit(m_cpu->sregs.est, LI_CPU_BF)&&!getBit(m_cpu->sregs.est, LI_CPU_ZF);
		}
		break;
		case 9:{ /* Below or Equal */
			return getBit(m_cpu->sregs.est, LI_CPU_BF)||getBit(m_cpu->sregs.est, LI_CPU_ZF);
		}
		break;
		case 10:{ /* Above or Equal */
			return !getBit(m_cpu->sregs.est, LI_CPU_BF)||getBit(m_cpu->sregs.est, LI_CPU_ZF);
		}
		break;
		case 11:{ /* Zero */
			return getBit(m_cpu->sregs.est, LI_CPU_ZF)&&!getBit(m_cpu->sregs.est, LI_CPU_CF)&&!getBit(m_cpu->sregs.est, LI_CPU_BF);
		}
		break;
		case 12:{ /* Non-Zero */
			return !getBit(m_cpu->sregs.est, LI_CPU_ZF)&&!getBit(m_cpu->sregs.est, LI_CPU_CF)&&!getBit(m_cpu->sregs.est, LI_CPU_BF);
		}
		break;
		case 13:{ /* Greater Zero */
			return !getBit(m_cpu->sregs.est, LI_CPU_ZF)&&!getBit(m_cpu->sregs.est, LI_CPU_NF);
		}
		break;
		case 14:{ /* Lesser Zero */
			return !getBit(m_cpu->sregs.est, LI_CPU_ZF)&&getBit(m_cpu->sregs.est, LI_CPU_NF);
		}
		break;
		case 15:{ /* Operand is Zero */
			return (*m_cpu->args.rego)==0;
		}
		break;
		case 16:{ /* Operand is not Zero */
			return (*m_cpu->args.rego)!=0;
		}
		break;
		case 17:{ /* Operand is Lesser Zero */
			return (Sint32)(*m_cpu->args.rego)<0;
		}
		break;
		case 18:{ /* Operand is Greater Zero */
			return (Sint32)(*m_cpu->args.rego)>0;
		}
		break;
		case 19:{ /* Operand is equal EDX */
			return (*m_cpu->args.rego)==(m_cpu->regs.n.edx);
		}
		break;
		case 20:{ /* Operand is not equal EDX */
			return (*m_cpu->args.rego)!=(m_cpu->regs.n.edx);
		}
		break;
		case 21:{ /* Operand is lesser EDX */
			return (Sint32)(*m_cpu->args.rego)<(Sint32)(m_cpu->regs.n.edx);
		}
		break;
		case 22:{ /* Operand is greater EDX */
			return (Sint32)(*m_cpu->args.rego)>(Sint32)(m_cpu->regs.n.edx);
		}
		break;
		case 23:{ /* Operand is equal EAX */
			return (*m_cpu->args.rego)==(m_cpu->regs.n.eax);
		}
		break;
		case 24:{ /* Operand is not equal EAX */
			return (*m_cpu->args.rego)!=(m_cpu->regs.n.eax);
		}
		break;
		case 25:{ /* Has Overflow */
			return getBit(m_cpu->sregs.est, LI_CPU_VF);
		}
		break;
		case 26:{ /* Carry Set */
			return getBit(m_cpu->sregs.est, LI_CPU_CF);
		}
		break;
		case 27:{ /* Carry Clear */
			return !getBit(m_cpu->sregs.est, LI_CPU_CF);
		}
		break;
		case 28:{ /* Borrow Set */
			return getBit(m_cpu->sregs.est, LI_CPU_BF);
		}
		break;
		case 29:{ /* Borrow Clear */
			return !getBit(m_cpu->sregs.est, LI_CPU_BF);
		}
		break;
		case 30:{ /* Odd Set */
			return getBit(m_cpu->sregs.est, LI_CPU_OF);
		}
		break;
		case 31:{ /* Odd Clear */
			return !getBit(m_cpu->sregs.est, LI_CPU_OF);
		}
		break;
	}
	return TRUE;
}

Bool LICpu_protectionThrown(LCpu *m_cpu){
	if(getBit(m_cpu->sregs.est, LI_CPU_PM)){
		LCpu_requestInterruption(m_cpu, LI_INT_PMVIOLATION);
		return TRUE;
	}
	return FALSE;
}


/* Program Flow */

void LCpu_reset(LCpu *m_cpu){
	memset(&m_cpu->regs, 0, sizeof(m_cpu->regs));
	memset(&m_cpu->sregs, 0, sizeof(m_cpu->sregs));
	
	m_cpu->hs.busy = FALSE;
	m_cpu->hs.ext_req = FALSE;
	m_cpu->hs.wait = FALSE;
	m_cpu->hs.waiti = FALSE;
	m_cpu->hs.waits = FALSE;
	
	m_cpu->sregs.lpc = m_cpu->start_jmp;
	m_cpu->sregs.epc = m_cpu->start_jmp;
}

void LCpu_jumpAbs(LCpu *m_cpu, Uint32 addr){
	m_cpu->sregs.lpc = addr;
	m_cpu->sregs.epc = addr;
}

void LCpu_jumpRel(LCpu *m_cpu, Sint32 addr){
	m_cpu->sregs.lpc += addr;
	m_cpu->sregs.epc = m_cpu->sregs.lpc;
}


void LICpu_int_call(LCpu *m_cpu, Uint32 addr){
	LCpu_push(m_cpu, m_cpu->sregs.est);
	LCpu_push(m_cpu, m_cpu->sregs.epc);
	m_cpu->sregs.est = clrBit(m_cpu->sregs.est, LI_CPU_PM);
	m_cpu->hs.wait = FALSE;
	LCpu_jumpAbs(m_cpu, addr);
}

void LICpu_int_return(LCpu *m_cpu){
	/* If is in waiting mode and current interruption is not the desired, put system in wait state */
	if(m_cpu->hs.waits){
		if(m_cpu->hs.waiti!=((Uint8)(m_cpu->sregs.est>>24))){
			m_cpu->hs.wait = TRUE;
		}
		else{
			m_cpu->hs.waits = FALSE;
		}
	}
	
	m_cpu->sregs.epc = LCpu_pop(m_cpu);
	m_cpu->sregs.est = LCpu_pop(m_cpu);
}

Bool LCpu_requestInterruption(LCpu *m_cpu, LIPInterruption intr){ // Returns Bool state => TRUE if the interruption was successfull did
	/* Detect the interruption type */
	if(intr.selector>127){
		if(m_cpu->hs.ext_req){
			return FALSE;
		}
		m_cpu->hs.ext_req = TRUE;
		
		if(!getBit(m_cpu->sregs.est, LI_CPU_EI)){
			while(m_cpu->hs.busy){}
		}
		else{
			return FALSE;
		}
	}
	Uint32 addr = LICPU_readBus32(m_cpu, (m_cpu->sregs.it + (intr.selector*2)));
	LICpu_int_call(m_cpu, addr);
	
	if(intr.selector>127){
		m_cpu->hs.ext_req = FALSE;
	}
	return TRUE;
}


void LICpu_step(LCpu *m_cpu){
	if(!m_cpu->hs.wait){
		Uint32 fetched = LCpu_fetch(m_cpu);
		LICpu_decode(m_cpu);
		m_cpu->args.func(m_cpu);
		m_cpu->sregs.lpc = m_cpu->sregs.epc;
	}
}

void LCpu_step(LCpu *m_cpu){
	m_cpu->hs.busy = TRUE;
	LICpu_step(m_cpu);
	m_cpu->hs.busy = FALSE;
}

Uint32 LICpu_process(void* arg){
	LCpu *m_cpu = (LCpu*)arg;
	Uint32 ltime = 0;
	
	while(TRUE){
		m_cpu->peri.running = TRUE;
		
		m_cpu->freq_i += m_cpu->freq_set;
		while((m_cpu->freq_i>0)&&(!m_cpu->hs.halt)){
			while(m_cpu->hs.ext_req);
			m_cpu->hs.busy = TRUE;
			for(Int s=0; s<128; s++){
				LICpu_step(m_cpu);
				m_cpu->freq_i--;
			}
			m_cpu->hs.busy = FALSE;
		}
		
		while((LTime_getMicros()-ltime)<15625);
		ltime = LTime_getMicros();
		/*printf("MI pulse at microsecond: %d\n", ltime);*/
		
		m_cpu->peri.running = FALSE;
		while(m_cpu->hs.halt){}
	}
	return 0;
}

void LCpu_execute(LCpu *m_cpu){
	m_cpu->hs.halt = FALSE;
	if(m_cpu->peri.t_exec==0){
		m_cpu->peri.t_exec = LThread_create(LICpu_process, m_cpu);
	}
}

void LCpu_stop(LCpu *m_cpu){
	m_cpu->hs.halt = TRUE;
	if(m_cpu->peri.t_exec!=0){
		while(m_cpu->peri.running){/* OBS: Expect the compiler do not optimize here */};
	}
}

