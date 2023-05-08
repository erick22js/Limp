#include <Limp/peri.h>
#include <Limp/pci.h>



/**
	OBJECT FUNCTIONS
*/

void LPeri_init(LPeri *peri, LBus *bus){
	memset(peri, 0, sizeof(LPeri));
	peri->bus = bus;
}


/**
	WORKING FUNCTIONS
*/

Bool LPeri_plug(LPeri *peri, LPci *m_pci){
	if(!peri->m_pci){
		Uint8 i_port;
		if(LPci_peri_plug(m_pci, peri, &i_port)){
			peri->port = i_port;
			peri->m_pci = m_pci;
			return TRUE;
		}
	}
	return FALSE;
}

Bool LPeri_plugAt(LPeri *peri, LPci *m_pci, Uint8 port){
	if(!peri->m_pci){
		if(LPci_peri_plugAt(m_pci, peri, port)){
			peri->port = port;
			peri->m_pci = m_pci;
			return TRUE;
		}
	}
	return FALSE;
}

Bool LPeri_unplug(LPeri *peri){
	if(peri->m_pci){
		LPci_peri_unplug(peri->m_pci, peri->port);
		peri->m_pci = NULL;
		peri->port = 0;
	}
}


void LPeri_out(LPeri *peri, Uint32 data){
	LPci_peri_write(peri->m_pci, peri->port, data);
}


Bool LPeri_interrupt(LPeri *peri){
	return LPci_peri_interrupt(peri->m_pci, peri->port);
}

