#ifndef gui_h
#define gui_h

#include <windows.h>
#include <commctrl.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

#include "test.h"

#define Ui HWND

#define NO_ID -1

#define gui_ui_text(txt, id, x, y, w, h) CreateWindowW(L"Static", txt, WS_CHILD | WS_VISIBLE | SS_LEFT, x, y, w, h, hwnd, (HMENU) id, NULL, NULL)
#define gui_ui_button(txt, id, x, y, w, h) CreateWindowW(L"Button", txt, WS_VISIBLE | WS_CHILD , x, y, w, h, hwnd, (HMENU) id, NULL, NULL)
#define gui_ui_checkbox(txt, id, x, y, w, h) CreateWindowW(L"button", txt, WS_VISIBLE | WS_CHILD | BS_CHECKBOX, x, y, w, h, hwnd, (HMENU) id, NULL, NULL)
#define gui_ui_edit(txt, id, x, y, w, h) CreateWindowW(L"Edit", txt, WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, w, h, hwnd, (HMENU) id, NULL, NULL)
#define gui_ui_dropdown(id, x, y, w) CreateWindow(WC_COMBOBOX, TEXT(""), CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, x, y, w, 200, hwnd, (HMENU)id, NULL, NULL)

#define gui_dropdown_addItem(ui, cstr) SendMessage(ui, CB_ADDSTRING, 0, TEXT(cstr))
#define gui_dropdown_setTo(ui, index) SendMessage(ui, CB_SETCURSEL, index, 0)
#define gui_dropdown_getIndex(ui) SendMessage((HWND)ui, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0)
#define gui_dropdown_getTchar(ui) ((TCHAR)SendMessage((HWND)ui, (UINT) CB_GETLBTEXT, (WPARAM) ItemIndex, (LPARAM) ListItem))

#define gui_is_checked(id) IsDlgButtonChecked(hwnd, id)

#define gui_get_text(ui, txt, len) GetWindowTextW(ui, txt, len)
#define gui_get_textSize(ui) GetWindowTextLengthW(ui)

#define gui_set_checked(id, state) CheckDlgButton(hwnd, id, state)
#define gui_set_text(ui, txt) SetWindowTextW(ui, txt)

static HINSTANCE _hInstance;
static HINSTANCE _hPrevInstance;
static LPSTR _szCmdLine;
static int _CmdShow;

HWND _gui_gui;
HWND _gui_dialog;
Int _guid_gui = 0;
Bool _gui_dialog_alreadyopen = FALSE;
wchar_t* _gui_dialog_msg = L"Insert a value:";
enum DialogVType{
	DVTString,
	DVTHexadecimal
}_gui_dialog_type = DVTHexadecimal;
union{
	Uint64 numeric;
	wchar_t* text;
	char* cstr;
}_gui_dialog_value = {
	.numeric = 0x0
};
Uint32 _gui_dialog_mode = 0;
wchar_t* _gui_dialog_text = L"12";
void (*_gui_dialog_callback)() = NULL;



