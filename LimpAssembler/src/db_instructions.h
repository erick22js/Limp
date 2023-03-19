#ifndef limps_dbinstructions_h
#define limps_dbinstructions_h

#include "api.h"


/**
    ARGUMENTS VARYATIONS
*/

typedef enum LSargValue{
    LS_ARGVALUE_VOID = 0,
    LS_ARGVALUE_IMM8,
    LS_ARGVALUE_IMM16,
    LS_ARGVALUE_IMM32,
    LS_ARGVALUE_IMM,
    LS_ARGVALUE_AMD,
    LS_ARGVALUE_REG,
}LSargValue;

typedef enum LSargName{
    LS_ARGNAME_VOID = 0,
    LS_ARGNAME_AUTO = 1,
    LS_ARGNAME_REGD,
    LS_ARGNAME_REGB,
    LS_ARGNAME_REGI,
    LS_ARGNAME_REGP,
    LS_ARGNAME_REGO,
    LS_ARGNAME_IMM,
    LS_ARGNAME_AMD,
    
    LS_ARGNAME_SHIFT1L = 0x0100,
    LS_ARGNAME_SHIFT2L = 0x0200,
    LS_ARGNAME_SHIFT3L = 0x0400,
    LS_ARGNAME_SHIFT1R = 0x0800,
    LS_ARGNAME_SHIFT2R = 0x1000,
    LS_ARGNAME_SHIFT3R = 0x2000,
}LSargName;


/**
    INSTRUCTIONS TYPE
*/

typedef enum LSInstrType{
    LS_INSTRTYPE_IR,
    LS_INSTRTYPE_AMI,
    LS_INSTRTYPE_SI,
    LS_INSTRTYPE_ADI,
    LS_INSTRTYPE_CDI,
    LS_INSTRTYPE_JL
}LSInstrType;


/**
    MNEMONIC STRUCTURE DEFINITION
*/

typedef struct LSMnemonic{
    Char* name; Uint32 opcode; LSInstrType type;
    Uint32 mod:8, func:8;
    
    struct{
        LSargName encname;
        LSargValue valtype;
    }args[4];
}LSMnemonic;

/*
LSMnemonic lsdb_mnemonics[] = {
    {
        "mov", 0x30, LS_INSTRTYPE_IR,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "movi", 0x30, LS_INSTRTYPE_IR,
        0x1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
        },
    },
    {
    	"add", 0x10, LS_INSTRTYPE_AMI,
    	0x0, 0,
    	{
    		{LS_ARGNAME_REGD, LS_ARGVALUE_REG},
    		{LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
    	}
    },
    {
    	"jl", 0x24, LS_INSTRTYPE_JL,
    	0x0, 0,
    	{
    		{LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
    	}
    },
    {
    	"inc", 0x14, LS_INSTRTYPE_SI,
    	0, 0x0,
    	{
    		{LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
    	}
    },
    {
    	"dec", 0x14, LS_INSTRTYPE_SI,
    	0, 0x1,
    	{
    		{LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
    	}
    },
    {
    	"ja", 0x20, LS_INSTRTYPE_ADI,
    	0x0, 0,
    	{
    		{LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
    	}
    },
    {
    	"jr", 0x20, LS_INSTRTYPE_ADI,
    	0x2, 0,
    	{
    		{LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
    	}
    },
};*/

#include "instructions.h"

Int lsdb_mnemonics_length = sizeof(lsdb_mnemonics)/sizeof(LSMnemonic);


#endif
