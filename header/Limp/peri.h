#ifndef limp_peripherical_h
#define limp_peripherical_h

#include <Limp/defines.h>
#include <Limp/time.h>
#include <Limp/thread.h>


struct LPeri{
	LEmulable emu;
	LPci *m_pci;
	Uint8 port;
	
	void (*send)(LPeri *peri, Uint32 data);
	
	void (*writeByte)(LPeri *peri, Uint32 offs, Uint8 data);
	Uint8 (*readByte)(LPeri *peri, Uint32 offs);
	
	LThread t_exec;
	Bool running;
	
	LBus *bus;
	
	Uint32 state; /* 0 = Initial State; any = Hardware Implementation */
	Uint32 acu[4]; /* Accumulator data */
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

void LPeri_out(LPeri *peri, Uint32 data);

Bool LPeri_interrupt(LPeri *peri);


#endif // limp_peripherical_h
