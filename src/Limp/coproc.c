#include <Limp/cpu.h>
#include <Limp/coproc.h>



void LCoproc_zeroes(LCoproc *coproc){
	memset(coproc, 0, sizeof(LCoproc));
}

void LCoproc_requestInterrupt(LCoproc *coproc){
	LIPInterruption request;
	switch(coproc->slot){
		case 0:{
			request = LI_INT_COPROC0;
		}
		break;
		case 1:{
			request = LI_INT_COPROC1;
		}
		break;
		case 2:{
			request = LI_INT_COPROC2;
		}
		break;
		case 3:{
			request = LI_INT_COPROC3;
		}
		break;
		default:{
			return;
		}
	}
	
	LCpu_requestInterruption(coproc->m_cpu, request);
}
