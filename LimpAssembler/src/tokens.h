#ifndef limps_tokens_h
#define limps_tokens_h

#include "api.h"
#include "memory.h"
#include "lexer.h"
#include "db_general.h"
#include "db_instructions.h"


#define LS_MAXIDENTIFIER_SIZE 31
#define LS_MAXSTRING_SIZE 4095



/**
    TYPES OF TOKEN
*/

typedef enum LSTokenType{
    /* Control */
    LS_TOKENTYPE_EOF,
    LS_TOKENTYPE_NEWLINE,
    
    /* Values */
    LS_TOKENTYPE_INTEGER,
    LS_TOKENTYPE_FLOAT,
    LS_TOKENTYPE_STRING,
    
    /* Symbols */
    LS_TOKENTYPE_IDENTIFIER,
    LS_TOKENTYPE_KEYWORD,
    LS_TOKENTYPE_MNEMONIC,
    
    /* Signs */
    LS_TOKENTYPE_SIGN,
}LSTokenType;


/**
    STRUCT AND OBJECTS
*/


typedef struct LSToken{
    LSTokenType type;
    
    union{
        Uint32 u32;
        Sint32 s32;
        Float32 f32;
        Char* string;
        LSKeyword *kw;
        LSMnemonic *mne;
        Uint32 sign;
    }data;
    Uint32 length;
}LSToken;



/**
    WORKING FUNCTIONS
*/

/* Identifier fetching */
LSDySPtr lsgtkn_ident_p = 0;
Uint32 LSToken_fetchIdentifier(LSFile *file, LSToken *tk, Int first){
    Char buffer[LS_MAXIDENTIFIER_SIZE+1];
    Int i = 0;
    Int chr = first;
    
    /* Keeps retrieving characters while are valid */
    while(Char_isIdentifier(chr)&&(i<=LS_MAXIDENTIFIER_SIZE)){
        buffer[i] = chr;
        i++;
        chr = LSLexer_get(file);
    }
    buffer[i] = 0;
    LSLexer_unget(file);
    
    /* Verify the identifier, wich may be a mnemonic or keyword */
    /* If is a keyword */
    for(Int i=0; i<lsdb_keywords_length; i++){
        if(Str_equal(buffer, lsdb_keywords[i].name)){
            tk->type = LS_TOKENTYPE_KEYWORD;
            tk->data.kw = &lsdb_keywords[i];
            return 0;
        }
    }
    /* If is a mnemonic */
    for(Int i=0; i<lsdb_mnemonics_length; i++){
        if(Str_equal(buffer, lsdb_mnemonics[i].name)){
            tk->type = LS_TOKENTYPE_MNEMONIC;
            tk->data.mne = &lsdb_mnemonics[i];
            return 0;
        }
    }
    
    /* Otherwise, is a program defined symbol */
    /* Allocates in the dynamic memory and returns its pointer */
    Char* wrap = LSDyS_wrapMemCmp((void*)buffer, i+1, &lsgtkn_ident_p, Str_equal);
    
    tk->type = LS_TOKENTYPE_IDENTIFIER;
    tk->data.string = wrap;
    return 0;
}

/* String fetching */
Int LSToken_decodeEscape(LSFile *file, Int chr){
	if(chr=='\\'){
		chr = LSLexer_get(file);
		switch(chr){
			case 'n':{
				return '\n';
			}
			break;
			case 't':{
				return '\t';
			}
			break;
			case '0':{
				return '\0';
			}
			break;
		}
	}
	return chr;
}

LSDySPtr lsgtkn_string_p = 0;
Uint32 LSToken_fetchString(LSFile *file, LSToken *tk){
    Char buffer[LS_MAXSTRING_SIZE+1];
    Int i = 0;
    Int chr = LSLexer_get(file);
    
    /* Keeps retrieving characters while are valid */
    while((chr!='"')&&(chr!=EOF)&&(i<=LS_MAXSTRING_SIZE)){
        buffer[i] = LSToken_decodeEscape(file, chr);
        i++;
        chr = LSLexer_get(file);
    }
    buffer[i] = 0;
    
    /* Allocates in the dynamic memory and returns its pointer */
    Char* wrap = LSDyS_wrapMemCmp((void*)buffer, i+1, &lsgtkn_string_p, Str_equal);
    
    tk->type = LS_TOKENTYPE_STRING;
    tk->data.string = wrap;
    tk->length = i;
    return 0;
}

