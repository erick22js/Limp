#ifndef limpextra_peri_key_h
#define limpextra_peri_key_h

#include <Limp/limp.h>
#include <Limp/bus.h>

#include <LimpExtra/peri_vga.h>


typedef struct LPKey{
	LPeri peri;
	Bool active;
	LPVga *vga;
}LPKey;


void LPKey_init(LPKey *peri, LBus *bus, LPVga *vga);

void LPKey_execute(LPKey *peri);


#endif // limpextra_peri_key_h
