#include <LimpExtra/peri_hd.h>



void LPHd_init(LPHd *peri, LBus *bus, Char* img_path){
	memset(peri, 0, sizeof(LPHd));
	LPeri_init(&peri->peri, bus);
	
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
}


Uint32 LIPHd_process(void* arg){
	LPHd *peri = arg;
	
	while(!LPeri_interrupt(&peri->peri));
	//Log("Hard Disk did it interruption!\n");
	
	while(peri->active){
		if(LPeri_inUpdtd(&peri->peri)){
			Uint32 ir = LPeri_in(&peri->peri);
			LPeri_out(&peri->peri, 1);
			switch(ir){
				case 0x10:{ // Info
					LPeri_out(&peri->peri, 2);
				}
				break;
				
				case 0x14:{ // Seek set the disk
					while(!LPeri_inUpdtd(&peri->peri)){};
					Uint32 offset = LPeri_in(&peri->peri);
					peri->seek = offset%peri->img_size;
					fseek(peri->img, peri->seek, SEEK_SET);
					LPeri_out(&peri->peri, 1);
				}
				break;
				case 0x15:{ // Seek current the disk
					while(!LPeri_inUpdtd(&peri->peri)){};
					Uint32 offset = LPeri_in(&peri->peri);
					peri->seek += offset;
					peri->seek %= peri->img_size;
					fseek(peri->img, peri->seek, SEEK_SET);
					LPeri_out(&peri->peri, 1);
				}
				break;
				case 0x18:{ // Sends a stream of u8 chars
					while(!LPeri_inUpdtd(&peri->peri)){};
					Uint32 size = LPeri_in(&peri->peri);
					LPeri_out(&peri->peri, 1);
					
					while(size){
						// Retrieves the input and sends confirm message
						while(!LPeri_inUpdtd(&peri->peri)){};
						Uint32 chr = LPeri_in(&peri->peri);
						LPeri_out(&peri->peri, 1);
						
						// Put character and updates stream
						fputc(chr, peri->img);
						peri->seek = (peri->seek+1)%peri->img_size;
						fseek(peri->img, peri->seek, SEEK_SET);
						fflush(peri->img);
						size--;
					}
				}
				break;
				case 0x19:{ // Reads a stream of u8 chars
					while(!LPeri_inUpdtd(&peri->peri)){};
					Uint32 size = LPeri_in(&peri->peri);
					LPeri_out(&peri->peri, 1);
					
					while(size){
						// Confirms the send message
						while(!LPeri_inUpdtd(&peri->peri)){};
						LPeri_in(&peri->peri);
						
						// Retrieves the character from stream and outputs
						Uint32 chr = fgetc(peri->img);
						LPeri_out(&peri->peri, chr);
						peri->seek = (peri->seek+1)%peri->img_size;
						fseek(peri->img, peri->seek, SEEK_SET);
						size--;
					}
				}
				break;
				case 0x1C:{ // Sends a pointer to memory and size of writing
					while(!LPeri_inUpdtd(&peri->peri)){};
					Uint32 pointer = LPeri_in(&peri->peri);
					LPeri_out(&peri->peri, 1);
					
					while(!LPeri_inUpdtd(&peri->peri)){};
					Uint32 size = LPeri_in(&peri->peri);
					LPeri_out(&peri->peri, 1);
					
					while(size){
						Uint32 chr = peri->peri.bus->read8(peri->peri.bus, pointer);
						
						// Put character and updates stream
						fputc(chr, peri->img);
						peri->seek = (peri->seek+1)%peri->img_size;
						fseek(peri->img, peri->seek, SEEK_SET);
						pointer++;
						size--;
					}
					fflush(peri->img);
					LPeri_out(&peri->peri, 1);
				}
				break;
				case 0x1D:{ // Sends a pointer to memory and size of reading
					while(!LPeri_inUpdtd(&peri->peri)){};
					Uint32 pointer = LPeri_in(&peri->peri);
					LPeri_out(&peri->peri, 1);
					
					while(!LPeri_inUpdtd(&peri->peri)){};
					Uint32 size = LPeri_in(&peri->peri);
					LPeri_out(&peri->peri, 1);
					
					while(size){
						// Put character and updates stream
						Uint32 chr = fgetc(peri->img);
						peri->seek = (peri->seek+1)%peri->img_size;
						fseek(peri->img, peri->seek, SEEK_SET);
						
						peri->peri.bus->write8(peri->peri.bus, pointer, chr);
						
						pointer++;
						size--;
					}
					fflush(peri->img);
					LPeri_out(&peri->peri, 1);
				}
				break;
			}
		}
	}
	
	LThread_free(peri->peri.t_exec);
	
	return 0;
}

void LPHd_execute(LPHd *peri){
	peri->active = TRUE;
	if(!peri->peri.t_exec){
		peri->peri.t_exec = LThread_create(&LIPHd_process, peri);
	}
}

