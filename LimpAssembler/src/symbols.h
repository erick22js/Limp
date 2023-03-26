#ifndef limps_symbols_h
#define limps_symbols_h

#include "api.h"
#include "db_instructions.h"
#include "db_general.h"



/**
    Symbol Expression
*/

typedef enum LSsymExpOpr{
    LS_SYMEXPOPR_OPERAND,
    
    LS_SYMEXPOPR_UNPLUS,
    LS_SYMEXPOPR_UNMINUS,
    LS_SYMEXPOPR_UNNOTBIT,
    LS_SYMEXPOPR_UNNOT,
    LS_SYMEXPOPR_BINSUM,
    LS_SYMEXPOPR_BINSUB,
    LS_SYMEXPOPR_BINMUL,
    LS_SYMEXPOPR_BINDIV,
    LS_SYMEXPOPR_BINANDBIT,
    LS_SYMEXPOPR_BINORBIT,
    LS_SYMEXPOPR_BINXORBIT,
    LS_SYMEXPOPR_BINLSHIFT,
    LS_SYMEXPOPR_BINRSHIFT,
    LS_SYMEXPOPR_BINOR,
    LS_SYMEXPOPR_BINAND,
    LS_SYMEXPOPR_BINEQUAL,
    LS_SYMEXPOPR_BINNOTEQUAL,
    LS_SYMEXPOPR_BINLESS,
    LS_SYMEXPOPR_BINGREAT,
    LS_SYMEXPOPR_BINLESSEQUAL,
    LS_SYMEXPOPR_BINGREATEQUAL,
}LSsymExpOpr;

typedef enum LSsymOprType{
    LS_SYMOPRTYPE_LITERAL,
    LS_SYMOPRTYPE_IDENTIFIER,
    LS_SYMOPRTYPE_EXPRESSION,
}LSsymOprType;

struct LSsymExpression;
typedef struct LSsymExpression LSsymExpression;
struct LSsymExpression{
    LSsymExpOpr oprt; /* Operator */
    struct{
        LSsymOprType type;
        union{
            Uint32 u32;
            Sint32 s32;
            LSsymExpression *exp;
            Char* identifier;
        }data;
    }opr1, opr2; /* Operands */
};


/**
    Instruction Symbols
*/

typedef enum LSsymAmdType{
    LS_AMDTYPE_IMMEDIATE,
    LS_AMDTYPE_REGISTER,
    LS_AMDTYPE_INDIRECT,
    LS_AMDTYPE_POINTER,
    LS_AMDTYPE_POINTERIMMEDIATEINDEXED,
    LS_AMDTYPE_POINTERINDEXED,
    LS_AMDTYPE_POINTERDYNAMIC,
    LS_AMDTYPE_POINTERELEMENT,
    LS_AMDTYPE_POINTERPREINCREMENT,
    LS_AMDTYPE_POINTERPREDECREMENT,
    LS_AMDTYPE_POINTERPOSINCREMENT,
    LS_AMDTYPE_POINTERPOSDECREMENT,
    LS_AMDTYPE_POINTERINDEXEDPOSINCREMENT,
    LS_AMDTYPE_POINTERINDEXEDPOSDECREMENT,
    LS_AMDTYPE_POINTERDYNAMICPOSINCREMENT,
    LS_AMDTYPE_POINTERDYNAMICPOSDECREMENT,
}LSsymAmdType;

typedef struct LSsymArg{
    LSargValue valtype;
    union{
        struct{
            LSsymAmdType type:4;
            Uint32 regb:3;
            Uint32 regi:3;
            Uint32 dsize:2;
            Uint32 imm;
        }amd;
        Uint32 regindex;
        Uint32 imm;
    }value;
}LSsymArg;

typedef struct LSsymValue{
    LSargValue valtype;
    union{
        Uint8 u8;
        Sint8 s8;
        Uint16 u16;
        Sint16 s16;
        Uint32 u32;
        Sint32 s32;
    }data;
	LSsymArg *arg;
}LSsymValue;


/**
    Symbol Command
    Its arranjed in a linked list way
*/

struct LSsymInstruction;
typedef struct LSsymInstruction LSsymInstruction;
struct LSsymInstruction{
    Uint32 args_len:4;
    Uint32 im:4;
    Uint32 f:4;
    Uint32 cond:8;
    Uint32 rego:4;
    Uint32 imm_extra:1;
    LSMnemonic* mnemonic;
    LSsymArg args[4];
};


/**
    Symbol Label
    Its arranjed in a linked list way
*/

struct LSsymLabel;
typedef struct LSsymLabel LSsymLabel;
struct LSsymLabel{
    Char* name;
    Uint32 address;
    
    LSsymLabel *next;
};


/**
	Literal Definition
	Its arranjed in a linked list way
*/

struct LSsymLitdef;
typedef struct LSsymLitdef LSsymLitdef;
struct LSsymLitdef{
	Char* name;
	LSsymValue value;
	
	LSsymLitdef *next;
};


/**
	Defines Definition
	Its arranjed in a linked list way
*/

struct LSsymDefine;
typedef struct LSsymDefine LSsymDefine;
struct LSsymDefine{
	Char* name;
	Char* src_path;
	Uint32 seek;
	Uint32 end;
	
	LSsymDefine *next;
};


/**
	Defines Macro
	Its arranjed in a linked list way
*/

struct LSsymMacro;
typedef struct LSsymMacro LSsymMacro;
struct LSsymMacro{
	Char* name;
	Char* src_path;
	Uint32 seek;
	Uint32 end;
	
	struct{
		LSargValue type;
		Char* name;
	}args[4];
	
	LSsymMacro *next;
};

typedef struct LSsymMacroArgs{
	LSsymArg args[4];
}LSsymMacroArgs;


/**
	Once Definition
	Its arranjed in a linked list way
*/

struct LSsymOnce;
typedef struct LSsymOnce LSsymOnce;
struct LSsymOnce{
	Char* path;
	
	LSsymDefine *next;
};


/**
	Scope Definition
*/

struct LSsymScope;
typedef struct LSsymScope LSsymScope;
struct LSsymScope{
	Char* name;
	Uint32 adr;
	
	LSsymLabel *label_first;
    LSsymLabel *label_last;
    
    LSsymLitdef *predef_first;
    LSsymLitdef *predef_last;
    
    LSsymLitdef *const_first;
    LSsymLitdef *const_last;

    LSsymDefine *def_first;
    LSsymDefine *def_last;
    
    LSsymMacro *macro_first;
    LSsymMacro *macro_last;
    
    LSsymMacro *macro;
    LSsymMacroArgs macro_args;
    
    LSsymScope *father;
    LSsymScope *next;
};


/**
    Arranjed linked lists Functions
*/

#define LLPush(firstPtr, lastPtr, elementPtr) {\
        if(firstPtr){\
            lastPtr->next = elementPtr;\
            lastPtr = elementPtr;\
        }\
        else{\
            firstPtr = elementPtr;\
            lastPtr = elementPtr;\
        }\
    }




#endif
