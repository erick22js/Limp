#include <stdio.h>

#include "parser.h"

/*
Char src[] =
"movi ebx, second\n"
"label:\n"
"add eax, [ebx-4]#byte\n"
"second:\n"
"add edx, [ebx-4]#word\n"
"add ecx, [ebx-4]#dword\n"
"jl label\n"
;
*/
LSFile *file;

Bool intequal(void* v1, void* v2){
    return *(Int*)v1 == *(Int*)v2;
}
LSDySPtr iptr = 0;

int main(){
    printf("#################################################### Begin ####################################################\n\n");
    
    /*
    FILE *file = fopen("teste.txt", "w");
    fputc('O', file);
    fclose(file);
    */
    
    file = LSLexer_openPath("test.asm");
    
    LSParser parser;
    
    LSParser_setup(&parser, file);
    Int errcode;
    if((errcode=LSParser_init(&parser))){
        printf("\n\nCompilation terminated with code error %d\n", errcode);
    }
    
    
    
    printf("\n\nProgram Ended with %d bytes allocated.", LSDyS_getTotalMemAllocated());
    
    return 0;
}


