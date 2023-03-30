#ifndef limps_expression_h
#define limps_expression_h

#include "tokener.h"
#include "symbols.h"
#include "parser.h"


#define LI_MAXARGUMENTS 4


/**
    SYMBOL ENCODING FUNCTIONS
*/

Int LSExp_leadDescriptor(LSToken *tk, LSKeywordType desctype, Uint32 *outv){
    if(tk->type==LS_TOKENTYPE_KEYWORD){
        if(tk->data.kw->type&desctype){
            *outv = tk->data.kw->code;
        }
        else{
            Error(LS_ERR_INVALIDDESC);
        }
    }
    else{
        Error(LS_ERR_EXPECTDESC);
    }
    return 0;
}

Int LSExp_getInstructionSize(LSParser *parser, LSMnemonic *mne, Int *out_size){
    LSToken *tk = &parser->tkr.tk;
    *out_size = 4;
    Uint32 value = 0;
    
    Throw(
		LSParser_previewToken(parser, FALSE)
	);
    if(LSToken_isSign(tk, '.')){
        if(mne->type==LS_INSTRTYPE_IR){
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSExp_leadDescriptor(tk, LS_KWTYPE_IMODE, &value)
            );
        }
        else if((mne->type==LS_INSTRTYPE_ADI)||(mne->type==LS_INSTRTYPE_CDI)){
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSExp_leadDescriptor(tk, LS_KWTYPE_CONDITION, &value)
            );
            /* Check for Register Operand Specifier */
            Throw(
				LSParser_previewToken(parser, FALSE)
			);
            if(LSToken_isSign(tk, '<')){
                Throw(
					LSParser_fetchToken(parser, FALSE)
				);
                Throw(
					LSParser_fetchToken(parser, FALSE)
				);
                
                if((tk->type==LS_TOKENTYPE_KEYWORD)&&(tk->data.kw->type&LS_KWTYPE_REGISTER)){}
                else{
                    Error(LS_ERR_EXPECTREGNAME);
                }
                
                Throw(
					LSParser_fetchToken(parser, FALSE)
				);
                if(!LSToken_isSign(tk, '>')){
                    Error(LS_ERR_EXPECTCLOSGRT);
                }
            }
            else{}
        }
        Throw(
			LSParser_previewToken(parser, FALSE)
		);
    }
    if(LSToken_isSign(tk, '.')){
        if((mne->type==LS_INSTRTYPE_AMI)||(mne->type==LS_INSTRTYPE_SI)||(mne->type==LS_INSTRTYPE_CDI)){
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSExp_leadDescriptor(tk, LS_KWTYPE_EFETCH, &value)
            );
        }
        else{
            Error(LS_ERR_EXPECTDESC);
        }
    }
    /*
    Throw(
		LSParser_fetchToken(parser, FALSE)
	);
    if(LSToken_isSign(tk, '.')){
        if(mne->type==LS_INSTRTYPE_IR){
            Throw(
                LSParser_fetchToken(parser, FALSE)
            );
            Throw(
                LSExp_leadDescriptor(tk, LS_KWTYPE_IMODE, &value)
            );
        }
        else if((mne->type==LS_INSTRTYPE_AMI)||(mne->type==LS_INSTRTYPE_SI)){
            Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSExp_leadDescriptor(tk, LS_KWTYPE_EFETCH, &value)
            );
        }
        else if(mne->type==LS_INSTRTYPE_CDI){
            Throw(
                LSParser_fetchToken(parser, FALSE)
			);
			if(tk->data.kw->type&LS_KWTYPE_EFETCH){
				Throw(
					LSExp_leadDescriptor(tk, LS_KWTYPE_EFETCH, &value)
				);
			}
			else if(tk->data.kw->type&LS_KWTYPE_CONDITION){}
			else{
				Error(LS_ERR_INVALIDDESC);
			}
        }
    }
    */
    
    if(value==3){
        (*out_size) += 4;
    }
    
    return 0;
}

Bool LSExp_compatibleTypes(LSargValue given, LSargValue base){
	if(given==base){
        return TRUE;
    }
    
    if(base==LS_ARGVALUE_IMM || base==LS_ARGVALUE_IMM32 || base==LS_ARGVALUE_IMM16 || base==LS_ARGVALUE_IMM8){
        return given==LS_ARGVALUE_IMM8 || given==LS_ARGVALUE_IMM16 || given==LS_ARGVALUE_IMM32 || given==LS_ARGVALUE_IMM;
    }
    
    if(base==LS_ARGVALUE_AMD || base==LS_ARGVALUE_VARY){
        return given!=LS_ARGVALUE_VOID;
    }
    
    return FALSE;
}


