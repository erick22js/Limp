#ifndef limp_cpu_h
#define limp_cpu_h

#include <Limp/defines.h>
#include <Limp/bus.h>
#include <Limp/alu.h>
#include <Limp/instructions/table.h>
#include <Limp/peri.h>


typedef struct LCpu{
	
	union{
		/* Names */
		struct{
			Uint32 ax;
			Uint32 dx;
			Uint32 cx;
			Uint32 bx;
			Uint32 fp;
			Uint32 sp;
			Uint32 ss;
			Uint32 sd;
			Uint32 e0;
			Uint32 e1;
			Uint32 e2;
			Uint32 e3;
			Uint32 e4;
			Uint32 e5;
			Uint32 e6;
			Uint32 e7;
		}n;
		
		/* Basis Types */
		/* Has blank spaced register for memory access security */
		Uint32 u[16];
		Sint32 s[16];
		Float32 f[16];
	}regs;
	
	/* Extra Registers */
	Uint32 *cache;
	Uint32 cache_length;
	
	struct{
		Uint32 epc;
		Uint32 lpc;
		Uint32 st;
		Uint32 efd;
		
		Uint32 it; /* Interruption Table Address */
		
		Uint32 ssiv; /* Stack setter on Interruption at virtual mode */
	}sregs;
	
	/* Hardware States */
	struct{
		Bool busy;
		Bool ext_req;
		Bool halt; /* Halted Execution */
		Bool wait; /* Waiting state */
		Bool waits; /* Waits for specific interruption */
		Uint8 waiti; /* Interruption to waits for */
	}hs;
	
	/* CoProcessors Conections */
	LCoproc *coprocs[4];
	LMmu *mmu;
	
	/* Inputs/Outputs and Peripherals */
	struct{
		LBus *bus;
		LPci *pci;
	}io;
	
	/* Instruction Decoding Arguments */
	struct{
		void (*func)(LCpu *m_cpu);
		void (**subfuncs)(LCpu *m_cpu);
		Uint32 selector, mod, im, adrm, dsize, cond, f, imm;
		Uint32 ea, data;
		Uint32 *rd, *rb, *ri, *rp, *ro;
		Uint32 regd, regb, regi, regp, rego;
	}args;
	
	/* Execution properties */
	/* Cycling properties */
	struct{
		Int cycles; /* The counter for cycling */
		Int cpb_set; /* Cycles per Busy state */
		Int bpp_set; /* Busy states per Phase */
	}cy;
	
	/* Cpu can be a Peripherical component */
	LPeri peri;
	
}LCpu;

#define LI_CPU_CF 0
#define LI_CPU_BF 1
#define LI_CPU_VF 2
#define LI_CPU_ZF 3
#define LI_CPU_NF 4
#define LI_CPU_OF 5

#define LI_CPU_EI 16
#define LI_CPU_PM 17
#define LI_CPU_VM 18

#define LI_CPU_WS 23


/**
	DATA
*/


/* System Predefined Interruptions */

extern const LIPInterruption LI_INT_PMVIOLATION;
extern const LIPInterruption LI_INT_INVALIDOPC;
extern const LIPInterruption LI_INT_INVDATAACCESS;
extern const LIPInterruption LI_INT_INVCODEACCESS;
extern const LIPInterruption LI_INT_ZERODIVISION;
extern const LIPInterruption LI_INT_DEBUGGING;
extern const LIPInterruption LI_INT_COPROC0;
extern const LIPInterruption LI_INT_COPROC1;
extern const LIPInterruption LI_INT_COPROC2;
extern const LIPInterruption LI_INT_COPROC3;
extern const LIPInterruption LI_INT_BIOSRESERVED1;
extern const LIPInterruption LI_INT_BIOSRESERVED2;



/**
	OBJECT FUNCTIONS
*/


void LCpu_init(LCpu *m_cpu, LBus *m_bus);

Bool LCpu_conMmu(LCpu *m_cpu, LMmu *m_mmu);
Int LCpu_conCop(LCpu *m_cpu, LCoproc *cop);


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

Inline Int LCpu_tAddress(LCpu *m_cpu, Uint32 *addr, LIPAdressAccess mode);
Inline Int LICpu_tAddress(LCpu *m_cpu, Uint32 *addr, LIPAdressAccess mode);

Uint8 LCpu_readMem8(LCpu *m_cpu, Uint32 addr);
Uint16 LCpu_readMem16(LCpu *m_cpu, Uint32 addr);
Uint32 LCpu_readMem32(LCpu *m_cpu, Uint32 addr);

void LCpu_writeMem8(LCpu *m_cpu, Uint32 addr, Uint8 data);
void LCpu_writeMem16(LCpu *m_cpu, Uint32 addr, Uint16 data);
void LCpu_writeMem32(LCpu *m_cpu, Uint32 addr, Uint32 data);

Uint32 LCpu_pop(LCpu *m_cpu);
void LCpu_push(LCpu *m_cpu, Uint32 data);

Uint32 LICpu_pop(LCpu *m_cpu);
void LICpu_push(LCpu *m_cpu, Uint32 data);

Uint32 LCpu_fetch(LCpu *m_cpu);


/* Extra Registers */

Uint32 LCpu_readCache(LCpu *m_cpu, Uint32 reg);
void LCpu_writeCache(LCpu *m_cpu, Uint32 reg, Uint32 data);


/* External Devices Access */

Uint32 LCpu_in(LCpu *m_cpu, Uint8 port);
Bool LCpu_inUpdtd(LCpu *m_cpu, Uint8 port);
void LCpu_out(LCpu *m_cpu, Uint8 port, Uint32 data);


/* Coprocessor Access */

Uint32 LCpu_co_readReg(LCpu *m_cpu, Uint8 co, Uint32 reg);
void LCpu_co_writeReg(LCpu *m_cpu, Uint8 co, Uint32 reg, Uint32 data);

void LCpu_co_disable(LCpu *m_cpu, Uint8 co);
void LCpu_co_enable(LCpu *m_cpu, Uint8 co);

Uint8 LCpu_co_checkState(LCpu *m_cpu, Uint8 co);

void LCpu_co_command(LCpu *m_cpu, Uint8 co, Uint32 cmd);


/* Instruction Handling */

void LICpu_decode(LCpu *m_cpu);

Bool LICpu_condition(LCpu *m_cpu);

Bool LICpu_protectionThrown(LCpu *m_cpu); /* Returns TRUE if has throwed a interruption */


/* Program Flow */

void LCpu_reset(LCpu *m_cpu);

void LCpu_jumpAbs(LCpu *m_cpu, Uint32 addr);
void LCpu_jumpRel(LCpu *m_cpu, Sint32 addr);

void LICpu_int_call(LCpu *m_cpu, Uint32 addr);
void LICpu_int_return(LCpu *m_cpu);
Bool LCpu_requestInterruption(LCpu *m_cpu, LIPInterruption intr);

void LCpu_step(LCpu *m_cpu);
void LCpu_execute(LCpu *m_cpu);
void LCpu_stop(LCpu *m_cpu);


/* Debugging */

void LCpu_log(LCpu *m_cpu);



#endif // limp_cpu_h
