#ifndef limp_instructions_table_h
#define limp_instructions_table_h

#include <Limp/defines.h>
#include <Limp/instructions/format.h>



/**
	INSTRUCTION DESCRIPTOR AND SYMBOLS DEFINITIONS
*/


typedef void (LIInstFormat)(LCpu *m_cpu, LIPSignal signal);

typedef struct LIInstDescriptor{
	LIInstFormat *decoder;
	void (*func)(LCpu *m_cpu);
	LIPSignal flags;
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


#include <Limp/instructions/opcode01.h>
#include <Limp/instructions/opcode02.h>
#include <Limp/instructions/opcode03.h>
#include <Limp/instructions/opcode04.h>

#include <Limp/instructions/opcode06.h>
#include <Limp/instructions/opcode07.h>
#include <Limp/instructions/opcode08.h>
#include <Limp/instructions/opcode09.h>
#include <Limp/instructions/opcode0A.h>
#include <Limp/instructions/opcode0B.h>
#include <Limp/instructions/opcode0C.h>
#include <Limp/instructions/opcode0D.h>
#include <Limp/instructions/opcode0E.h>
#include <Limp/instructions/opcode0F.h>

#include <Limp/instructions/opcode10.h>
#include <Limp/instructions/opcode11.h>
#include <Limp/instructions/opcode12.h>
#include <Limp/instructions/opcode13.h>
#include <Limp/instructions/opcode14.h>
#include <Limp/instructions/opcode15.h>

#include <Limp/instructions/opcode18.h>

#include <Limp/instructions/opcode1A.h>
#include <Limp/instructions/opcode1B.h>
#include <Limp/instructions/opcode1C.h>
#include <Limp/instructions/opcode1D.h>

#include <Limp/instructions/opcode19.h>
#include <Limp/instructions/opcode20.h>
#include <Limp/instructions/opcode21.h>
#include <Limp/instructions/opcode22.h>
#include <Limp/instructions/opcode23.h>
#include <Limp/instructions/opcode24.h>
#include <Limp/instructions/opcode25.h>
#include <Limp/instructions/opcode26.h>
#include <Limp/instructions/opcode27.h>
#include <Limp/instructions/opcode28.h>

#include <Limp/instructions/opcode2B.h>
#include <Limp/instructions/opcode2C.h>
#include <Limp/instructions/opcode2D.h>

#include <Limp/instructions/opcode30.h>
#include <Limp/instructions/opcode31.h>
#include <Limp/instructions/opcode32.h>
#include <Limp/instructions/opcode33.h>
#include <Limp/instructions/opcode34.h>
#include <Limp/instructions/opcode35.h>
#include <Limp/instructions/opcode36.h>
#include <Limp/instructions/opcode37.h>
#include <Limp/instructions/opcode38.h>

#include <Limp/instructions/opcode3A.h>
#include <Limp/instructions/opcode3B.h>
#include <Limp/instructions/opcode3C.h>
#include <Limp/instructions/opcode3D.h>


extern LIInstDescriptor LIIsa_table[64];


#endif // limp_instructions_table_h