/**
    SYMBOL DECODING FUNCTIONS
*/

/* Returns zero in invalid operator */
Int LSExp_unaryOprOrder(Int opr){
	switch(opr){
		
	}
	return 0;
}

/* Returns zero in invalid operator */
Int LSExp_binaryOprOrder(Int opr){
	switch(opr){
		case '||':
			return 1;
		case '&&':
			return 2;
		case '|':
			return 3;
		case '^':
			return 4;
		case '&':
			return 5;
		case '==':case '!=':
			return 6;
		case '<':case '>':case '<=':case '>=':
			return 7;
		case '<<':case '>>':
			return 8;
		case '+':case '-':
			return 9;
		case '*':case '/':case '%':
			return 10;
	}
	return 0;
}

Int LSExp_solveBinary(LSParser *parser, LSsymValue *val1, Int opr, LSsymValue *val2, LSsymValue *res){
	res->valtype = val1->valtype>val2->valtype?val1->valtype:val2->valtype;
	switch(opr){
		case '+':{
			res->data.u32 = val1->data.u32+val2->data.u32;
		}
		break;
		case '-':{
			res->data.u32 = val1->data.u32-val2->data.u32;
		}
		break;
		case '*':{
			res->data.u32 = val1->data.u32*val2->data.u32;
		}
		break;
		case '/':{
			res->data.u32 = val1->data.u32/val2->data.u32;
		}
		break;
		case '%':{
			res->data.u32 = val1->data.u32%val2->data.u32;
		}
		break;
		case '<<':{
			res->data.u32 = val1->data.u32<<val2->data.u32;
		}
		break;
		case '>>':{
			res->data.u32 = val1->data.u32>>val2->data.u32;
		}
		break;
		case '<':{
			res->data.u32 = val1->data.u32<val2->data.u32;
		}
		break;
		case '>':{
			res->data.u32 = val1->data.u32>val2->data.u32;
		}
		break;
		case '<=':{
			res->data.u32 = val1->data.u32<=val2->data.u32;
		}
		break;
		case '>=':{
			res->data.u32 = val1->data.u32>=val2->data.u32;
		}
		break;
		case '==':{
			res->data.u32 = val1->data.u32==val2->data.u32;
		}
		break;
		case '!=':{
			res->data.u32 = val1->data.u32!=val2->data.u32;
		}
		break;
		case '&':{
			res->data.u32 = val1->data.u32&val2->data.u32;
		}
		break;
		case '|':{
			res->data.u32 = val1->data.u32|val2->data.u32;
		}
		break;
		case '^':{
			res->data.u32 = val1->data.u32^val2->data.u32;
		}
		break;
		case '&&':{
			res->data.u32 = val1->data.u32&&val2->data.u32;
		}
		break;
		case '||':{
			res->data.u32 = val1->data.u32||val2->data.u32;
		}
		break;
	}
	return 0;
}

Int LSExp_fetchUnary(LSParser *parser, LSsymValue *res);
Int LSExp_fetchBinary(LSParser *parser, LSsymValue *res, LSsymValue *val1_pre, Int opr1_pre);

