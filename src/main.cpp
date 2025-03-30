#include "system_lib.h"

//#############################################################################
//								PLATFORM GLOBALS
//#############################################################################
static bool running = true;

//#############################################################################
//								PLATFORM FUNCTIONS
//#############################################################################
bool platform_create_window(int width, int height,char* name);
void platform_update_window();

//#############################################################################
//								WINDOWS PLATFORM
//#############################################################################
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

//#############################################################################
//								WINDOWS GLOBALS
//#############################################################################

static HWND window;

//#############################################################################
//								PLATFORM IMPLEMENTATIONS
//#############################################################################
LRESULT CALLBACK windows_window_callback(HWND window, UINT msg,
										WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	
	switch(msg)
	{
		case WM_CLOSE:
		{
			running = false;
			break;
		}
		default:
		{
			result = DefWindowProcA(window, msg, wParam, lParam);
		}
	}

	return result;

}

bool platform_create_window(int width, int height,char* name)
{
	HINSTANCE instance = GetModuleHandleA(0);

	WNDCLASSA wc = {};
	wc.hInstance = instance;
	wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = name;
	wc.lpfnWndProc = windows_window_callback;

	if(!RegisterClassA(&wc))
	{
		return false;
	}

	int dwStyle = WS_OVERLAPPEDWINDOW;

	window = CreateWindowExA(WS_EX_LAYERED,name,
									name,
									dwStyle,
									100,
									100,
									width,
									height,
									NULL,
									NULL,
									instance,
									NULL);

	
	if(window == NULL)
	{
		return false;
	}

	SetLayeredWindowAttributes(window, 0, 200, LWA_ALPHA);

	ShowWindow(window,SW_SHOW);

	return true;

}

void platform_update_window()
{
	MSG msg;

	while(PeekMessageA(&msg, window, 0,0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}


#endif

int main()
{
	platform_create_window(720, 480,"The System");
	while(running)
    {
        //update
		platform_update_window();

		SM_TRACE("Test");
		SM_WARN("Test");
		SM_ERROR("Test");
		SM_ASSERT(false,"Assertion hit");
    }
 
    return 0;
}