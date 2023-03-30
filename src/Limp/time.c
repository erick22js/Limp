#include <time.h>
#include <Limp/time.h>



Uint32 LTime_getMicros(){
	struct timeval tv;
	mingw_gettimeofday(&tv, NULL);
	return tv.tv_usec;
}

Uint32 LTime_getSecs(){
	struct timeval tv;
	mingw_gettimeofday(&tv, NULL);
	return tv.tv_sec;
}
