#include <LimpExtra/peri_stdout.h>



void LPStdout_init(LPStdout *peri, LBus *bus, FILE *file){
	memset(peri, 0, sizeof(LPStdout));
	LPeri_init(&peri->peri, bus);
	peri->file = file;
}


Uint32 LIPStdout_process(void* arg){
	LPStdout *peri = arg;
	
	while(!LPeri_interrupt(&peri->peri));
	//Log("Stdout did it interruption!\n");
	
	while(peri->active){
		if(LPeri_inUpdtd(&peri->peri)){
			Int ir = LPeri_in(&peri->peri);
			LPeri_out(&peri->peri, 1);
			switch(ir){
				case 0x10:{ // Info
					LPeri_out(&peri->peri, 1);
				}
				break;
				
				case 0x21:{ // Sends a stream of u8 chars
					while(!LPeri_inUpdtd(&peri->peri)){};
					Uint32 size = LPeri_in(&peri->peri);
					LPeri_out(&peri->peri, 1);
					
					while(size){
						// Retrieves the input and sends confirm message
						while(!LPeri_inUpdtd(&peri->peri)){};
						Uint32 chr = LPeri_in(&peri->peri);
						LPeri_out(&peri->peri, 1);
						
						// Put character and updates stream
						fputc(chr, peri->file);
						size--;
					}
					fflush(peri->file);
				}
				case 0x24:{ // Sends a pointer to memory and size of writing
					while(!LPeri_inUpdtd(&peri->peri)){};
					Uint32 pointer = LPeri_in(&peri->peri);
					LPeri_out(&peri->peri, 1);
					
					while(!LPeri_inUpdtd(&peri->peri)){};
					Uint32 size = LPeri_in(&peri->peri);
					LPeri_out(&peri->peri, 1);
					
					while(size){
						Uint32 chr = peri->peri.bus->read8(peri->peri.bus, pointer);
						
						// Put character
						fputc(chr, peri->file);
						pointer++;
						size--;
					}
					fflush(peri->file);
					LPeri_out(&peri->peri, 1);
				}
				break;
			}
		}
	}
	
	LThread_free(peri->peri.t_exec);
	
	return 0;
}

void LPStdout_execute(LPStdout *peri){
	peri->active = TRUE;
	if(!peri->peri.t_exec){
		peri->peri.t_exec = LThread_create(&LIPStdout_process, peri);
	}
}

