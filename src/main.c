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

int main(int argc, char **argv){
    printf("#################################################### Begin ####################################################\n\n");
    
    for(Int i=1; i<argc; i++){
		file = LSLexer_openPath(argv[i]);
		if(!file){
			printf("File at \"\" not found :-\\\n", argv[i]);
			continue;
		}
		
		Char out_file_path[LS_MAXH_PATHSIZE];
		LSDh_zero(out_file_path);
		LSDh_copy(out_file_path, file->path);
		LSDh_cext(out_file_path, "o");
		LSFile *out_file = LSWbuff_openUserFile(out_file_path);
		
		LSParser parser;
		
		LSParser_setup(&parser, file);
		parser.out_file = out_file;
		Int errcode;
		if((errcode=LSParser_init(&parser))){
			printf("\n\nCompilation terminated with code error %d\n", errcode);
		}
    }
    printf("\n\nProgram Ended with %d bytes allocated.", LSDyS_getTotalMemAllocated());
    
    return 0;
}


