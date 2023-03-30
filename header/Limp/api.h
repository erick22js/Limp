#ifndef limp_api_h
#define limp_api_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdatomic.h>



/**
	TYPES DEFINITION
*/


typedef _Bool Bool;
typedef atomic_flag AtomicFlag;

typedef char Char;

typedef size_t SizeT;

typedef intptr_t IntPtr;

typedef int Int;

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;
typedef unsigned long long Uint64;

typedef signed char Sint8;
typedef signed short Sint16;
typedef signed int Sint32;
typedef signed long long Sint64;

typedef float Float;

typedef float Float32;
typedef double Float64;

#define Atomic(Type) _Atomic Type

#define Inline inline



/**
	VALUES DEFINITION
*/


#ifdef NULL
	#undef NULL
#endif
#define NULL ((void*)0)

#define ATOMIC_FLAG_FALSE ATOMIC_FLAG_INIT

#define FALSE 0
#define TRUE 1



/**
	UTILITY FUNCTIONS
*/

#define getBit(data, o) (((data)>>(o))&1)
#define setBit(data, o) ((data)|(1<<(o)))
#define clrBit(data, o) ((data)&(~(1<<(o))))
#define togBit(data, o) ((data)^(1<<(o)))
#define setVBit(data, o, v) (((data)&(~(1<<(o))))|(((Bool)((v)!=0))<<(o)))
#define getSign(data) (getBit(data, (sizeof(data)<<3)-1))

#define castS8T16(data) ((Uint16)((Sint16)((Sint8)((Uint8)(data)))))
#define castS8T32(data) ((Uint32)((Sint32)((Sint8)((Uint8)(data)))))
#define castS16T32(data) ((Uint32)((Sint32)((Sint16)((Uint16)(data)))))

extern Atomic(Bool) _Log_lock;
#define Log(...){\
		while(_Log_lock);\
		_Log_lock = TRUE;\
		printf(__VA_ARGS__);\
		_Log_lock = FALSE;\
	}

#define atomicTestAndSet(flag) atomic_flag_test_and_set(flag)
#define atomicTestAndClear(flag) atomic_flag_clear(flag)


/**
	SETTINGS DEFINITION
*/

#define LI_LITTLEENDIAN
#define LI_WINDOWS
#define LI_32BIT
#define LI_INTEL_COREI3


#endif // limp_api_h
