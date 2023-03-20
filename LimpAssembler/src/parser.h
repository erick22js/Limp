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
    LSsymLitdef *predef_first;
    LSsymLitdef *predef_last;
    LSsymLitdef *const_first;
    LSsymLitdef *const_last;
    
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

Bool LSParser_hasPredef(LSParser *parser, Char* name){
	LSsymLitdef *cpredef = parser->predef_first;
	while(cpredef){
		if(Str_equal(cpredef->name, name)){
			return TRUE;
		}
		cpredef = cpredef->next;
	}
	return FALSE;
}

Bool LSParser_hasConst(LSParser *parser, Char* name){
	LSsymLitdef *cconst = parser->const_first;
	while(cconst){
		if(Str_equal(cconst->name, name)){
			return TRUE;
		}
		cconst = cconst->next;
	}
	return FALSE;
}

Bool LSParser_hasSymbol(LSParser *parser, Char* name){
	return LSParser_hasLabel(parser, name)||LSParser_hasPredef(parser, name)||LSParser_hasConst(parser, name);
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

Uint32 LSParser_getPredef(LSParser *parser, Char* name){
	LSsymLitdef *cpredef = parser->predef_first;
	while(cpredef){
		if(Str_equal(cpredef->name, name)){
			return cpredef->value.data.u32;
		}
		cpredef = cpredef->next;
	}
	return 0;
}

Uint32 LSParser_getConst(LSParser *parser, Char* name){
	LSsymLitdef *cconst = parser->const_first;
	while(cconst){
		if(Str_equal(cconst->name, name)){
			return cconst->value.data.u32;
		}
		cconst = cconst->next;
	}
	return 0;
}

Uint32 LSParser_getSymbol(LSParser *parser, Char* name){
	if(LSParser_hasLabel(parser, name)){
		return LSParser_getLabel(parser, name);
	}
	if(LSParser_hasPredef(parser, name)){
		return LSParser_getPredef(parser, name);
	}
	if(LSParser_hasConst(parser, name)){
		return LSParser_getConst(parser, name);
	}
}


LSFile *LSParser_getCurrentFile(LSParser *parser){
	return parser->files[parser->file_i-1];
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
        parser->tkr.preview = FALSE;
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
            LSTokener_fetch(&parser->tkr);
            
            /* Must be a preprocessor identifier */
            if(tk->type!=LS_TOKENTYPE_IDENTIFIER){
				/* TODO: Throw Exception => Expected a preprocessor name */
				Error(1);
            }
            
            /* Must be a valid preprocessor */
            /* PROC: Predefine a literal with name in program */
            if(LSToken_isIdentifier(tk, "predef")){
				LSTokener_fetch(&parser->tkr);
				
				if(tk->type!=LS_TOKENTYPE_IDENTIFIER){
					/* TODO: Throw Exception => Expected a identifier */
					Error(1);
				}
				Char* identifier = tk->data.string;
				
				if(LSParser_hasSymbol(parser, identifier)){
					/* TODO: Throw Exception => Symbol with same name already defined */
					Error(1);
				}
				
				/* Evals next expression and attribs to symbol */
				LSsymValue res = {0, 0};
				Throw(
					LSExp_fetchExpression(parser, &res)
				);
				
				LSsymLitdef *literal = Calloc(sizeof(LSsymLitdef));
                literal->name = identifier;
                literal->value = res;
                LLPush(parser->predef_first, parser->predef_last, literal);
            }
            /* PROC: Define a value with name in program */
            else if(LSToken_isIdentifier(tk, "const")){}
            /* PROC: Imports a assembler module */
            else if(LSToken_isIdentifier(tk, "import")){
				
            }
            /* PROC: Includes a external file */
            else if(LSToken_isIdentifier(tk, "include")){
				LSTokener_fetch(&parser->tkr);
				
				if(tk->type!=LS_TOKENTYPE_STRING){
					/* TODO: Throw Exception => Expected a string relative path */
					Error(1);
				}
				Char* relpath = tk->data.string;
				
				Char path[LS_MAXH_PATHSIZE];
				LSDh_zero(path);
				LSDh_copy(path, LSParser_getCurrentFile(parser)->path);
				LSDh_up(path);
				LSDh_cd(path, relpath);
				
				printf("Opening file in path: '%s'\n", path);
				LSFile *file = LSLexer_openPath(path);
				
				LSParser_pushFile_(parser, file);
				continue;
            }
            else{
				/* TODO: Throw Exception => Expected a valid preprocessor name */
				Error(1);
            }
            /* Suspends processing until end of line instruction */
            while(!LSToken_endOfArgumentList(tk)){
                LSTokener_fetch(&parser->tkr);
            }
        }
        /* May be a label definition */
        else if(tk->type==LS_TOKENTYPE_IDENTIFIER){
            Char* identifier = tk->data.string;
            LSTokener_fetch(&parser->tkr);
            
            /* Its a label definition */
            if(LSToken_isSign(tk, ':')){
				/* Cannot have any other symbol with the same name */
				if(LSParser_hasSymbol(parser, identifier)){
					/* TODO: Throw Exception => Symbol with same name already defined */
					Error(1);
				}
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
            LSTokener_fetch(&parser->tkr);
            
            /* Must be a preprocessor identifier */
            if(tk->type!=LS_TOKENTYPE_IDENTIFIER){
				/* TODO: Throw Exception => Expected a preprocessor name */
				Error(1);
            }
            
            /* Must be a valid preprocessor */
            /* PROC: Predefine a literal with name in program */
            if(LSToken_isIdentifier(tk, "predef")){}
            /* PROC: Define a value with name in program */
            else if(LSToken_isIdentifier(tk, "const")){
				LSTokener_fetch(&parser->tkr);
				
				if(tk->type!=LS_TOKENTYPE_IDENTIFIER){
					/* TODO: Throw Exception => Expected a identifier */
					Error(1);
				}
				Char* identifier = tk->data.string;
				
				if(LSParser_hasSymbol(parser, identifier)){
					/* TODO: Throw Exception => Symbol with same name already defined */
					Error(1);
				}
				
				/* Evals next expression and attribs to symbol */
				LSsymValue res = {0, 0};
				Throw(
					LSExp_fetchExpression(parser, &res)
				);
				
				LSsymLitdef *literal = Calloc(sizeof(LSsymLitdef));
                literal->name = identifier;
                literal->value = res;
                LLPush(parser->const_first, parser->const_last, literal);
            }
            /* PROC: Imports a assembler module */
            else if(LSToken_isIdentifier(tk, "import")){
				
            }
            /* PROC: Includes a external file */
            else if(LSToken_isIdentifier(tk, "include")){
				LSTokener_fetch(&parser->tkr);
				
				if(tk->type!=LS_TOKENTYPE_STRING){
					/* TODO: Throw Exception => Expected a string relative path */
					Error(1);
				}
				Char* relpath = tk->data.string;
				
				Char path[LS_MAXH_PATHSIZE];
				LSDh_zero(path);
				LSDh_copy(path, LSParser_getCurrentFile(parser)->path);
				LSDh_up(path);
				LSDh_cd(path, relpath);
				
				printf("Opening file in path: '%s'\n", path);
				LSFile *file = LSLexer_openPath(path);
				
				LSParser_pushFile_(parser, file);
				continue;
            }
            else{
				/* TODO: Throw Exception => Expected a valid preprocessor name */
				Error(1);
            }
            /* Suspends processing until end of line instruction */
            while(!LSToken_endOfArgumentList(tk)){
                LSTokener_fetch(&parser->tkr);
            }
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
    
    Uint32 errcode = LSParser_parsesrc_(parser, parser->src_files[0]);
    if(errcode){
		printf("Error in src file '%s', at line %d and offset %d", parser->files[parser->file_i-1]->path, LSLexer_line(parser->files[parser->file_i-1]), LSLexer_offset(parser->files[parser->file_i-1]));
		return errcode;
    }
    
    return 0;
}


#endif
