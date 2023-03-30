#ifndef limp_coprocessor_h
#define limp_coprocessor_h

#include <Limp/defines.h>


struct LCoproc{
	Bool enabled;
	
	void *apidata;
	
	Uint32 (*readReg)(Uint32 reg);
	void (*writeReg)(Uint32 reg, Uint32 data);
	void (*receive)(Uint32 cmd);
};


#endif // limp_coprocessor_h
