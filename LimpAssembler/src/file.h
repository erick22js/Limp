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

LSFile lsg_files_[LS_MAX_FILES];


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
        return feof(file->file);
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
                chr = fgetc(file->file);
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
        }
    }
}

void LSFile_seekBegin(LSFile *file, Int offset){
    if(file->bufft){
        file->buffer_seek = offset;
    }
    else{
        fseek(file->file, offset, SEEK_SET);
    }
}

void LSFile_seekCurrent(LSFile *file, Int offset){
    if(file->bufft){
        file->buffer_seek += offset;
    }
    else{
        fseek(file->file, offset, SEEK_CUR);
    }
}

void LSFile_seekEnd(LSFile *file, Int offset){
    if(file->bufft){
        file->buffer_seek = file->buffer_size+offset;
    }
    else{
        fseek(file->file, offset, SEEK_END);
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
        rewind(file->file);
    }
}

void LSFile_close(LSFile *file){
    file->open = FALSE;
    
    if(!file->bufft){
        fclose(file->file);
    }
}



#endif
