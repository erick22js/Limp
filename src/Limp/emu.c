#include <Limp/emu.h>



void LEmu_initEmulable(LEmulable *emu){
	emu->emuStamp = NULL;
	emu->emuStep = NULL;
}


void LEmu_emuStamp(LEmulable**emu_devs, void**emu_objs, Int length){
	for(Int i=0; i<length; i++){
		LEmulable *dev = emu_devs[i];
		if(dev->emuStamp){
			dev->emuStamp(emu_objs[i]);
		}
	}
}

void LEmu_emuStep(LEmulable**emu_devs, void**emu_objs, Int length){
	for(Int i=0; i<length; i++){
		LEmulable *dev = emu_devs[i];
		if(dev->emuStep){
			dev->emuStep(emu_objs[i]);
		}
	}
}
