#ifndef limp_emu_h
#define limp_emu_h

#include <Limp/defines.h>


void LEmu_initEmulable(LEmulable *emu);

void LEmu_emuStamp(LEmulable**emu_devs, void**emu_objs, Int length);
void LEmu_emuStep(LEmulable**emu_devs, void**emu_objs, Int length);


#endif // limp_emu_h