Int LSExp_fetchUnary(LSParser *parser, LSsymValue *res){
    LSToken *tk = &parser->tkr.tk;
    
	Throw(
		LSParser_fetchToken(parser, FALSE)
	);
	if(LSToken_isSign(tk, '-')){
		Throw(
			LSExp_fetchUnary(parser, res)
		);
		res->data.s32 = -(res->data.s32);
	}
	else if(LSToken_isSign(tk, '+')){
		Throw(
			LSExp_fetchUnary(parser, res)
		);
	}
	else if(LSToken_isSign(tk, '!')){
		Throw(
			LSExp_fetchUnary(parser, res)
		);
		res->data.s32 = !(res->data.s32);
	}
	else if(LSToken_isSign(tk, '~')){
		Throw(
			LSExp_fetchUnary(parser, res)
		);
		res->data.s32 = !(res->data.s32);
	}
	else if(LSToken_isSign(tk, '(')){
		Throw(
			LSExp_fetchBinary(parser, res, NULL, 0)
		);
		Throw(
			LSParser_fetchToken(parser, FALSE)
		);
		if(!LSToken_isSign(tk, ')')){
			Error(LS_ERR_EXPECTCLOSPAREN);
		}
	}
	else if(LSToken_isSign(tk, '@')){
		Throw(
			LSParser_previewToken(parser, FALSE)
		)
		if((tk->type==LS_TOKENTYPE_INTEGER)||(tk->type==LS_TOKENTYPE_IDENTIFIER)){
			Throw(
				LSExp_fetchUnary(parser, res)
			);
			res->data.s32 = res->data.u32-parser->encode_address_program;
		}
		else{
			res->data.u32 = parser->encode_address_program;
			res->valtype = LS_ARGVALUE_IMM;
		}
	}
	else if((tk->type==LS_TOKENTYPE_INTEGER)||(tk->type==LS_TOKENTYPE_FLOAT)){
		res->data.u32 = tk->data.u32;
		res->valtype = LS_ARGVALUE_IMM;
	}
	else if(tk->type==LS_TOKENTYPE_IDENTIFIER){
		LSsymArg *macro_arg = LSParser_getMacroArgument(parser, tk->data.string);
		if(macro_arg){
			if(macro_arg->valtype==LS_ARGVALUE_AMD){
				res->arg = macro_arg;
			}
			res->data.u32 = macro_arg->value.imm;
			res->valtype = macro_arg->valtype;
		}
		else if(LSParser_hasSymbol(parser, tk->data.string, TRUE)){
			res->data.u32 = LSParser_getSymbol(parser, tk->data.string);
			res->valtype = LS_ARGVALUE_IMM32;
		}
		else{
			Error(LS_ERR_SYMBOLUNDEF);
		}
	}
	else{
        Error(LS_ERR_UNEXPECTTK);
	}
	
	Throw(
		LSParser_previewToken(parser, FALSE)
	);
	if(LSToken_isSign(tk, '#')||LSToken_isSign(tk, ':')){
		Bool signed_cast = LSToken_isSign(tk, ':');
		Throw(
			LSParser_fetchToken(parser, FALSE)
		);
		Throw(
			LSParser_fetchToken(parser, FALSE)
		);
		
		/* Cast to higher size for easy casting */
		switch(res->valtype){
			case LS_ARGVALUE_IMM8:{
				res->data.s32 = res->data.s8;
			}
			break;
			case LS_ARGVALUE_IMM16:{
				res->data.s32 = res->data.s16;
			}
			break;
		}
		
		/* Now, cast to desired size */
		if((tk->type==LS_TOKENTYPE_KEYWORD)&&(tk->data.kw->type&LS_KWTYPE_ADRSIZE)){
			Sint32 s32 = res->data.s32;
			Uint32 u32 = res->data.u32;
			switch(tk->data.kw->code){
				case 0:{
					if(signed_cast){
						res->data.s8 = s32;
					}
					else{
						res->data.u32 = u32&0xFF;
					}
					res->valtype = LS_ARGVALUE_IMM8;
				}
				break;
				case 1:{
					if(signed_cast){
						res->data.s16 = s32;
					}
					else{
						res->data.u32 = u32&0xFFFF;
					}
					res->valtype = LS_ARGVALUE_IMM16;
				}
				break;
				case 2:{
					res->data.u32 = u32;
					res->valtype = LS_ARGVALUE_IMM32;
				}
				break;
				default:{
					Error(LS_ERR_QWORDNINLINE);
				}
			}
		}
		else{
			Error(LS_ERR_EXPECTDTSIZE);
		}
	}
	
	return 0;
}

