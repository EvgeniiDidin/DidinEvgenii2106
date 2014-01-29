//Exap project.
//Created by Didin Yevgenii, group 2016
#include <windows.h>
#include <math.h>
HWND hMainWnd;
HWND hEdit;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	HWND Button;
	HWND rButton1, rButton2, rButton3;
	char szClassName[] = "MyClass";
	MSG msg;
	WNDCLASSEX wc;

	// filling struct of window class
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Hello1";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Register Window class
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, TEXT("Cannot register class"), TEXT("Error"), MB_OK);
		return 0;
	}

	// Create main window
	hMainWnd = CreateWindow(
		TEXT("Hello1"), TEXT("A Hello1 Application"), WS_OVERLAPPEDWINDOW,
		200, 200, 620, 380,
		(HWND)NULL, (HMENU)NULL,
		(HINSTANCE)hInstance, NULL
		);

	if (!hMainWnd) {
		MessageBox(NULL, TEXT("Cannot create main window"), TEXT("Error"), MB_OK);
		return 0;
	}
	Button = CreateWindow(TEXT("button"), TEXT("Press me"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 10, 80, 30, hMainWnd, (HMENU)10000, hInstance, NULL);								//here (hmenu)10000 is descriptor of child window class
	hEdit = CreateWindow(TEXT("EDIT"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE,
		100, 10, 500, 50, hMainWnd, NULL, hInstance, NULL);

	ShowWindow(hMainWnd, nCmdShow);				//call paint func in callback

	
	while (GetMessage(&msg, NULL, 0, 0)) //cycle of getting messages
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);			
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	POINT pt[1000];
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;

	switch (msg)
	{
	case WM_COMMAND:
		
		hDC = GetDC(hWnd);
		pt[0].x = 0;
		pt[0].y = 190;
		MoveToEx(hDC, pt[0].x, pt[0].y, NULL);
		for (int i = 1; i < 500; i++)
		{
			pt[i].x = pt[i - 1].x + 1;
			pt[i].y =pt[i-1].y - sin(pt[i-1].x/4)*8;
			LineTo(hDC, pt[i].x, pt[i].y);
		}
		
		break;
	case WM_SIZE:

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);		//hDC -context of device

		GetClientRect(hWnd, &rect);					// params of hWnd go to rect
		EndPaint(hWnd, &ps);			
		return 0;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}
