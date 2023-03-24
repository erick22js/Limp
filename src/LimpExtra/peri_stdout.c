#include <LimpExtra/peri_stdout.h>




void LPStdout_init(LPStdout *peri, FILE *file){
	memset(peri, 0, sizeof(LPStdout));
	LPeri_init(peri);
	peri->file = file;
}


Uint32 LIPStdout_process(void* arg){
	LPStdout *peri = arg;
	
	while(peri->active){
		if(LPeri_inUpdtd(&peri->peri)){
			Int chr = LPeri_in(&peri->peri);
			fputc(chr, peri->file);
			LPeri_out(&peri->peri, 1);
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

