#ifndef windows_display_h
#define windows_display_h

#include <windows.h>
#include <stdint.h>


typedef struct WinDisplay{
	WNDCLASS wclass;
	HWND window;
	HDC ctx;
	int client_width, client_height;
	BITMAPINFO bitmap_info;
	int bitmap_width, bitmap_height;
	void* bitmap_data;
}WinDisplay;


void WinInit(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow);

void WinCreateDisplay(WinDisplay *display, int mapwidth, int mapheight, int winwidth, int winheight);

int WinRenderizeDisplay(WinDisplay *display);


#endif // windows_display_h
