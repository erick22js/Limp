#ifndef limps_lexer_h
#define limps_lexer_h

#include "file.h"
#include "memory.h"
#include "error.h"


LSFile *LSLexer_openSrc(Char* string){
    Int size = 0;
    Char* cs = string;
    while(*cs){
        size++; cs++;
    }
    LSFile *file = LSFile_loadBuffer((Byte*)string, size, TRUE);
    if(file){
        file->apidata = (void*)((1<<16)|(0));
    }
    return file;
}

LSFile *LSLexer_openPath(Char* path){
    return LSFile_loadUserFile(path, TRUE);
}

Bool LSLexer_eof(LSFile *file){
    return LSFile_eof(file);
}

Int LSLexer_get(LSFile *file){
    return LSFile_getc(file);
}

void LSLexer_unget(LSFile *file){
    LSFile_ungetc(file);
}

void LSLexer_seekSet(LSFile *file, Int offset){
    LSFile_seekBegin(file, offset);
}

void LSLexer_rewind(LSFile *file){
    LSFile_rewind(file);
}

void LSLexer_close(LSFile *file){
    LSFile_close(file);
}

Int LSLexer_line(LSFile *file){
    return ((Int)file->apidata)>>16;
}

Int LSLexer_offset(LSFile *file){
    return ((Int)file->apidata)&0xFFFF;
}


/**
    CHARACTER UTILITIES
*/

Bool Char_isBlank(Int chr){
    return chr==' '||chr=='\t'||(chr<0x20);
}

Bool Char_isBinary(Int chr){
    return chr=='0'||chr=='1';
}

Bool Char_isOctal(Int chr){
    return chr>='0'&&chr<='7';
}

Bool Char_isDecimal(Int chr){
    return chr>='0'&&chr<='9';
}

Bool Char_isHexadecimal(Int chr){
    return (chr>='0'&&chr<='9')||(chr>='a'&&chr<='f')||(chr>='A'&&chr<='F');
}

Bool Char_isIdentifier(Int chr){
    return (chr>='a'&&chr<='z')||(chr>='A'&&chr<='Z')||Char_isDecimal(chr)||(chr=='_');
}

Int Char_toValue(Int chr){
    return (chr>='0'&&chr<='9')?(chr-'0'):
        (chr>='A'&&chr<='F')?(chr-'A')+10:
        (chr>='a'&&chr<='f')?(chr-'a')+10:0;
}



#endif