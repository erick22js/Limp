#include <stdio.h>
#include <LimpExtra/bus_std.h>



/**
	BUS MEMORY MAP
	
	0x00000000..0x00003FFF => IO Registers (Mapped 64B for each port)
	0x00004000..0x00007FFF => Low RAM (Reserved for BIOS Processing)
	0x00008000..0x0000FFFF => Entry ROM (Reserved for BIOS Execution)
	0x00010000..0x7FFFFFFF => Fixed RAM (Reserved for OS/Programs Processing)
	0x80000000..0xFFFFFFFF => Dynamic RAM (Reserved for OS/Programs Processing) (Actually, mirromed to Fixed RAM)
*/

/**
	GLOBAL PROPERTIES
*/
#define RAMSIZE (1024*1024*8) // 8MB
Uint8 ram[RAMSIZE];

Uint8 lram[1024*16]; // 16KB

Uint8 rom[1024*32]; // 32KB
Uint32 rom_size = 0;


/**
	BUS ADDRESS ACCESS
*/

inline static Uint8 bus_read(LBus *bus, Uint32 addr){
	if(addr<0x4000){
		Uint32 device = addr>>6;
		Uint32 offset = addr&0x3F;
		
		if(device<128){
			LPeri *peri = bus->pci->io_signals[device].peripherical;
			if(peri && peri->readByte){
				return peri->readByte(peri, offset);
			}
		}
	}
	else if(addr<0x8000){
		addr -= 0x4000;
		return lram[addr];
	}
	else if(addr<0x10000){
		addr -= 0x8000;
		if(addr<rom_size){
			return rom[addr];
		}
	}
	else if(addr<0x80000000){
		addr -= 0x10000;
		if(addr<RAMSIZE){
			return ram[addr];
		}
	}
	else{
		addr -= 0x80000000;
		if(addr<RAMSIZE){
			return ram[addr];
		}
	}
	return 0;
}

inline static void bus_write(LBus *bus, Uint32 addr, Uint8 data){
	if(addr<0x4000){
		Uint32 device = addr>>6;
		Uint32 offset = addr&0x3F;
		
		if(device<128){
			LPeri *peri = bus->pci->io_signals[device].peripherical;
			if(peri && peri->writeByte){
				peri->writeByte(peri, offset, data);
			}
		}
	}
	else if(addr<0x8000){
		addr -= 0x4000;
		lram[addr] = data;
	}
	else if(addr<0x10000){
		addr -= 0x8000;
		if(addr<rom_size){
			rom[addr] = data;
		}
	}
	else if(addr<0x80000000){
		addr -= 0x10000;
		if(addr<RAMSIZE){
			ram[addr] = data;
		}
	}
	else{
		addr -= 0x80000000;
		if(addr<RAMSIZE){
			ram[addr] = data;
		}
	}
}


/**
	READ FROM BUS
*/

Uint8 bus_std_read8_(LBus *bus, Uint32 addr){
	return bus_read(bus, addr);
}

Uint16 bus_std_read16_(LBus *bus, Uint32 addr){
	Uint8 data_[2];
	data_[0] = bus_read(bus, addr++);
	data_[1] = bus_read(bus, addr);
	return *(Uint16*)&data_;
}

Uint32 bus_std_read32_(LBus *bus, Uint32 addr){
	Uint8 data_[4];
	data_[0] = bus_read(bus, addr++);
	data_[1] = bus_read(bus, addr++);
	data_[2] = bus_read(bus, addr++);
	data_[3] = bus_read(bus, addr);
	return *(Uint32*)&data_;
}


/**
	WRITE TO BUS
*/

void bus_std_write8_(LBus *bus, Uint32 addr, Uint8 data){
	bus_write(bus, addr, data);
}

void bus_std_write16_(LBus *bus, Uint32 addr, Uint16 data){
	Uint8* data_ = (Uint8*)&data;
	bus_write(bus, addr++, data_[0]);
	bus_write(bus, addr, data_[1]);
}

void bus_std_write32_(LBus *bus, Uint32 addr, Uint32 data){
	Uint8* data_ = (Uint8*)&data;
	bus_write(bus, addr++, data_[0]);
	bus_write(bus, addr++, data_[1]);
	bus_write(bus, addr++, data_[2]);
	bus_write(bus, addr, data_[3]);
}


/**
	OBJECT SETTINGS
*/

void LBStd_init(LBus *bus, LPci *pci, Uint32 init_vec){
	bus->read8 = bus_std_read8_;
	bus->read16 = bus_std_read16_;
	bus->read32 = bus_std_read32_;
	bus->write8 = bus_std_write8_;
	bus->write16 = bus_std_write16_;
	bus->write32 = bus_std_write32_;
	bus->entry_jmp = init_vec;
	bus->pci = pci;
	
	/* Opening rom file */
	FILE* from = NULL;
	from = fopen("rom.bin", "rb");
	if(from){
		fseek(from, 0, SEEK_END);
		rom_size = ftell(from);
		fseek(from, 0, SEEK_SET);
		fread(rom, 1, rom_size, from);
	}
}



#ifdef _notdefined_

#include <stdio.h>
#include <LimpExtra/bus_std.h>



