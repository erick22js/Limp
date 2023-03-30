#ifndef limps_rbuffer_h
#define limps_rbuffer_h

#include "file.h"


LSFile* LSRbuff_openUserFile(Char* path){
    return LSFile_loadUserFile(path, TRUE);
}

void LSRbuff_close(LSFile *file){
    LSFile_close(file);
}


Uint8 LSRbuff_read8(LSFile *file){
    return LSFile_getc(file)&0xFF;
}

Uint16 LSRbuff_read16(LSFile *file){
    return (LSFile_getc(file)&0xFF)|((LSFile_getc(file)&0xFF)<<8);
}

Uint32 LSRbuff_read32(LSFile *file){
    return (LSFile_getc(file)&0xFF)|((LSFile_getc(file)&0xFF)<<8)|((LSFile_getc(file)&0xFF)<<16)|((LSFile_getc(file)&0xFF)<<24);
}

Uint16 LSRbuff_read16B(LSFile *file){
    return ((LSFile_getc(file)&0xFF)<<8)|(LSFile_getc(file)&0xFF);
}

Uint32 LSRbuff_read32B(LSFile *file){
    return ((LSFile_getc(file)&0xFF)<<24)|((LSFile_getc(file)&0xFF)<<16)|((LSFile_getc(file)&0xFF)<<8)|(LSFile_getc(file)&0xFF);
}


void LSRbuff_seekBegin(LSFile *file, Int offset){
    LSFile_seekBegin(file, offset);
}

void LSRbuff_seekCurrent(LSFile *file, Int offset){
    LSFile_seekCurrent(file, offset);
}

void LSRbuff_seekEnd(LSFile *file, Int offset){
    LSFile_seekEnd(file, offset);
}


Uint32 LSRbuff_getSize(LSFile *file){
	Uint32 offset = LSFile_tell(file);
	LSFile_seekEnd(file, 0);
	Uint32 size = LSFile_tell(file);
	LSFile_seekBegin(file, offset);
	return size;
}


#endif // limps_rbuffer_h