Int LSExp_fetchBinary(LSParser *parser, LSsymValue *res, LSsymValue *val1_pre, Int opr1_pre){
	/* Fetchinf for first operand */
    LSToken *tk = &parser->tkr.tk;
    LSsymValue val1;
	if(val1_pre){
		val1 = *val1_pre;
	}
	else{
		Throw(
			LSExp_fetchUnary(parser, &val1)
		);
	}
	
	/* Fetching for first operator */
	Int opr1 = 0;
	if(opr1_pre){
		opr1 = opr1_pre;
	}
	else{
		Throw(
			LSParser_previewToken(parser, FALSE)
		);
		if((tk->type==LS_TOKENTYPE_SIGN)&&LSExp_binaryOprOrder(tk->data.sign)){
			opr1 = tk->data.sign;
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
		}
		else{
			*res = val1;
			return 0;
		}
	}
	
	/* Fetching for second operand */
    LSsymValue val2;
	Throw(
		LSExp_fetchUnary(parser, &val2)
	);
	
	/* Fetching for second operator */
	Int opr2 = 0;
	Throw(
		LSParser_previewToken(parser, FALSE)
	);
	if((tk->type==LS_TOKENTYPE_SIGN)&&LSExp_binaryOprOrder(tk->data.sign)){
		opr2 = tk->data.sign;
		Throw(
			LSParser_fetchToken(parser, FALSE)
		);
		
		if(LSExp_binaryOprOrder(opr1)>=LSExp_binaryOprOrder(opr2)){
			LSsymValue res2;
			Throw(
				LSExp_solveBinary(parser, &val1, opr1, &val2, &res2)
			);
			Throw(
				LSExp_fetchBinary(parser, res, &res2, opr2)
			);
			return 0;
		}
		else{
			LSsymValue res2;
			Throw(
				LSExp_fetchBinary(parser, &res2, &val2, opr2)
			);
			Throw(
				LSExp_solveBinary(parser, &val1, opr1, &res2, res)
			);
			return 0;
		}
	}
	else{
		LSExp_solveBinary(parser, &val1, opr1, &val2, res);
		return 0;
	}
	return 0;
}

Int LSExp_fetchExpression(LSParser *parser, LSsymValue *res){
    Throw(
		LSExp_fetchBinary(parser, res, NULL, 0)
	);
    
    return 0;
}

