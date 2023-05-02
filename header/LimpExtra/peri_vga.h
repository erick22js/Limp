#ifndef limpextra_peri_vga_h
#define limpextra_peri_vga_h

#include <Limp/limp.h>
#include <Limp/bus.h>

#include <Windows/display.h>


typedef struct LPVga{
	LPeri peri;
	Bool active;
	WinDisplay display;
	
	Bool enable_render;
	Bool pixel_mode;
	Int vector_terminal;
	Int vector_pixel;
}LPVga;


void LPVga_init(LPVga *peri, LBus *bus, Int wid, Int hei, Int wwid, Int whei);

void LPVga_execute(LPVga *peri);


#endif // limpextra_peri_vga_h
