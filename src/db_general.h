#ifndef limps_dbgeneral_h
#define limps_dbgeneral_h

#include "db_instructions.h"


typedef enum LSKeywordType{
    LS_KWTYPE_REGISTER = 0x01,
    LS_KWTYPE_RSTANDARD = 0x02,
    LS_KWTYPE_REXTRA = 0x04,
    LS_KWTYPE_CONDITION = 0x10,
    LS_KWTYPE_IMODE = 0x20,
    LS_KWTYPE_EFETCH = 0x40,
    LS_KWTYPE_ADRSIZE = 0x80,
    LS_KWTYPE_ARGTYPE = 0x100,
}LSKeywordType;

typedef struct LSKeyword{
    Char* name;
    Uint32 code;
    LSKeywordType type;
}LSKeyword;

LSKeyword lsdb_keywords[] = {
    {"ax", 0, LS_KWTYPE_REGISTER|LS_KWTYPE_RSTANDARD},
    {"dx", 1, LS_KWTYPE_REGISTER|LS_KWTYPE_RSTANDARD},
    {"cx", 2, LS_KWTYPE_REGISTER|LS_KWTYPE_RSTANDARD},
    {"bx", 3, LS_KWTYPE_REGISTER|LS_KWTYPE_RSTANDARD},
    {"fp", 4, LS_KWTYPE_REGISTER|LS_KWTYPE_RSTANDARD},
    {"sp", 5, LS_KWTYPE_REGISTER|LS_KWTYPE_RSTANDARD},
    {"ss", 6, LS_KWTYPE_REGISTER|LS_KWTYPE_RSTANDARD},
    {"sd", 7, LS_KWTYPE_REGISTER|LS_KWTYPE_RSTANDARD},
    {"e0", 0, LS_KWTYPE_REGISTER|LS_KWTYPE_REXTRA},
    {"e1", 1, LS_KWTYPE_REGISTER|LS_KWTYPE_REXTRA},
    {"e2", 2, LS_KWTYPE_REGISTER|LS_KWTYPE_REXTRA},
    {"e3", 3, LS_KWTYPE_REGISTER|LS_KWTYPE_REXTRA},
    {"e4", 4, LS_KWTYPE_REGISTER|LS_KWTYPE_REXTRA},
    {"e5", 5, LS_KWTYPE_REGISTER|LS_KWTYPE_REXTRA},
    {"e6", 6, LS_KWTYPE_REGISTER|LS_KWTYPE_REXTRA},
    {"e7", 7, LS_KWTYPE_REGISTER|LS_KWTYPE_REXTRA},
    
    {"aw", 0, LS_KWTYPE_CONDITION},
    {"eq", 1, LS_KWTYPE_CONDITION},
    {"ne", 2, LS_KWTYPE_CONDITION},
    {"lt", 3, LS_KWTYPE_CONDITION},
    {"gt", 4, LS_KWTYPE_CONDITION},
    {"le", 5, LS_KWTYPE_CONDITION},
    {"ge", 6, LS_KWTYPE_CONDITION},
    {"blw", 7, LS_KWTYPE_CONDITION},
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
    
    {"Byte", 0, LS_KWTYPE_ADRSIZE},
    {"Word", 1, LS_KWTYPE_ADRSIZE},
    {"Dword", 2, LS_KWTYPE_ADRSIZE},
    {"Qword", 3, LS_KWTYPE_ADRSIZE},
    
    {"Imm", LS_ARGVALUE_IMM, LS_KWTYPE_ARGTYPE},
    {"Amd", LS_ARGVALUE_AMD, LS_KWTYPE_ARGTYPE},
    {"Reg", LS_ARGVALUE_REG, LS_KWTYPE_ARGTYPE},
    {"RegS", LS_ARGVALUE_REGS, LS_KWTYPE_ARGTYPE},
    {"RegE", LS_ARGVALUE_REGE, LS_KWTYPE_ARGTYPE},
};
Int lsdb_keywords_length = sizeof(lsdb_keywords)/sizeof(LSKeyword);





#endif
