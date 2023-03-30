#ifndef limp_mmu_h
#define limp_mmu_h

#include <Limp/defines.h>
#include <Limp/coproc.h>


struct LMmu{
	LCoproc coproc;
	
	/* Returns: 0 if no any error, otherwise, any other value on error */
	Int (*tAddr)(Uint32 *addr, Uint32 lcpu_st);
};


#endif // limp_mmu_h
