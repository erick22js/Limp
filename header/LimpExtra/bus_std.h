#ifndef limpextra_bus_std_h
#define limpextra_bus_std_h

#include <Limp/limp.h>


#define BUS_STD_MEMSIZE_ (1024*1024*8)
Uint8 bus_std_mem_[BUS_STD_MEMSIZE_];

Uint8 bus_std_read8_(LBus *bus, Uint32 addr);
Uint16 bus_std_read16_(LBus *bus, Uint32 addr);
Uint32 bus_std_read32_(LBus *bus, Uint32 addr);

void bus_std_write8_(LBus *bus, Uint32 addr, Uint8 data);
void bus_std_write16_(LBus *bus, Uint32 addr, Uint16 data);
void bus_std_write32_(LBus *bus, Uint32 addr, Uint32 data);

void LBStd_init(LBus *bus, Uint32 init_vec);


#endif // limpextra_bus_std_h
