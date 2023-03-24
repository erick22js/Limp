#ifndef limps_dbgeneral_h
#define limps_dbgeneral_h

#include "api.h"


typedef enum LSKeywordType{
    LS_KWTYPE_REGISTER = 0x01,
    LS_KWTYPE_CONDITION = 0x02,
    LS_KWTYPE_IMODE = 0x04,
    LS_KWTYPE_EFETCH = 0x08,
    LS_KWTYPE_ADRSIZE = 0x10,
}LSKeywordType;

typedef struct LSKeyword{
    Char* name;
    Uint32 code;
    LSKeywordType type;
}LSKeyword;

LSKeyword lsdb_keywords[] = {
    {"eax", 0, LS_KWTYPE_REGISTER},
    {"edx", 1, LS_KWTYPE_REGISTER},
    {"ecx", 2, LS_KWTYPE_REGISTER},
    {"ebx", 3, LS_KWTYPE_REGISTER},
    {"efp", 4, LS_KWTYPE_REGISTER},
    {"esp", 5, LS_KWTYPE_REGISTER},
    {"ess", 6, LS_KWTYPE_REGISTER},
    {"esd", 7, LS_KWTYPE_REGISTER},
    
    {"aw", 0, LS_KWTYPE_CONDITION},
    {"eq", 1, LS_KWTYPE_CONDITION},
    {"ne", 2, LS_KWTYPE_CONDITION},
    {"lt", 3, LS_KWTYPE_CONDITION},
    {"gt", 4, LS_KWTYPE_CONDITION},
    {"le", 5, LS_KWTYPE_CONDITION},
    {"ge", 6, LS_KWTYPE_CONDITION},
    {"bl", 7, LS_KWTYPE_CONDITION},
    {"ab", 8, LS_KWTYPE_CONDITION},
    {"be", 9, LS_KWTYPE_CONDITION},
    {"ae", 10, LS_KWTYPE_CONDITION},
    {"ez", 11, LS_KWTYPE_CONDITION},
    {"nz", 12, LS_KWTYPE_CONDITION},
    {"gz", 13, LS_KWTYPE_CONDITION},
    {"lz", 14, LS_KWTYPE_CONDITION},
    {"oez", 15, LS_KWTYPE_CONDITION},
    {"onz", 16, LS_KWTYPE_CONDITION},
    {"ogz", 17, LS_KWTYPE_CONDITION},
    {"olz", 18, LS_KWTYPE_CONDITION},
    {"oed", 19, LS_KWTYPE_CONDITION},
    {"ond", 20, LS_KWTYPE_CONDITION},
    {"old", 21, LS_KWTYPE_CONDITION},
    {"ogd", 22, LS_KWTYPE_CONDITION},
    {"oea", 23, LS_KWTYPE_CONDITION},
    {"ona", 24, LS_KWTYPE_CONDITION},
    {"ov", 25, LS_KWTYPE_CONDITION},
    {"sc", 26, LS_KWTYPE_CONDITION},
    {"cc", 27, LS_KWTYPE_CONDITION},
    {"sb", 28, LS_KWTYPE_CONDITION},
    {"cb", 29, LS_KWTYPE_CONDITION},
    {"so", 30, LS_KWTYPE_CONDITION},
    {"co", 31, LS_KWTYPE_CONDITION},
    
    {"b", 0, LS_KWTYPE_IMODE|LS_KWTYPE_EFETCH},
    {"d", 3, LS_KWTYPE_IMODE|LS_KWTYPE_EFETCH},
    
    {"w", 0, LS_KWTYPE_IMODE},
    {"uw", 0, LS_KWTYPE_IMODE},
    {"hw", 1, LS_KWTYPE_IMODE},
    {"sw", 2, LS_KWTYPE_IMODE},
    
    {"byte", 0, LS_KWTYPE_ADRSIZE},
    {"word", 1, LS_KWTYPE_ADRSIZE},
    {"dword", 2, LS_KWTYPE_ADRSIZE},
    {"qword", 3, LS_KWTYPE_ADRSIZE},
};
Int lsdb_keywords_length = sizeof(lsdb_keywords)/sizeof(LSKeyword);





#endif
