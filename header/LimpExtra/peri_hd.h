#ifndef limpextra_peri_hd_h
#define limpextra_peri_hd_h

#include <Limp/limp.h>
#include <Limp/bus.h>


typedef struct LPHd{
	LPeri peri;
	FILE* img;
	long img_size;
	Bool active;
	
	long seek;
}LPHd;


void LPHd_init(LPHd *peri, LBus *bus, Char* img_path);


#endif // limpextra_peri_hd_h
