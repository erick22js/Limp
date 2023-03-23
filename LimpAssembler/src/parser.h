#ifndef limps_parser_h
#define limps_parser_h


struct LSParser;
typedef struct LSParser LSParser;


#include "tokener.h"
#include "symbols.h"
#include "encoder.h"
#include "rbuffer.h"


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
    struct{
    	LSFile *file;
    	Bool internal;
    }files[LS_MAXPARSER_FILEDEPTH];
    Int file_i;
    LSFile *src_files[LS_MAXPARSER_SRCFILES];
    Int src_files_i;
    LSFile *out_file;
    
    /* Parsing symbols tree */
    LSsymOnce *once_first;
    LSsymOnce *once_last;
    LSsymScope *scope_master; /* The first scope */
    LSsymScope *scope_in; /* The scope wich parser is in */
    LSsymScope *scope_current; /* The scope wich parser uses as reference for retrieving next scope */
    LSsymScope *scope_first;
    LSsymScope *scope_last;
    
}LSParser;
LSDySPtr lsgpsr_path_p = 0;

Bool LSParser_hasLabel(LSsymScope *scope, Char* name){
	LSsymLabel *clabel = scope->label_first;
	while(clabel){
		if(Str_equal(clabel->name, name)){
			return TRUE;
		}
		clabel = clabel->next;
	}
	return FALSE;
}

Bool LSParser_hasPredef(LSsymScope *scope, Char* name){
	LSsymLitdef *cpredef = scope->predef_first;
	while(cpredef){
		if(Str_equal(cpredef->name, name)){
			return TRUE;
		}
		cpredef = cpredef->next;
	}
	return FALSE;
}

Bool LSParser_hasConst(LSsymScope *scope, Char* name){
	LSsymLitdef *cconst = scope->const_first;
	while(cconst){
		if(Str_equal(cconst->name, name)){
			return TRUE;
		}
		cconst = cconst->next;
	}
	return FALSE;
}

Bool LSParser_hasSymbol(LSParser *parser, Char* name, Bool all_scopes){
	LSsymScope *actscope = parser->scope_in;
	while(actscope){
		Bool has = LSParser_hasLabel(actscope, name)||LSParser_hasPredef(actscope, name)||LSParser_hasConst(actscope, name);
		if(has){
			return TRUE;
		}
		actscope = actscope->father;
		if(!all_scopes){
			break;
		}
	}
	return FALSE;
}

Uint32 LSParser_getLabel(LSsymScope *scope, Char* name){
	LSsymLabel *clabel = scope->label_first;
	while(clabel){
		if(Str_equal(clabel->name, name)){
			return clabel->address;
		}
		clabel = clabel->next;
	}
	return 0;
}

Uint32 LSParser_getPredef(LSsymScope *scope, Char* name){
	LSsymLitdef *cpredef = scope->predef_first;
	while(cpredef){
		if(Str_equal(cpredef->name, name)){
			return cpredef->value.data.u32;
		}
		cpredef = cpredef->next;
	}
	return 0;
}

Uint32 LSParser_getConst(LSsymScope *scope, Char* name){
	LSsymLitdef *cconst = scope->const_first;
	while(cconst){
		if(Str_equal(cconst->name, name)){
			return cconst->value.data.u32;
		}
		cconst = cconst->next;
	}
	return 0;
}

Uint32 LSParser_getSymbol(LSParser *parser, Char* name){
	LSsymScope *actscope = parser->scope_in;
	while(actscope){
		if(LSParser_hasLabel(actscope, name)){
			return LSParser_getLabel(actscope, name);
		}
		if(LSParser_hasPredef(actscope, name)){
			return LSParser_getPredef(actscope, name);
		}
		if(LSParser_hasConst(actscope, name)){
			return LSParser_getConst(actscope, name);
		}
		actscope = actscope->father;
	}
	return 0;
}


LSFile *LSParser_getCurrentFile(LSParser *parser){
	return parser->files[parser->file_i-1].file;
}


