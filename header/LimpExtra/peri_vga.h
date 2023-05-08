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
	Uint32 vector_control;
	/*
	Int vector_terminal;
	Int vector_pixel;
	*/
	
	// Process control registers
	Uint32 ctrl_l;
	Uint32 ctrl_r;
	Uint32 ctrl_char;
	Uint32 ctrl_pi;
}LPVga;


void LPVga_init(LPVga *peri, LBus *bus, Int wwid, Int whei);


#endif // limpextra_peri_vga_h
