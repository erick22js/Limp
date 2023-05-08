#ifndef limpextra_peri_key_h
#define limpextra_peri_key_h

#include <Limp/limp.h>
#include <Limp/bus.h>

#include <LimpExtra/peri_vga.h>


typedef struct LPKey{
	LPeri peri;
	Bool active;
	LPVga *vga;
	
	Uint8 vkeys[256];
	Uint8 vi;
}LPKey;


void LPKey_init(LPKey *peri, LBus *bus, LPVga *vga);


#endif // limpextra_peri_key_h
