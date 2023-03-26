#ifndef limps_error_h
#define limps_error_h

#include "api.h"



#define Throw(eval) {Uint32 code = (eval); if(code){printf("Caught Error %d at file '%s' in line %d, throwing it away\n", code, __FILE__, __LINE__); return code;}}

#define Error(code) {printf("\n############## Error %d throwed at file '%s' in line %d ##############\n\n", code, __FILE__, __LINE__); return code;}


#define LS_ERR_EXPECTDESC 0x0002 /* Expected a descriptor */
#define LS_ERR_EXPECTCLOSPAREN 0x0003 /* Expected a closin paren */
#define LS_ERR_SYMBOLUNDEF 0x0004 /* Symbol is not defined */
#define LS_ERR_UNEXPECTTK 0x0005 /* Unexpected token */
#define LS_ERR_QWORDNINLINE 0x0006 /* Qword is not allowed on inline operations */
#define LS_ERR_EXPECTDTSIZE 0x0007 /* Expected a data size identifier */
#define LS_ERR_EXPECTCOMMA 0x0008 /* Expected a comma separator */
#define LS_ERR_EXPECTREGNAME 0x0009 /* Expected a register name */
#define LS_ERR_EXPECTINDECOP 0x000A /* Expected a pos increment or decrement operator */
#define LS_ERR_EXPECTENDADRM 0x000B /* Expected end of addressing mode clause */
#define LS_ERR_EXPECTADRMSIZE 0x000C /* Expected name of adressing mode data access size. ie: byte, word, dword or quarter */
#define LS_ERR_EXPECTENDARG 0x000D /* Expected end of argument */
#define LS_ERR_EXPECTCLOSGRT 0x000E /* Expected closin '>' */
#define LS_ERR_EXPECTPREPNAME 0x000F /* Expected a preprocessor name */
#define LS_ERR_EXPECTIDENTIFIER 0x0010 /* Expected a identifier */
#define LS_ERR_SYMBOLALREADYDEF 0x0011 /* Symbol with same name already defined */
#define LS_ERR_EXPECTSTRING 0x0012 /* Expected a string */
#define LS_ERR_OUTGLOBAL 0x0013 /* Trying to go out of global scope */
#define LS_ERR_EXPECTVALIDPREPNAME 0x0014 /* Expected a valid preprocessor name */
#define LS_ERR_UNALOWEDPOSFIX 0x0015 /* Unallowed number posfix */
#define LS_ERR_INCOMPATIBLEARG 0x0016 /* Incompatible arguments types */
#define LS_ERR_INVALIDDESC 0x00017 /* Invalid Descriptor disposition */


Char* LSErr_msgFromCode(Uint32 code){
	switch(code){
		case LS_ERR_INVALIDDESC: return "Invalid Descriptor disposition";
		case LS_ERR_EXPECTDESC: return "Expected a descriptor";
		case LS_ERR_EXPECTCLOSPAREN: return "Expected a closin paren";
		case LS_ERR_SYMBOLUNDEF: return "Symbol is not defined";
		case LS_ERR_UNEXPECTTK: return "Unexpected token";
		case LS_ERR_QWORDNINLINE: return "Qword is not allowed on inline operations";
		case LS_ERR_EXPECTDTSIZE: return "Expected a data size identifier";
		case LS_ERR_EXPECTCOMMA: return "Expected a comma separator";
		case LS_ERR_EXPECTREGNAME: return "Expected a register name";
		case LS_ERR_EXPECTINDECOP: return "Expected a pos increment or decrement operator";
		case LS_ERR_EXPECTENDADRM: return "Expected end of addressing mode clause";
		case LS_ERR_EXPECTADRMSIZE: return "Expected name of adressing mode data access size. ie: byte, word, dword or quarter";
		case LS_ERR_EXPECTENDARG: return "Expected end of argument";
		case LS_ERR_EXPECTCLOSGRT: return "Expected closin '>'";
		case LS_ERR_EXPECTPREPNAME: return "Expected a preprocessor name";
		case LS_ERR_EXPECTIDENTIFIER: return "Expected a identifier";
		case LS_ERR_SYMBOLALREADYDEF: return "Symbol with same name already defined";
		case LS_ERR_EXPECTSTRING: return "Expected a string";
		case LS_ERR_OUTGLOBAL: return "Trying to go out of global scope";
		case LS_ERR_EXPECTVALIDPREPNAME: return "Expected a valid preprocessor name";
		case LS_ERR_UNALOWEDPOSFIX: return "Unallowed number posfix";
		case LS_ERR_INCOMPATIBLEARG: return "Incompatible arguments types";
	}
	return "<Not catalogged error>";
}


#endif
