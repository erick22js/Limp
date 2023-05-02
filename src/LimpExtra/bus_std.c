#include <LimpExtra/bus_std.h>



Uint8 bus_std_read8_(LBus *bus, Uint32 addr){
	if(addr>=BUS_STD_MEMSIZE_){
		return 0;
	}
	return bus_std_mem_[addr];
}

Uint16 bus_std_read16_(LBus *bus, Uint32 addr){
	if(addr>=BUS_STD_MEMSIZE_){
		return 0;
	}
	Uint8 data_[2];
	data_[0] = bus_std_mem_[addr++];
	data_[1] = bus_std_mem_[addr];
	return *(Uint16*)&data_;
}

Uint32 bus_std_read32_(LBus *bus, Uint32 addr){
	if(addr>=BUS_STD_MEMSIZE_){
		return 0;
	}
	Uint8 data_[4];
	data_[0] = bus_std_mem_[addr++];
	data_[1] = bus_std_mem_[addr++];
	data_[2] = bus_std_mem_[addr++];
	data_[3] = bus_std_mem_[addr];
	return *(Uint32*)&data_;
}


void bus_std_write8_(LBus *bus, Uint32 addr, Uint8 data){
	if(addr>=BUS_STD_MEMSIZE_){
		return;
	}
	bus_std_mem_[addr] = data;
}

void bus_std_write16_(LBus *bus, Uint32 addr, Uint16 data){
	if(addr>=BUS_STD_MEMSIZE_){
		return;
	}
	Uint8* data_ = (Uint8*)&data;
	bus_std_mem_[addr++] = data_[0];
	bus_std_mem_[addr] = data_[1];
}

void bus_std_write32_(LBus *bus, Uint32 addr, Uint32 data){
	if(addr>=BUS_STD_MEMSIZE_){
		return;
	}
	Uint8* data_ = (Uint8*)&data;
	bus_std_mem_[addr++] = data_[0];
	bus_std_mem_[addr++] = data_[1];
	bus_std_mem_[addr++] = data_[2];
	bus_std_mem_[addr] = data_[3];
}


void LBStd_init(LBus *bus, Uint32 init_vec){
	bus->read8 = bus_std_read8_;
	bus->read16 = bus_std_read16_;
	bus->read32 = bus_std_read32_;
	bus->write8 = bus_std_write8_;
	bus->write16 = bus_std_write16_;
	bus->write32 = bus_std_write32_;
	bus->start_jmp = init_vec;
}

