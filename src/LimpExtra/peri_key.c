#include <LimpExtra/peri_key.h>




int keys[] = {
	
};


void LPKey_init(LPKey *peri, LBus *bus, LPVga *vga){
	memset(peri, 0, sizeof(LPKey));
	LPeri_init(&peri->peri, bus);
	
	/* TODO */
	peri->vga = vga;
}


Uint32 LIPKey_process(void* arg){
	LPKey *peri = arg;
	
	Uint8 vkeys[256] = {0};
	
	while(!LPeri_interrupt(&peri->peri));
	Log("Keyboard did it interruption!\n");
	
	while(peri->active){
		if(LPeri_inUpdtd(&peri->peri)){
			Uint32 ir = LPeri_in(&peri->peri);
			LPeri_out(&peri->peri, 1);
			switch(ir){
				case 0x10:{ // Type
					LPeri_out(&peri->peri, 4);
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
			}
		}
		if(peri->vga->display.has_focus){
			for(Int i=0; i<256; i++){
				SHORT st = GetKeyState(i);
				vkeys[i] = (vkeys[i]&(~1))|st&1;
				if(st&0x8000){
					if(!(vkeys[i]&0x80)){
						vkeys[i] |= 0x80;
						Log("%.3d = 0x%x is DOWN\n", i, st);
						LPeri_out(&peri->peri, (vkeys[i]<<8)|(i));
						while(!LPeri_interrupt(&peri->peri));
						break;
					}
				}
				else{
					if(vkeys[i]&0x80){
						vkeys[i] &= ~0x80;
						Log("%.3d = 0x%x is UP\n", i, st);
						LPeri_out(&peri->peri, (vkeys[i]<<8)|(i));
						while(!LPeri_interrupt(&peri->peri));
						break;
					}
				}
			}
		}
	}
	
	LThread_free(peri->peri.t_exec);
	
	return 0;
}

void LPKey_execute(LPKey *peri){
	peri->active = TRUE;
	if(!peri->peri.t_exec){
		peri->peri.t_exec = LThread_create(&LIPKey_process, peri);
	}
}

