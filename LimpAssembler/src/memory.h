#ifndef limps_memory_h
#define limps_memory_h

#include "api.h"


#define LS_DYNAMICMEM_LENGTH 1024*1024*2 // 2 MB
#define LS_STACKMEM_LENGTH 1024*128 // 128 KB


typedef Uint32 LSDySPtr; // Limp Assembler Dynamic Stream Pointer :-)

Byte lsg_dymem_b_[LS_DYNAMICMEM_LENGTH];
Uint32 lsg_dymem_top_ = 4;
Byte lsg_stmem_b_[LS_STACKMEM_LENGTH];
Uint32 lsg_stmem_bot_ = LS_STACKMEM_LENGTH;


/**
    DYNAMIC WORKING FUNCTIONS
*/

void LSDyS_copyMem(void* dest, void* src, Int size){
    Byte *destb = (Byte*)dest;
    Byte *srcb = (Byte*)src;
    while(size){
        *destb = (*srcb);
        destb++, srcb++;
        size--;
    }
}

void* LSDyS_alloc(Int size){
    /* Aligns the size of data to 4 bytes */
    Int sizea = (size&(~3)) + (((size&3)!=0)<<2);
    
    /* Retrives pointer to data */
    void* datam = (void*)&lsg_dymem_b_[lsg_dymem_top_];
    
    /* Advances the stack pointer aligned */
    lsg_dymem_top_ += sizea;
    return datam;
}

void* LSDyS_calloc(Int size){
    /* Aligns the size of data to 4 bytes */
    Int sizea = (size&(~3)) + (((size&3)!=0)<<2);
    void* datam = LSDyS_alloc(size);
    
    Byte* dtb = (Byte*)datam;
    while(sizea){
        *dtb = 0;
        sizea--;
    }
    return datam;
}

void* LSDyS_wrapMem(void* data, Int size, LSDySPtr *ptr){
    /* Aligns the size of data to 4 bytes */
    Int sizea = (size&(~3)) + (((size&3)!=0)<<2);
    
    /* Stores the last stream header offset in current stream header and retrives pointer to data */
    *(Uint32*)(&lsg_dymem_b_[lsg_dymem_top_]) = *ptr;
    void* datam = (void*)&lsg_dymem_b_[lsg_dymem_top_+4];
    
    /* Updates the pointer to current stream header */
    *ptr = lsg_dymem_top_;
    
    /* Advances the stack pointer aligned */
    lsg_dymem_top_ += sizea+4;
    
    /* Copies the retrieve data to allocated and return its pointer */
    LSDyS_copyMem(datam, data, size);
    return datam;
}

void* LSDyS_wrapMemCmp(void* data, Int size, LSDySPtr *ptr, Bool(*equalFunc)(void* v1, void* v2)){
    LSDySPtr ptrl = *ptr;
    
    /* Verify for a match data, using the given comparator function */
    while(ptrl){
        void* datam = (void*)&lsg_dymem_b_[ptrl+4];
        if(equalFunc(data, datam)){
            return datam;
        }
        ptrl = *(Uint32*)(&lsg_dymem_b_[ptrl]);
    }
    
    /* If ended here, has need for allocating a new one */
    return LSDyS_wrapMem(data, size, ptr);
}

Int LSDyS_getTotalMemAllocated(){
    return (lsg_dymem_top_-4);
}

#define Alloc(size) LSDyS_alloc(size)
#define Calloc(size) LSDyS_calloc(size)
#define WarpMem(data, size, ptr) LSDyS_wrapMem(data, size, ptr)
#define WarpMemCmp(data, size, ptr, equalfunc) LSDyS_wrapMemCmp(data, size, ptr, equalFunc)
#define WarpObj(data, ptr) LSDyS_wrapMem(data, sizeof(data), ptr)
#define WarpObjCmp(data, ptr, equalfunc) LSDyS_wrapMemCmp(data, sizeof(data), ptr, equalFunc)


/**
	STACK WORKING FUNCTIONS
*/

void* LSDyS_stkPush(Int size){
	lsg_stmem_bot_ -= size;
	return &lsg_stmem_b_[lsg_stmem_bot_];
}

void* LSDyS_cpush(Int size){
	void* datam = LSDyS_stkPush(size);
	
	Byte* dtb = (Byte*)datam;
	while(size){
		*dtb = 0;
		dtb++;
		size--;
	}
	return datam;
}

void LSDyS_stkPop(Int size){
	lsg_stmem_bot_ += size;
}

#define Cpush(size) LSDyS_cpush(size)


/**
    UTILITIES FUNCTIONS
*/

Bool Str_equal(void* str1, void* str2){
    Char* pstr1 = (Char*)str1;
    Char* pstr2 = (Char*)str2;
    while((*pstr1)||(*pstr2)){
        if((*pstr1)!=(*pstr2)){
            return FALSE;
        }
        pstr1++, pstr2++;
    }
    return TRUE;
}

Int Str_length(Char* str){
    Int len = 0;
    while(*str){
        len++;
        str++;
    }
    return len;
}



#endif
