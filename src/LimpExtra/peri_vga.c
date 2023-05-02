#include <LimpExtra/peri_vga.h>
#include "vga_font.h"




void LPVga_init(LPVga *peri, LBus *bus, Int wid, Int hei, Int wwid, Int whei){
	memset(peri, 0, sizeof(LPVga));
	LPeri_init(&peri->peri, bus);
	
	/* Loading window for displaying */
	WinCreateDisplay(&peri->display, wid, hei, wwid, whei);
}


void Vga_renderTerminal(LPVga *peri){
	Int adr = peri->peri.bus->read32(peri->peri.bus, peri->vector_terminal);
	Int width = peri->display.bitmap_width, height = peri->display.bitmap_height;
	Int rows = width/8, lines = height/12;
	Int ci = 0;
	
	for(Int l=0; l<lines; l++){
		for(Int r=0; r<rows; r++){
			Uint32 cdata = peri->peri.bus->read32(peri->peri.bus, adr + ci);
			ci += 4;
			
			Uint8 chr1 = cdata&0xFF;
			Uint8 chr2 = (cdata>>8)&0xFF;
			
			Uint8 cdata_fore = (cdata>>16)&0xFF;
			Uint8 pitch_fore = (((cdata_fore>>6)&0x01)?0x07:0x0)|(((cdata_fore>>6)&0x02)?0x38:0x0);
			Uint32 color_fore = ((cdata_fore&0x03)<<6)|(((cdata_fore>>2)&0x03)<<14)|(((cdata_fore>>4)&0x03)<<22)|
								(pitch_fore)|(pitch_fore<<8)|(pitch_fore<<16);
			Uint8 cdata_back = (cdata>>24)&0xFF;
			Uint8 pitch_back = (((cdata_back>>6)&0x01)?0x07:0x0)|(((cdata_back>>6)&0x02)?0x38:0x0);
			Uint32 color_back = ((cdata_back&0x03)<<6)|(((cdata_back>>2)&0x03)<<14)|(((cdata_back>>4)&0x03)<<22)|
								(pitch_back)|(pitch_back<<8)|(pitch_back<<16);
			
			Int c1_off = (chr1&0xF)*8 + (chr1>>4)*12*VGA_FONT_WIDTH;
			Int c2_off = (chr2&0xF)*8 + (chr2>>4)*12*VGA_FONT_WIDTH;
			Int s_off = r*8 + l*12*width;
			
			for(Int oy=0; oy<12; oy++){
				for(Int ox=0; ox<8; ox++){
					Uint8 px1 = vga_font[c1_off];
					Uint8 px2 = vga_font[c2_off];
					((Uint32*)peri->display.bitmap_data)[s_off] = (px1|px2)?color_fore:color_back;
					c1_off++, c2_off++, s_off++;
				}
				c1_off += VGA_FONT_WIDTH-8;
				c2_off += VGA_FONT_WIDTH-8;
				s_off += width-8;
			}
		}
	}
}

void Vga_renderScreen(LPVga *peri){
	Int adr = peri->peri.bus->read32(peri->peri.bus, peri->vector_pixel);
	Int width = peri->display.bitmap_width, height = peri->display.bitmap_height;
	Int pi = 0;
	for(Int i=0; i<width*height; i++){
		Uint32 pixel = peri->peri.bus->read32(peri->peri.bus, adr + pi);
		pi += 4;
		Uint8 red = (pixel>>0)&0xff;
		Uint8 green = (pixel>>8)&0xff;
		Uint8 blue = (pixel>>16)&0xff;
		((Uint32*)peri->display.bitmap_data)[i] = (red<<16)|(green<<8)|(blue<<0);
	}
}

void Vga_clearScreen(LPVga *peri){
	Int width = peri->display.bitmap_width, height = peri->display.bitmap_height;
	for(Int i=0; i<width*height; i++){
		((Uint32*)peri->display.bitmap_data)[i] = 0x000000;
	}
}


Uint32 LIPVga_process(void* arg){
	LPVga *peri = arg;
	
	while(!LPeri_interrupt(&peri->peri));
	Log("Display did it interruption!\n");
	
	while(peri->active){
		if(LPeri_inUpdtd(&peri->peri)){
			Uint32 ir = LPeri_in(&peri->peri);
			LPeri_out(&peri->peri, 1);
			switch(ir){
				case 0x10:{ // Type
					LPeri_out(&peri->peri, 7);
				}
				break;
				case 0x11:{ // Brand
					LPeri_out(&peri->peri, 0);
				}
				break;
				case 0x12:{ // Branch
					LPeri_out(&peri->peri, 0);
				}
				break;
				case 0x13:{ // Version
					LPeri_out(&peri->peri, 0);
				}
				break;
				
				case 0x20:{ // Enable Rendering
					peri->enable_render = TRUE;
					LPeri_out(&peri->peri, 1);
				}
				break;
				case 0x21:{ // Disable Rendering
					peri->enable_render = FALSE;
					LPeri_out(&peri->peri, 1);
				}
				break;
				case 0x22:{ // Set Pixel mode
					peri->pixel_mode = TRUE;
					LPeri_out(&peri->peri, 1);
				}
				break;
				case 0x23:{ // Set Terminal mode
					peri->pixel_mode = FALSE;
					LPeri_out(&peri->peri, 1);
				}
				break;
				case 0x28:{ // Set vector to terminal characters
					LPeri_out(&peri->peri, 1);
					while(!LPeri_inUpdtd(&peri->peri)){};
					peri->vector_terminal = LPeri_in(&peri->peri);
					LPeri_out(&peri->peri, 1);
				}
				break;
				case 0x29:{ // Set vector to screen pixels
					LPeri_out(&peri->peri, 1);
					while(!LPeri_inUpdtd(&peri->peri)){};
					peri->vector_pixel = LPeri_in(&peri->peri);
					LPeri_out(&peri->peri, 1);
				}
				break;
			}
		}
		
		if(peri->enable_render){
			if(peri->pixel_mode){
				Vga_renderScreen(peri);
			}
			else{
				Vga_renderTerminal(peri);
			}
		}
		else{
			Vga_clearScreen(peri);
		}
		WinRenderizeDisplay(&peri->display);
	}
	
	LThread_free(peri->peri.t_exec);
	
	return 0;
}

void LPVga_execute(LPVga *peri){
	peri->active = TRUE;
	if(!peri->peri.t_exec){
		peri->peri.t_exec = LThread_create(&LIPVga_process, peri);
	}
}

