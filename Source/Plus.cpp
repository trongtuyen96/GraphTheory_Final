// Plus.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Plus.h"
#include "DAY_CAO_THE.h"
#define Max 100
#define value 40
#define MAX_LOADSTRING 100



// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void WholeCity(HDC hdc)
{
	Graphics graphics(hdc);
	DAY_CAO_THE map;
	int a[Max][Max];
	int m;
	int n;
	map.input("Input.txt", a, m, n);
	Pen pen(Color(255, 0, 0, 0), 2.0F);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			graphics.DrawRectangle(&pen, j*value + value/20, i*value + value/20, value - value/10, value - value/10);
		}
	}
	graphics.DrawRectangle(&pen, 0, 0, value*n, value*m);
	/*HatchBrush hBrush(HatchStyleDiagonalCross, Color(255, 0, 0, 0), Color(0, 0, 0, 0));
	for (int i = 0; i < map.Wall.size(); i++)
	{
		graphics.FillRectangle(&hBrush, (map.Wall[i].x - 1)*value + value / 20, (map.Wall[i].y - 1)*value + value / 20, value - value / 10, value - value / 10);
	}*/
	Image image(L"brick3.png");
	for (int i = 0; i < map.Wall.size(); i++)
	{
		graphics.DrawImage(&image, (map.Wall[i].x - 1)*value + value / 20, (map.Wall[i].y - 1)*value + value / 20, value - value / 10, value - value / 10);
	}
	map.Chi_phi_min(a, m, n);
	
	// Draw Line
	Pen pen3(Color::Red, 4.0F);
	for (int i = 0; i < map.Duong_noi_DCT.size(); i++)
	{
		for (int j = 1; j < map.Duong_noi_DCT[i].ListOfPoint.size(); j++)
		{
			graphics.DrawLine(&pen3, (map.Duong_noi_DCT[i].ListOfPoint[j].y - 1)*value + value/2, (map.Duong_noi_DCT[i].ListOfPoint[j].x - 1)*value + value/2, (map.Duong_noi_DCT[i].ListOfPoint[j - 1].y - 1)*value + value/2, (map.Duong_noi_DCT[i].ListOfPoint[j - 1].x - 1)*value + value/2);
		}
	}
	// Draw String
	map.output("Output.txt", a, m, n);
	SolidBrush  brush(Color(255, 0, 0, 0));
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, value / 2 + 4, FontStyleRegular, UnitPixel);


	for (int i = 1; i < map.Khu_Dan_Cu.size(); i++)
	{
		Pen pen2(Color::Red, 8.0F);
		if (i == 2)
		{
			pen2.SetColor(Color::Blue);
		}
		if (i == 3)
		{
			pen2.SetColor(Color::Green);
		}
		if (i == 4)
		{
			pen2.SetColor(Color::Yellow);
		}
		if (i == 5)
		{
			pen2.SetColor(Color::Purple);
		}
		if (i == 6)
		{
			pen2.SetColor(Color::Orange);
		}
		if (i == 7)
		{
			pen2.SetColor(Color::DarkBlue);
		}
		if (i == 8)
		{
			pen2.SetColor(Color::Brown);
		}
		if (i == 9)
		{
			pen2.SetColor(Color::Pink);
		}
		if (i == 10)
		{
			pen2.SetColor(Color::Gray);
		}

		// Draw Home
		int m = i;
		WCHAR C[16];
		swprintf(C, sizeof(C) / sizeof(*C), L"%d", m);
		SolidBrush pen4(Color::White);
		for (int j = 0; j < map.Khu_Dan_Cu[i].Can_ho.size(); j++)
		{
			graphics.FillRectangle(&pen4, (map.Khu_Dan_Cu[i].Can_ho[j].y - 1)*value + 2, (map.Khu_Dan_Cu[i].Can_ho[j].x - 1)*value + 2, value - 4, value - 4);
			PointF      pointf((map.Khu_Dan_Cu[i].Can_ho[j].y - 1)*value + value/4, (map.Khu_Dan_Cu[i].Can_ho[j].x - 1)*value + value/6);
			graphics.DrawString(C, -1, &font, pointf, &brush);
			graphics.DrawRectangle(&pen2, (map.Khu_Dan_Cu[i].Can_ho[j].y - 1)*value + 6, (map.Khu_Dan_Cu[i].Can_ho[j].x - 1)*value + 6, value - 12, value - 12);
		}

	}
	// Draw Factory 
	/*for (int i = 0; i < map.Fac.size(); i++)
	{
		PointF      pointf((map.Fac[i].x - 1)*value + value/6, (map.Fac[i].y - 1)*value + value/6);
		graphics.DrawString(L"X", -1, &font, pointf, &brush);
	}*/
	Image image2(L"factory.png");
	for (int i = 0; i < map.Fac.size(); i++)
	{
		graphics.DrawImage(&image2, (map.Fac[i].x - 1)*value + value / 20, (map.Fac[i].y - 1)*value + value / 20, value - value / 10, value - value / 10);
	}

}




int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PLUS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PLUS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLUS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PLUS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		WholeCity(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