void _dialogLoad(){
	if(_gui_dialog_type==DVTString){
		if(_gui_dialog_value.text){
			Int len = wcslen(_gui_dialog_value.text);
			_gui_dialog_text = _gui_dialog_value.text;
		}
		else{
			_gui_dialog_text = L"";
		}
	}
	else{
		_gui_dialog_text = malloc(sizeof(wchar_t)*128);
		char temp[128];
		switch(_gui_dialog_mode){
			case 0:{ // Hexadecimal
				sprintf(temp, "0x%x\0", _gui_dialog_value.numeric);
			}
			break;
			case 1:{ // Decimal
				sprintf(temp, "%u\0", _gui_dialog_value.numeric);
			}
			break;
			case 2:{ // Octal
				sprintf(temp, "0o%o\0", _gui_dialog_value.numeric);
			}
			break;
			case 3:{ // Floating-Pointer
				sprintf(temp, "0f%f\0", *(Float*)&_gui_dialog_value.numeric);
			}
			break;
			case 4:{ // Format IR
				sprintf(temp, ".ir 0x%X, %d, %d, %d, %d, 0x%X",
							(_gui_dialog_value.numeric>>26)&0x3F, // Opcode
							(_gui_dialog_value.numeric>>24)&0x3, // Mod
							(_gui_dialog_value.numeric>>22)&0x3, // IM
							(_gui_dialog_value.numeric>>19)&0x7, // RegD
							(_gui_dialog_value.numeric>>16)&0x7, // RegB
							_gui_dialog_value.numeric&0xFFFF // Imm
				);
			}
			break;
			case 5:{ // Format AMI
				sprintf(temp, ".ami 0x%X, %d, 0x%X, %d, %d, %d, %d, %d, 0x%X",
							(_gui_dialog_value.numeric>>26)&0x3F, // Opcode
							(_gui_dialog_value.numeric>>24)&0x3, // Mod
							(_gui_dialog_value.numeric>>20)&0xF, // AdrM
							(_gui_dialog_value.numeric>>18)&0x3, // DSize
							(_gui_dialog_value.numeric>>17)&0x1, // F
							(_gui_dialog_value.numeric>>14)&0x7, // RegD
							(_gui_dialog_value.numeric>>11)&0x7, // RegI
							(_gui_dialog_value.numeric>>8)&0x7, // RegB
							_gui_dialog_value.numeric&0xFF // Imm
				);
			}
			break;
			case 6:{ // Format SI
				sprintf(temp, ".si 0x%X, %d, 0x%X, %d, %d, %d, %d, 0x%X",
							(_gui_dialog_value.numeric>>26)&0x3F, // Opcode
							(_gui_dialog_value.numeric>>24)&0x3, // Mod
							(_gui_dialog_value.numeric>>18)&0x3F, // Func
							(_gui_dialog_value.numeric>>17)&0x1, // F
							(_gui_dialog_value.numeric>>14)&0x7, // RegD
							(_gui_dialog_value.numeric>>11)&0x7, // RegI
							(_gui_dialog_value.numeric>>8)&0x7, // RegB
							_gui_dialog_value.numeric&0xFF // Imm
				);
			}
			break;
			case 7:{ // Format ADI
				sprintf(temp, ".adi 0x%X, %d, 0x%X, %d, 0x%X",
							(_gui_dialog_value.numeric>>26)&0x3F, // Opcode
							(_gui_dialog_value.numeric>>24)&0x3, // Mod
							(_gui_dialog_value.numeric>>19)&0x1F, // Condition
							(_gui_dialog_value.numeric>>16)&0x7, // RegO
							_gui_dialog_value.numeric&0xFFFF // Imm
				);
			}
			break;
			case 8:{ // Format CDI
				sprintf(temp, ".cdi 0x%X, %d, 0x%X, %d, %d, %d, %d, 0x%X",
							(_gui_dialog_value.numeric>>26)&0x3F, // Opcode
							(_gui_dialog_value.numeric>>24)&0x3, // Mod
							(_gui_dialog_value.numeric>>19)&0x1F, // Condition
							(_gui_dialog_value.numeric>>17)&0x1, // F
							(_gui_dialog_value.numeric>>14)&0x7, // RegD
							(_gui_dialog_value.numeric>>11)&0x7, // RegO
							(_gui_dialog_value.numeric>>8)&0x7, // RegB
							_gui_dialog_value.numeric&0xFF // Imm
				);
			}
			break;
			case 9:{ // Format JL
				sprintf(temp, ".jl 0x%X, 0x%X",
							(_gui_dialog_value.numeric>>26)&0x3F, // Opcode
							_gui_dialog_value.numeric&0x3FFFFFF // Imm
				);
			}
			break;
			default:{ // Unknown
				sprintf(temp, "unknown");
			}
		}
		Int len = strlen(temp);
		Int cv = 0;
		mbstowcs_s(NULL, _gui_dialog_text, (len+1), temp, len);
	}
}

Int gui_dialogParseNumber_number(char* buffer){
	Int value = 0;
	
	if((*buffer)=='0'){
		buffer++;
		if((*buffer)>='1' && (*buffer)<='9'){
			sscanf(buffer, "%d", &value);
		}
		else if((*buffer)=='x'){
			buffer++;
			sscanf(buffer, "%x", &value);
		}
		else if((*buffer)=='o'){
			buffer++;
			sscanf(buffer, "%o", &value);
		}
		else if((*buffer)=='f'){
			buffer++;
			sscanf(buffer, "%f", &value);
		}
	}
	else if((*buffer)>='1' && (*buffer)<='9'){
		sscanf(buffer, "%d", &value);
	}
	
	return value;
}

