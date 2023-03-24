#ifndef test_h
#define test_h

#include <Limp/limp.h>

#include <LimpExtra/extra.h>

LBus gbus;
LPci gpci;
LCpu gcpu;

LPStdout gstdout;


void setup(){
	/* BUS Setup */
	LBStd_init(&gbus);
	
	/* CPU Setup */
	LCpu_init(&gcpu, &gbus);
	gcpu.freq_set = 1024*1024*1; /* Setting the frequency of Cpu */
	
	/* PCI Setup */
	LPci_init(&gpci, &gcpu);
	
	/* PERIPHERICALs Setup */
	LPStdout_init(&gstdout, stdout);
	LPeri_plugAt(&gstdout, &gpci, 0x10);
}

void init(){
	/* PERIPHERICALs Execution Start */
	LPStdout_execute(&gstdout);
	
	/* CPU Reseting */
	LCpu_reset(&gcpu);
}

void close(){
	
}

#include "gui.h"


#endif // test_h
