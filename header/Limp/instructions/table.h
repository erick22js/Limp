#ifndef limp_instructions_table_h
#define limp_instructions_table_h

#include <Limp/defines.h>
#include <Limp/instructions/format.h>



/**
	INSTRUCTION DESCRIPTOR AND SYMBOLS DEFINITIONS
*/


typedef void (LIInstFormat)(LCpu *m_cpu, LPSignal signal);

typedef struct LIInstDescriptor{
	LIInstFormat *decoder;
	void (*func)(LCpu *m_cpu);
	LPSignal flags;
	void (**subfuncs)(LCpu *m_cpu);
}LIInstDescriptor;



/**
	BASE INSTRUCTIONS
*/


LIInstFormat LIIsaFmt_ir;
LIInstFormat LIIsaFmt_ami;
LIInstFormat LIIsaFmt_si;
LIInstFormat LIIsaFmt_adi;
LIInstFormat LIIsaFmt_cdi;
LIInstFormat LIIsaFmt_jl;

void LIIsaDtb_undefined(LCpu *m_cpu);
void LIIsaDtb_nop(LCpu *m_cpu);



/**
	TABLE INSTRUCTIONS
*/


#include <Limp/instructions/opcode07.h>

#include <Limp/instructions/opcode0F.h>

#include <Limp/instructions/opcode10.h>
#include <Limp/instructions/opcode11.h>

#include <Limp/instructions/opcode15.h>

#include <Limp/instructions/opcode18.h>

#include <Limp/instructions/opcode1A.h>
#include <Limp/instructions/opcode1B.h>

#include <Limp/instructions/opcode20.h>

#include <Limp/instructions/opcode30.h>
#include <Limp/instructions/opcode31.h>

#include <Limp/instructions/opcode34.h>


extern LIInstDescriptor LIIsa_table[64];


#endif // limp_instructions_table_h
