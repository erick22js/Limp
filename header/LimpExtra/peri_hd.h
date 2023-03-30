#ifndef limpextra_peri_hd_h
#define limpextra_peri_hd_h

#include <Limp/limp.h>
#include <Limp/bus.h>


typedef struct LPHd{
	LPeri peri;
	FILE* img;
	Uint32 img_size;
	Bool active;
	
	Uint32 seek;
}LPHd;


void LPHd_init(LPHd *peri, LBus *bus, Char* img_path);

void LPHd_execute(LPHd *peri);


#endif // limpextra_peri_hd_h
