#ifndef limp_defines
#define limp_defines

#include <Limp/api.h>
#include <Limp/bus.h>


struct LCpu;
typedef struct LCpu LCpu;

struct LCoproc;
typedef struct LCoproc LCoproc;

struct LMmu;
typedef struct LMmu LMmu;

struct LPci;
typedef struct LPci LPci;

struct LPeri;
typedef struct LPeri LPeri;

typedef enum LIPSignal{
	LPROCS_NONE = 0x0000,
	LPROCS_ONLYADDRESS = 0x0001,
}LIPSignal;

typedef struct LIPInterruption{
	Uint8 selector;
}LIPInterruption;

typedef enum LIPAdressAccess{
	LIP_ADRESSACCESS_WRITE = 0x100000, /* 0=read; 1=write */
	LIP_ADRESSACCESS_EXECUTE = 0x200000, /* 0=data; 1=code */
}LIPAdressAccess;


#endif // limp_defines