/**
	BUS MEMORY MAP
	
	0x00000000..0x00003FFF => IO Registers (Mapped 64B for each port)
	0x00004000..0x00007FFF => Low RAM (Reserved for BIOS Processing)
	0x00008000..0x0000FFFF => Entry ROM (Reserved for BIOS Execution)
	0x00010000..0x7FFFFFFF => Fixed RAM (Reserved for OS/Programs Processing)
	0x80000000..0xFFFFFFFF => Dynamic RAM (Reserved for OS/Programs Processing)
*/

/**
	BUS ADDRESS ACCESS
*/
Uint32 laddr = 0;
Uint8 bus_data[4] = {0, 0, 0, 0};
Uint8 rom[1024*32];
Uint32 rom_size = 0;

inline static void* bus_access(LBus *bus, Uint32 addr){
	(*(Uint32*)bus_data) = 0;
	laddr = addr;
	
	if(addr<=0x3FFF){
		Uint32 device = addr>>6;
		Uint32 offset = addr&0x3F;
		
		if(device>=128){
			device -= 128;
			LPeri *peri = bus->pci->io_signals[device].peripherical;
			if(peri->readReg){
				bus_data[0] = peri->readReg(peri, offset++);
				bus_data[1] = peri->readReg(peri, offset++);
				bus_data[2] = peri->readReg(peri, offset++);
				bus_data[3] = peri->readReg(peri, offset);
				return bus_data;
			}
		}
		return NULL;
	}
	else if(addr<=0x7FFF){
		addr -= 0x4000;
		if(addr<BUS_STD_MEMSIZE_){
			return &bus_std_mem_[addr];
		}
		else{
			return NULL;
		}
	}
	else if(addr<=0xFFFF){
		addr -= 0x8000;
		if(addr<rom_size){
			bus_data[0] = rom[addr++];
			bus_data[1] = rom[addr++];
			bus_data[2] = rom[addr++];
			bus_data[3] = rom[addr++];
			return bus_data;
		}
		else{
			return NULL;
		}
	}
	else{
		addr -= 0xC000;
		if(addr<BUS_STD_MEMSIZE_){
			return &bus_std_mem_[addr];
		}
		else{
			return NULL;
		}
	}
}

inline static void bus_flush(LBus *bus){
	if(laddr<=0x3FFF){
		Uint32 device = laddr>>6;
		Uint32 offset = laddr&0x3F;
		
		if(device>=128){
			device -= 128;
			LPeri *peri = bus->pci->io_signals[device].peripherical;
			if(peri->writeReg){
				//bus_data[0] = peri->readReg(peri, offset++);
				//bus_data[1] = peri->readReg(peri, offset++);
				//bus_data[2] = peri->readReg(peri, offset++);
				//bus_data[3] = peri->readReg(peri, offset);
				//peri->writeReg(peri, )
			}
		}
	}
}


/**
	READ FROM BUS
*/

Uint8 bus_std_read8_(LBus *bus, Uint32 addr){
	Uint8 *access = (Uint8*)bus_access(bus, addr);
	if(access){
		return *access;
	}
	return 0;
}

Uint16 bus_std_read16_(LBus *bus, Uint32 addr){
	Uint8* access = (Uint8*)bus_access(bus, addr);
	if(access){
		Uint8 data_[2];
		data_[0] = access[0];
		data_[1] = access[1];
		return *(Uint16*)&data_;
	}
	return 0;
}

Uint32 bus_std_read32_(LBus *bus, Uint32 addr){
	Uint8* access = (Uint8*)bus_access(bus, addr);
	if(access){
		Uint8 data_[4];
		data_[0] = access[0];
		data_[1] = access[1];
		data_[2] = access[2];
		data_[3] = access[3];
		return *(Uint32*)&data_;
	}
	return 0;
}


/**
	WRITE TO BUS
*/

void bus_std_write8_(LBus *bus, Uint32 addr, Uint8 data){
	Uint8 *access = (Uint8*)bus_access(bus, addr);
	if(access){
		*access = data;
	}
	bus_flush(bus);
}

void bus_std_write16_(LBus *bus, Uint32 addr, Uint16 data){
	Uint8* access = (Uint8*)bus_access(bus, addr);
	if(access){
		Uint8* data_ = (Uint8*)&data;
		access[0] = data_[0];
		access[1] = data_[1];
	}
	bus_flush(bus);
}

void bus_std_write32_(LBus *bus, Uint32 addr, Uint32 data){
	Uint8* access = (Uint8*)bus_access(bus, addr);
	if(access){
		Uint8* data_ = (Uint8*)&data;
		access[0] = data_[0];
		access[1] = data_[1];
		access[2] = data_[2];
		access[3] = data_[3];
	}
	bus_flush(bus);
}


/**
	OBJECT SETTINGS
*/

void LBStd_init(LBus *bus, LPci *pci, Uint32 init_vec){
	bus->read8 = bus_std_read8_;
	bus->read16 = bus_std_read16_;
	bus->read32 = bus_std_read32_;
	bus->write8 = bus_std_write8_;
	bus->write16 = bus_std_write16_;
	bus->write32 = bus_std_write32_;
	bus->entry_jmp = init_vec;
	bus->pci = pci;
	
	/* Opening rom file */
	FILE* from = NULL;
	from = fopen("rom.bin", "rb");
	if(from){
		fseek(from, 0, SEEK_END);
		rom_size = ftell(from);
		fseek(from, 0, SEEK_SET);
		fread(rom, 1, rom_size, from);
	}
}

#endif
