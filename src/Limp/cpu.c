#include <Limp/cpu.h>
#include <Limp/coproc.h>
#include <Limp/mmu.h>
#include <Limp/pci.h>


/**
	DATA
*/


/* System Predefined Interruptions */

const LIPInterruption LI_INT_PMVIOLATION = {1};
const LIPInterruption LI_INT_INVALIDOPC = {2};
const LIPInterruption LI_INT_INVDATAACCESS = {4};
const LIPInterruption LI_INT_INVCODEACCESS = {5};
const LIPInterruption LI_INT_ZERODIVISION = {7};
const LIPInterruption LI_INT_DEBUGGING = {9};
const LIPInterruption LI_INT_COPROC0 = {10};
const LIPInterruption LI_INT_COPROC1 = {11};
const LIPInterruption LI_INT_COPROC2 = {12};
const LIPInterruption LI_INT_COPROC3 = {13};
const LIPInterruption LI_INT_BIOSRESERVED1 = {14};
const LIPInterruption LI_INT_BIOSRESERVED2 = {15};



/**
	EMULATION FUNCTIONS
*/

void LCpu_emuStamp(void *obj){
	LCpu *m_cpu = obj;
	
	for(Int i=0; i<64; i++){
		if(!m_cpu->hs.halt){
			LCpu_step(m_cpu);
		}
	}
}

void LCpu_emuStep(void *obj){
	LCpu *m_cpu = obj;
	
	if(!m_cpu->hs.halt){
		LCpu_step(m_cpu);
	}
}


/**
	OBJECT FUNCTIONS
*/


void LCpu_init(LCpu *m_cpu, LBus *m_bus){
	memset(m_cpu, 0, sizeof(LCpu));
	
	/* Sets emulation methods */
	m_cpu->emu.emuStamp = LCpu_emuStamp;
	m_cpu->emu.emuStep = LCpu_emuStep;
	
	/* Sets the default cycling to 16MHz */
	m_cpu->cy.cpb_set = 128;
	m_cpu->cy.bpp_set = 2048;
	
	m_cpu->io.bus = m_bus;
}

Bool LCpu_conMmu(LCpu *m_cpu, LMmu *m_mmu){
	m_cpu->coprocs[0] = &m_mmu->coproc;
	m_cpu->mmu = m_mmu;
	m_mmu->coproc.m_cpu = m_cpu;
	m_mmu->coproc.slot = 0;
	return TRUE;
}

Int LCpu_conCop(LCpu *m_cpu, LCoproc *cop){
	if(m_cpu->coprocs[1]){
		if(m_cpu->coprocs[2]){
			if(!m_cpu->coprocs[3]){
				m_cpu->coprocs[3] = cop;
				cop->m_cpu = m_cpu;
				cop->slot = 3;
				return 3;
			}
		}
		else{
			m_cpu->coprocs[2] = cop;
			cop->m_cpu = m_cpu;
			cop->slot = 2;
			return 2;
		}
	}
	else{
		m_cpu->coprocs[1] = cop;
		cop->m_cpu = m_cpu;
		cop->slot = 1;
		return 1;
	}
	cop->m_cpu = NULL;
	cop->slot = -1;
	return 0;
}


/**
	WORKING FUNCTIONS
*/


