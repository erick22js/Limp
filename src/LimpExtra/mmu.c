#include <LimpExtra/mmu.h>
#include <Limp/cpu.h>



Uint32 trvector[20];

/* Are in total 16 registers

The segments are formed by:

	ADDRESS:16..BASE:16
	LIMIT:16..FLAGS:16

	Address is the virtual 16-bit bank segment position to be
comparated to address.
	Limit is the virtual 16-bit bank segment limit to be
comparated to address.
	Base is the logical 16-bit bank segment position to be replaced
in virtual gived address.
	Flags is the control flags for access to segment.

	A segment is choosed if the virtual address is between the
segment address and limit, if, teste the access flags, if did with
success, replaces the high word by the base of segment.

System restricted
	0  => Segment 1 of system address/base
	1  => Segment 1 of system limit/flags
	2  => Segment 2 of system address/base
	3  => Segment 2 of system limit/flags
	4  => Segment 3 of system address/base
	5  => Segment 3 of system limit/flags
	6  => Segment 4 of system address/base
	7  => Segment 4 of system limit/flags

Application free
	8  => Segment 1 of application address/base
	9  => Segment 1 of application limit/flags
	10 => Segment 2 of application address/base
	11 => Segment 2 of application limit/flags
	12 => Segment 3 of application address/base
	13 => Segment 3 of application limit/flags
	14 => Segment 4 of application address/base
	15 => Segment 4 of application limit/flags
*/

Uint32 readReg(LCoproc *coproc, Uint32 reg){
	if(reg<20){
		return trvector[reg];
	}
	return 0;
}

void writeReg(LCoproc *coproc, Uint32 reg, Uint32 data){
	if(reg<20){
		trvector[reg] = data;
	}
}

void receive(LCoproc *coproc, Uint32 cmd){
	/* Nothing for now! */
}

Int tAddr(LMmu *mmu, Uint32 *addr, Uint32 lcpu_st){
	Bool pm = getBit(lcpu_st, LI_CPU_PM); /* Non-PM grant most privileges */
	lcpu_st >>= 16;
	Uint32 radr = addr;
	Int i = 0;
	for(; i<16; i+=2){
		/* Search for a match segment */
		if(trvector[i+1]&0x8000&&isBetween(radr, trvector[i]&0xFFFF0000, trvector[i+1]&0xFFFF0000)){
			/* Will restricts all the actions if is in protected mode */
			if(pm){
				/* Cannot access protected segments */
				if(trvector[i+1]&1){
					return 1;
				}
				/* Cannot execute a not executable segment */
				if((lcpu_st^trvector[i+1])&LIP_ADRESSACCESS_FE){
					return 2;
				}
				/* If segment is restrict with read and write operations */
				if(trvector[i+1]&LIP_ADRESSACCESS_RRW){
					/* Reading and writing must match */
					if((lcpu_st^trvector[i+1])&LIP_ADRESSACCESS_FRW){
						return 3;
					}
				}
			}
			*addr = ((*addr)&0xFFFF)|(trvector[i]<<16);
			return 0;
		}
	}
	if(pm){
		return 4;
	}
	return 0;
}


void LEMmu_init(LMmu *m_mmu){
	memset(m_mmu, 0, sizeof(m_mmu));
	LCoproc_zeroes(&m_mmu->coproc);
	m_mmu->tAddr = tAddr;
	m_mmu->coproc.readReg = readReg;
	m_mmu->coproc.writeReg = writeReg;
	m_mmu->coproc.receive = receive;
}
