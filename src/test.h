#ifndef test_h
#define test_h

#include <Limp/limp.h>

#include <LimpExtra/extra.h>

LBus gbus;
LPci gpci;
LCpu gcpu;

LPStdout gstdout;
LPHd ghd;



void setup(){
	/* BUS Setup */
	LBStd_init(&gbus);
	
	/* CPU Setup */
	LCpu_init(&gcpu, &gbus);
	gcpu.freq_set = 1024*1024*1; /* Setting the frequency of Cpu */
	
	/* PCI Setup */
	LPci_init(&gpci, &gcpu);
	
	/* PERIPHERICALs Setup */
	LPStdout_init(&gstdout, &gbus, stdout);
	LPeri_plugAt(&gstdout, &gpci, 0x10);
	LPHd_init(&ghd, &gbus, "data/disk.img");
	LPeri_plugAt(&ghd, &gpci, 0x12);
}

void init(){
	/* PERIPHERICALs Execution Start */
	LPStdout_execute(&gstdout);
	LPHd_execute(&ghd);
	
	/* CPU Reseting */
	LCpu_reset(&gcpu);
	
}

void close(){
	
}

#include "gui.h"


#endif // test_h