/* Number fetching */
Uint32 LSToken_fetchNbinary(LSFile *file, LSToken *tk){
    Int chr = LSLexer_get(file);
    Uint32 value = 0;
    
    while(Char_isBinary(chr)){
        value <<= 1;
        value |= Char_toValue(chr);
        chr = LSLexer_get(file);
    }
    if(Char_isIdentifier(chr)){
		Error(LS_ERR_UNALOWEDPOSFIX);
    }
    LSLexer_unget(file);
    
    tk->data.u32 = value;
    tk->type = LS_TOKENTYPE_INTEGER;
    return 0;
}

Uint32 LSToken_fetchNoctal(LSFile *file, LSToken *tk){
    Int chr = LSLexer_get(file);
    Uint32 value = 0;
    
    while(Char_isOctal(chr)){
        value <<= 3;
        value |= Char_toValue(chr);
        chr = LSLexer_get(file);
    }
    if(Char_isIdentifier(chr)){
		Error(LS_ERR_UNALOWEDPOSFIX);
    }
    LSLexer_unget(file);
    
    tk->data.u32 = value;
    tk->type = LS_TOKENTYPE_INTEGER;
    return 0;
}

Float32 LSToken_fetchNFdecimal(LSFile *file, Float *out){
	Int chr = '.';
	Float value = 0;
	Float dividend = 10;
	
	while(Char_isDecimal((chr=LSLexer_get(file)))){
		value += Char_toValue(chr)/dividend;
		dividend *= 10;
	}
    if(Char_isIdentifier(chr)){
		Error(LS_ERR_UNALOWEDPOSFIX);
    }
	LSLexer_unget(file);
	
	*out = value;
	return 0;
}

Uint32 LSToken_fetchNdecimal(LSFile *file, LSToken *tk, Int first){
    Int chr = first;
    Uint32 value = 0;
    
    while(Char_isDecimal(chr)){
        value *= 10;
        value += Char_toValue(chr);
        chr = LSLexer_get(file);
    }
    if(Char_isIdentifier(chr)){
		Error(LS_ERR_UNALOWEDPOSFIX);
    }
    if(chr=='.'){
		Float dec = 0;
		Throw(
			LSToken_fetchNFdecimal(file, &dec)
		);
		dec += value;
		value = *(Uint32*)&dec;
    }
    else{
		LSLexer_unget(file);
    }
    
    tk->data.u32 = value;
    tk->type = LS_TOKENTYPE_INTEGER;
    return 0;
}

Float32 LSToken_fetchNFhexadecimal(LSFile *file, Float *out){
	Int chr = '.';
	Float value = 0;
	Float dividend = 16;
	
	while(Char_isHexadecimal((chr=LSLexer_get(file)))){
		value += Char_toValue(chr)/dividend;
		dividend *= 16;
	}
    if(Char_isIdentifier(chr)){
		Error(LS_ERR_UNALOWEDPOSFIX);
    }
	LSLexer_unget(file);
	
	*out = value;
	return 0;
}

Uint32 LSToken_fetchNhexadecimal(LSFile *file, LSToken *tk){
    Int chr = LSLexer_get(file);
    Uint32 value = 0;
    
    while(Char_isHexadecimal(chr)){
        value <<= 4;
        value |= Char_toValue(chr);
        chr = LSLexer_get(file);
    }
    if(Char_isIdentifier(chr)){
		Error(LS_ERR_UNALOWEDPOSFIX);
    }
    if(chr=='.'){
		Float dec = 0;
		Throw(
			LSToken_fetchNFhexadecimal(file, &dec)
		);
		dec += value;
		value = *(Uint32*)&dec;
    }
    else{
		LSLexer_unget(file);
    }
    
    tk->data.u32 = value;
    tk->type = LS_TOKENTYPE_INTEGER;
    return 0;
}

