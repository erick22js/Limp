#ifndef limp_defines
#define limp_defines

#include <Limp/api.h>


struct LCpu;
typedef struct LCpu LCpu;

typedef enum LPSignal{
	LPROCS_NONE = 0x0000,
	LPROCS_ONLYADDRESS = 0x0001,
}LPSignal;


#endif // limp_defines