Int LSExp_fetchArgument(Bool first, LSParser *parser, LSsymArg *arg){
    LSToken *tk = &parser->tkr.tk;
    
    /* Verify if has ended arguments list */
	Throw(
		LSParser_previewToken(parser, FALSE)
	);
	if(LSToken_endOfArgumentList(tk)){
		arg->valtype = LS_ARGVALUE_VOID;
        arg->value.imm = 0;
		return 0;
	}
    
    /* Each argument must be separated by a comma */
    /* If current argument is not the first, consume the comma */
    if(!first){
        Throw(
			LSParser_fetchToken(parser, FALSE)
		)
        if(!LSToken_isSign(tk, ',')){
            Error(LS_ERR_EXPECTCOMMA);
        }
    }
    
    /* Now, start fetching for the argument */
    Throw(
		LSParser_previewToken(parser, FALSE)
	);
    
    /* Its a lonely register */
    if((tk->type==LS_TOKENTYPE_KEYWORD)&&(tk->data.kw->type&LS_KWTYPE_REGISTER)){
        Throw(
			LSParser_fetchToken(parser, FALSE)
		);
        arg->valtype = LS_ARGVALUE_REG;
        arg->value.regindex = tk->data.kw->code;
    }
    /* Its a amd for memory */
    else if(LSToken_isSign(tk, '[')){
		Throw(
			LSParser_fetchToken(parser, FALSE)
		);
        Throw(
			LSParser_previewToken(parser, FALSE)
		);
        
        if((tk->type==LS_TOKENTYPE_KEYWORD)&&(tk->data.kw->type&LS_KWTYPE_REGISTER)){
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
			arg->value.amd.regb = tk->data.kw->code;
			
			Throw(
                LSParser_previewToken(parser, FALSE)
			);
			/* ADRM: Pointer */
			if(LSToken_isSign(tk, ']')){
				arg->value.amd.type = LS_AMDTYPE_POINTER;
			}
			/* ADRM: Pointer Pos-Increment */
			else if(LSToken_isSign(tk, '++')){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				arg->value.amd.type = LS_AMDTYPE_POINTERPOSINCREMENT;
			}
			/* ADRM: Pointer Pos-Decrement */
			else if(LSToken_isSign(tk, '--')){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				arg->value.amd.type = LS_AMDTYPE_POINTERPOSDECREMENT;
			}
			else if(LSToken_isSign(tk, '+')){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				
				Throw(
					LSParser_previewToken(parser, FALSE)
				);
				if((tk->type==LS_TOKENTYPE_KEYWORD)&&(tk->data.kw->type&LS_KWTYPE_REGISTER)){
					Throw(
						LSParser_fetchToken(parser, FALSE)
					);
					arg->value.amd.regi = tk->data.kw->code;
					
					Throw(
						LSParser_previewToken(parser, FALSE)
					);
					/* ADRM: Pointer Indexed */
					if(LSToken_isSign(tk, ']')){
						arg->value.amd.type = LS_AMDTYPE_POINTERINDEXED;
					}
					/* ADRM: Pointer Dynamic */
					else if(LSToken_isSign(tk, '+')){
						Throw(
							LSParser_fetchToken(parser, FALSE)
						);
						
						LSsymValue res = {0, 0};
						Throw(
							LSExp_fetchExpression(parser, &res)
						);
						
						arg->value.amd.type = LS_AMDTYPE_POINTERDYNAMIC;
						arg->value.amd.imm = res.data.u32;
					}
					/* ADRM: Pointer Dynamic (with minus prefix) */
					else if(LSToken_isSign(tk, '+')){
						Throw(
							LSParser_fetchToken(parser, FALSE)
						);
						
						LSsymValue res = {0, 0};
						Throw(
							LSExp_fetchExpression(parser, &res)
						);
						
						arg->value.amd.type = LS_AMDTYPE_POINTERDYNAMIC;
						arg->value.amd.imm = -res.data.u32;
					}
					/* ADRM: Pointer Element */
					else if(LSToken_isSign(tk, '*')){
						Throw(
							LSParser_fetchToken(parser, FALSE)
						);
						
						LSsymValue res = {0, 0};
						Throw(
							LSExp_fetchExpression(parser, &res)
						);
						
						arg->value.amd.type = LS_AMDTYPE_POINTERELEMENT;
						arg->value.amd.imm = res.data.u32;
					}
					else{
						Error(LS_ERR_UNEXPECTTK);
					}
				}
				else if(LSToken_isSign(tk, '(')){
					Throw(
						LSParser_fetchToken(parser, FALSE)
					);
					Throw(
						LSParser_fetchToken(parser, FALSE)
					);
					
					if((tk->type==LS_TOKENTYPE_KEYWORD)&&(tk->data.kw->type&LS_KWTYPE_REGISTER)){
						arg->value.amd.regi = tk->data.kw->code;
					}
					else{
						Error(LS_ERR_EXPECTREGNAME);
					}
					
					Throw(
						LSParser_fetchToken(parser, FALSE)
					);
					/* ADRM: Pointer Indexed Pos-Increment */
					if(LSToken_isSign(tk, '++')){
						arg->value.amd.type = LS_AMDTYPE_POINTERINDEXEDPOSINCREMENT;
					}
					/* ADRM: Pointer Indexed Pre-Decrement */
					else if(LSToken_isSign(tk, '--')){
						arg->value.amd.type = LS_AMDTYPE_POINTERINDEXEDPOSDECREMENT;
					}
					else{
						Error(LS_ERR_EXPECTINDECOP);
					}
					
					Throw(
						LSParser_fetchToken(parser, FALSE)
					);
					if(!LSToken_isSign(tk, ')')){
						Error(LS_ERR_EXPECTCLOSPAREN);
					}
					
					Throw(
						LSParser_previewToken(parser, FALSE)
					);
					/* ADRM: Pointer Dynamic Pos-Increment or Pos-Decremented */
					if(LSToken_isSign(tk, '+')){
						Throw(
							LSParser_fetchToken(parser, FALSE)
						);
						
						LSsymValue res = {0, 0};
						Throw(
							LSExp_fetchExpression(parser, &res)
						);
						
						arg->value.amd.type = arg->value.amd.type==LS_AMDTYPE_POINTERINDEXEDPOSINCREMENT? LS_AMDTYPE_POINTERDYNAMICPOSINCREMENT: LS_AMDTYPE_POINTERDYNAMICPOSDECREMENT;
						arg->value.amd.imm = res.data.u32;
					}
					else if(LSToken_isSign(tk, '-')){
						Throw(
							LSParser_fetchToken(parser, FALSE)
						);
						
						LSsymValue res = {0, 0};
						Throw(
							LSExp_fetchExpression(parser, &res)
						);
						
						arg->value.amd.type = arg->value.amd.type==LS_AMDTYPE_POINTERINDEXEDPOSINCREMENT? LS_AMDTYPE_POINTERDYNAMICPOSINCREMENT: LS_AMDTYPE_POINTERDYNAMICPOSDECREMENT;
						arg->value.amd.imm = -res.data.u32;
					}
					else if(LSToken_isSign(tk, ']')){}
					else{
						Error(LS_ERR_EXPECTCLOSPAREN);
					}
				}
				/* ADRM: Pointer Immediate Indexed */
				else{
					LSsymValue res = {0, 0};
					Throw(
						LSExp_fetchExpression(parser, &res)
					);
					
					arg->value.amd.type = LS_AMDTYPE_POINTERIMMEDIATEINDEXED;
					arg->value.amd.imm = res.data.u32;
				}
			}
			else if(LSToken_isSign(tk, '-')){
				Throw(
					LSParser_fetchToken(parser, FALSE)
				);
				
				/* ADRM: Pointer Immediate Indexed (with minus prefix) */
				LSsymValue res = {0, 0};
				Throw(
					LSExp_fetchExpression(parser, &res)
				);
				
				arg->value.amd.type = LS_AMDTYPE_POINTERIMMEDIATEINDEXED;
				arg->value.amd.imm = -res.data.u32;
			}
			else{
				Error(LS_ERR_UNEXPECTTK);
			}
        }
        /* ADRM: Pointer Pre-Increment */
        else if(LSToken_isSign(tk, '++')){
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
			if((tk->type==LS_TOKENTYPE_KEYWORD)&&(tk->data.kw->type&LS_KWTYPE_REGISTER)){
				arg->value.amd.type = LS_AMDTYPE_POINTERPREINCREMENT;
				arg->value.amd.regb = tk->data.kw->code;
			}
			else{
				Error(LS_ERR_EXPECTREGNAME);
			}
        }
        /* ADRM: Pointer Pre-Decrement */
        else if(LSToken_isSign(tk, '--')){
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
			if((tk->type==LS_TOKENTYPE_KEYWORD)&&(tk->data.kw->type&LS_KWTYPE_REGISTER)){
				arg->value.amd.type = LS_AMDTYPE_POINTERPREDECREMENT;
				arg->value.amd.regb = tk->data.kw->code;
			}
			else{
				Error(LS_ERR_EXPECTREGNAME);
			}
        }
        /* ADRM: Indirect */
        else{
			LSsymValue res = {0, 0};
			Throw(
				LSExp_fetchExpression(parser, &res)
			);
			
			arg->value.amd.type = LS_AMDTYPE_INDIRECT;
			arg->value.amd.imm = res.data.u32;
        }
		arg->valtype = LS_ARGVALUE_AMD;
		
		/* Checks if is not end of addressing mode */
		Throw(
			LSParser_fetchToken(parser, FALSE)
		);
		if(!LSToken_isSign(tk, ']')){
			Error(LS_ERR_EXPECTENDADRM);
		}
		
		/* Checks for any adrmsize specifier */
		Throw(
			LSParser_previewToken(parser, FALSE)
		);
		if(LSToken_isSign(tk, '#')){
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
			if((tk->type==LS_TOKENTYPE_KEYWORD)&&(tk->data.kw->type&LS_KWTYPE_ADRSIZE)){
				arg->value.amd.dsize = tk->data.kw->code;
			}
			else{
				Error(LS_ERR_EXPECTADRMSIZE);
			}
		}
		
		arg->value.amd.imm = (arg->value.amd.imm>>arg->value.amd.dsize)|((arg->value.amd.imm&0x80000000)>>1)|(arg->value.amd.imm&0x80000000);
		
    }
    /* Its a literal expression */
    else{
        LSsymValue res = {0, 0};
        Throw(
            LSExp_fetchExpression(parser, &res)
        );
		arg->valtype = res.valtype;
        if(res.valtype==LS_ARGVALUE_AMD){
			*arg = *res.arg;
        }
        else{
			arg->value.imm = res.data.u32;
        }
    }
    
    Throw(
		LSParser_previewToken(parser, FALSE)
	);
    if(!LSToken_endOfArgument(tk)){
        Error(LS_ERR_EXPECTENDARG);
    }
    
    return 0;
}

