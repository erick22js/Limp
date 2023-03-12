#ifndef limp_bus_h
#define limp_bus_h

#include <Limp/api.h>


typedef struct LBus{
	
	void* datap;
	
	Uint8 (*read8)(struct LBus *bus, Uint32 addr);
	Uint16 (*read16)(struct LBus *bus, Uint32 addr);
	Uint32 (*read32)(struct LBus *bus, Uint32 addr);
	
	void (*write8)(struct LBus *bus, Uint32 addr, Uint8 data);
	void (*write16)(struct LBus *bus, Uint32 addr, Uint16 data);
	void (*write32)(struct LBus *bus, Uint32 addr, Uint32 data);
	
}LBus;



/**
	TEMPLATE FUNCTIONS
*/


static Uint8 LTBus_read8_(LBus *bus, Uint32 addr){return 0;}
static Uint16 LTBus_read16_(LBus *bus, Uint32 addr){return 0;}
static Uint32 LTBus_read32_(LBus *bus, Uint32 addr){return 0;}

static void LTBus_write8_(LBus *bus, Uint32 addr, Uint8 data){}
static void LTBus_write16_(LBus *bus, Uint32 addr, Uint16 data){}
static void LTBus_write32_(LBus *bus, Uint32 addr, Uint32 data){}



/**
	OBJECT FUNCTIONS
*/


void LBus_init(LBus *m_bus);



/**
	WORKING FUNCTIONS
*/



#endif // limp_bus_h
