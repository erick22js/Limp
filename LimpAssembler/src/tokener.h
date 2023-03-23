#ifndef limps_tokener_h
#define limps_tokener_h

#include "lexer.h"
#include "tokens.h"


typedef struct LSTokener{
    LSFile *file;
    LSToken tk;
    struct{
    	Uint16 offset;
    }last;
    Bool ended;
    
    Bool preview;
}LSTokener;


/**
    OBJECT FUNCTIONS
*/

void LSTokener_init(LSTokener *tkr, LSFile *file){
	memset(tkr, 0, sizeof(LSTokener));
    tkr->file = file;
}


/**
    WORKING FUNCTIONS
*/

/* Fetches the next token */
/* Returns Error code */
Int LSTokener_fetch(LSTokener *tkr){
	tkr->last.offset = LSLexer_offset(tkr->file);
	
    /* Do not fetch anything if it was did in preview mode */
    if(tkr->preview){
        tkr->preview = FALSE;
        return 0;
    }
    
    /* In case of no any fetching, sets token as end of file */
    tkr->tk.type = LS_TOKENTYPE_EOF;
    tkr->tk.data.u32 = 0;
    
    Int chr = 0;
    
    /* Keeps getting character until file is not ended */
    while(!LSLexer_eof(tkr->file)){
        chr = LSLexer_get(tkr->file);
        
        /* Is a not printable character */
        if(Char_isBlank(chr)&&(chr!='\n')){
            continue;
        }
        else{
			tkr->last.offset = LSLexer_offset(tkr->file)-1;
			
			/* Is a breakline character */
			if(chr=='\n'){
				tkr->tk.type = LS_TOKENTYPE_NEWLINE;
				tkr->tk.data.u32 = 0;
				break;
			}
			/* Is a number precursor */
			else if(Char_isDecimal(chr)){
				Throw(
					LSToken_fetchNumber(tkr->file, &tkr->tk, chr)
				);
				break;
			}
			/* Is a identifier precursor */
			else if(Char_isIdentifier(chr)){
				Throw(
					LSToken_fetchIdentifier(tkr->file, &tkr->tk, chr)
				);
				break;
			}
			/* Is a string literal */
			else if(chr=='"'){
				Throw(
					LSToken_fetchString(tkr->file, &tkr->tk)
				);
				break;
			}
			/* Is a character literal */
			else if(chr=='\''){
				Throw(
					LSToken_fetchChar(tkr->file, &tkr->tk)
				);
				break;
			}
			/* Is any other sign character */
			else{
				tkr->tk.type = LS_TOKENTYPE_SIGN;
				switch(chr){
					case '+':{
						chr = LSLexer_get(tkr->file);
						if(chr=='+'){
							tkr->tk.data.sign = '++';
						}
						else{
							LSLexer_unget(tkr->file);
							tkr->tk.data.sign = '+';
						}
					}
					break;
					case '-':{
						chr = LSLexer_get(tkr->file);
						if(chr=='-'){
							tkr->tk.data.sign = '--';
						}
						else{
							LSLexer_unget(tkr->file);
							tkr->tk.data.sign = '-';
						}
					}
					break;
					case ';':{
						while(chr!='\n' && chr!=EOF){
								chr = LSLexer_get(tkr->file);
							}
							continue;
					}
					case '/':{
						chr = LSLexer_get(tkr->file);
						/* Multi line commentary */
						if(chr=='*'){
							while(chr!=EOF){
								chr = LSLexer_get(tkr->file);
								if(chr=='*'){
									chr = LSLexer_get(tkr->file);
									if(chr=='/'){
										break;
									}
								}
							}
							continue;
						}
						/* One line commentary */
						else if(chr=='/'){
							while(chr!='\n' && chr!=EOF){
								chr = LSLexer_get(tkr->file);
							}
							continue;
						}
						else{
							LSLexer_unget(tkr->file);
							tkr->tk.data.sign = '-';
						}
					}
					break;
					case '!':{
						chr = LSLexer_get(tkr->file);
						if(chr=='='){
							tkr->tk.data.sign = '!=';
						}
						else{
							LSLexer_unget(tkr->file);
							tkr->tk.data.sign = '!';
						}
					}
					break;
					case '>':{
						chr = LSLexer_get(tkr->file);
						if(chr=='>'){
							tkr->tk.data.sign = '>>';
						}
						else if(chr=='='){
							tkr->tk.data.sign = '>=';
						}
						else{
							LSLexer_unget(tkr->file);
							tkr->tk.data.sign = '>';
						}
					}
					break;
					case '<':{
						chr = LSLexer_get(tkr->file);
						if(chr=='<'){
							tkr->tk.data.sign = '<<';
						}
						else if(chr=='='){
							tkr->tk.data.sign = '<=';
						}
						else{
							LSLexer_unget(tkr->file);
							tkr->tk.data.sign = '<';
						}
					}
					break;
					case '&':{
						chr = LSLexer_get(tkr->file);
						if(chr=='&'){
							tkr->tk.data.sign = '&&';
						}
						else{
							LSLexer_unget(tkr->file);
							tkr->tk.data.sign = '&';
						}
					}
					break;
					case '|':{
						chr = LSLexer_get(tkr->file);
						if(chr=='|'){
							tkr->tk.data.sign = '||';
						}
						else{
							LSLexer_unget(tkr->file);
							tkr->tk.data.sign = '|';
						}
					}
					break;
					case '=':{
						chr = LSLexer_get(tkr->file);
						if(chr=='='){
							tkr->tk.data.sign = '==';
						}
						else{
							LSLexer_unget(tkr->file);
							tkr->tk.data.sign = '=';
						}
					}
					break;
					default:{
						tkr->tk.data.sign = chr;
					}
				}
				break;
			}
        }
    }
    
    if(LSLexer_eof(tkr->file)){
        tkr->ended = TRUE;
    }
    //LSToken_print(&tkr->tk);
    return 0;
}

/* Fetches next token only for previewing */
Int LSTokener_preview(LSTokener *tkr){
    /* Do not fetch anything if it was did in preview mode */
    if(tkr->preview){
        return 0;
    }
    LSTokener_fetch(tkr);
    tkr->preview = TRUE;
    return 0;
}



#endif
