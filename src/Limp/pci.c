#include <Limp/pci.h>
#include <Limp/cpu.h>


/**
	OBJECT FUNCTIONS
*/

void LPci_init(LPci *m_pci, LCpu *m_cpu){
	memset(m_pci, 0, sizeof(LPci));
	
	m_pci->m_cpu = m_cpu;
	m_cpu->io.pci = m_pci;
}


/**
	WORKING FUNCTIONS
	NOTE: Any communication between cpu and periphericals may be solved by the below functions
*/

Bool LPci_cpu_readUpdtd(LPci *m_pci, Uint8 port){
	return m_pci->io_signals[port&0x7F].output_chg;
}

Uint32 LPci_cpu_read(LPci *m_pci, Uint8 port){
	m_pci->io_signals[port&0x7F].output_chg = FALSE;
	return m_pci->io_signals[port&0x7F].output;
}

void LPci_cpu_write(LPci *m_pci, Uint8 port, Uint32 data){
	LPeri *peri = m_pci->io_signals[port&0x7F].peripherical;
	m_pci->io_signals[port&0x7F].input = data;
	if(peri && peri->send){
		peri->send(peri, data);
	}
}


Bool LPci_peri_plug(LPci *m_pci, LPeri *peri, Uint8 *o_port){
	for(Int i=1; i<128; i++){
		if(!m_pci->io_signals[i].peripherical){
			m_pci->io_signals[i].peripherical = peri;
			m_pci->io_signals[i].input = 0;
			m_pci->io_signals[i].output = 0;
			*o_port = i;
			return TRUE;
		}
	}
	*o_port = 0;
	return FALSE;
}

Bool LPci_peri_plugAt(LPci *m_pci, LPeri *peri, Uint8 port){
	port &= 0x7F;
	
	if(m_pci->io_signals[port].peripherical){
		return FALSE;
	}
	m_pci->io_signals[port].peripherical = peri;
	m_pci->io_signals[port].input = 0;
	m_pci->io_signals[port].output = 0;
	return TRUE;
}

void LPci_peri_unplug(LPci *m_pci, Uint8 port){
	port &= 0x7F;
	
	m_pci->io_signals[port].peripherical = NULL;
	m_pci->io_signals[port].input = 0;
	m_pci->io_signals[port].output = 0;
}


void LPci_peri_write(LPci *m_pci, Uint8 port, Uint32 data){
	m_pci->io_signals[port&0x7F].output_chg = TRUE;
	m_pci->io_signals[port&0x7F].output = data;
}


Bool LPci_peri_interrupt(LPci *m_pci, Uint8 port){
	volatile static AtomicFlag locked = ATOMIC_FLAG_FALSE;
	if(atomicTestAndSet(&locked)){
		return FALSE;
	}
	
	LIPInterruption intr = {.selector = port|0x80};
	Bool status = LCpu_requestInterruption(m_pci->m_cpu, intr);
	
	atomicTestAndClear(&locked);
	return status;
}