/* Retuns 0 when no error */
Uint32 LSToken_fetchNumber(LSFile *file, LSToken *tk, Int first){
    Int chr = first;
    if(chr=='0'){
        chr = LSLexer_get(file);
        if(chr=='x'){
            Throw(
				LSToken_fetchNhexadecimal(file, tk)
			);
        }
        else if(chr=='o'){
            Throw(
				LSToken_fetchNoctal(file, tk)
			);
        }
        else if(chr=='b'){
            Throw(
				LSToken_fetchNbinary(file, tk)
			);
        }
        else if(Char_isDecimal(chr)){
            Throw(
				LSToken_fetchNdecimal(file, tk, chr)
			);
        }
		else if(chr=='.'){
			Float dec = 0;
			Throw(
				LSToken_fetchNFdecimal(file, &dec)
			);
			Uint32 value = *(Uint32*)&dec;
			
			tk->data.u32 = value;
			tk->type = LS_TOKENTYPE_INTEGER;
		}
        else{
            LSLexer_unget(file);
            tk->data.s32 = 0;
            tk->type = LS_TOKENTYPE_INTEGER;
        }
    }
    else{
        Throw(
			LSToken_fetchNdecimal(file, tk, first)
		);
    }
    return 0;
}


/**
    COMPARISION FUNCTIONS
*/

Bool LSToken_isSign(LSToken *token, Int chr){
    return (token->type==LS_TOKENTYPE_SIGN)&&(token->data.sign==chr);
}

Bool LSToken_isIdentifier(LSToken *token, Char* str){
    return (token->type==LS_TOKENTYPE_IDENTIFIER)&&(Str_equal(token->data.string, str));
}

Bool LSToken_isKeyword(LSToken *token, Char* str){
    return (token->type==LS_TOKENTYPE_KEYWORD)&&(Str_equal(token->data.kw->name, str));
}

Bool LSToken_isMnemonic(LSToken *token, Char* str){
    return (token->type==LS_TOKENTYPE_MNEMONIC)&&(Str_equal(token->data.mne->name, str));
}


Bool LSToken_endOfArgument(LSToken *tk){
    return LSToken_isSign(tk, ',')||(tk->type==LS_TOKENTYPE_NEWLINE)||(tk->type==LS_TOKENTYPE_EOF);
}

Bool LSToken_endOfArgumentList(LSToken *tk){
    return (tk->type==LS_TOKENTYPE_NEWLINE)||(tk->type==LS_TOKENTYPE_EOF);
}


/**
    UTILITY FUNCTIONS
*/

void LSToken_print(LSToken *token){
    printf("TK# ");
    switch(token->type){
        case LS_TOKENTYPE_EOF:{
            printf("End-Of-File");
        }
        break;
        case LS_TOKENTYPE_NEWLINE:{
            printf("New-Line");
        }
        break;
        case LS_TOKENTYPE_INTEGER:{
            printf("Integer: %d", token->data.s32);
        }
        break;
        case LS_TOKENTYPE_FLOAT:{
            printf("Float: %f", token->data.f32);
        }
        break;
        case LS_TOKENTYPE_STRING:{
            printf("String: '%s'", token->data.string);
        }
        break;
        case LS_TOKENTYPE_IDENTIFIER:{
            printf("Identifier: '%s'", token->data.string);
        }
        break;
        case LS_TOKENTYPE_KEYWORD:{
            printf("Keyword: %s", token->data.kw->name);
        }
        break;
        case LS_TOKENTYPE_MNEMONIC:{
            printf("Mnemonic: %s", token->data.mne->name);
        }
        break;
        case LS_TOKENTYPE_SIGN:{
            printf("Sign: %c", token->data.sign);
        }
        break;
        default:{
            printf("-unknown-");
        }
    }
    printf("\n");
}


#endif