void gui_dialogParseNumber_jsp(char **buffer){
	while((**buffer)==' '){
		(*buffer)++;
	}
}

void gui_dialogParseNumber_jnum(char **buffer){
	while((**buffer)==' '){
		(*buffer)++;
	}
	while(((**buffer)!=' ')&&((**buffer)!=0)){
		(*buffer)++;
	}
}

Int gui_dialogParseNumber_fetch(char **buffer){
	Int value = 0;
	gui_dialogParseNumber_jsp(buffer);
	value = gui_dialogParseNumber_number(*buffer);
	gui_dialogParseNumber_jnum(buffer);
	return value;
}

Int gui_dialogParseNumber_decIR(char **buffer){
	Int value = 0;
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3F)<<26; // Opcode
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3)<<24; // Mod
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3)<<22; // Im
	value |= (gui_dialogParseNumber_fetch(buffer)&0x7)<<19; // RegD
	value |= (gui_dialogParseNumber_fetch(buffer)&0x7)<<16; // RegB
	value |= (gui_dialogParseNumber_fetch(buffer)&0xFFFF); // Imm
	return value;
}

Int gui_dialogParseNumber_decAMI(char **buffer){
	Int value = 0;
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3F)<<26; // Opcode
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3)<<24; // Mod
	value |= (gui_dialogParseNumber_fetch(buffer)&0xF)<<20; // AdrM
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3)<<18; // DSize
	value |= (gui_dialogParseNumber_fetch(buffer)&0x1)<<17; // F
	value |= (gui_dialogParseNumber_fetch(buffer)&0x7)<<14; // RegD
	value |= (gui_dialogParseNumber_fetch(buffer)&0x7)<<11; // RegI
	value |= (gui_dialogParseNumber_fetch(buffer)&0x7)<<8; // RegB
	value |= (gui_dialogParseNumber_fetch(buffer)&0xFF); // Imm
	return value;
}

Int gui_dialogParseNumber_decSI(char **buffer){
	Int value = 0;
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3F)<<26; // Opcode
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3)<<24; // Mod
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3F)<<18; // DSize
	value |= (gui_dialogParseNumber_fetch(buffer)&0x1)<<17; // F
	value |= (gui_dialogParseNumber_fetch(buffer)&0x7)<<14; // RegD
	value |= (gui_dialogParseNumber_fetch(buffer)&0x7)<<11; // RegI
	value |= (gui_dialogParseNumber_fetch(buffer)&0x7)<<8; // RegB
	value |= (gui_dialogParseNumber_fetch(buffer)&0xFF); // Imm
	return value;
}

Int gui_dialogParseNumber_decADI(char **buffer){
	Int value = 0;
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3F)<<26; // Opcode
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3)<<24; // Mod
	value |= (gui_dialogParseNumber_fetch(buffer)&0x1F)<<19; // Condition
	value |= (gui_dialogParseNumber_fetch(buffer)&0x7)<<16; // RegO
	value |= (gui_dialogParseNumber_fetch(buffer)&0xFFFF); // Imm
	return value;
}

Int gui_dialogParseNumber_decCDI(char **buffer){
	Int value = 0;
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3F)<<26; // Opcode
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3)<<24; // Mod
	value |= (gui_dialogParseNumber_fetch(buffer)&0x1F)<<19; // Condition
	value |= (1)<<18; // gap
	value |= (gui_dialogParseNumber_fetch(buffer)&0x1)<<17; // F
	value |= (gui_dialogParseNumber_fetch(buffer)&0x7)<<14; // RegD
	value |= (gui_dialogParseNumber_fetch(buffer)&0x7)<<11; // RegO
	value |= (gui_dialogParseNumber_fetch(buffer)&0x7)<<8; // RegB
	value |= (gui_dialogParseNumber_fetch(buffer)&0xFF); // Imm
	return value;
}

Int gui_dialogParseNumber_decJL(char **buffer){
	Int value = 0;
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3F)<<26; // Opcode
	value |= (gui_dialogParseNumber_fetch(buffer)&0x3FFFFFF); // Imm
	return value;
}

