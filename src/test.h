#ifndef test_h
#define test_h

#include <Limp/limp.h>

#include <LimpExtra/extra.h>

LBus gbus;
LPci gpci;
LCpu gcpu;
LMmu gmmu;

LPStdout gstdout;
LPHd ghd;
LPVga gvga;
LPKey gkey;



void setup(){
	// BUS Setup
	LBStd_init(&gbus, 0x0);
	
	// CPU Setup
	LCpu_init(&gcpu, &gbus);
	//gcpu.freq_set = 1024*1024*1; // Setting the frequency of Cpu
	
	// MMU Setup
	LEMmu_init(&gmmu);
	LCpu_conMmu(&gcpu, &gmmu);
	
	// PCI Setup
	LPci_init(&gpci, &gcpu);
	
	// PERIPHERICALs Setup
	LPStdout_init(&gstdout, &gbus, stdout);
	LPeri_plugAt(&gstdout, &gpci, 0x10);
	LPHd_init(&ghd, &gbus, "data/disk.img");
	LPeri_plugAt(&ghd, &gpci, 0x12);
	LPVga_init(&gvga, &gbus, 320, 240, 640, 480);
	LPeri_plugAt(&gvga, &gpci, 0x20);
	LPKey_init(&gkey, &gbus, &gvga);
	LPeri_plugAt(&gkey, &gpci, 0x18);
}

void init(){
	/* PERIPHERICALs Execution Start */
	LPStdout_execute(&gstdout);
	LPHd_execute(&ghd);
	LPVga_execute(&gvga);
	LPKey_execute(&gkey);
	
	/* CPU Reseting */
	LCpu_reset(&gcpu);
}

void close(){
	
}

#include "gui.h"


#endif // test_h