Bool LSParser_hasOnce(LSParser *parser, Char* id){
	LSsymOnce *once = parser->once_first;
	
	while(once){
		if(Str_equal(id, once->path)){
			return TRUE;
		}
		once = once->next;
	}
	
	return FALSE;
}


/*
    UTILITY FUNCTIONS
*/

Bool LSParser_pushFile_(LSParser *parser, LSFile *file, Bool internal){
    if(parser->file_i==LS_MAXPARSER_FILEDEPTH){
        return FALSE;
    }
    LSLexer_rewind(file);
    parser->files[parser->file_i].file = file;
    parser->files[parser->file_i].internal = internal;
    parser->file_i++;
    parser->tkr.file = file;
    return TRUE;
}

Bool LSParser_popFile_(LSParser *parser){
    if(parser->file_i){
        parser->file_i--;
        if(parser->file_i){
            LSLexer_close(parser->files[parser->file_i].file);
        }
        parser->files[parser->file_i].file = NULL;
        parser->tkr.file = parser->files[parser->file_i-1].file;
        parser->tkr.preview = FALSE;
        return TRUE;
    }
    else{
        return FALSE;
    }
}

void LSParser_pushScope(LSParser *parser, Char* name){
	LSsymScope* scope = Calloc(sizeof(LSsymScope));
	scope->name = name;
	scope->adr = parser->process_address_program;
	LLPush(parser->scope_first, parser->scope_last, scope);
	
	scope->father = parser->scope_in;
	parser->scope_in = scope;
	if(parser->scope_current){
		//printf("Entering from scope '%s' to '%s'\n", parser->scope_current->name, name);
		parser->scope_current->next = scope;
	}
	parser->scope_current = scope;
}

void LSParser_enterScope(LSParser *parser){
	LSsymScope* scope = parser->scope_current->next;
	
	//printf("Entering from scope '%s' to '%s'\n", parser->scope_current->name, scope->name);
	scope->father = parser->scope_in;
	parser->scope_in = scope;
	parser->scope_current = scope;
}

Bool LSParser_leaveScope(LSParser *parser){
	if(parser->scope_in->father){
		//printf("Leaving from scope '%s' to '%s'\n", parser->scope_current->name, parser->scope_in->father->name);
		parser->scope_in = parser->scope_in->father;
		return TRUE;
	}
	return FALSE;
}

void LSParser_rewindScope(LSParser *parser){
	parser->scope_in = parser->scope_master;
	parser->scope_current = parser->scope_master;
	//printf("Rewinding to scope '%s'\n", parser->scope_current->name);
	parser->once_first = NULL;
	parser->once_last = NULL;
}



/**
	PREPROCESSOR HANDLING
*/

LSsymDefine *LSParser_getDefined(LSParser *parser, Char* name, Bool all_scopes){
	LSsymScope *actscope = parser->scope_in;
	while(actscope){
		LSsymDefine *cdef = actscope->def_first;
		while(cdef){
			if(Str_equal(cdef->name, name)){
				return cdef;
			}
			cdef = cdef->next;
		}
		actscope = actscope->father;
		if(!all_scopes){
			break;
		}
	}
	return NULL;
}

Int LSParser_openDefinition(LSParser *parser, LSsymDefine *define){
	if(define->src_len){
		LSFile* file = LSLexer_openBuffer(define->src, define->src_len, LSParser_getCurrentFile(parser)->path);
		LSParser_pushFile_(parser, file, TRUE);
	}
	return 0;
}

Int LSParser_fetchToken(LSParser *parser, Bool ignore_defines){
	Throw(
		LSTokener_fetch(&parser->tkr)
	);/*
	if(parser->tkr.tk.type==LS_TOKENTYPE_IDENTIFIER&&!ignore_defines){
		LSsymDefine *define = LSParser_getDefined(parser, parser->tkr.tk.data.string, TRUE);
		if(define){
			LSParser_openDefinition(parser, define);
			Throw(
				LSTokener_fetch(&parser->tkr)
			);
		}
	}
	else if(parser->tkr.tk.type==LS_TOKENTYPE_EOF){
		if(parser->file_i>1){
			LSParser_popFile_(parser);
			Throw(
				LSTokener_fetch(&parser->tkr)
			);
		}
	}*/
	return 0;
}

