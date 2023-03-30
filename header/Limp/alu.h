#ifndef limp_alu_h
#define limp_alu_h

#include <Limp/defines.h>



/**
	ARITHMETIC FUNCTIONS
*/


Inline Uint32 LIAlu_add(LCpu *m_cpu, Uint32 v1, Uint32 v2, Bool wcarry);
Inline Uint32 LIAlu_sub(LCpu *m_cpu, Uint32 v1, Uint32 v2, Bool wborrow);
Inline Uint32 LIAlu_mul(LCpu *m_cpu, Uint32 v1, Uint32 v2);
Inline Uint32 LIAlu_hmul(LCpu *m_cpu, Uint32 v1, Uint32 v2);
Inline Uint32 LIAlu_div(LCpu *m_cpu, Uint32 v1, Uint32 v2);
Inline Uint32 LIAlu_mod(LCpu *m_cpu, Uint32 v1, Uint32 v2);
Inline Uint32 LIAlu_ldiv(LCpu *m_cpu, Uint32 v1, Uint32 v2);

Inline Uint32 LIAlu_and(LCpu *m_cpu, Uint32 v1, Uint32 v2);
Inline Uint32 LIAlu_nand(LCpu *m_cpu, Uint32 v1, Uint32 v2);
Inline Uint32 LIAlu_or(LCpu *m_cpu, Uint32 v1, Uint32 v2);
Inline Uint32 LIAlu_xor(LCpu *m_cpu, Uint32 v1, Uint32 v2);
Inline Uint32 LIAlu_not(LCpu *m_cpu, Uint32 v1);
Inline void LIAlu_test(LCpu *m_cpu, Uint32 v1);

Inline Uint32 LIAlu_lshf(LCpu *m_cpu, Uint32 v1, Uint32 v2);
Inline Uint32 LIAlu_rshf(LCpu *m_cpu, Uint32 v1, Uint32 v2);
Inline Uint32 LIAlu_lrot(LCpu *m_cpu, Uint32 v1, Uint32 v2);
Inline Uint32 LIAlu_rrot(LCpu *m_cpu, Uint32 v1, Uint32 v2);



#endif // limp_alu_h
