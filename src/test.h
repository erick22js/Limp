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

void *(emu_objs[]) = {
	&gcpu,
	&gstdout,
	&ghd,
	&gvga,
	&gkey,
};
LEmulable *(emu_devs[]) = {
	&gcpu.emu,
	&gstdout.peri.emu,
	&ghd.peri.emu,
	&gvga.peri.emu,
	&gkey.peri.emu,
};
Int emu_devs_length = sizeof(emu_devs)/sizeof(LEmulable*);


LThread emu_thread;
Bool emu_stopped;


Uint32 emu_run(void *p){
	while(TRUE){
		while(emu_stopped);
		//LEmu_emuStep(emu_devs, emu_objs, emu_devs_length);
		LEmu_emuStamp(emu_devs, emu_objs, emu_devs_length);
	}
	
	return 0;
}


void setup(){
	// BUS Setup
	LBStd_init(&gbus, &gpci, 0x8000);
	
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
	LPHd_init(&ghd, &gbus, "disk.img");
	LPeri_plugAt(&ghd, &gpci, 0x12);
	LPVga_init(&gvga, &gbus, 640, 480);
	LPeri_plugAt(&gvga, &gpci, 0x20);
	LPKey_init(&gkey, &gbus, &gvga);
	LPeri_plugAt(&gkey, &gpci, 0x18);
}

void init(){
	/* PERIPHERICALs Execution Start */
	
	/* CPU Reseting */
	LCpu_reset(&gcpu);
	emu_stopped = TRUE;
	emu_thread = LThread_create(emu_run, NULL);
}

void close(){
	LThread_destroy(emu_thread);
}

#include "gui.h"


#endif // test_h