Int LSParser_previewToken(LSParser *parser, Bool ignore_defines){
	Throw(
		LSTokener_preview(&parser->tkr)
	);/*
	parser->tkr.preview = FALSE;
	if(parser->tkr.tk.type==LS_TOKENTYPE_IDENTIFIER&&!ignore_defines){
		LSsymDefine *define = LSParser_getDefined(parser, parser->tkr.tk.data.string, TRUE);
		if(define){
			LSParser_openDefinition(parser, define);
			Throw(
				LSTokener_preview(&parser->tkr)
			);
		}
	}
	else if(parser->tkr.tk.type==LS_TOKENTYPE_EOF){
		if(parser->file_i>1){
			LSParser_popFile_(parser);
			Throw(
				LSTokener_preview(&parser->tkr)
			);
		}
	}*/
	return 0;
}


#include "expression.h"


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
        Throw(
			LSParser_fetchToken(parser, FALSE)
		);
        
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
            Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            
            /* Must be a preprocessor identifier */
            if(tk->type!=LS_TOKENTYPE_IDENTIFIER){
				Error(LS_ERR_EXPECTPREPNAME);
            }
            
            /* Must be a valid preprocessor */
            /* PROC: Predefine a literal with name in program */
            if(LSToken_isIdentifier(tk, "predef")){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				
				if(tk->type!=LS_TOKENTYPE_IDENTIFIER){
					Error(LS_ERR_EXPECTIDENTIFIER);
				}
				Char* identifier = tk->data.string;
				
				if(LSParser_hasSymbol(parser, identifier, FALSE)){
					Error(LS_ERR_SYMBOLALREADYDEF);
				}
				
				/* Evals next expression and attribs to symbol */
				LSsymValue res = {0, 0};
				Throw(
					LSExp_fetchExpression(parser, &res)
				);
				
				LSsymLitdef *literal = Calloc(sizeof(LSsymLitdef));
                literal->name = identifier;
                literal->value = res;
                LLPush(parser->scope_in->predef_first, parser->scope_in->predef_last, literal);
            }
            /* PROC: Define a value with name in program */
            else if(LSToken_isIdentifier(tk, "const")){}
            /* PROC: Define a src with name */
            else if(LSToken_isIdentifier(tk, "define")){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				
				if(tk->type!=LS_TOKENTYPE_IDENTIFIER){
					Error(LS_ERR_EXPECTIDENTIFIER);
				}
				Char* identifier = tk->data.string;
				
				Uint32 begin = LSLexer_tell(LSParser_getCurrentFile(parser));
				/* Retrieves the characters for symbol definition */
				while(!LSToken_endOfArgumentList(tk)){
					Throw(
						LSParser_fetchToken(parser, TRUE)
					);
				}
				Uint32 end = LSLexer_tell(LSParser_getCurrentFile(parser))-1;
				Uint32 length = end-begin;
				
				Char* src = Calloc(length)+1;
				LSLexer_seekSet(LSParser_getCurrentFile(parser), begin);
				LSLexer_read(LSParser_getCurrentFile(parser), src, length);
				
				LSsymDefine *define = Calloc(sizeof(LSsymDefine));
				define->name = identifier;
				define->src = src;
				define->src_len = length;
				LLPush(parser->scope_in->def_first, parser->scope_in->def_last, define);
            }
            /* PROC: Imports a assembler module */
            else if(LSToken_isIdentifier(tk, "import")){
				
            }
            /* PROC: Includes a external file */
            else if(LSToken_isIdentifier(tk, "include")){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				
				if(tk->type!=LS_TOKENTYPE_STRING){
					Error(LS_ERR_EXPECTSTRING);
				}
				Char* relpath = tk->data.string;
				
				Char path[LS_MAXH_PATHSIZE];
				LSDh_zero(path);
				LSDh_copy(path, LSParser_getCurrentFile(parser)->path);
				LSDh_up(path);
				LSDh_cd(path, relpath);
				
				//printf("Opening file in path: '%s'\n", path);
				LSFile *file = LSLexer_openPath(path);
				
				LSParser_pushFile_(parser, file, FALSE);
				continue;
            }
            /* PROC: Includes a external binary file */
            else if(LSToken_isIdentifier(tk, "bin")){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				
				if(tk->type!=LS_TOKENTYPE_STRING){
					Error(LS_ERR_EXPECTSTRING);
				}
				Char* relpath = tk->data.string;
				
				Char path[LS_MAXH_PATHSIZE];
				LSDh_zero(path);
				LSDh_copy(path, LSParser_getCurrentFile(parser)->path);
				LSDh_up(path);
				LSDh_cd(path, relpath);
				
				LSFile *file = LSRbuff_openUserFile(path);
				Uint32 size = LSRbuff_getSize(file);
				parser->process_address_program += file;
				parser->process_address_binary += file;
				LSRbuff_close(file);
				continue;
            }
            /* PROC: Sets this file to process only a once time */
            else if(LSToken_isIdentifier(tk, "once")||LSToken_isIdentifier(tk, "notonce")){
				Bool has_cond = LSToken_isIdentifier(tk, "once");
				Throw(
					LSParser_previewToken(parser, FALSE)
				);
				
				Char* id;
				if(tk->type==LS_TOKENTYPE_STRING){
					id = tk->data.string;
				}
				else{
					id = LSParser_getCurrentFile(parser)->path;
				}
				
				if(LSParser_hasOnce(parser, id)==has_cond){
					break;
				}
				else{
					LSsymOnce *once = Calloc(sizeof(LSsymOnce));
					once->path = LSDyS_wrapMemCmp((void*)id, LS_MAX_PATHSIZE, &lsgpsr_path_p, Str_equal);
					LLPush(parser->once_first, parser->once_last, once);
				}
            }
            /* PROC: Defines a symbol for once files execution control */
            else if(LSToken_isIdentifier(tk, "defonce")){
				Throw(
					LSParser_previewToken(parser, FALSE)
				);
				
				if(tk->type!=LS_TOKENTYPE_STRING){
					Error(LS_ERR_EXPECTSTRING);
				}
				Char* id = tk->data.string;
				
				if(!LSParser_hasOnce(parser, id)){
					LSsymOnce *once = Calloc(sizeof(LSsymOnce));
					once->path = LSDyS_wrapMemCmp((void*)id, LS_MAX_PATHSIZE, &lsgpsr_path_p, Str_equal);
					LLPush(parser->once_first, parser->once_last, once);
				}
            }
            /* PROC: Enters a scope */
            else if(LSToken_isIdentifier(tk, "scope")){
				Throw(
					LSParser_previewToken(parser, FALSE)
				);
				
				Char* name = "";
				if(tk->type==LS_TOKENTYPE_IDENTIFIER){
					Throw(
						LSParser_fetchToken(parser, FALSE)
					);
					name = tk->data.string;
				}
				
				LSParser_pushScope(parser, name);
            }
            /* PROC: Enters a scope */
            else if(LSToken_isIdentifier(tk, "endscope")){
				if(!LSParser_leaveScope(parser)){
					Error(LS_ERR_OUTGLOBAL);
				}
            }
            /* PROC: inserts raw bytes */
            else if(LSToken_isIdentifier(tk, "d32")|LSToken_isIdentifier(tk, "d16")|LSToken_isIdentifier(tk, "d8")){
				Uint32 symbols = 1;
				while(!LSToken_endOfArgumentList(tk)){
					if(LSToken_isSign(tk, ',')){
						symbols++;
					}
					Throw(
						LSParser_fetchToken(parser, TRUE)
					);
				}
				if(LSToken_isIdentifier(tk, "d32")){
					symbols *= 4;
				}
				else if(LSToken_isIdentifier(tk, "d16")){
					symbols *= 2;
				}
				parser->process_address_program += symbols;
				parser->process_address_binary += symbols;
            }
            /* PROC: inserts text bytes on binary */
            else if(LSToken_isIdentifier(tk, "text")){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				
				if(tk->type!=LS_TOKENTYPE_STRING){
					Error(LS_ERR_EXPECTSTRING);
				}
				Char* cstr = tk->data.string;
				
				Int len = Str_length(cstr);
				
				parser->process_address_program += len;
				parser->process_address_binary += len;
            }
            /* PROC: aligns to the dword boundary (4-bytes) */
            else if(LSToken_isIdentifier(tk, "align")){
				parser->process_address_program = (parser->process_address_program&(~3))+(parser->process_address_program&3?4:0);
				parser->process_address_binary = (parser->process_address_binary&(~3))+(parser->process_address_binary&3?4:0);
            }
            /* PROC: sets the current program address in binary */
            else if(LSToken_isIdentifier(tk, "adr")){
				LSsymValue res = {0, 0};
				Throw(
					LSExp_fetchExpression(parser, &res)
				);
				parser->process_address_program = res.data.u32;
            }
            /* PROC: ends the current file preprocessing */
            else if(LSToken_isIdentifier(tk, "break")){
            	break;
            }
            else{
				Error(LS_ERR_EXPECTVALIDPREPNAME);
            }
            /* Suspends processing until end of line instruction */
            while(!LSToken_endOfArgumentList(tk)){
                Throw(
					LSParser_fetchToken(parser, TRUE)
				);
            }
        }
        /* May be a label definition */
        else if(tk->type==LS_TOKENTYPE_IDENTIFIER){
            Char* identifier = tk->data.string;
            Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            
            /* Its a label definition */
            if(LSToken_isSign(tk, ':')){
				/* Cannot have any other symbol with the same name */
				if(LSParser_hasSymbol(parser, identifier, FALSE)){
					Error(LS_ERR_SYMBOLALREADYDEF);
				}
                LSsymLabel *label = Calloc(sizeof(LSsymLabel));
                label->name = identifier;
                label->address = parser->process_address_program;
                LLPush(parser->scope_in->label_first, parser->scope_in->label_last, label);
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
                Throw(
					LSParser_fetchToken(parser, TRUE)
				);
            }
        }
        /* Undentified command */
        else{
            
        }
        
        // Test code
        //LSToken_print(tk);
        //printf("#@@@@ Processor at adr: %d\n", parser->process_address_program);
    }
    return 0;
}

