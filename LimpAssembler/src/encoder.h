#ifndef limps_encoder_h
#define limps_encoder_h

#include "api.h"
#include "wbuffer.h"


/**
    ENCODE FUNCTIONS
*/

Uint32 LSEnc_toIR(Uint32 base, Uint32 mod, Uint32 im, Uint32 regd, Uint32 regb, Uint32 imm){
    return
        ((base&0x3F)<<26) |
        ((mod&0x3)<<24) |
        ((im&0x3)<<22) |
        ((regd&0x7)<<19) |
        ((regb&0x7)<<16) |
        (imm&0xFFFF);
}

Uint32 LSEnc_toAMI(Uint32 base, Uint32 mod, Uint32 adrm, Uint32 dsize, Uint32 f, Uint32 regd, Uint32 regi, Uint32 regb, Uint32 imm){
    return
        ((base&0x3F)<<26) |
        ((mod&0x3)<<24) |
        ((adrm&0xF)<<20) |
        ((dsize&0x3)<<18) |
        ((f&0x1)<<17) |
        ((regd&0x7)<<14) |
        ((regi&0x7)<<11) |
        ((regb&0x7)<<8) |
        (imm&0xFF);
}

Uint32 LSEnc_toSI(Uint32 base, Uint32 mod, Uint32 func, Uint32 f, Uint32 regd, Uint32 regi, Uint32 regb, Uint32 imm){
    return
        ((base&0x3F)<<26) |
        ((mod&0x3)<<24) |
        ((func&0x3F)<<18) |
        ((f&0x1)<<17) |
        ((regd&0x7)<<14) |
        ((regi&0x7)<<11) |
        ((regb&0x7)<<8) |
        (imm&0xFF);
}

Uint32 LSEnc_toADI(Uint32 base, Uint32 mod, Uint32 cond, Uint32 rego, Uint32 imm){
    return
        ((base&0x3F)<<26) |
        ((mod&0x3)<<24) |
        ((cond&0x1F)<<19) |
        ((rego&0x7)<<16) |
        (imm&0xFFFF);
}

Uint32 LSEnc_toCDI(Uint32 base, Uint32 mod, Uint32 cond, Uint32 f, Uint32 regd, Uint32 rego, Uint32 regb, Uint32 imm){
    return
        ((base&0x3F)<<26) |
        ((mod&0x3)<<24) |
        ((cond&0x1F)<<19) |
        (1<<18) |
        ((f&0x1)<<17) |
        ((regd&0x7)<<14) |
        ((rego&0x7)<<11) |
        ((regb&0x7)<<8) |
        (imm&0xFF);
}

Uint32 LSEnc_toJL(Uint32 base, Uint32 imm){
    return
        ((base&0x3F)<<26) |
        (imm&0x3FFFFFF);
}


/**
    BINARY WRITING FUNCTIONS
*/