Int gui_dialogParseNumber(){
	Int value = 0;
	char* buffer = (char*)malloc(wcslen(_gui_dialog_text)+1);
	char* og = buffer;
	wcstombs_s(NULL, buffer, wcslen(_gui_dialog_text)+1, _gui_dialog_text, wcslen(_gui_dialog_text)+1);
	
	if((*buffer)>='0' && (*buffer)<='9'){
		value = gui_dialogParseNumber_number(buffer);
	}
	else if((*buffer)=='.'){
		buffer++;
		if((*buffer)=='i'){
			buffer += 2;
			value = gui_dialogParseNumber_decIR(&buffer);
		}
		else if((*buffer)=='s'){
			buffer += 2;
			value = gui_dialogParseNumber_decSI(&buffer);
		}
		else if((*buffer)=='c'){
			buffer += 3;
			value = gui_dialogParseNumber_decCDI(&buffer);
		}
		else if((*buffer)=='j'){
			buffer += 2;
			value = gui_dialogParseNumber_decJL(&buffer);
		}
		else if((*buffer)=='a'){
			buffer++;
			
			if((*buffer)=='m'){
				buffer += 2;
				value = gui_dialogParseNumber_decAMI(&buffer);
			}
			else if((*buffer)=='d'){
				buffer += 2;
				value = gui_dialogParseNumber_decADI(&buffer);
			}
		}
	}
	
	free(og);
	return value;
}

void _dialogStore(){
	if(_gui_dialog_type==DVTString){
		if(_gui_dialog_value.text){
			_gui_dialog_value.text = _gui_dialog_text;
		}
		else{
			_gui_dialog_value.text = L"";
		}
	}
	else{
		_gui_dialog_value.numeric = gui_dialogParseNumber();
	}
}

void _dialogClt(){
	if(_gui_dialog_type==DVTString){
		
	}
	else{
		free(_gui_dialog_text);
	}
}

static BOOL IsEdit(Ui hWnd){
    if (hWnd == NULL){
		return FALSE;
	}
    TCHAR szClassName[6];
    return GetClassName(hWnd, szClassName, 6) && wcscmp(szClassName, L"Edit")==0;
}

LRESULT CALLBACK dialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static Int id_btn_set = 1;
	
	static Ui ui_edit;
	
	switch(msg){
		/* Define o layout da janela na sua criação */
		case WM_CREATE:{
			gui_ui_text(_gui_dialog_msg, NO_ID, 16, 32, 256, 32);
			
			_dialogLoad();
			ui_edit = gui_ui_edit(_gui_dialog_text, NO_ID, 16, 64, 256, 20);
			_dialogClt();
			SetFocus(ui_edit);
			
			gui_ui_button(L"Set", id_btn_set, 288, 64, 64, 20);
		}
		break;
		/* Eventos dispachados pelos elementos */
		case WM_COMMAND:{
			if(LOWORD(wParam) == id_btn_set){
				_gui_dialog_text = malloc(sizeof(wchar_t)*(gui_get_textSize(ui_edit)+1));
				gui_get_text(ui_edit, _gui_dialog_text, gui_get_textSize(ui_edit)+1);
				_dialogStore();
				free(_gui_dialog_text);
				
				if(_gui_dialog_callback){
					_gui_dialog_callback();
				}
				
				EnableWindow(_gui_gui, TRUE);
				DestroyWindow(_gui_dialog);
			}
		}
		break;
		/* Na destruição da janela */
		case WM_DESTROY:{
			_gui_dialog_alreadyopen = FALSE;
			gui_refresh();
		}
		break;
		
		/* Verifica a entrada */
		case WM_KEYDOWN:{
			/*if(wParam==VK_RETURN){
				_gui_dialog_text = malloc(sizeof(wchar_t)*(gui_get_textSize(ui_edit)+1));
				gui_get_text(ui_edit, _gui_dialog_text, gui_get_textSize(ui_edit)+1);
				_dialogStore();
				free(_gui_dialog_text);
				
				if(_gui_dialog_callback){
					_gui_dialog_callback();
				}
				
				EnableWindow(_gui_gui, TRUE);
				DestroyWindow(_gui_dialog);
			}*/
		}
		break;
	}
	
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void gui_showDialog(wchar_t* msg){
	if(_gui_dialog_alreadyopen){
		return;
	}
	_gui_dialog_alreadyopen = TRUE;
	EnableWindow(_gui_gui, FALSE);
	
	/* Window 2 Setup */
	WNDCLASSW wc2 = {0};
	wc2.lpszClassName = L"Dialog";
	wc2.hInstance     = _hInstance;
	wc2.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc2.lpfnWndProc   = dialogProc;
	wc2.hCursor       = LoadCursor(0, IDC_ARROW);
	
	_gui_dialog_msg = msg;
	
	RegisterClassW(&wc2);
	_gui_dialog = CreateWindowW(wc2.lpszClassName, L"Set Value",
		WS_OVERLAPPED | WS_VISIBLE,
		200, 200, 400, 200, 0, 0, _hInstance, 0);
	SetFocus(_gui_dialog); 
}

