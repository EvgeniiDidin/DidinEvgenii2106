//Exap project.
//Created by Didin Yevgenii, group 2016
#include <windows.h>
#include <math.h>
#include "inf2post.h"
#include "calc.h"
HWND hMainWnd;
HWND hEdit;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 
	HWND Button;
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
		100, 10, 500, 50, hMainWnd, (HMENU)1000, hInstance, NULL);

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
	double realnumbarr[10000];
	char postfix[100][100];
	TCHAR enterstring[100];
	char char_enterstring[100];
	char* string = calloc(100, 1);
	char* poststring=calloc(100,1);
	double d=3.1415/310;	//params for drawing
	int k=20, l=180;
	HBRUSH hBr;
	POINT pt[1000];
	POINT xOy[4] = { { 0, 190 }, { 620, 190 }, { 310, 0 }, { 310, 380 } };
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;


	switch (msg)
	{
	case WM_COMMAND:
		
		
		if (LOWORD(wParam) == 10000){
			hDC = GetDC(hWnd);
			GetDlgItemText(hWnd, LOWORD(1000), enterstring, 100);
			CharToOemW(enterstring, char_enterstring); //Transforms TCHAR to char*
			
			First_Transformation(char_enterstring, string);
			PostfixNotation(string, poststring);
			Get_Two_Dimensional_Char_Array(poststring, postfix);
			Get_Double_Array(postfix, realnumbarr); //making array of double to use it later in calculation
			SetRect(&rect, 0, 60, 620, 380);
			hBr = CreateSolidBrush(RGB(255, 255, 255));
			FillRect(hDC, &rect, hBr);

			//MoveToEx(hDC, xOy[0].x, xOy[0].y, NULL); //drawing Ox		//it doesn't work/ didnt found solution
			//LineTo(hDC, xOy[1].x, xOy[1].y, NULL);
			//MoveToEx(hDC, xOy[2].x, xOy[2].y, NULL); //drawing Oy
			//LineTo(hDC, xOy[3].x, xOy[3].y, NULL);
			l = 180;
			pt[0].x = 0;
			pt[0].y = 190;
			MoveToEx(hDC, pt[0].x, pt[0].y, NULL);
			for (int i = 1; i < 700; i++)
			{
			pt[i].x = pt[i - 1].x + 1;
			pt[i].y = 190 - Calc((pt[i].x - 310 )/ d / k / l, postfix, realnumbarr) *k;
			LineTo(hDC, pt[i].x, pt[i].y);
			}
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
