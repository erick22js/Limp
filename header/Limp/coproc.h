#ifndef limp_coprocessor_h
#define limp_coprocessor_h

#include <Limp/defines.h>


struct LCoproc{
	Bool enabled;
	
	void *apidata;
	
	LCpu *m_cpu;
	Int slot;
	
	Uint32 (*readReg)(LCoproc *coproc, Uint32 reg);
	void (*writeReg)(LCoproc *coproc, Uint32 reg, Uint32 data);
	void (*receive)(LCoproc *coproc, Uint32 cmd);
	void (*exec)(LCoproc *coproc);
};


void LCoproc_zeroes(LCoproc *coproc);

void LCoproc_requestInterrupt(LCoproc *coproc);


#endif // limp_coprocessor_h
