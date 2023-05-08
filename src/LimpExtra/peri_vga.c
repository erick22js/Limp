#include <LimpExtra/peri_vga.h>
#include "vga_font.h"



void LPVga_emuStamp(void *obj){
	LPVga *peri = obj;
	
	switch(peri->peri.state){
		case 0:{
			if(LPeri_interrupt(&peri->peri)){
				peri->peri.state = 1; // Exits the initial state
			}
		}
		break;
		
		case 1:{
			if(peri->pixel_mode || !peri->enable_render){
				Int adr = peri->peri.bus->read32(peri->peri.bus, peri->vector_control + 4);
				Int width = peri->display.bitmap_width, height = peri->display.bitmap_height;
				for(Int i=0; i<32; i++){
					Uint8 pixel = peri->peri.bus->read8(peri->peri.bus, adr + peri->ctrl_pi + i);
					Uint8 pitchu =  ((pixel&0x80)?0x42:0);
					Uint8 pitchd =  ((pixel&0x40)?0x11:0);
					Uint32 color =  ((pixel&0x20)?0x000088|(pitchd):0)    |((pixel&0x10)?0x000024|(pitchu):0)|
									((pixel&0x08)?0x008800|(pitchd<<8):0) |((pixel&0x04)?0x002400|(pitchu<<8):0)|
									((pixel&0x02)?0x880000|(pitchd<<16):0)|((pixel&0x01)?0x240000|(pitchu<<16):0);
					
					((Uint32*)peri->display.bitmap_data)[peri->ctrl_pi+i] = peri->enable_render?color:0;
				}
				peri->ctrl_pi += 32;
				if(peri->ctrl_pi >= (width*height)){
					peri->ctrl_pi = 0;
					WinRenderizeDisplay(&peri->display);
				}
			}
			else{
				Uint32 adr = peri->peri.bus->read32(peri->peri.bus, peri->vector_control);
				Int width = peri->display.bitmap_width, height = peri->display.bitmap_height;
				
				Uint32 cdata = peri->peri.bus->read32(peri->peri.bus, adr + peri->ctrl_char*4);
				
				Uint8 chr1 = cdata&0xFF;
				Uint8 chr2 = (cdata>>8)&0xFF;
				
				Uint8 cdata_fore = (cdata>>16)&0xFF;
				Uint8 pitchu_fore =  ((cdata_fore&0x80)?0x42:0);
				Uint8 pitchd_fore =  ((cdata_fore&0x40)?0x11:0);
				Uint32 color_fore = ((cdata_fore&0x20)?0x000088|(pitchd_fore):0)    |((cdata_fore&0x10)?0x000024|(pitchu_fore):0)|
									((cdata_fore&0x08)?0x008800|(pitchd_fore<<8):0) |((cdata_fore&0x04)?0x002400|(pitchu_fore<<8):0)|
									((cdata_fore&0x02)?0x880000|(pitchd_fore<<16):0)|((cdata_fore&0x01)?0x240000|(pitchu_fore<<16):0);
				Uint8 cdata_back = (cdata>>24)&0xFF;
				Uint8 pitchu_back =  ((cdata_back&0x80)?0x42:0);
				Uint8 pitchd_back =  ((cdata_back&0x40)?0x11:0);
				Uint32 color_back = ((cdata_back&0x20)?0x000088|(pitchd_back):0)    |((cdata_back&0x10)?0x000024|(pitchu_back):0)|
									((cdata_back&0x08)?0x008800|(pitchd_back<<8):0) |((cdata_back&0x04)?0x002400|(pitchu_back<<8):0)|
									((cdata_back&0x02)?0x880000|(pitchd_back<<16):0)|((cdata_back&0x01)?0x240000|(pitchu_back<<16):0);
				
				Int c1_off = (chr1&0xF)*8 + (chr1>>4)*12*VGA_FONT_WIDTH;
				Int c2_off = (chr2&0xF)*8 + (chr2>>4)*12*VGA_FONT_WIDTH;
				Int s_off = peri->ctrl_r*8 + peri->ctrl_l*12*width;
				
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
				
				peri->ctrl_char++;
				peri->ctrl_r++;
				if(peri->ctrl_r >= 40){
					peri->ctrl_r = 0;
					peri->ctrl_l++;
				}
				if(peri->ctrl_l >= 20){
					peri->ctrl_l = 0;
					peri->ctrl_char = 0;
					WinRenderizeDisplay(&peri->display);
				}
			}
		}
		break;
		
		case 0x20:{ // Enable Rendering
			peri->enable_render = TRUE;
			LPeri_out(&peri->peri, 1);
			peri->peri.state = 0x1;
		}
		break;
		case 0x21:{ // Disable Rendering
			peri->enable_render = FALSE;
			LPeri_out(&peri->peri, 1);
			peri->peri.state = 0x1;
		}
		break;
		case 0x22:{ // Set Pixel mode
			peri->pixel_mode = TRUE;
			LPeri_out(&peri->peri, 1);
			peri->peri.state = 0x1;
		}
		break;
		case 0x23:{ // Set Terminal mode
			peri->pixel_mode = FALSE;
			LPeri_out(&peri->peri, 1);
			peri->peri.state = 0x1;
		}
		break;
		case 0x28:{
			if(peri->peri.acu[1]){
				peri->vector_control = peri->peri.acu[0];
				LPeri_out(&peri->peri, 1);
				peri->peri.state = 0x1;
			}
		}
		break;
	}
}


