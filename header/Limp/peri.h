#ifndef limp_peripherical_h
#define limp_peripherical_h

#include <Limp/defines.h>


struct LPeri{
	LPci *m_pci;
	Uint8 port;
	
	void *api_data;
};


/**
	OBJECT FUNCTIONS
*/

void LPeri_init(LPeri *peri);


/**
	WORKING FUNCTIONS
*/

Bool LPeri_plug(LPeri *peri, LPci *m_pci);
Bool LPeri_unplug(LPeri *peri);

Uint32 LPeri_in(LPeri *peri);
void LPeri_out(LPeri *peri, Uint32 data);

void LPeri_interrupt(LPeri *peri);


#endif // limp_peripherical_h