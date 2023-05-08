#ifndef limp_pci_h
#define limp_pci_h

#include <Limp/defines.h>
#include <Limp/peri.h>


struct LPci{
	/* Peripherical wiring */
	struct{
		LPeri *peripherical;
		Uint32 input;
		Bool output_chg;
		Uint32 output;
	}io_signals[128];
	
	/* Cpu wiring */
	LCpu *m_cpu;
};


/**
	OBJECT FUNCTIONS
*/

void LPci_init(LPci *m_pci, LCpu *m_cpu);


/**
	WORKING FUNCTIONS
	NOTE: Any communication between cpu and periphericals may be solved by the below functions
*/

Bool LPci_cpu_readUpdtd(LPci *m_pci, Uint8 port);
Uint32 LPci_cpu_read(LPci *m_pci, Uint8 port);
void LPci_cpu_write(LPci *m_pci, Uint8 port, Uint32 data);

Bool LPci_peri_plug(LPci *m_pci, LPeri *peri, Uint8 *o_port);
Bool LPci_peri_plugAt(LPci *m_pci, LPeri *peri, Uint8 port);
void LPci_peri_unplug(LPci *m_pci, Uint8 port);

void LPci_peri_write(LPci *m_pci, Uint8 port, Uint32 data);

Bool LPci_peri_interrupt(LPci *m_pci, Uint8 port);



#endif // limp_pci_h
