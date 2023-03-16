#include <Limp/thread.h>

#ifdef LI_WINDOWS

#include <windows.h>

struct LThread_{
	Bool in_use;
	Uint32 (*callback)(void* param);
	void* param;
	Uint32 return_code;
	
	HANDLE handle;
}threads[LIMP_MAXTHREADS];

typedef struct LThread_ LThread_;


DWORD WINAPI LThread_winCreate(LPVOID lpParameter){
	LThread_ *thread = (LThread_*)lpParameter;
	thread->return_code = thread->callback(thread->param);
	return 0;
}

LThread LThread_create(Uint32 (*callback)(void* param), void* param){
	for(Int i=1; i<LIMP_MAXTHREADS; i++){
		if(!threads[i].in_use){
			threads[i].in_use = TRUE;
			threads[i].callback = callback;
			threads[i].param = param;
			threads[i].return_code = 0;
			
			threads[i].handle = CreateThread(
				NULL,    			// Thread attributes
				0,       			// Stack size (0 = use default)
				LThread_winCreate,	// Thread start address
				&threads[i],    	// Parameter to pass to the thread
				0,       			// Creation flags
				NULL);
			
			return i;
		}
	}
	return 0;
}

Uint32 LThread_join(LThread thread){
	WaitForSingleObject(threads[thread].handle, INFINITE);
	Int code = threads[thread].return_code;
	threads[thread].in_use = FALSE;
	CloseHandle(threads[thread].handle);
	return code;
}

Bool LThread_destroy(LThread thread){
	if(TerminateThread(threads[thread].handle, 0)){
		threads[thread].in_use = FALSE;
		CloseHandle(threads[thread].handle);
		return TRUE;
	}
	return FALSE;
}

#endif // LI_WINDOWS