void LSEnc_writeInstruction(LSFile *outfile, LSsymInstruction *instr){
    Uint32 opcode = 0;
    LSMnemonic* mne = instr->mnemonic;
    /* The instruction arguments */
    Uint32 base = mne->opcode;
    Uint32 mod = mne->mod;
    Uint32 im = instr->im;
    Uint32 func = mne->func;
    Uint32 adrm = 0;
    Uint32 dsize = 0;
    Uint32 cond = instr->cond;
    Uint32 f = instr->f;
    Uint32 regd = 0;
    Uint32 regb = 0;
    Uint32 regi = 0;
    Uint32 regp = 0;
    Uint32 rego = instr->rego;
    Uint32 imm = 0;
    
    /*
        Distributes the values from arguments to above instruction descriptors
    */
    
    for(Int i=0; i<instr->args_len; i++){
		/* Special Value Operation */
		if(mne->args[i].encname&LS_ARGNAME_SHIFT1L){
			instr->args[i].value.imm <<= 1;
		}
		if(mne->args[i].encname&LS_ARGNAME_SHIFT2L){
			instr->args[i].value.imm <<= 2;
		}
		if(mne->args[i].encname&LS_ARGNAME_SHIFT3L){
			instr->args[i].value.imm <<= 3;
		}
		if(mne->args[i].encname&LS_ARGNAME_SHIFT1R){
			instr->args[i].value.imm >>= 1;
		}
		if(mne->args[i].encname&LS_ARGNAME_SHIFT2R){
			instr->args[i].value.imm >>= 2;
		}
		if(mne->args[i].encname&LS_ARGNAME_SHIFT3R){
			instr->args[i].value.imm >>= 3;
		}
		
		/* Encoding to instruction */
        switch(mne->args[i].encname&0xFF){
            case LS_ARGNAME_REGD:{
                regd = instr->args[i].value.imm;
            }
            break;
            case LS_ARGNAME_REGB:{
                regb = instr->args[i].value.imm;
            }
            break;
            case LS_ARGNAME_REGI:{
                regi = instr->args[i].value.imm;
            }
            break;
            case LS_ARGNAME_REGP:{
                regp = instr->args[i].value.imm;
            }
            break;
            case LS_ARGNAME_REGO:{
                rego = instr->args[i].value.imm;
            }
            break;
            case LS_ARGNAME_IMM:{
                imm = instr->args[i].value.imm;
            }
            break;
            case LS_ARGNAME_AMD:{
            	if(instr->args[i].valtype==LS_ARGVALUE_REG){
					adrm = LS_AMDTYPE_REGISTER;
					regb = instr->args[i].value.regindex;
            	}
            	else if(instr->args[i].valtype!=LS_ARGVALUE_AMD){
					adrm = LS_AMDTYPE_IMMEDIATE;
					imm = instr->args[i].value.imm;
            	}
            	else{
					adrm = instr->args[i].value.amd.type;
					dsize = instr->args[i].value.amd.dsize;
					regb = instr->args[i].value.amd.regb;
					regi = instr->args[i].value.amd.regi;
					imm = instr->args[i].value.amd.imm;
				}
            }
            break;
        }
    }
    
    
    /*
        Chooses the correspondent instruction format for data encoding
    */
    printf("#Encoding properties:\n\t- mnemonic: '%s';\n\t- base: 0x%x;\n\t- mod: 0x%x;\n\t- im: 0x%x;\n\t- func: 0x%x;\n\t- adrm: 0x%x;\n\t- dsize: %d;\n\t- cond: 0x%x;\n\t- f: %d;\n\t- regd: %d;\n\t- regb: %d;\n\t- regi: %d;\n\t- regp: %d;\n\t- rego: %d;\n\t- imm: 0x%x;\n",
		mne->name, base, mod, im, func, adrm, dsize, cond, f, regd, regb, regi, regp, rego, imm);
    switch(mne->type){
        case LS_INSTRTYPE_IR:{
            opcode = LSEnc_toIR(base, mod, im, regd, regb, imm);
        }
        break;
        case LS_INSTRTYPE_AMI:{
            opcode = LSEnc_toAMI(base, mod, adrm, dsize, f, regd, regi, regb, imm);
        }
        break;
        case LS_INSTRTYPE_SI:{
            opcode = LSEnc_toSI(base, mod, func, f, regd, regi, regb, imm);
        }
        break;
        case LS_INSTRTYPE_ADI:{
            opcode = LSEnc_toADI(base, mod, cond, rego, imm);
        }
        break;
        case LS_INSTRTYPE_CDI:{
            opcode = LSEnc_toCDI(base, mod, cond, f, regd, rego, regb, imm);
        }
        break;
        case LS_INSTRTYPE_JL:{
            opcode = LSEnc_toJL(base, imm);
        }
        break;
    }
    
    LSWbuff_write32(outfile, opcode);
    
    if(instr->imm_extra){
        LSWbuff_write32(outfile, imm);
    }
}



#endif
