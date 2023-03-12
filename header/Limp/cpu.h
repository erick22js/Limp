#ifndef limp_cpu_h
#define limp_cpu_h

#include <Limp/defines.h>
#include <Limp/bus.h>
#include <Limp/alu.h>
#include <Limp/instructions/table.h>


typedef struct LCpu{
	
	union{
		/* Names */
		struct{
			Uint32 eax;
			Uint32 edx;
			Uint32 ecx;
			Uint32 ebx;
			Uint32 efp;
			Uint32 esp;
			Uint32 ess;
			Uint32 esd;
		}n;
		
		/* Basis Types */
		/* Has one extra register for memory security */
		Uint32 u[9];
		Sint32 s[9];
		Float32 f[9];
	}regs;
	
	struct{
		Uint32 epc;
		Uint32 lpc;
		Uint32 est;
		Uint32 efd;
	}sregs;
	
	/* Inputs/Outputs */
	struct{
		LBus *bus;
	}io;
	
	/* Instruction Decoding Arguments */
	struct{
		void (*func)(LCpu *m_cpu);
		void (**subfuncs)(LCpu *m_cpu);
		Uint32 mod, im, adrm, dsize, cond, f, imm;
		Uint32 ea, data;
		Uint32 *regd, *regb, *regi, *regp, *rego;
	}args;
	
}LCpu;

#define LI_CPU_CF 0
#define LI_CPU_BF 1
#define LI_CPU_VF 2
#define LI_CPU_ZF 3
#define LI_CPU_NF 4
#define LI_CPU_OF 5

#define LI_CPU_EI 16
#define LI_CPU_PM 17




/**
	OBJECT FUNCTIONS
*/


void LCpu_init(LCpu *m_cpu, LBus *m_bus);



/**
	WORKING FUNCTIONS
*/


/* Memory Access */

#define LICPU_readBus8(m_cpu, addr)\
	(m_cpu->io.bus->read8(m_cpu->io.bus, addr))
#define LICPU_readBus16(m_cpu, addr)\
	(m_cpu->io.bus->read16(m_cpu->io.bus, addr&(~1)))
#define LICPU_readBus32(m_cpu, addr)\
	(m_cpu->io.bus->read32(m_cpu->io.bus, addr&(~3)))

#define LICPU_writeBus8(m_cpu, addr, data)\
	(m_cpu->io.bus->write8(m_cpu->io.bus, addr, data))
#define LICPU_writeBus16(m_cpu, addr, data)\
	(m_cpu->io.bus->write16(m_cpu->io.bus, addr&(~1), data))
#define LICPU_writeBus32(m_cpu, addr, data)\
	(m_cpu->io.bus->write32(m_cpu->io.bus, addr&(~3), data))

Uint8 LCpu_readMem8(LCpu *m_cpu, Uint32 addr);
Uint16 LCpu_readMem16(LCpu *m_cpu, Uint32 addr);
Uint32 LCpu_readMem32(LCpu *m_cpu, Uint32 addr);

void LCpu_writeMem8(LCpu *m_cpu, Uint32 addr, Uint8 data);
void LCpu_writeMem16(LCpu *m_cpu, Uint32 addr, Uint16 data);
void LCpu_writeMem32(LCpu *m_cpu, Uint32 addr, Uint32 data);

Uint32 LCpu_pop(LCpu *m_cpu);

void LCpu_push(LCpu *m_cpu, Uint32 data);

Uint32 LCpu_fetch(LCpu *m_cpu);


/* Instruction Handling */

void LICpu_decode(LCpu *m_cpu);

Bool LICpu_condition(LCpu *m_cpu);


/* Program Flow */

void LCpu_jumpA(LCpu *m_cpu, Uint32 addr);
void LCpu_jumpR(LCpu *m_cpu, Sint32 addr);

void LICpu_int_call(LCpu *m_cpu, Uint32 addr);
void LICpu_int_return(LCpu *m_cpu, Uint32 addr);

void LICpu_step(LCpu *m_cpu);

void LCpu_step(LCpu *m_cpu);


/* Debugging */

void LCpu_log(LCpu *m_cpu);



#endif // limp_cpu_h