void gui_refresh(){
	EnableWindow(_gui_gui, !IsWindowEnabled(_gui_gui));
	EnableWindow(_gui_gui, !IsWindowEnabled(_gui_gui));
	if(IsWindowEnabled(_gui_gui)){
		SetFocus(_gui_gui);
	}
}


#define gui_write(ui, fmt, ...){\
		char buffer[1024];\
		sprintf(buffer, fmt, ##__VA_ARGS__);\
		Int len = strlen(buffer);\
		wchar_t* text = malloc(sizeof(wchar_t)*(len+1));\
		mbstowcs_s(NULL, text, (len+1), buffer, len);\
		gui_set_text(ui, text);\
	}


Int guiset_reg_i = 0;
void guiset_reg(){
	Uint32 value = _gui_dialog_value.numeric;
	if(guiset_reg_i==8){
		gcpu.sregs.epc = value;
	}
	else if(guiset_reg_i==9){
		gcpu.sregs.efd = value;
	}
	else{
		gcpu.regs.u[guiset_reg_i&7] = value;
	}
}
Uint32 guiget_reg(Uint32 index){
	if(index==8){
		return gcpu.sregs.epc;
	}
	else if(index==9){
		return gcpu.sregs.efd;
	}
	else{
		return gcpu.regs.u[index&7];
	}
}

Uint32 guiset_mem_baseadr = 0;
Uint32 guiset_mem_offset = 0;
Uint32 guiset_mem_size = 8;
Uint32 guiset_mem_coff = 0, guiset_mem_cadr = 0;
void guiset_mem(){
	Uint32 value = _gui_dialog_value.numeric;
	Uint32 adr = guiset_mem_baseadr+guiset_mem_offset;
	if(guiset_mem_size==8){
		LICPU_writeBus8((&gcpu), adr, value);
	}
	else{
		LICPU_writeBus32((&gcpu), adr, value);
	}
}
void guiset_memadr(){
	Uint32 value = _gui_dialog_value.numeric;
	guiset_mem_baseadr = value;
}
Uint32 guiget_mem(Uint32 offset, Uint32 size){
	Uint32 adr = guiset_mem_baseadr+offset;
	if(size==8){
		return LICPU_readBus8((&gcpu), adr);
	}
	else{
		return LICPU_readBus32((&gcpu), adr);
	}
}


struct GuiReg{
	wchar_t *name;
	Int id_btn_set;
	Ui ui_txt_v;
}guiregs[] = {
	{L"EAX", 1},
	{L"EDX", 2},
	{L"ECX", 3},
	{L"EBX", 4},
	{L"EFP", 5},
	{L"ESP", 6},
	{L"ESS", 7},
	{L"ESD", 8},
	{L"EPC", 9},
	{L"EFD", 10},
};
Int guiregs_len = sizeof(guiregs)/sizeof(struct GuiReg);

struct GuiFlag{
	wchar_t *name;
	Int offset;
	Int id_chk;
}guiflags[] = {
	{L"CF", 0, 16},
	{L"BF", 1, 17},
	{L"VF", 2, 18},
	{L"ZF", 3, 19},
	{L"NF", 4, 20},
	{L"OF", 5, 21},
	{L"EI", 16, 22},
	{L"PM", 17, 23},
	{L"VM", 18, 24},
};
Int guiflags_len = sizeof(guiflags)/sizeof(struct GuiFlag);


