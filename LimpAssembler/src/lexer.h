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
        file->apidata = 0x00010001;
    }
    return file;
}

LSFile *LSLexer_openPath(Char* path){
    LSFile *file = LSFile_loadUserFile(path, TRUE);
    if(file){
        file->apidata = 0x00010001;
    }
    return file;
}

Bool LSLexer_eof(LSFile *file){
    return LSFile_eof(file);
}

Int LSLexer_get(LSFile *file){
    Int *chr = LSFile_getc(file);
    if(chr=='\n'){
		file->apidata &= 0xFFFF0000;
		file->apidata += 0x00010001;
    }
    else{
		file->apidata += 0x00000001;
    }
    return chr;
}

void LSLexer_unget(LSFile *file){
    LSFile_ungetc(file);
	file->apidata -= 1;
}

void LSLexer_seekSet(LSFile *file, Int offset){
    LSFile_seekBegin(file, offset);
    file->apidata = 0x00010001;
}

void LSLexer_rewind(LSFile *file){
    LSFile_rewind(file);
    file->apidata = 0x00010001;
}

void LSLexer_close(LSFile *file){
    LSFile_close(file);
}

Int LSLexer_line(LSFile *file){
    return (file->apidata)>>16;
}

Int LSLexer_offset(LSFile *file){
    return (file->apidata)&0xFFFF;
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
