#ifndef test_h
#define test_h

#include <Limp/limp.h>

LBus gbus;
LCpu gcpu;

#define GMEM_SIZE (1024*1024*8)
Uint8 gmem[GMEM_SIZE];


Uint8 m_read8_(LBus *bus, Uint32 addr){
	if(addr>=GMEM_SIZE){
		return 0;
	}
	return gmem[addr];
}
Uint16 m_read16_(LBus *bus, Uint32 addr){
	if(addr>=GMEM_SIZE){
		return 0;
	}
	Uint8 data_[2];
	data_[0] = gmem[addr++];
	data_[1] = gmem[addr];
	return *(Uint16*)&data_;
}
Uint32 m_read32_(LBus *bus, Uint32 addr){
	if(addr>=GMEM_SIZE){
		return 0;
	}
	Uint8 data_[4];
	data_[0] = gmem[addr++];
	data_[1] = gmem[addr++];
	data_[2] = gmem[addr++];
	data_[3] = gmem[addr];
	return *(Uint32*)&data_;
}

void m_write8_(LBus *bus, Uint32 addr, Uint8 data){
	if(addr>=GMEM_SIZE){
		return;
	}
	gmem[addr] = data;
}
void m_write16_(LBus *bus, Uint32 addr, Uint16 data){
	if(addr>=GMEM_SIZE){
		return;
	}
	Uint8* data_ = (Uint8*)&data;
	gmem[addr++] = data_[0];
	gmem[addr] = data_[1];
}
void m_write32_(LBus *bus, Uint32 addr, Uint32 data){
	if(addr>=GMEM_SIZE){
		return;
	}
	Uint8* data_ = (Uint8*)&data;
	gmem[addr++] = data_[0];
	gmem[addr++] = data_[1];
	gmem[addr++] = data_[2];
	gmem[addr] = data_[3];
}


void setup(){
	LBus_init(&gbus);
	
	gbus.read8 = m_read8_;
	gbus.read16 = m_read16_;
	gbus.read32 = m_read32_;
	
	gbus.write8 = m_write8_;
	gbus.write16 = m_write16_;
	gbus.write32 = m_write32_;
	
	LCpu_init(&gcpu, &gbus);
	
}

void init(){
	LCpu_log(&gcpu);
	
	/*
	LCpu_writeMem32(&gcpu, 0x0000, 0x45129045);
	
	LCpu_fetch(&gcpu);
	
	Uint32 data = LIAlu_ldiv(&gcpu, 3, 4);
	
	Uint64 dl = data;
	dl = dl*1000000000/(Uint64)4294967296;
	Uint32 dw = dl;
	
	printf(".%.9u\n", dw);
	
	LCpu_log(&gcpu);
	*/
	
	LCpu_writeMem32(&gcpu, 0x0000, 0x45129045);
	
	for(Int i=0; i<4; i++){
		LCpu_step(&gcpu);
		LCpu_log(&gcpu);
	}
	
}

#include "gui.h"


#endif // test_h
