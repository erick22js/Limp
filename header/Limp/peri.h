#ifndef limp_peripherical_h
#define limp_peripherical_h

#include <Limp/defines.h>
#include <Limp/time.h>
#include <Limp/thread.h>


struct LPeri{
	LPci *m_pci;
	Uint8 port;
	
	LThread t_exec;
	Bool running;
	
	LBus *bus;
	
	void *api_data;
};


/**
	OBJECT FUNCTIONS
*/

void LPeri_init(LPeri *peri, LBus *bus);


/**
	WORKING FUNCTIONS
*/

Bool LPeri_plug(LPeri *peri, LPci *m_pci);
Bool LPeri_plugAt(LPeri *peri, LPci *m_pci, Uint8 port);
Bool LPeri_unplug(LPeri *peri);

Bool LPeri_inUpdtd(LPeri *peri);
Uint32 LPeri_in(LPeri *peri);
void LPeri_out(LPeri *peri, Uint32 data);

Bool LPeri_interrupt(LPeri *peri);


#endif // limp_peripherical_h
