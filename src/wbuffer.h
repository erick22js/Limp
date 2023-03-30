#ifndef limps_wbuffer_h
#define limps_wbuffer_h

#include "file.h"


LSFile* LSWbuff_openUserFile(Char* path){
    return LSFile_loadUserFile(path, FALSE);
}

void LSWbuff_close(LSFile *file){
    LSFile_close(file);
}


void LSWbuff_write8(LSFile *file, Byte data){
    LSFile_putc(file, data);
}

void LSWbuff_write16(LSFile *file, Uint16 data){
    LSFile_putc(file, data);
    LSFile_putc(file, data>>8);
}

void LSWbuff_write32(LSFile *file, Uint32 data){
    LSFile_putc(file, data);
    LSFile_putc(file, data>>8);
    LSFile_putc(file, data>>16);
    LSFile_putc(file, data>>24);
}

void LSWbuff_write16B(LSFile *file, Uint16 data){
    LSFile_putc(file, data>>8);
    LSFile_putc(file, data);
}

void LSWbuff_write32B(LSFile *file, Uint32 data){
    LSFile_putc(file, data>>24);
    LSFile_putc(file, data>>16);
    LSFile_putc(file, data>>8);
    LSFile_putc(file, data);
}


void LSWbuff_seekBegin(LSFile *file, Int offset){
    LSFile_seekBegin(file, offset);
}

void LSWbuff_seekCurrent(LSFile *file, Int offset){
    LSFile_seekCurrent(file, offset);
}

void LSWbuff_seekEnd(LSFile *file, Int offset){
    LSFile_seekEnd(file, offset);
}




#endif