#ifndef limp_pci_h
#define limp_pci_h

#include <Limp/defines.h>
#include <Limp/peri.h>


struct LPci{
	/* TODO */
};


/**
	WORKING FUNCTIONS
*/

Uint32 LPci_read(LPci *m_pci, Uint8 port);
void LPci_write(LPci *m_pci, Uint8 port, Uint32 data);


#endif // limp_pci_h
