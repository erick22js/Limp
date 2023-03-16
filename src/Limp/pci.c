#include <Limp/pci.h>
#include <Limp/cpu.h>


/**
	OBJECT FUNCTIONS
*/

void LPci_init(LPci *m_pci, LCpu *m_cpu){
	memset(m_pci, 0, sizeof(LPci));
	
	m_pci->m_cpu = m_cpu;
}


/**
	WORKING FUNCTIONS
	NOTE: Any communication between cpu and periphericals may be solved by the below functions
*/

Uint32 LPci_cpu_read(LPci *m_pci, Uint8 port){
	return m_pci->io_signals[port&0x7F].output;
}

void LPci_cpu_write(LPci *m_pci, Uint8 port, Uint32 data){
	m_pci->io_signals[port&0x7F].input = data;
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

void LPci_peri_unplug(LPci *m_pci, Uint8 port){
	port &= 0x7F;
	
	m_pci->io_signals[port].peripherical = NULL;
	m_pci->io_signals[port].input = 0;
	m_pci->io_signals[port].output = 0;
}


Uint32 LPci_peri_read(LPci *m_pci, Uint8 port){
	return m_pci->io_signals[port&0x7F].input;
}

void LPci_peri_write(LPci *m_pci, Uint8 port, Uint32 data){
	m_pci->io_signals[port&0x7F].output = data;
}


Bool LPci_peri_interrupt(LPci *m_pci, Uint8 port){
	static Bool locked = FALSE;
	if(locked){
		return FALSE;
	}
	locked = TRUE;
	
	LIPInterruption intr = {.selector = port|0x80};
	Bool status = LCpu_requestInterruption(m_pci->m_cpu, intr);
	
	locked = FALSE;
	return status;
}
