#ifndef limps_api_h
#define limps_api_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef _Bool Bool;

typedef char Char;

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;
typedef unsigned long long Uint64;

typedef signed char Sint8;
typedef signed short Sint16;
typedef signed int Sint32;
typedef signed long long Sint64;

typedef float Float32;
typedef double Float64;

typedef signed char Byte;
typedef short Short;
typedef int Int;
typedef long long Long;
typedef float Float;
typedef double Double;


#ifndef EOF
    #define EOF 0xFFFFFFFF
#endif

#ifndef NULL
    #define NULL 0
#endif
#ifndef ZERO
    #define ZERO 0
#endif
#ifndef FALSE
    #define FALSE 0
#endif
#ifndef TRUE
    #define TRUE 1
#endif



#endif