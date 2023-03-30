#include <Limp/bus.h>



/**
	OBJECT FUNCTIONS
*/


void LBus_init(LBus *m_bus){
	memset(m_bus, 0, sizeof(LBus));
	
	m_bus->read8 = LTBus_read8_;
	m_bus->read16 = LTBus_read16_;
	m_bus->read32 = LTBus_read32_;
	
	m_bus->write8 = LTBus_write8_;
	m_bus->write16 = LTBus_write16_;
	m_bus->write32 = LTBus_write32_;
}



/**
	WORKING FUNCTIONS
*/


