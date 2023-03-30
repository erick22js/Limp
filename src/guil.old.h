#ifndef gui_h
#define gui_h

#include <windows.h>
#include <wchar.h>

#define Ui HWND

#define gui_ui_text(txt, id, x, y, w, h) CreateWindowW(L"Static", txt, WS_CHILD | WS_VISIBLE | SS_LEFT, x, y, w, h, hwnd, (HMENU) id, NULL, NULL)
#define gui_ui_button(txt, id, x, y, w, h) CreateWindowW(L"Button", txt, WS_VISIBLE | WS_CHILD , x, y, w, h, hwnd, (HMENU) id, NULL, NULL)
#define gui_ui_checkbox(txt, id, x, y, w, h) CreateWindowW(L"button", txt, WS_VISIBLE | WS_CHILD | BS_CHECKBOX, x, y, w, h, hwnd, (HMENU) id, NULL, NULL)
#define gui_ui_edit(txt, id, x, y, w, h) CreateWindowW(L"Edit", txt, WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, w, h, hwnd, (HMENU) id, NULL, NULL)

#define gui_is_checked(id) IsDlgButtonChecked(hwnd, id)

#define gui_get_text(ui, txt, len) GetWindowTextW(ui, txt, len)
#define gui_get_textSize(ui) GetWindowTextLengthW(ui)

#define gui_set_checked(id, state) CheckDlgButton(hwnd, id, state)
#define gui_set_text(ui, txt) SetWindowTextW(ui, txt)



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	int id_beep = 1;
	int id_check = 2;
	int id_edit = 3;
	int id_btn = 4;
	
	static Ui texto;
	static Ui edit;
	
	switch(msg){
		/* Define o layout da janela na sua criação */
		case WM_CREATE:{
			texto = gui_ui_text(L"Ola Mundo!", -1, 0, 100, 100, 20);
			gui_ui_button(L"Windows", id_beep, 20, 50, 80, 25);
			edit = gui_ui_edit(L"Default", id_edit, 0, 250, 150, 20);
			gui_ui_button(L"Usar", id_btn, 150, 250, 80, 25);
			gui_ui_checkbox(L"Show Title", id_check, 20, 20, 185, 35);
			
		}
		break;
		/* Eventos dispachados pelos elementos */
		case WM_COMMAND:{
			if (LOWORD(wParam) == id_beep){
				MessageBeep(MB_OK);
			}
			if (LOWORD(wParam) == id_btn){
				int len = gui_get_textSize(edit) + 1;
				wchar_t text[len];

				gui_get_text(edit, text, len);
				gui_set_text(texto, text);
            }
            if(LOWORD(wParam) == id_check){
				Bool checked = gui_is_checked(id_check);
				gui_set_checked(id_check, !checked);
            }
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
			printf("Pressed key 0x%x\n", wParam);
		}
		break;
	}
	
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int CmdShow) {

	//MessageBoxW(NULL, L"Ola GUI!", L"Titulo", MB_OK);

	MSG  msg;    
	WNDCLASSW wc = {0};
	wc.lpszClassName = L"Center";
	wc.hInstance     = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc   = WndProc;
	wc.hCursor       = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);
	CreateWindowW(wc.lpszClassName, L"Janela",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, 800, 480, 0, 0, hInstance, 0); 

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	_main();

	return 0;
}


#endif // gui_h
