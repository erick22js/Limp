#ifndef limpextra_peri_stdout_h
#define limpextra_peri_stdout_h

#include <Limp/limp.h>


typedef struct LPStdout{
	LPeri peri;
	FILE *file;
	Bool active;
}LPStdout;


void LPStdout_init(LPStdout *peri, LBus *bus, FILE *file);


#endif // limpextra_peri_stdout_h
