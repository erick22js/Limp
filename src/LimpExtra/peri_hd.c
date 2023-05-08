#include <LimpExtra/peri_hd.h>



void LPHd_emuStamp(void *obj){
	LPHd *peri = obj;
	
	switch(peri->peri.state){
		case 0:{
			if(LPeri_interrupt(&peri->peri)){
				peri->peri.state = 1; // Exits the initial state
			}
		}
		break;
		
		case 0x14:{
			if(peri->peri.acu[1]){
				long seek = peri->peri.acu[0];
				seek *= 1024;
				peri->seek = seek%peri->img_size;
				fseek(peri->img, peri->seek, SEEK_SET);
				LPeri_out(&peri->peri, 1);
				peri->peri.state = 1;
			}
		}
		break;
		case 0x15:{
			if(peri->peri.acu[1]){
				long seek = peri->peri.acu[0];
				seek *= 1024;
				peri->seek += seek;
				peri->seek %= peri->img_size;
				fseek(peri->img, peri->seek, SEEK_CUR);
				LPeri_out(&peri->peri, 1);
				peri->peri.state = 1;
			}
		}
		break;
		
		case 0x1A:{
			long pointer = peri->peri.acu[0];
			pointer = pointer*1024 + 1024-peri->peri.acu[2];
			for(Int i=0; i<128&&peri->peri.acu[1]&&peri->peri.acu[2]; i++){
				Uint8 data = peri->peri.bus->read8(peri->peri.bus, pointer);
				if(peri->seek>=peri->img_size){
					peri->seek %= peri->img_size;
					fseek(peri->img, peri->seek, SEEK_SET);
				}
				fputc(data, peri->img);
				pointer++;
				peri->seek++;
				peri->peri.acu[2]--;
			}
			if(!peri->peri.acu[2]){
				peri->peri.acu[2] = 1024;
				peri->peri.acu[1]--;
				peri->peri.acu[0]++;
			}
			if(!peri->peri.acu[1]){
				LPeri_out(&peri->peri, 1);
				peri->peri.state = 1;
			}
		}
		break;
		
		case 0x1E:{
			long pointer = peri->peri.acu[0];
			pointer = pointer*1024 + 1024-peri->peri.acu[2];
			for(Int i=0; i<128&&peri->peri.acu[1]&&peri->peri.acu[2]; i++){
				Uint8 data = fgetc(peri->img);
				if(peri->seek>=peri->img_size){
					peri->seek %= peri->img_size;
					fseek(peri->img, peri->seek, SEEK_SET);
				}
				peri->peri.bus->write8(peri->peri.bus, pointer, data);
				pointer++;
				peri->seek++;
				peri->peri.acu[2]--;
			}
			if(!peri->peri.acu[2]){
				peri->peri.acu[2] = 1024;
				peri->peri.acu[1]--;
				peri->peri.acu[0]++;
			}
			if(!peri->peri.acu[1]){
				LPeri_out(&peri->peri, 1);
				peri->peri.state = 1;
			}
		}
		break;
	}
}


void LPHd_send(LPeri *peri, Uint32 data){
	switch(peri->state){
		case 1:{ // The Lobby state
			switch(data){
				case 0x10:{ // Info
					LPeri_out(peri, 2);
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
				
				case 0x14:{ // Seek set the disk
					/*
						[0] = offset
						[1] = status
					*/
					peri->acu[1] = 0;
					peri->state = 0x14;
				}
				break;
				case 0x15:{ // Seek current the disk
					/*
						[0] = offset
						[1] = status
					*/
					peri->acu[1] = 0;
					peri->state = 0x15;
				}
				break;
				case 0x18:{ // Sends a pointer to memory and size of writing
					/*
						[0] = pointer (in 1KB)
						[1] = size (in 1KB)
						[2] = move offset
					*/
					peri->state = 0x18;
				}
				break;
				case 0x1C:{ // Sends a pointer to memory and size of reading
					/*
						[0] = pointer (in 1KB)
						[1] = size (in 1KB)
						[2] = move offset
					*/
					peri->state = 0x1C;
				}
				break;
			}
		}
		break;
		
		case 0x14:{ // Seek set the disk
			if(!peri->acu[1]){
				peri->acu[0] = data;
				peri->acu[1] = 1;
			}
		}
		break;
		case 0x15:{ // Seek current the disk
			if(!peri->acu[1]){
				peri->acu[0] = data;
				peri->acu[1] = 1;
			}
		}
		break;
		
		case 0x18:{
			peri->acu[0] = data;
			peri->state = 0x19;
		}
		break;
		case 0x19:{
			peri->acu[1] = data;
			peri->acu[2] = 1024;
			peri->state = 0x1A;
		}
		break;
		
		case 0x1C:{
			peri->acu[0] = data;
			peri->state = 0x1D;
		}
		break;
		case 0x1D:{
			peri->acu[1] = data;
			peri->acu[2] = 1024;
			peri->state = 0x1E;
		}
		break;
	}
}


Uint8 LPHd_readByte(LPeri *peri, Uint32 offs){
	LPHd *hd = peri->api_data;
	
	Uint32 mem[4] = {
		hd->img_size>>10
	};
	if(offs<sizeof(mem)){
		return ((Uint8*)mem)[offs];
	}
	else{
		return 0;
	}
}

void LPHd_writeByte(LPeri *peri, Uint32 offs, Uint8 data){
	
}

void LPHd_init(LPHd *peri, LBus *bus, Char* img_path){
	memset(peri, 0, sizeof(LPHd));
	LPeri_init(&peri->peri, bus);
	peri->peri.api_data = peri;
	
	/* Loading the Storage Image */
	Open: {
		FILE* img = fopen(img_path, "r+b");
		if(img){
			peri->img = img;
			fseek(img, 0, SEEK_END);
			peri->img_size = ftell(img);
			fseek(img, 0, SEEK_SET);
		}
		else{
			img = fopen(img_path, "wb");
			/* Generates a new Storager with 16MB */
			fseek(img, 1024*1024*16 - 1, SEEK_SET);
			fputc(0, img);
			fclose(img);
			goto Open;
		}
	}
	
	/* Setup Methods */
	peri->peri.emu.emuStamp = LPHd_emuStamp;
	peri->peri.send = LPHd_send;
	peri->peri.readByte = LPHd_readByte;
	peri->peri.writeByte = LPHd_writeByte;
}

