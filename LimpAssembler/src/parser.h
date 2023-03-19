#ifndef limps_parser_h
#define limps_parser_h


struct LSParser;
typedef struct LSParser LSParser;


#include "tokener.h"
#include "symbols.h"
#include "encoder.h"


#define LS_MAXPARSER_FILEDEPTH 16
#define LS_MAXPARSER_SRCFILES 4


typedef struct LSParser{
    LSTokener tkr;
    
    /* Parser Properties */
    Bool parsing;
    Uint32 process_address_program;
    Uint32 process_address_binary;
    Uint32 encode_address_program;
    Uint32 encode_address_binary;
    
    /* Parsing file tree */
    LSFile *files[LS_MAXPARSER_FILEDEPTH];
    Int file_i;
    LSFile *src_files[LS_MAXPARSER_SRCFILES];
    Int src_files_i;
    LSFile *out_file;
    
    /* Parsing symbols tree */
    LSsymLabel *label_first;
    LSsymLabel *label_last;
    
}LSParser;

Bool LSParser_hasLabel(LSParser *parser, Char* name){
	LSsymLabel *clabel = parser->label_first;
	while(clabel){
		if(Str_equal(clabel->name, name)){
			return TRUE;
		}
		clabel = clabel->next;
	}
	return FALSE;
}

Bool LSParser_hasSymbol(LSParser *parser, Char* name){
	return LSParser_hasLabel(parser, name);
}

Uint32 LSParser_getLabel(LSParser *parser, Char* name){
	LSsymLabel *clabel = parser->label_first;
	while(clabel){
		if(Str_equal(clabel->name, name)){
			return clabel->address;
		}
		clabel = clabel->next;
	}
	return 0;
}

Uint32 LSParser_getSymbol(LSParser *parser, Char* name){
	if(LSParser_hasLabel(parser, name)){
		return LSParser_getLabel(parser, name);
	}
}


#include "expression.h"


/*
    UTILITY FUNCTIONS
*/

Bool LSParser_pushFile_(LSParser *parser, LSFile *file){
    if(parser->file_i==LS_MAXPARSER_FILEDEPTH){
        return FALSE;
    }
    LSLexer_rewind(file);
    parser->files[parser->file_i] = file;
    parser->file_i++;
    parser->tkr.file = file;
    return TRUE;
}

Bool LSParser_popFile_(LSParser *parser){
    if(parser->file_i){
        parser->file_i--;
        if(parser->file_i){
            LSLexer_close(parser->files[parser->file_i]);
        }
        parser->files[parser->file_i] = NULL;
        parser->tkr.file = parser->files[parser->file_i-1];
        return TRUE;
    }
    else{
        return FALSE;
    }
}


/*
    OBJECT FUNCTIONS
*/

void LSParser_setup(LSParser *parser, LSFile *file){
    memset(parser, 0, sizeof(LSParser));
    LSTokener_init(&parser->tkr, file);
    
    parser->src_files[0] = file;
    parser->src_files_i++;
}


/*
    WORKING FUNCTIONS
*/

Int LSParser_process_file_(LSParser *parser){
    LSToken *tk = &parser->tkr.tk;
    parser->tkr.ended = FALSE;
    
    /* Process the current file until reach the end */
    while(!parser->tkr.ended){
        LSTokener_fetch(&parser->tkr);
        
        /* Break line */
        if(tk->type==LS_TOKENTYPE_NEWLINE){
            continue;
        }
        /* End of file */
        else if(tk->type==LS_TOKENTYPE_EOF){
            break;
        }
        /* If token is a preprocessor precursor */
        else if(LSToken_isSign(tk, '.')){
            /* TODO */
        }
        /* May be a label definition */
        else if(tk->type==LS_TOKENTYPE_IDENTIFIER){
            Char* identifier = tk->data.string;
            LSTokener_fetch(&parser->tkr);
            
            /* Its a label definition */
            if(LSToken_isSign(tk, ':')){
                LSsymLabel *label = Calloc(sizeof(LSsymLabel));
                label->name = identifier;
                label->address = parser->process_address_program;
                LLPush(parser->label_first, parser->label_last, label);
                continue;
            }
        }
        /* Is a instruction precursor */
        else if(tk->type==LS_TOKENTYPE_MNEMONIC){
            LSMnemonic *mne = tk->data.mne;
            Int size = 0;
			Throw(
				LSExp_getInstructionSize(parser, mne, &size)
			);
            parser->process_address_program += size;
            parser->process_address_binary += size;
            
            /* Suspends processing until end of line instruction */
            while(!LSToken_endOfArgumentList(tk)){
                LSTokener_fetch(&parser->tkr);
            }
        }
        /* Undentified command */
        else{
            
        }
        
        // Test code
        LSToken_print(tk);
        printf("#@@@@ Processor at adr: %d\n", parser->process_address_program);
    }
    return 0;
}

Int LSParser_encode_file_(LSParser *parser){
    LSToken *tk = &parser->tkr.tk;
    parser->tkr.ended = FALSE;
    
    /* Process the current file until reach the end */
    while(!parser->tkr.ended){
        LSTokener_fetch(&parser->tkr);
        
        /* Break line */
        if(tk->type==LS_TOKENTYPE_NEWLINE){
            continue;
        }
        /* End of file */
        else if(tk->type==LS_TOKENTYPE_EOF){
            break;
        }
        /* If token is a preprocessor precursor */
        else if(LSToken_isSign(tk, '.')){
            /* TODO */
        }
        /* May be a label definition */
        else if(tk->type==LS_TOKENTYPE_IDENTIFIER){
            LSTokener_fetch(&parser->tkr);
            
            /* Its a label definition */
            if(LSToken_isSign(tk, ':')){
                continue;
            }
        }
        /* Is a instruction precursor */
        else if(tk->type==LS_TOKENTYPE_MNEMONIC){
            LSMnemonic *mne = tk->data.mne;
            Int size = 0;
            LSsymInstruction instr;
            Throw(
                LSExp_fetchInstruction(parser, &instr, mne, &size)
            );
            
            /* Encodes current instruction */
            LSEnc_writeInstruction(parser->out_file, &instr);
            
            parser->encode_address_program += size;
            parser->encode_address_binary += size;
        }
        /* Undentified command */
        else{
            Error(1);
        }
        
        // Test code
        LSToken_print(tk);
        printf("#!!!! Encoder at adr: %d\n", parser->encode_address_program);
    }
    return 0;
}

Int LSParser_parsesrc_(LSParser *parser, LSFile *file){
    /* Process and encode all the files to binary, while has file in stack */
    parser->out_file = LSWbuff_openUserFile("output.o");
    
    /* Process - Phase 1 */
    LSParser_pushFile_(parser, file);
    do{
        Throw(
            LSParser_process_file_(parser)
        );
        LSParser_popFile_(parser);
    }while(parser->file_i);
    printf("\n");
    /* Encode - Phase 2 */
    LSParser_pushFile_(parser, file);
    do{
        Throw(
            LSParser_encode_file_(parser)
        );
        LSParser_popFile_(parser);
    }while(parser->file_i);
    
    /* End of Src Compilation */
    LSWbuff_close(parser->out_file);
    return 0;
}

Int LSParser_init(LSParser *parser){
    parser->parsing = TRUE;
    Throw(
        LSParser_parsesrc_(parser, parser->src_files[0])
    );
    
    return 0;
}


#endif