Int LSParser_encode_file_(LSParser *parser){
    LSToken *tk = &parser->tkr.tk;
    parser->tkr.ended = FALSE;
    
    /* Process the current file until reach the end */
    while(!parser->tkr.ended){
        Throw(
			LSParser_fetchToken(parser, FALSE)
		);
        
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
            Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            
            /* Must be a preprocessor identifier */
            if(tk->type!=LS_TOKENTYPE_IDENTIFIER){
				Error(LS_ERR_EXPECTPREPNAME);
            }
            
            /* Must be a valid preprocessor */
            /* PROC: Predefine a literal with name in program */
            if(LSToken_isIdentifier(tk, "predef")){}
            /* PROC: Define a value with name in program */
            else if(LSToken_isIdentifier(tk, "const")){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				
				if(tk->type!=LS_TOKENTYPE_IDENTIFIER){
					Error(LS_ERR_EXPECTIDENTIFIER);
				}
				Char* identifier = tk->data.string;
				
				if(LSParser_hasSymbol(parser, identifier, FALSE)){
					Error(LS_ERR_SYMBOLALREADYDEF);
				}
				
				/* Evals next expression and attribs to symbol */
				LSsymValue res = {0, 0};
				Throw(
					LSExp_fetchExpression(parser, &res)
				);
				
				LSsymLitdef *literal = Calloc(sizeof(LSsymLitdef));
                literal->name = identifier;
                literal->value = res;
                LLPush(parser->scope_in->const_first, parser->scope_in->const_last, literal);
            }
            /* PROC: Define a src with name */
            else if(LSToken_isIdentifier(tk, "define")){}
            /* PROC: Imports a assembler module */
            else if(LSToken_isIdentifier(tk, "import")){
				
            }
            /* PROC: Includes a external file */
            else if(LSToken_isIdentifier(tk, "include")){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				
				if(tk->type!=LS_TOKENTYPE_STRING){
					Error(LS_ERR_EXPECTSTRING);
				}
				Char* relpath = tk->data.string;
				
				Char path[LS_MAXH_PATHSIZE];
				LSDh_zero(path);
				LSDh_copy(path, LSParser_getCurrentFile(parser)->path);
				LSDh_up(path);
				LSDh_cd(path, relpath);
				
				//printf("Opening file in path: '%s'\n", path);
				LSFile *file = LSLexer_openPath(path);
				
				LSParser_pushFile_(parser, file, FALSE);
				continue;
            }
            /* PROC: Includes a external binary file */
            else if(LSToken_isIdentifier(tk, "bin")){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				
				if(tk->type!=LS_TOKENTYPE_STRING){
					Error(LS_ERR_EXPECTSTRING);
				}
				Char* relpath = tk->data.string;
				
				Char path[LS_MAXH_PATHSIZE];
				LSDh_zero(path);
				LSDh_copy(path, LSParser_getCurrentFile(parser)->path);
				LSDh_up(path);
				LSDh_cd(path, relpath);
				
				LSFile *file = LSRbuff_openUserFile(path);
				Uint32 size = LSRbuff_getSize(file);
				
				while(size){
					LSWbuff_write8(parser->out_file, LSRbuff_read8(file));
					size--;
				}
				
				parser->encode_address_program += file;
				parser->encode_address_binary += file;
				
				LSRbuff_close(file);
				continue;
            }
            /* PROC: Defines file for be include only a once time */
            else if(LSToken_isIdentifier(tk, "once")||LSToken_isIdentifier(tk, "notonce")){
				Bool has_cond = LSToken_isIdentifier(tk, "once");
				Throw(
					LSParser_previewToken(parser, FALSE)
				);
				
				Char* id;
				if(tk->type==LS_TOKENTYPE_STRING){
					id = tk->data.string;
				}
				else{
					id = LSParser_getCurrentFile(parser)->path;
				}
				
				if(LSParser_hasOnce(parser, id)==has_cond){
					break;
				}
				else{
					LSsymOnce *once = Calloc(sizeof(LSsymOnce));
					once->path = LSDyS_wrapMemCmp((void*)id, LS_MAX_PATHSIZE, &lsgpsr_path_p, Str_equal);
					LLPush(parser->once_first, parser->once_last, once);
				}
            }
            /* PROC: Defines a symbol for once files execution control */
            else if(LSToken_isIdentifier(tk, "defonce")){
				Throw(
					LSParser_previewToken(parser, FALSE)
				);
				
				if(tk->type!=LS_TOKENTYPE_STRING){
					Error(LS_ERR_EXPECTSTRING);
				}
				Char* id = tk->data.string;
				
				if(!LSParser_hasOnce(parser, id)){
					LSsymOnce *once = Calloc(sizeof(LSsymOnce));
					once->path = LSDyS_wrapMemCmp((void*)id, LS_MAX_PATHSIZE, &lsgpsr_path_p, Str_equal);
					LLPush(parser->once_first, parser->once_last, once);
				}
            }
            /* PROC: Enters a scope */
            else if(LSToken_isIdentifier(tk, "scope")){
				LSParser_enterScope(parser);
            }
            /* PROC: Enters a scope */
            else if(LSToken_isIdentifier(tk, "endscope")){
				if(!LSParser_leaveScope(parser)){
					Error(LS_ERR_OUTGLOBAL);
				}
            }
            /* PROC: inserts raw bytes */
            else if(LSToken_isIdentifier(tk, "d32")|LSToken_isIdentifier(tk, "d16")|LSToken_isIdentifier(tk, "d8")){
				Uint32 type = LSToken_isIdentifier(tk, "d32")?2:LSToken_isIdentifier(tk, "d16")?1:0;
				Uint32 symbols = 1;
				Bool expecting = TRUE;
				
				while(!LSToken_endOfArgumentList(tk)||expecting){
					LSsymValue res = {0, 0};
					Throw(
						LSExp_fetchExpression(parser, &res)
					);
					if(type==2){
						LSWbuff_write32(parser->out_file, res.data.u32);
					}
					else if(type==1){
						LSWbuff_write16(parser->out_file, res.data.u32);
					}
					else{
						LSWbuff_write8(parser->out_file, res.data.u32);
					}
					expecting = FALSE;
					Throw(
						LSParser_previewToken(parser, FALSE)
					);
					if(LSToken_isSign(tk, ',')){
						Throw(
							LSParser_fetchToken(parser, FALSE)
						);
						symbols++;
						expecting = TRUE;
					}
				}
				
				if(type==2){
					symbols *= 4;
				}
				else if(type==1){
					symbols *= 2;
				}
				parser->encode_address_program += symbols;
				parser->encode_address_binary += symbols;
            }
            /* PROC: inserts text bytes on binary */
            else if(LSToken_isIdentifier(tk, "text")){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				
				if(tk->type!=LS_TOKENTYPE_STRING){
					Error(LS_ERR_EXPECTSTRING);
				}
				Char* cstr = tk->data.string;
				
				Uint8* tstr = (Uint8*)cstr;
				Uint32 length = tk->length;
				while(length){
					LSWbuff_write8(parser->out_file, (*tstr));
					tstr++;
					length--;
				}
				
				Int len = tk->length;
				
				parser->encode_address_program += len;
				parser->encode_address_binary += len;
            }
            /* PROC: aligns to the dword boundary (4-bytes) */
            else if(LSToken_isIdentifier(tk, "align")){
				parser->encode_address_program = (parser->encode_address_program&(~3))+(parser->encode_address_program&3?4:0);
				parser->encode_address_binary = (parser->encode_address_binary&(~3))+(parser->encode_address_binary&3?4:0);
				LSWbuff_seekBegin(parser->out_file, parser->encode_address_binary);
            }
            /* PROC: sets the current program address in binary */
            else if(LSToken_isIdentifier(tk, "adr")){
				LSsymValue res = {0, 0};
				Throw(
					LSExp_fetchExpression(parser, &res)
				);
				parser->encode_address_program = res.data.u32;
            }
            /* PROC: ends the current file preprocessing */
            else if(LSToken_isIdentifier(tk, "break")){
            	break;
            }
            else{
				Error(LS_ERR_EXPECTVALIDPREPNAME);
            }
            /* Suspends processing until end of line instruction */
            while(!LSToken_endOfArgumentList(tk)){
                Throw(
					LSParser_fetchToken(parser, TRUE)
				);
            }
        }
        /* May be a label definition */
        else if(tk->type==LS_TOKENTYPE_IDENTIFIER){
            Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            
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
            Error(LS_ERR_UNEXPECTTK);
        }
        
        // Test code
        //LSToken_print(tk);
        //printf("#!!!! Encoder at adr: %d\n", parser->encode_address_program);
    }
    return 0;
}

Int LSParser_parsesrc_(LSParser *parser, LSFile *file){
    /* Process and encode all the files to binary, while has file in stack */
    parser->out_file = LSWbuff_openUserFile("output.o");
    
    /* Process - Phase 1 */
    LSParser_pushFile_(parser, file, FALSE);
    LSParser_pushScope(parser, "#Global");
    parser->scope_master = parser->scope_in;
    do{
        Throw(
            LSParser_process_file_(parser)
        );
        LSParser_popFile_(parser);
    }while(parser->file_i);
    printf("\n");
    /* Encode - Phase 2 */
    LSParser_pushFile_(parser, file, FALSE);
    LSParser_rewindScope(parser);
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
		printf("Compilation fail :-(\n");
		printf("Error in src file '%s', at line %d and offset %d\nCode %d: \"%s\"", parser->files[parser->file_i-1].file->path, LSLexer_line(parser->files[parser->file_i-1].file), parser->tkr.last.offset, errcode, LSErr_msgFromCode(errcode));
		return errcode;
    }
    else{
		printf("Compilation success!\n");
    }
    
    return 0;
}


#endif
