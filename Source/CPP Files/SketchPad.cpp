// Paint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SketchPad.h"

// Global Variables \\

#define MAX_LOADSTRING 100

int current_Shape_count = 0;					//Amount of current shapes.

bool mouse_down = false;						//Is the mouse pressed down.

int mouse_down_x = 0;							//Store mouse x/y co-ords.
int mouse_down_y = 0;
int mouse_up_x = 0;
int mouse_up_y = 0;

bool checkToolbar_Line = false;					//Boolians to check the Toolbar.
bool checkToolbar_UFCircle = false;				//Are the Toolbar Buttons Pressed?
bool checkToolbar_UFSquare = false;
bool checkToolbar_FCircle = false;
bool checkToolbar_FSquare = false;

COLORREF BorderColor;							//Border Colour varibles
int br = 0;
int bg = 0;
int bb = 0;

COLORREF FillColor;								//Fill Colour varibles
int fr = 0;
int fg = 0;
int fb = 0;

int clientWidth = 0;							//Clients Width and Height
int clientHeight = 0;

Store s;										// Variable to access the stored shapes
												
Vector2D v0, v1;								// X and Y are stored in the Vectors, the Vectors are stored in the Edge
Edge e0;										// and the Edge is Stored in the Struct with the shapes.

HWND hWndToolbar;								// Create a Global Handle to the Toolbar

HINSTANCE hInst;								// Current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// The main window class name


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);

HWND WINAPI CreateToolBar(HWND hWnd, HINSTANCE hInstance);

BOOL WINAPI ChooseColor();

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT));

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
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL; //NULL background for double buffering
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PAINT);
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	CreateToolBar(hWnd, hInstance); //create a toobar
	ShowWindow(hWnd, nCmdShow); //show the toolbar
	UpdateWindow(hWnd); //update the window

   return TRUE;
}

HWND WINAPI CreateToolBar(HWND hWnd, HINSTANCE hInstance)
{
	 // Define the amount of buttons for the Toolbar.
    const int numButtons = 9;

	//Load custom images
	HIMAGELIST hToolBar = ImageList_LoadImage(hInstance, (LPCTSTR)IDB_TOOLBAR, 16, 1, RGB(192,192,192), IMAGE_BITMAP, LR_CREATEDIBSECTION);

	if(!hToolBar)
	{
		return FALSE;
	}

	//Create toolbar
	hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_BORDER,
								0, 0, 0, 0, hWnd, NULL, hInstance, NULL);

	if (!hWndToolbar)
	{
		return FALSE;
	}

	//Set the images
    SendMessage(hWndToolbar, TB_SETIMAGELIST, (WPARAM)0, (LPARAM)hToolBar);

	//Create the buttons
	TBBUTTON tbButtons[numButtons] = 
    {
	  //{ imageID,		menuID,					Button State,		Button Style,		{?}, ?,	Text},
        { 0,			ID_FILE_NEW,			TBSTATE_ENABLED,	TBSTYLE_BUTTON,		{0}, 0, (INT_PTR)L"New"},
		{ 1,			ID_DRAW_ERASE,			TBSTATE_ENABLED,	TBSTYLE_BUTTON,		{0}, 0, (INT_PTR)L"Undo"},
		{ 2,			ID_DRAW_LINE,			TBSTATE_ENABLED,	TBSTYLE_CHECKGROUP, {0}, 0, (INT_PTR)L"Line"},
        { 3,			ID_DRAW_UFCIRCLE,		TBSTATE_ENABLED,	TBSTYLE_CHECKGROUP, {0}, 0, (INT_PTR)L"Circle"},
        { 4,			ID_DRAW_UFSQUARE,		TBSTATE_ENABLED,	TBSTYLE_CHECKGROUP, {0}, 0, (INT_PTR)L"Square"},
		{ 5,			ID_DRAW_FCIRCLE,		TBSTATE_ENABLED,	TBSTYLE_CHECKGROUP, {0}, 0, (INT_PTR)L"Circle"},
        { 6,			ID_DRAW_FSQUARE,		TBSTATE_ENABLED,	TBSTYLE_CHECKGROUP, {0}, 0, (INT_PTR)L"Square"},
		{ 7,			ID_COLOR_BORDERCOLOR,	TBSTATE_ENABLED,	TBSTYLE_BUTTON,		{0}, 0, (INT_PTR)L"Border"},
		{ 7,			ID_COLOR_FILLCOLOR,		TBSTATE_ENABLED,	TBSTYLE_BUTTON,		{0}, 0, (INT_PTR)L"Fill"}
    };

	SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hWndToolbar, TB_ADDBUTTONS, numButtons, (LPARAM)&tbButtons);
	SendMessage(hWndToolbar, TB_SETBITMAPSIZE, (WPARAM)0, (LPARAM)MAKELONG(16,16));

	SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0); 
	ShowWindow(hWndToolbar , SW_SHOW);

   return hWndToolbar;
}