void LPVga_send(LPeri *peri, Uint32 data){
	switch(peri->state){
		case 1:{ // The Lobby state
			switch(data){
				case 0x10:{ // Info
					LPeri_out(peri, 7);
				}
				break;
				case 0x11:{ // Brand
					LPeri_out(peri, 0);
				}
				break;
				case 0x12:{ // Branch
					LPeri_out(peri, 0);
				}
				break;
				case 0x13:{ // Version
					LPeri_out(peri, 0);
				}
				break;
				
				case 0x20:{ // Enable Rendering
					peri->state = 0x20;
				}
				break;
				case 0x21:{ // Disable Rendering
					peri->state = 0x21;
				}
				break;
				case 0x22:{ // Set Pixel mode
					peri->state = 0x22;
				}
				break;
				case 0x23:{ // Set Terminal mode
					peri->state = 0x23;
				}
				break;
				case 0x28:{ // Set vector to control data in memory
					/*
						[0] = address
						[1] = status
					*/
					peri->acu[1] = 0;
					peri->state = 0x28;
				}
				break;
			}
		}
		break;
		
		case 0x28:{
			if(!peri->acu[1]){
				peri->acu[0] = data;
				peri->acu[1] = 1;
			}
		}
		break;
	}
}


Uint8 LPVga_readByte(LPeri *peri, Uint32 offs){
	LPVga *vga = peri->api_data;
	
	Uint32 mem[4] = {
		320, 240, 40, 20,
	};
	if(offs<sizeof(mem)){
		return ((Uint8*)mem)[offs];
	}
	else{
		return 0;
	}
}

void LPVga_writeByte(LPeri *peri, Uint32 offs, Uint8 data){
	
}


void LPVga_init(LPVga *peri, LBus *bus, Int wwid, Int whei){
	memset(peri, 0, sizeof(LPVga));
	LPeri_init(&peri->peri, bus);
	peri->peri.api_data = peri;
	
	/* Loading window for displaying */
	/* The resolution is fixed at 320x240 pixels or 40x20 characters */
	WinCreateDisplay(&peri->display, 320, 240, wwid, whei);
	
	/* Setup Methods */
	peri->peri.emu.emuStamp = LPVga_emuStamp;
	peri->peri.send = LPVga_send;
	peri->peri.readByte = LPVga_readByte;
	peri->peri.writeByte = LPVga_writeByte;
}

