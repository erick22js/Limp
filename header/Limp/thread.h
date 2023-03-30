#ifndef limp_thread_h
#define limp_thread_h

#include <pthread.h>

#include <Limp/api.h>

#define LIMP_MAXTHREADS 256

/**
	SYMBOL FOR THREAD OBJECT
*/

typedef Uint32 LThread;



/**
	WORKING AND OBJECT FUNCTIONS
*/


LThread LThread_create(Uint32 (*callback)(void* param), void* param);

Uint32 LThread_join(LThread thread);

Bool LThread_destroy(LThread thread);
void LThread_free(LThread thread);


#endif // limp_thread_h