Int LSExp_fetchInstruction(LSParser *parser, LSsymInstruction *instr, LSMnemonic *mne, Int *out_size){
    LSToken *tk = &parser->tkr.tk;
    *out_size = 4;
    Uint32 value = 0;
    
    memset(instr, 0, sizeof(LSsymInstruction));
    
    /* Descriptor Determination */
    Throw(
		LSParser_previewToken(parser, FALSE)
	);
    if(LSToken_isSign(tk, '.')){
        if(mne->type==LS_INSTRTYPE_IR){
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSExp_leadDescriptor(tk, LS_KWTYPE_IMODE, &value)
            );
            instr->im = value;
        }
        else if((mne->type==LS_INSTRTYPE_ADI)||(mne->type==LS_INSTRTYPE_CDI)){
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSExp_leadDescriptor(tk, LS_KWTYPE_CONDITION, &value)
            );
            instr->cond = value;
            /* Check for Register Operand Specifier */
            Throw(
				LSParser_previewToken(parser, FALSE)
			);
            if(LSToken_isSign(tk, '<')){
                Throw(
					LSParser_fetchToken(parser, FALSE)
				);
                Throw(
					LSParser_fetchToken(parser, FALSE)
				);
                
                if((tk->type==LS_TOKENTYPE_KEYWORD)&&(tk->data.kw->type&LS_KWTYPE_REGISTER)){
                    instr->rego = tk->data.kw->code;
                }
                else{
                    Error(LS_ERR_EXPECTREGNAME);
                }
                
                Throw(
					LSParser_fetchToken(parser, FALSE)
				);
                if(!LSToken_isSign(tk, '>')){
                    Error(LS_ERR_EXPECTCLOSGRT);
                }
            }
            else{
                instr->rego = 0;
            }
        }
        Throw(
			LSParser_previewToken(parser, FALSE)
		);
    }
    if(LSToken_isSign(tk, '.')){
        if((mne->type==LS_INSTRTYPE_AMI)||(mne->type==LS_INSTRTYPE_SI)||(mne->type==LS_INSTRTYPE_CDI)){
			Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSParser_fetchToken(parser, FALSE)
			);
            Throw(
                LSExp_leadDescriptor(tk, LS_KWTYPE_EFETCH, &value)
            );
            instr->f = value&1;
        }
        else{
            Error(LS_ERR_EXPECTDESC);
        }
    }
    
    if(value==3){
        (*out_size) += 4;
        instr->imm_extra = TRUE;
        instr->f = 1;
    }
    
    /* Arguments fetching */
    /* For instructions, the max arguments are 4 */
    LSsymArg args[4];
    Uint32 args_total = 4;
    for(Int i=0; i<4; i++){
        /* Verify for match argument */
        if(mne->args[i].encname){
            /* Fetches the current instruction */
            Throw(
                LSExp_fetchArgument(i==0, parser, &args[i])
            );
            if(!LSExp_compatibleTypes(args[i].valtype, mne->args[i].valtype)){
                printf("$ Incompatible arguments! %d to %d\n", args[i].valtype, mne->args[i].valtype);
                Error(LS_ERR_INCOMPATIBLEARG);
            }
        }
        /* The arguments ends on current index */
        else{
            args_total = i;
            break;
        }
    }
    
    /* Check if has reached the end of instruction */
    Throw(
		LSParser_previewToken(parser, FALSE)
	);
    if(!LSToken_endOfArgumentList(tk)){
        printf("$ Incompatible arguments!\n");
        Error(LS_ERR_UNEXPECTTK);
    }
    
    /* Adding the arguments */
    instr->args_len = args_total;
    for(Int i=0; i<args_total; i++){
        instr->args[i] = args[i];
    }
    instr->mnemonic = mne;
    
    return 0;
}

Int LSExp_fetchMacro(LSParser *parser, LSsymMacro *macro, LSsymMacroArgs *args){
    LSToken *tk = &parser->tkr.tk;
    
    /* Arguments fetching */
    /* For macros, the max arguments are 4 */
    Uint32 args_total = 4;
    for(Int i=0; i<4; i++){
        /* Verify for match argument */
        if(macro->args[i].type){
            /* Fetches the current instruction */
            Throw(
                LSExp_fetchArgument(i==0, parser, &args->args[i])
            );
            if(!LSExp_compatibleTypes(args->args[i].valtype, macro->args[i].type)){
                printf("$ Incompatible arguments! %d to %d\n", args->args[i].valtype, macro->args[i].type);
                Error(LS_ERR_INCOMPATIBLEARG);
            }
        }
        /* The arguments ends on current index */
        else{
            args_total = i;
            break;
        }
    }
    
    /* Check if has reached the end of instruction */
    Throw(
		LSParser_previewToken(parser, FALSE)
	);
    if(!LSToken_endOfArgumentList(tk)){
        printf("$ Incompatible arguments!\n");
        Error(LS_ERR_UNEXPECTTK);
    }
    
    return 0;
}



#endif
