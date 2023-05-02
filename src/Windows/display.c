#define UNICODE

#include <Windows/display.h>

HINSTANCE gInstance;
HINSTANCE gPrevInstance;
PWSTR gCmdLine;
int gCmdShow;

typedef uint32_t u32;


LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {
    switch(Message) {
        case WM_DESTROY: { PostQuitMessage(0); } break;
        default: { return DefWindowProc(Window, Message, WParam,  LParam); }
    }
    return 0;
}


void WinCreateDisplay(WinDisplay *display, int mapwidth, int mapheight, int winwidth, int winheight){
	//display->wclass = {};
	memset(&display->wclass, 0, sizeof(display->wclass));
	const wchar_t ClassName[] = L"Windows Display";
	display->wclass.lpfnWndProc = WindowProc;
	display->wclass.hInstance = gInstance;
	display->wclass.lpszClassName = ClassName;
	display->wclass.hCursor = LoadCursor(0, IDC_ARROW);
	
	if(!RegisterClass(&display->wclass)) {
		MessageBox(0, L"RegisterClass failed", 0, 0);
		return GetLastError();
	}

	display->window = CreateWindowEx(0, ClassName, L"Windows Display",
		WS_OVERLAPPED | WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		400, 200, winwidth, winheight, 0, 0, gInstance, 0);

	if(!display->window) {
		MessageBox(0, L"CreateWindowEx failed", 0, 0);
		return GetLastError();
	}


	// Get client area dimensions 
	RECT ClientRect;
	GetClientRect(display->window, &ClientRect);
	display->client_width = ClientRect.right - ClientRect.left;
	display->client_height = ClientRect.bottom - ClientRect.top;

	display->bitmap_width = mapwidth;
	display->bitmap_height = mapheight;

	// Allocate memory for the bitmap
	int BytesPerPixel = 4;

	display->bitmap_data = VirtualAlloc(0,
								display->bitmap_width * display->bitmap_height * BytesPerPixel,
								MEM_RESERVE|MEM_COMMIT,
								PAGE_READWRITE
								);
	
	// BitmapInfo struct for StretchDIBits
	display->bitmap_info.bmiHeader.biSize = sizeof(display->bitmap_info.bmiHeader);
	display->bitmap_info.bmiHeader.biWidth = display->bitmap_width;
	// Negative height makes top left as the coordinate system origin for the DrawPixel function, otherwise its bottom left
	display->bitmap_info.bmiHeader.biHeight = -display->bitmap_height;
	display->bitmap_info.bmiHeader.biPlanes = 1;
	display->bitmap_info.bmiHeader.biBitCount = 32;
	display->bitmap_info.bmiHeader.biCompression = BI_RGB;

	display->ctx = GetDC(display->window);
}


int WinRenderizeDisplay(WinDisplay *display){
	MSG Message;
	display->has_focus = GetForegroundWindow()==display->window;
	while(PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) {
		if(Message.message == WM_QUIT){return 0;}
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	
	StretchDIBits(display->ctx, 
		0, 0,
		display->client_width, display->client_height,
		0, 0,
		display->bitmap_width, display->bitmap_height,
		display->bitmap_data, &display->bitmap_info,
		DIB_RGB_COLORS, SRCCOPY);
	return 1;
}


void WinInit(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow){
	gInstance = Instance;
	gPrevInstance = PrevInstance;
	gCmdLine = CmdLine;
	gCmdShow = CmdShow;
}