// Create a Color Dialog
BOOL ChooseColor(HWND hWnd)
{
	CHOOSECOLOR cc;
	static COLORREF CustCol[16];
	static DWORD rgbCurrent;

	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hWnd;
	cc.lpCustColors = (LPDWORD) CustCol;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT | CC_SOLIDCOLOR;
 
	if (ChooseColor(&cc) == TRUE) 
	{	
		rgbCurrent = cc.rgbResult;
	}

	return rgbCurrent; //return color selected
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

	// define custom functions
	void NewPaint(HWND);
	void ReDraw(HDC&);
	void CheckToolbar();
	void ResetCoOrd();
	void Undo(HWND);

	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_FILE_NEW:
			{
			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_FILE_NEW, 1);
			NewPaint(hWnd);												//NewPaint erasers all shapes leaving a black page.
			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_FILE_NEW, 0);
			}
			break;
		case ID_DRAW_LINE:
			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_DRAW_LINE, 1);	//if the menu button for draw line is selected, select the line button on the toolbar
			CheckToolbar();												//CheckToolBar checks to see if any of the relevant buttons are pressed.
			ResetCoOrd();												//RestCoOrds resets the coords for shape drawing, stops unwanted drawing.
			break;
		case ID_DRAW_ERASE:
			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_DRAW_ERASE, 1);
			Undo(hWnd);													//undo erasers the last drawn shape.
			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_DRAW_ERASE, 0);
			break;
		case ID_DRAW_UFCIRCLE:
			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_DRAW_UFCIRCLE, 1);
			CheckToolbar();
			ResetCoOrd();
			break;
		case ID_DRAW_UFSQUARE:
			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_DRAW_UFSQUARE, 1);
			CheckToolbar();
			ResetCoOrd();
			break;
		case ID_DRAW_FCIRCLE:
			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_DRAW_FCIRCLE, 1);
			CheckToolbar();
			ResetCoOrd();
			break;
		case ID_DRAW_FSQUARE:
			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_DRAW_FSQUARE, 1);
			CheckToolbar();
			ResetCoOrd();
			break;
		case ID_COLOR_BORDERCOLOR:
			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_COLOR_BORDERCOLOR, 1);

			BorderColor = ChooseColor(hWnd);									//Open the color dialog to pick a border color.
			br = GetRValue(BorderColor);
			bg = GetGValue(BorderColor);
			bb = GetBValue(BorderColor);

			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_COLOR_BORDERCOLOR, 0);
			break;
		case ID_COLOR_FILLCOLOR:
			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_COLOR_FILLCOLOR, 1);

			FillColor = ChooseColor(hWnd);										//Open the color dialog to pick a fill color.
			fr = GetRValue(FillColor);
			fg = GetGValue(FillColor);
			fb = GetBValue(FillColor);

			SendMessage(hWndToolbar, TB_CHECKBUTTON, ID_COLOR_FILLCOLOR, 0);
			break;
		case ID_HELP_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_SIZE:
		SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);		//resize the toolbar when the application is resized.
		ShowWindow(hWndToolbar, SW_SHOW);					//show the toolbar.
		break;
	case WM_PAINT:
		{
		hdc = BeginPaint(hWnd, &ps);

		//get client.
		RECT client;
		GetClientRect(hWnd, &client);

		//Find width/height.
		clientWidth = client.right - client.left;
		clientHeight = client.bottom + client.left;

		//create double buffering
		HDC bdc = CreateCompatibleDC(hdc);
		HBITMAP backbuff = CreateCompatibleBitmap( hdc, clientWidth, clientHeight);
		HGDIOBJ oldobj = SelectObject( bdc, backbuff);

		//draw rect around client area
		Rectangle(bdc, client.left, client.top, client.right, client.bottom);

		//draw line
		if(checkToolbar_Line)
		{
			Draw_Line(bdc, e0, BorderColor);
		}

		//draw filled square
		if(checkToolbar_FSquare)
		{
			Draw_Square(bdc, e0, BorderColor, FillColor, true);
		}

		//draw filled circle
		if(checkToolbar_FCircle)
		{
			Draw_Circle(bdc, e0, BorderColor, FillColor, true);
		}

		//draw unfilled square
		if(checkToolbar_UFSquare)
		{
			Draw_Square(bdc, e0, BorderColor, FillColor, false);
		}

		//draw unfilled circle
		if(checkToolbar_UFCircle)
		{
			Draw_Circle(bdc, e0, BorderColor, FillColor, false);
		}

		ReDraw(bdc);		//ReDraws all of the shapes stored in Store.ccp

		//copy content from bdc to hdc
		BitBlt(hdc, 0, 0, clientWidth, clientHeight, bdc, 0, 0, SRCCOPY);

		// select and delete objects
		SelectObject(bdc, oldobj);
		DeleteObject(backbuff);
		DeleteDC(bdc);
		ReleaseDC(hWnd, hdc);
		
		EndPaint(hWnd, &ps);
		}
		break;
	case WM_LBUTTONDOWN:

		mouse_down = true;

		//set coords when needed on left mouse button down.
		if(checkToolbar_Line || checkToolbar_UFSquare || checkToolbar_FSquare || checkToolbar_UFCircle || checkToolbar_FCircle)
		{
			mouse_down_x = LOWORD(lParam);
			mouse_down_y = HIWORD(lParam);

			//SET Vectors & Edge
			v0.SetX(mouse_down_x), v0.SetY(mouse_down_y);
			e0.SetV0(v0);
		}

		break;
	case WM_MOUSEMOVE:

		//set coords when needed on mouse move.
		if(checkToolbar_Line || checkToolbar_UFSquare || checkToolbar_FSquare || checkToolbar_UFCircle || checkToolbar_FCircle)
		{
			if ( mouse_down )
			{
				mouse_up_x = LOWORD(lParam);
				mouse_up_y = HIWORD(lParam);

				//SET Vectors & Edge
				v1.SetX(mouse_up_x), v1.SetY(mouse_up_y);
				e0.SetV1(v1);
			}
		}

		//repaint screen
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_LBUTTONUP:

		mouse_down = false;

		mouse_up_x = LOWORD(lParam);
		mouse_up_y = HIWORD(lParam);

		//SET Vectors & Edge
		v1.SetX(mouse_up_x), v1.SetY(mouse_up_y);
		e0.SetV1(v1);

		//Store shapes when finished drawing or on left mouse button up.
		if(checkToolbar_Line)
		{
			//store the Line
			Store(0, current_Shape_count, e0, BorderColor, FillColor, false);

			//increment shape count or reset
			if(current_Shape_count < 10000) {current_Shape_count += 1;} else {current_Shape_count = 0;}
		}

		if(checkToolbar_UFSquare)
		{
			//store the UnFilled Square
			Store(1, current_Shape_count, e0, BorderColor, FillColor, false);

			//increment shape count or reset
			if(current_Shape_count < 10000) {current_Shape_count += 1;} else {current_Shape_count = 0;}
		
		}

		if(checkToolbar_FSquare)
		{
			//store the Filled Square
			Store(1, current_Shape_count, e0, BorderColor, FillColor, true);

			//increment shape count or reset
			if(current_Shape_count < 10000) {current_Shape_count += 1;} else {current_Shape_count = 0;}
		
		}

		if(checkToolbar_UFCircle)
		{
			//store the UnFilled Circle
			Store(2, current_Shape_count, e0, BorderColor, FillColor, false);

			//increment shape count or reset
			if(current_Shape_count < 10000) {current_Shape_count += 1;} else {current_Shape_count = 0;}
		}

		if(checkToolbar_FCircle)
		{
			//store the Filled Circle
			Store(2, current_Shape_count, e0, BorderColor, FillColor, true);

			//increment shape count or reset
			if(current_Shape_count < 10000) {current_Shape_count += 1;} else {current_Shape_count = 0;}
		}
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

