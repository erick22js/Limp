#ifndef limps_error_h
#define limps_error_h

#include "api.h"



#define Throw(eval) {Uint32 code = (eval); if(code){printf("Caught Error %d at file '%s' in line %d, throwing it away\n", code, __FILE__, __LINE__); return code;}}

#define Error(code) {printf("\n############## Error %d throwed at file '%s' in line %d ##############\n\n", code, __FILE__, __LINE__); return code;}



#endif