LRESULT CALLBACK guiProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static const Int adrs = 12;
	static const Int ofs = 16;
	
	static Int id_btn_step = 32;
	static Int id_btn_reset = 33;
	static Int id_dpd_editloadmode = 34;
	static Int id_btn_setadr = 48;
	static Int id_btn_cells[12*16];
	static Int id_menu_load = 64;
	static Int id_menu_dump = 65;
	
	static Ui ui_btn_cells[12*16];
	static Ui ui_txt_adrs[12];
	static Ui ui_dpd_editloadmode;
	
	
	switch(msg){
		/* Define o layout da janela na sua criação */
		case WM_CREATE:{
			
			/* Register Panel */
			for(Int i=0; i<guiregs_len; i++){
				gui_ui_text(guiregs[i].name, NO_ID, 16, 32+(i*32), 64, 32);
				guiregs[i].ui_txt_v = gui_ui_text(L"0x0", NO_ID, 80, 32+(i*32), 128, 32);
				gui_ui_button(L"Set", guiregs[i].id_btn_set, 228, 32+(i*32), 64, 20);
			}
			
			
			/* Flags Panel */
			for(Int i=0; i<guiflags_len; i++){
				gui_ui_text(guiflags[i].name, NO_ID, 16+(i*32), 368, 32, 32);
				gui_ui_checkbox(L"", guiflags[i].id_chk, 16+(i*32), 388, 32, 32);
			}
			
			
			/* Memory View Panel */
			/* Adresses */
			gui_ui_button(L"Address", id_btn_setadr, 320, 90, 64, 32);
			for(Int i=0; i<adrs; i++){
				ui_txt_adrs[i] = gui_ui_text(L"0x00000000", NO_ID, 320, 128+(i*24), 96, 24);
			}
			/* Offsets */
			for(Int i=0; i<ofs; i++){
				//.ir 0x30, 1, 0, 0, 0, 0x4589
				wchar_t txt[] = L"0";
				txt[0] = i<10?L'0'+i:L'A'+((10-i));
				gui_ui_text(txt, NO_ID, 412+(i*24), 104, 32, 24);
			}
			/* Cells */
			for(Int ai=0; ai<adrs; ai++){
				for(Int oi=0; oi<ofs; oi++){
					id_btn_cells[ai*ofs+oi] = 128+ai*ofs+oi;
					ui_btn_cells[ai*ofs+oi] = gui_ui_text(L"00", id_btn_cells[ai*ofs+oi], 404+(oi*24), 128+(ai*24), 24, 24);
				}
			}
			
			/* Control Panel */
			gui_ui_button(L"Step", id_btn_step, 336, 32, 64, 32);
			gui_ui_button(L"Reset", id_btn_reset, 416, 32, 64, 32);
			ui_dpd_editloadmode = gui_ui_dropdown(id_dpd_editloadmode, 496, 32, 128);
			
			gui_dropdown_addItem(ui_dpd_editloadmode, "hexadecimal");
			gui_dropdown_addItem(ui_dpd_editloadmode, "decimal");
			gui_dropdown_addItem(ui_dpd_editloadmode, "octal");
			gui_dropdown_addItem(ui_dpd_editloadmode, "floating pointer");
			gui_dropdown_addItem(ui_dpd_editloadmode, "format IR");
			gui_dropdown_addItem(ui_dpd_editloadmode, "format AMI");
			gui_dropdown_addItem(ui_dpd_editloadmode, "format SI");
			gui_dropdown_addItem(ui_dpd_editloadmode, "format ADI");
			gui_dropdown_addItem(ui_dpd_editloadmode, "format CDI");
			gui_dropdown_addItem(ui_dpd_editloadmode, "format JL");
			
			gui_dropdown_setTo(ui_dpd_editloadmode, 0);
			
			/* Setting Top Menu */
			HMENU hMenubar;
			HMENU hMenu;
			
			hMenubar = CreateMenu();
			hMenu = CreateMenu();
			
			AppendMenuW(hMenu, MF_STRING, id_menu_load, L"&Load Memory");
			AppendMenuW(hMenu, MF_STRING, id_menu_dump, L"&Dump Memory");
			
			AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&File");
			SetMenu(hwnd, hMenubar);
			
		}
		break;
		/* Eventos dispachados pelos elementos */
		case WM_COMMAND:{
			for(Int i=0; i<guiregs_len; i++){
				if(LOWORD(wParam) == guiregs[i].id_btn_set){
					guiset_reg_i = i;
					_gui_dialog_value.numeric = guiget_reg(i);
					_gui_dialog_callback = guiset_reg;
					gui_showDialog(guiregs[i].name);
				}
			}
			for(Int i=0; i<guiflags_len; i++){
				if(LOWORD(wParam) == guiflags[i].id_chk){
					Bool checked = !gui_is_checked(guiflags[i].id_chk);
					gui_set_checked(guiflags[i].id_chk, checked);
					gcpu.sregs.est = setVBit(gcpu.sregs.est, guiflags[i].offset, checked);
				}
			}
			if(LOWORD(wParam) == id_btn_setadr){
				_gui_dialog_value.numeric = guiset_mem_baseadr;
				_gui_dialog_callback = guiset_memadr;
				gui_showDialog(L"Memory address");
			}
			if(LOWORD(wParam) == id_btn_step){
				LICpu_step(&gcpu);
				gui_refresh();
			}
			if(LOWORD(wParam) == id_dpd_editloadmode){
				_gui_dialog_mode = gui_dropdown_getIndex(ui_dpd_editloadmode);
			}
			static TCHAR defaultFile[260] = "mem.bin";
			if(LOWORD(wParam) == id_menu_load){
				OPENFILENAME ofn = {0}; 
				TCHAR szFile[260];
				memcpy(szFile, defaultFile, sizeof(szFile));
				// Initialize remaining fields of OPENFILENAME structure
				ofn.lStructSize = sizeof(ofn); 
				ofn.hwndOwner = hwnd; 
				ofn.lpstrFile = szFile; 
				ofn.nMaxFile = sizeof(szFile); 
				ofn.lpstrFilter = TEXT("All\0*.*\0Binary\0*.bin\0"); 
				ofn.nFilterIndex = 1; 
				ofn.lpstrFileTitle = NULL; 
				ofn.nMaxFileTitle = 0; 
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

				if(GetOpenFileName(&ofn) == TRUE){ 
					// use ofn.lpstrFile here
					memcpy(defaultFile, ofn.lpstrFile, sizeof(defaultFile));
					FILE *file = fopen(ofn.lpstrFile, "r");
					
					for(Int i=0; i<1024*1024*8; i++){
						LICPU_writeBus8((&gcpu), i, fgetc(file));
					}
					
					gui_refresh();
					fclose(file);
				}
			}
			if(LOWORD(wParam) == id_menu_dump){
				OPENFILENAME ofn = {0}; 
				TCHAR szFile[260];
				memcpy(szFile, defaultFile, sizeof(szFile));
				// Initialize remaining fields of OPENFILENAME structure
				ofn.lStructSize = sizeof(ofn); 
				ofn.hwndOwner = hwnd; 
				ofn.lpstrFile = szFile; 
				ofn.nMaxFile = sizeof(szFile); 
				ofn.lpstrFilter = TEXT("All\0*.*\0Binary\0*.bin\0"); 
				ofn.nFilterIndex = 1; 
				ofn.lpstrFileTitle = NULL; 
				ofn.nMaxFileTitle = 0; 
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST;
				
				if(GetSaveFileName(&ofn) == TRUE){ 
					// use ofn.lpstrFile here
					memcpy(defaultFile, ofn.lpstrFile, sizeof(defaultFile));
					printf("Dumping to %s\n", ofn.lpstrFile);
					
					FILE *file = fopen(ofn.lpstrFile, "w");
					
					for(Int i=0; i<1024*1024*8; i++){
						fputc(LICPU_readBus8((&gcpu), i), file);
					}
					
					fclose(file);
				}
			}
		}
		break;
		/* Atualização da tela */
		case WM_ENABLE:{
			for(Int i=0; i<guiregs_len; i++){
				gui_write(guiregs[i].ui_txt_v, "0x%X", guiget_reg(i));
			}
			for(Int i=0; i<guiflags_len; i++){
				gui_set_checked(guiflags[i].id_chk, (gcpu.sregs.est>>guiflags[i].offset)&1);
			}
			for(Int i=0; i<adrs; i++){
				gui_write(ui_txt_adrs[i], "%.8X", guiset_mem_baseadr+(i*16));
			}
			for(Int ai=0; ai<adrs; ai++){
				for(Int oi=0; oi<ofs; oi++){
					Uint32 adr = guiset_mem_baseadr+ai*ofs+oi;
					gui_write(ui_btn_cells[ai*ofs+oi], " %.2X ", guiget_mem(ai*ofs+oi, 8));
				}
			}
		}
		break;
		case WM_CTLCOLORSTATIC:{
			Bool bkcolored = FALSE;
			for(Int ai=0; ai<adrs; ai++){
				for(Int oi=0; oi<ofs; oi++){
					if(GetWindowLong(lParam, GWL_ID)==id_btn_cells[ai*ofs+oi]){
						Uint32 adr = guiset_mem_baseadr+ai*ofs+oi;
						if((adr&(~3))==(gcpu.sregs.epc&(~3))){
							SetBkColor(wParam, RGB(255, 255, 0));
							bkcolored = TRUE;
						}
						if((guiset_mem_cadr==ai)&&(guiset_mem_size==8?(guiset_mem_coff==oi):((guiset_mem_coff&(~3))==(oi&(~3))))&&_gui_dialog_alreadyopen&&(_gui_dialog_callback==guiset_mem)){
							SetBkColor(wParam, RGB(255, 0, 0));
							bkcolored = TRUE;
						}
					}
				}
			}
			if(!bkcolored){
				SetBkMode(wParam, TRANSPARENT);
			}
			//SelectObject(wParam, hBoldFont);
			return (INT_PTR)GetSysColorBrush(COLOR_BTNFACE);
		}
		break;
		/* Na destruição da janela */
		case WM_DESTROY:{
			PostQuitMessage(0);
			exit(0);
		}
		break;
		
		/* Verifica a entrada */
		case WM_KEYDOWN:{
			if(wParam==VK_PRIOR){
				guiset_mem_baseadr -= 64;
				gui_refresh();
			}
			if(wParam==VK_NEXT){
				guiset_mem_baseadr += 64;
				gui_refresh();
			}
			if(wParam==VK_F3){
				LICpu_step(&gcpu);
				gui_refresh();
			}
		}
		break;
	}
	
	if((GetKeyState(1)&0x80)||(GetKeyState(2)&0x80)){
		POINT p;
		if(GetCursorPos(&p)){
			ScreenToClient(hwnd, &p);
			if((p.x>=404)&&(p.x<788)&&(p.y>=128)&&(p.y<416)&&(!_gui_dialog_alreadyopen)){
				Int x = (p.x-404)/24;
				Int y = (p.y-128)/24;
				guiset_mem_offset = y*ofs+x;
				guiset_mem_size = (GetKeyState(1)&0x80)?8:32;
				_gui_dialog_value.numeric = guiget_mem(y*ofs+x, guiset_mem_size);
				_gui_dialog_callback = guiset_mem;
				guiset_mem_coff = x;
				guiset_mem_cadr = y;
				gui_showDialog((GetKeyState(1)&0x80)?L"8-bit Memory value":L"32-bit Memory value");
			}
		}
	}
	
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int CmdShow) {
	
	setup();
	
	_hInstance = hInstance;
	_hPrevInstance = hPrevInstance;
	_szCmdLine = szCmdLine;
	_CmdShow = CmdShow;
	
	/* Main Window Setup */
	MSG  msg;    
	WNDCLASSW wc = {0};
	wc.lpszClassName = L"Gui";
	wc.hInstance     = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc   = guiProc;
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	
	RegisterClassW(&wc);
	_gui_gui = CreateWindowW(wc.lpszClassName, L"Janela",
		WS_OVERLAPPED | WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		100, 100, 840, 480, 0, (HMENU)_guid_gui, hInstance, 0); 
	
	gui_refresh();
	
	/* Init GUI Processing */
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	//_main();
	
	return 0;
}


#endif // gui_h