//resets the coords.
void ResetCoOrd()
{
	mouse_down_x = 0;
	mouse_down_y = 0;
	mouse_up_x = 0;
	mouse_up_y = 0;

	v0.SetX(mouse_down_x), v0.SetY(mouse_down_y);
	v1.SetX(mouse_up_x), v1.SetY(mouse_up_y);
	e0.SetV0(v0);
	e0.SetV1(v1);
}

//clears the canvas.
void NewPaint(HWND hWnd)
{
	int j = 0;

	ResetCoOrd();

	j = current_Shape_count;
	for ( int i = 0; i < j; i++ )
	{
		s.SetEdge(i, e0);
		s.SetBC(i, 0);
		s.SetFC(i, 0);
		s.SetFill(i, false);
	}
	current_Shape_count = 0;

	InvalidateRect(hWnd, NULL, true);
}

//checks the toolbar for active and inactive buttons.
void CheckToolbar()
{
	//check to see which toolbar button is checked
	if(SendMessage(hWndToolbar, TB_ISBUTTONCHECKED, ID_DRAW_LINE, 0) != 0)
	{checkToolbar_Line = true;} else {checkToolbar_Line = false;}

	if(SendMessage(hWndToolbar, TB_ISBUTTONCHECKED, ID_DRAW_UFCIRCLE, 0) != 0)
	{checkToolbar_UFCircle = true;} else {checkToolbar_UFCircle = false;}

	if(SendMessage(hWndToolbar, TB_ISBUTTONCHECKED, ID_DRAW_UFSQUARE, 0) != 0)
	{checkToolbar_UFSquare = true;} else {checkToolbar_UFSquare = false;}

	if(SendMessage(hWndToolbar, TB_ISBUTTONCHECKED, ID_DRAW_FCIRCLE, 0) != 0)
	{checkToolbar_FCircle = true;} else {checkToolbar_FCircle = false;}

	if(SendMessage(hWndToolbar, TB_ISBUTTONCHECKED, ID_DRAW_FSQUARE, 0) != 0)
	{checkToolbar_FSquare = true;} else {checkToolbar_FSquare = false;}
}

// A Redraw Function
// This Redraws all of the shapes currently stored.
void ReDraw(HDC& bdc)
{
	int j = 0;
	int i = 0;

	j = current_Shape_count;
	for (i = 0; i < j; i++ )
	{
		if(s.GetType(i) == 0)
		{
			Draw_Line(bdc, s.GetEdge(i), s.GetBC(i));
		}
		if(s.GetType(i) == 1)
		{
			Draw_Square(bdc, s.GetEdge(i), s.GetBC(i), s.GetFC(i), s.GetFill(i));
		}
		if(s.GetType(i) == 2)
		{
			Draw_Circle(bdc, s.GetEdge(i), s.GetBC(i), s.GetFC(i), s.GetFill(i));
		}
	}
}

// The Eraser function (simply an undo script)
// This removes the last shape drawn if a shape exists.
void Undo(HWND hWnd)
{
	if(current_Shape_count > 0)
	{
		int i = current_Shape_count;

		ResetCoOrd();

		s.SetEdge(i, e0);
		s.SetBC(i, 0);
		s.SetFC(i, 0);
		s.SetFill(i, false);

		current_Shape_count -= 1;

		InvalidateRect(hWnd, NULL, true);
	}
}