Int LCpu_tAddress(LCpu *m_cpu, Uint32 *addr, LIPAdressAccess mode){
	if(getBit(m_cpu->sregs.st, LI_CPU_VM)){
		if(m_cpu->mmu){
			if(m_cpu->mmu->tAddr(&m_cpu->mmu, addr, mode|m_cpu->sregs.st)){
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

Int LICpu_tAddress(LCpu *m_cpu, Uint32 *addr, LIPAdressAccess mode){
	if(m_cpu->mmu){
		if(m_cpu->mmu->tAddr(&m_cpu->mmu, addr, mode|m_cpu->sregs.st)){
			return 1;
		}
	}
	return 0;
}


/* Memory Access */

Uint8 LCpu_readMem8(LCpu *m_cpu, Uint32 addr){
	if(LCpu_tAddress(m_cpu, &addr, 0)){
		return 0;
	}
	/* Updates the cycle count */
	m_cpu->cy.cycles--;
	return LICPU_readBus8(m_cpu, addr);
}

Uint16 LCpu_readMem16(LCpu *m_cpu, Uint32 addr){
	if(LCpu_tAddress(m_cpu, &addr, 0)){
		return 0;
	}
	/* Updates the cycle count */
	m_cpu->cy.cycles--;
	return LICPU_readBus16(m_cpu, addr);
}

Uint32 LCpu_readMem32(LCpu *m_cpu, Uint32 addr){
	if(LCpu_tAddress(m_cpu, &addr, 0)){
		return 0;
	}
	/* Updates the cycle count */
	m_cpu->cy.cycles--;
	return LICPU_readBus32(m_cpu, addr);
}


void LCpu_writeMem8(LCpu *m_cpu, Uint32 addr, Uint8 data){
	if(LCpu_tAddress(m_cpu, &addr, LIP_ADRESSACCESS_WRITE)){
		return 0;
	}
	LICPU_writeBus8(m_cpu, addr, data);
	/* Updates the cycle count */
	m_cpu->cy.cycles--;
}

void LCpu_writeMem16(LCpu *m_cpu, Uint32 addr, Uint16 data){
	if(LCpu_tAddress(m_cpu, &addr, LIP_ADRESSACCESS_WRITE)){
		return 0;
	}
	LICPU_writeBus16(m_cpu, addr, data);
	/* Updates the cycle count */
	m_cpu->cy.cycles--;
}

void LCpu_writeMem32(LCpu *m_cpu, Uint32 addr, Uint32 data){
	if(LCpu_tAddress(m_cpu, &addr, LIP_ADRESSACCESS_WRITE)){
		return 0;
	}
	LICPU_writeBus32(m_cpu, addr, data);
	/* Updates the cycle count */
	m_cpu->cy.cycles--;
}


Uint32 LCpu_pop(LCpu *m_cpu){
	Uint32 addr = m_cpu->regs.n.sp;
	m_cpu->regs.n.sp += 4;
	if(LCpu_tAddress(m_cpu, &addr, 0)){
		return 0;
	}
	/* Updates the cycle count */
	m_cpu->cy.cycles--;
	return LICPU_readBus32(m_cpu, addr);
}


void LCpu_push(LCpu *m_cpu, Uint32 data){
	m_cpu->regs.n.sp -= 4;
	Uint32 addr = m_cpu->regs.n.sp;
	if(LCpu_tAddress(m_cpu, &addr, LIP_ADRESSACCESS_WRITE)){
		return 0;
	}
	LICPU_writeBus32(m_cpu, addr, data);
	/* Updates the cycle count */
	m_cpu->cy.cycles--;
}

Uint32 LICpu_pop(LCpu *m_cpu){
	Uint32 addr = m_cpu->regs.n.sp;
	m_cpu->regs.n.sp += 4;
	/* Updates the cycle count */
	m_cpu->cy.cycles--;
	return LICPU_readBus32(m_cpu, addr);
}


void LICpu_push(LCpu *m_cpu, Uint32 data){
	m_cpu->regs.n.sp -= 4;
	Uint32 addr = m_cpu->regs.n.sp;
	LICPU_writeBus32(m_cpu, addr, data);
	/* Updates the cycle count */
	m_cpu->cy.cycles--;
}


Uint32 LCpu_fetch(LCpu *m_cpu){
	Uint32 addr = m_cpu->sregs.epc;
	m_cpu->sregs.epc += 4;
	if(LCpu_tAddress(m_cpu, &addr, LIP_ADRESSACCESS_EXECUTE)){
		return 0;
	}
	/* Updates the cycle count */
	m_cpu->cy.cycles--;
	return (m_cpu->sregs.efd = LICPU_readBus32(m_cpu, addr));
}


/* Extra Registers */

Uint32 LCpu_readCache(LCpu *m_cpu, Uint32 addr){
	if(m_cpu->cache&&(addr<m_cpu->cache_length)){
		return m_cpu->cache[addr];
	}
	return 0;
}

void LCpu_writeCache(LCpu *m_cpu, Uint32 addr, Uint32 data){
	if(m_cpu->cache&&(addr<m_cpu->cache_length)){
		m_cpu->cache[addr] = data;
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
	//Log("Outputing data 0x%x to port 0x%x\n", data, port);
	if(m_cpu->io.pci){
		LPci_cpu_write(m_cpu->io.pci, port, data);
	}
}


/* Coprocessor Access */

Uint32 LCpu_co_readReg(LCpu *m_cpu, Uint8 co, Uint32 reg){
	co &= 3;
	if(m_cpu->coprocs[co]){
		if(m_cpu->coprocs[co]->readReg){
			return m_cpu->coprocs[co]->readReg(&m_cpu->coprocs[co], reg);
		}
	}
	
	return 0;
}

void LCpu_co_writeReg(LCpu *m_cpu, Uint8 co, Uint32 reg, Uint32 data){
	co &= 3;
	if(m_cpu->coprocs[co]){
		if(m_cpu->coprocs[co]->writeReg){
			m_cpu->coprocs[co]->writeReg(&m_cpu->coprocs[co], reg, data);
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
			m_cpu->coprocs[co]->receive(&m_cpu->coprocs[co], cmd);
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
			return getBit(m_cpu->sregs.st, LI_CPU_ZF);
		}
		break;
		case 2:{ /* Not Equal */
			return !getBit(m_cpu->sregs.st, LI_CPU_ZF);
		}
		break;
		case 3:{ /* Lesser Than */
			return (getBit(m_cpu->sregs.st, LI_CPU_VF)!=getBit(m_cpu->sregs.st, LI_CPU_NF))&&!getBit(m_cpu->sregs.st, LI_CPU_ZF);
		}
		break;
		case 4:{ /* Greater Than */
			return (getBit(m_cpu->sregs.st, LI_CPU_VF)==getBit(m_cpu->sregs.st, LI_CPU_NF))&&!getBit(m_cpu->sregs.st, LI_CPU_ZF);
		}
		break;
		case 5:{ /* Lesser or Equal */
			return (getBit(m_cpu->sregs.st, LI_CPU_VF)!=getBit(m_cpu->sregs.st, LI_CPU_NF))||getBit(m_cpu->sregs.st, LI_CPU_ZF);
		}
		break;
		case 6:{ /* Greater or Equal */
			return (getBit(m_cpu->sregs.st, LI_CPU_VF)==getBit(m_cpu->sregs.st, LI_CPU_NF))||getBit(m_cpu->sregs.st, LI_CPU_ZF);
		}
		break;
		case 7:{ /* Below Than */
			return getBit(m_cpu->sregs.st, LI_CPU_BF)&&!getBit(m_cpu->sregs.st, LI_CPU_ZF);
		}
		break;
		case 8:{ /* Above Than */
			return !getBit(m_cpu->sregs.st, LI_CPU_BF)&&!getBit(m_cpu->sregs.st, LI_CPU_ZF);
		}
		break;
		case 9:{ /* Below or Equal */
			return getBit(m_cpu->sregs.st, LI_CPU_BF)||getBit(m_cpu->sregs.st, LI_CPU_ZF);
		}
		break;
		case 10:{ /* Above or Equal */
			return !getBit(m_cpu->sregs.st, LI_CPU_BF)||getBit(m_cpu->sregs.st, LI_CPU_ZF);
		}
		break;
		case 11:{ /* Zero */
			return getBit(m_cpu->sregs.st, LI_CPU_ZF)&&!getBit(m_cpu->sregs.st, LI_CPU_CF)&&!getBit(m_cpu->sregs.st, LI_CPU_BF);
		}
		break;
		case 12:{ /* Non-Zero */
			return !getBit(m_cpu->sregs.st, LI_CPU_ZF)&&!getBit(m_cpu->sregs.st, LI_CPU_CF)&&!getBit(m_cpu->sregs.st, LI_CPU_BF);
		}
		break;
		case 13:{ /* Greater Zero */
			return !getBit(m_cpu->sregs.st, LI_CPU_ZF)&&!getBit(m_cpu->sregs.st, LI_CPU_NF);
		}
		break;
		case 14:{ /* Lesser Zero */
			return !getBit(m_cpu->sregs.st, LI_CPU_ZF)&&getBit(m_cpu->sregs.st, LI_CPU_NF);
		}
		break;
		case 15:{ /* Operand is Zero */
			return (*m_cpu->args.ro)==0;
		}
		break;
		case 16:{ /* Operand is not Zero */
			return (*m_cpu->args.ro)!=0;
		}
		break;
		case 17:{ /* Operand is Lesser Zero */
			return (Sint32)(*m_cpu->args.ro)<0;
		}
		break;
		case 18:{ /* Operand is Greater Zero */
			return (Sint32)(*m_cpu->args.ro)>0;
		}
		break;
		case 19:{ /* Operand is equal EDX */
			return (*m_cpu->args.ro)==(m_cpu->regs.n.dx);
		}
		break;
		case 20:{ /* Operand is not equal EDX */
			return (*m_cpu->args.ro)!=(m_cpu->regs.n.dx);
		}
		break;
		case 21:{ /* Operand is lesser EDX */
			return (Sint32)(*m_cpu->args.ro)<(Sint32)(m_cpu->regs.n.dx);
		}
		break;
		case 22:{ /* Operand is greater EDX */
			return (Sint32)(*m_cpu->args.ro)>(Sint32)(m_cpu->regs.n.dx);
		}
		break;
		case 23:{ /* Operand is equal EAX */
			return (*m_cpu->args.ro)==(m_cpu->regs.n.ax);
		}
		break;
		case 24:{ /* Operand is not equal EAX */
			return (*m_cpu->args.ro)!=(m_cpu->regs.n.ax);
		}
		break;
		case 25:{ /* Has Overflow */
			return getBit(m_cpu->sregs.st, LI_CPU_VF);
		}
		break;
		case 26:{ /* Carry Set */
			return getBit(m_cpu->sregs.st, LI_CPU_CF);
		}
		break;
		case 27:{ /* Carry Clear */
			return !getBit(m_cpu->sregs.st, LI_CPU_CF);
		}
		break;
		case 28:{ /* Borrow Set */
			return getBit(m_cpu->sregs.st, LI_CPU_BF);
		}
		break;
		case 29:{ /* Borrow Clear */
			return !getBit(m_cpu->sregs.st, LI_CPU_BF);
		}
		break;
		case 30:{ /* Odd Set */
			return getBit(m_cpu->sregs.st, LI_CPU_OF);
		}
		break;
		case 31:{ /* Odd Clear */
			return !getBit(m_cpu->sregs.st, LI_CPU_OF);
		}
		break;
	}
	return TRUE;
}

Bool LICpu_protectionThrown(LCpu *m_cpu){
	if(getBit(m_cpu->sregs.st, LI_CPU_PM)){
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
	
	if(m_cpu->mmu){
		m_cpu->sregs.lpc = m_cpu->io.bus->entry_jmp;
		m_cpu->sregs.epc = m_cpu->io.bus->entry_jmp;
	}
	
	//m_cpu->hs.halt = TRUE;
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
	/* Saves the old registers to stack */
	Uint32 sp = m_cpu->regs.n.sp;
	if(getBit(m_cpu->sregs.st, LI_CPU_VM)){
		/* On Virtual Mode, stack pointer must be reset to avoid address problems */
		m_cpu->sregs.st = m_cpu->sregs.ssiv;
	}
	LICpu_push(m_cpu, sp);
	LICpu_push(m_cpu, m_cpu->sregs.st);
	LICpu_push(m_cpu, m_cpu->sregs.epc);
	
	/* Sets the new flow state */
	m_cpu->sregs.st = clrBit(m_cpu->sregs.st, LI_CPU_PM);
	m_cpu->sregs.st = clrBit(m_cpu->sregs.st, LI_CPU_VM);
	m_cpu->sregs.st = clrBit(m_cpu->sregs.st, LI_CPU_EI);
	
	/* Disable waiting and jump to intented vector */
	m_cpu->hs.wait = FALSE;
	LCpu_jumpAbs(m_cpu, addr);
}

void LICpu_int_return(LCpu *m_cpu){
	/* If is in waiting mode and current interruption is not the desired, put system in wait state */
	if(m_cpu->hs.waits){
		if(m_cpu->hs.waiti!=((Uint8)(m_cpu->sregs.st>>24))){
			m_cpu->hs.wait = TRUE;
		}
		else{
			m_cpu->hs.waits = FALSE;
		}
	}
	
	/* Restores the old flow registers control */
	m_cpu->sregs.epc = LICpu_pop(m_cpu);
	m_cpu->sregs.st = LICpu_pop(m_cpu);
	m_cpu->regs.n.sp = LICpu_pop(m_cpu);
}

Bool LCpu_requestInterruption(LCpu *m_cpu, LIPInterruption intr){ // Returns Bool state => TRUE if the interruption was successfull did
	/* Check if is a external request interruption */
	if(intr.selector>127){
		if(m_cpu->hs.ext_req){
			return FALSE;
		}
		m_cpu->hs.ext_req = TRUE;
		
		if(!getBit(m_cpu->sregs.st, LI_CPU_EI)){
			m_cpu->hs.ext_req = FALSE;
			return FALSE;
		}
		/* Must wait system goes from busy state to deal with request */
		while(m_cpu->hs.busy){}
	}
	Uint32 addr = LICPU_readBus32(m_cpu, (m_cpu->sregs.it + (intr.selector*4)))&(~3);
	LICpu_int_call(m_cpu, addr);
	m_cpu->sregs.st = (m_cpu->sregs.st&0x00FFFFFF)|(intr.selector<<24);
	
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
	/* Sets the access to cpu */
	LCpu *m_cpu = (LCpu*)arg;
	/* Serves to time pass measure */
	Uint32 ltime = 0;
	
	/* Phase counter for cpu execution measure */
	Int phase_i = 0;
	
	/* Will keep processing until device is running */
	m_cpu->peri.running = TRUE;
	while(m_cpu->peri.running){
		/* Do avaliation of halting state */
		Bool halted = m_cpu->hs.halt;
		
		/* Cannot keep executing if is on halt state */
		while(m_cpu->hs.halt){}
		
		/* Phase cycling is reseted */
		phase_i += m_cpu->cy.bpp_set;
		/* Process each phase (if not halt) */
		while((phase_i>0) && (!halted)){
			m_cpu->hs.halt = FALSE;
			/* Between each busy state, handdle any external requested interruption */
			while(m_cpu->hs.ext_req);
			
			/* Puts on busy state */
			m_cpu->hs.busy = TRUE;
			
			/* The busy cycling is reseted */
			m_cpu->cy.cycles += m_cpu->cy.cpb_set;
			/* Process the busy execution (if not halt) */
			while((m_cpu->cy.cycles>0) && (!halted)){
				/* Step the cpu processing */
				LICpu_step(m_cpu);
				/* Updates the halt avaliation */
				halted = m_cpu->hs.halt;
			}
			/* Process the coprocessors */
			for(Int i=0; i<4; i++){
				if(m_cpu->coprocs[i] && m_cpu->coprocs[i]->exec){
					m_cpu->coprocs[i]->exec(m_cpu->coprocs[i]);
				}
			}
			
			/* Leaves the busy state */
			m_cpu->hs.busy = FALSE;
			
			/* Updates the phase */
			phase_i--;
		}
		
		/* Retrives current time and prevent from over execution */
		/* The system runs 64 phases per second, wich means, each */
		/* phase is 1/64 seconds, or 15625 microseconds */
		while((LTime_getMicros()-ltime)<15625);
		ltime = LTime_getMicros(); /* Updates time to match */
		/*Log("MI pulse at microsecond: %d\n", ltime);*/
	}
	
	/* In case of execution process shutdown */
	return 0;
}

void LCpu_execute(LCpu *m_cpu){
	m_cpu->hs.halt = FALSE;
	/* // Legacy Threaded Code
	if(m_cpu->hs.halt){
		m_cpu->hs.halt = FALSE;
		if(m_cpu->peri.t_exec==0){
			m_cpu->peri.t_exec = LThread_create(LICpu_process, m_cpu);
		}
		while(!m_cpu->hs.busy){
			m_cpu->hs.halt = FALSE;
		};
	}
	*/
}

void LCpu_stop(LCpu *m_cpu){
	m_cpu->hs.halt = TRUE;
	/* // Legacy Threaded Code
	if(!m_cpu->hs.halt){
		m_cpu->hs.halt = TRUE;
		if(m_cpu->peri.t_exec!=0){
			while(m_cpu->hs.busy){
				m_cpu->hs.halt = TRUE;
			};
		}
	}
	*/
}

