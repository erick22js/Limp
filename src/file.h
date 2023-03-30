#ifndef limps_file_h
#define limps_file_h

#include "api.h"
#include "dirhanddler.h"


#define LS_MAX_FILES 32

typedef struct LSFile{
    /* File definitions */
    Bool open;
    Char path[LS_MAX_PATHSIZE];
    
    /* Definition for buffer type */
    Char* buffer;
    Uint32 buffer_size;
    Uint32 buffer_seek;
    
    /* Definition for user file type */
    FILE *file;
    Uint32 file_seek;
    Uint32 file_seek_set;
    Uint32 file_end;
    
    /* General */
    Bool bufft; /* Is type buffer */
    Bool readm; /* Is read mode */
    
    /* Utilities */
    Char latest[16];
    Uint16 latest_i:4;
    Uint16 latest_feed:4;
    
    /* Custom data */
    Uint32 userdata;
    Uint32 apidata;
}LSFile;

LSFile lsg_files_[LS_MAX_FILES] = {0};


/**
    OBJECT FUNCTIONS
*/


LSFile *LSIFile_firstNotOpen(){
    for(Int i=0; i<LS_MAX_FILES; i++){
        if(!lsg_files_[i].open){
            return &lsg_files_[i];
        }
    }
    return NULL;
}

LSFile *LSFile_loadBuffer(Byte* buffer, Uint32 buffer_size, Bool read_mode){
    LSFile *file = LSIFile_firstNotOpen();
    if(file){
        memset(file, 0, sizeof(LSFile));
        file->open = TRUE;
        file->buffer = buffer;
        file->buffer_size = buffer_size;
        file->bufft = TRUE;
        file->readm = read_mode;
        file->latest_i = 0;
        file->latest_feed = 0;
        file->userdata = NULL;
        file->apidata = NULL;
        return file;
    }
    return NULL;
}

LSFile *LSFile_loadUserFile(Char* path, Bool read_mode){
    LSFile *file = LSIFile_firstNotOpen();
    if(file){
        memset(file, 0, sizeof(LSFile));
        file->file = fopen(path, read_mode?"rb":"wb");
        if(!file->file){
            return NULL;
        }
        file->file_seek = 0;
        file->file_seek_set = 0;
        file->file_end = 0xFFFFFFFF;
        LSDh_copy(file->path, path);
        file->open = TRUE;
        file->bufft = FALSE;
        file->readm = read_mode;
        file->latest_i = 0;
        file->latest_feed = 0;
        file->userdata = NULL;
        file->apidata = NULL;
        return file;
    }
    return NULL;
}

LSFile *LSFile_loadUserFileRestricted(Char* path, Bool read_mode, Uint32 seek, Uint32 end){
    LSFile *file = LSIFile_firstNotOpen();
    if(file){
        memset(file, 0, sizeof(LSFile));
        file->file = fopen(path, read_mode?"rb":"wb");
        if(!file->file){
            return NULL;
        }
        fseek(file->file, seek, SEEK_SET);
        file->file_seek = seek;
        file->file_seek_set = seek;
        file->file_end = end;
        LSDh_copy(file->path, path);
        file->open = TRUE;
        file->bufft = FALSE;
        file->readm = read_mode;
        file->latest_i = 0;
        file->latest_feed = 0;
        file->userdata = NULL;
        file->apidata = NULL;
        return file;
    }
    return NULL;
}


/**
    WORKING FUNCTIONS
*/



Bool LSFile_eof(LSFile *file){
    if(file->bufft){
        return file->buffer_seek>=file->buffer_size;
    }
    else{
        return feof(file->file)||(file->file_seek>=file->file_end);
    }
}

Int LSFile_getc(LSFile *file){
    Int chr = 0;
    if(file->readm){
        if(file->latest_feed){
            chr = file->latest[file->latest_i];
            file->latest_feed--;
            file->latest_i++;
        }
        else{
            if(file->bufft){
                if((file->buffer_seek)>=(file->buffer_size)){
                    chr = EOF;
                }
                else{
                    chr = file->buffer[file->buffer_seek];
                }
                file->buffer_seek++;
            }
            else{
                if(file->file_seek<file->file_end){
                	chr = fgetc(file->file);
                }
                else{
					chr = EOF;
                }
                file->file_seek++;
            }
            file->latest[file->latest_i] = chr;
            file->latest_i++;
        }
    }
    return chr;
}

void LSFile_ungetc(LSFile *file){
    if(file->readm){
        file->latest_i--;
        file->latest_feed++;
    }
}

Uint32 LSFile_read(LSFile *file, void* dest, Uint32 length){
	Int count = 0;
	Byte* destb = dest;
	if(file->readm){
        while(length){
			Int chr = LSFile_getc(file);
			if(chr==EOF){
				break;
			}
			destb++;
			length--;
			count++;
        }
    }
    return count;
}

void LSFile_putc(LSFile *file, Byte chr){
    if(!file->readm){
        if(file->bufft){
            file->buffer[file->buffer_seek] = chr;
            file->buffer_seek++;
        }
        else{
            fputc(chr, file->file);
            file->file_seek++;
        }
    }
}

void LSFile_seekBegin(LSFile *file, Int offset){
    if(file->bufft){
        file->buffer_seek = offset;
    }
    else{
        fseek(file->file, offset, SEEK_SET);
        file->file_seek = ftell(file->file);
    }
}

void LSFile_seekCurrent(LSFile *file, Int offset){
    if(file->bufft){
        file->buffer_seek += offset;
    }
    else{
        fseek(file->file, offset, SEEK_CUR);
        file->file_seek = ftell(file->file);
    }
}

void LSFile_seekEnd(LSFile *file, Int offset){
    if(file->bufft){
        file->buffer_seek = file->buffer_size+offset;
    }
    else{
        fseek(file->file, offset, SEEK_END);
        file->file_seek = ftell(file->file);
    }
}

Int LSFile_tell(LSFile *file){
    if(file->bufft){
        return file->buffer_seek;
    }
    else{
        return ftell(file->file);
    }
}

void LSFile_rewind(LSFile *file){
    if(file->bufft){
        file->buffer_seek = 0;
    }
    else{
		fseek(file->file, file->file_seek_set, SEEK_SET);
		file->file_seek = file->file_seek_set;
    }
}

void LSFile_close(LSFile *file){
    file->open = FALSE;
    
    if(!file->bufft){
        fclose(file->file);
    }
}



#endif
