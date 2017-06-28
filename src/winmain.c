#include <windows.h>
#include <commctrl.h>
//#include <vectors.h>
#include "resource.h"
#include "callbacks.h"

HWND hTwindow;
HWND hGwindow;
HWND hTool;

// Our application entry point.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	INITCOMMONCONTROLSEX icc;
	CLIENTCREATESTRUCT ccs;
	WNDCLASSEX wc;
	LPCTSTR MainWndClass = TEXT("Win32 Test application");
	//LPCTSTR ToolWnd = TEXT("Tool Window");
	HWND hWnd;
	HACCEL hAccelerators;
	HMENU hSysMenu;
	MSG msg;
	TBBUTTON tbb[3];
	TBADDBITMAP tbab;
	HIMAGELIST g_hImageList = NULL;
	RECT rcTool;
	int iToolHeight;

	HWND hStatus;
	RECT rcStatus;
	int iStatusHeight;

	HWND hEdit;
	int iEditHeight;
	RECT rcClient;

	// Initialise common controls.
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

  // Class for our main window.
	wc.cbSize		= sizeof(wc);
	wc.style		= 0;
	wc.lpfnWndProc	= &MainWndProc;
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hInstance	= hInstance;
	wc.hIcon		= (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_DEFAULTCOLOR | LR_SHARED);
	wc.hCursor		= (HCURSOR) LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);
	wc.hbrBackground	= (HBRUSH) (COLOR_BTNFACE + 1);
	wc.lpszMenuName		= MAKEINTRESOURCE(IDR_MAINMENU);
	wc.lpszClassName	= MainWndClass;
	wc.hIconSm			= (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON,
							GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON),
							LR_DEFAULTCOLOR | LR_SHARED);

	// Register our window classes, or error.
	if (! RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Error registering window class."), TEXT("Error"), MB_ICONERROR | MB_OK);
		return 0;
	}

	// Create instance of main window.
	hWnd = CreateWindowEx(0, MainWndClass, MainWndClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
							520, 200, NULL, NULL, hInstance, NULL);

	// Error if window creation failed.
	if (! hWnd)
	{
		MessageBox(NULL, TEXT("Error creating main window."), TEXT("Error"), MB_ICONERROR | MB_OK);
		return 0;
	}

	// Load accelerators.
	hAccelerators = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));

	// Add "about" to the system menu.
	hSysMenu = GetSystemMenu(hWnd, FALSE);
	InsertMenu(hSysMenu, 5, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
	InsertMenu(hSysMenu, 6, MF_BYPOSITION, ID_HELP_ABOUT, TEXT("About"));

		hTwindow  = CreateWindowEx(0, MainWndClass, NULL, WS_CHILD | WS_VISIBLE|WS_OVERLAPPED , 0, 0, 100, 16,
				hWnd, NULL, GetModuleHandle(NULL), NULL);
		if (! hTwindow)
			{
				MessageBox(NULL, TEXT("Error creating hTwindow."), TEXT("Error"), MB_ICONERROR | MB_OK);
				return 0;
			}

		UpdateWindow(hTwindow);
		hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE |WS_BORDER , 0, CW_USEDEFAULT, 0, 0,
				/*hWnd*/hTwindow, (HMENU)IDC_MAIN_TOOL, GetModuleHandle(NULL), NULL);

		if (! hTool)
			{
				MessageBox(NULL, TEXT("Error creating hTool."), TEXT("Error"), MB_ICONERROR | MB_OK);
				return 0;
			}
		SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

		tbab.hInst = HINST_COMMCTRL;
		tbab.nID = IDB_STD_SMALL_COLOR;
		ZeroMemory(tbb, sizeof(tbb));
		tbb[0].iBitmap = STD_FILENEW;
		tbb[0].fsState = TBSTATE_ENABLED;
		tbb[0].fsStyle = TBSTYLE_BUTTON;
		tbb[0].idCommand = IDC_NEW;

		tbb[1].iBitmap = STD_FILEOPEN;
		tbb[1].fsState = TBSTATE_ENABLED;
		tbb[1].fsStyle = TBSTYLE_BUTTON;
		tbb[1].idCommand = IDC_OPEN;

		tbb[2].iBitmap = STD_FILESAVE;
		tbb[2].fsState = TBSTATE_ENABLED;
		tbb[2].fsStyle = TBSTYLE_BUTTON;
		tbb[2].idCommand = IDC_SAVE;

		SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbab);

		SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb)/sizeof(TBBUTTON), (LPARAM)&tbb);
//		SendMessage(hTool, TB_AUTOSIZE, 0, 0);
		SendMessage(hTwindow, TB_AUTOSIZE, 0, 0);

		ccs.hWindowMenu  = GetSubMenu(GetMenu(hWnd), 2);
		ccs.idFirstChild = ID_MDI_FIRSTCHILD;
		hGwindow  = CreateWindowEx(WS_EX_CLIENTEDGE, MainWndClass, NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,0
							, 30, 100, 100,
				hWnd, (HMENU)IDC_MAIN_MDI, GetModuleHandle(NULL), (LPVOID)&ccs);
		if (! hGwindow)
			{
				MessageBox(NULL, TEXT("Error creating hTwindow."), TEXT("Error"), MB_ICONERROR | MB_OK);
				return 0;
			}
/*
	hTool = GetDlgItem(hWnd, IDC_MAIN_TOOL);
	SendMessage(hTool, TB_AUTOSIZE, 0, 0);

	GetWindowRect(hTool, &rcTool);
	iToolHeight = rcTool.bottom - rcTool.top;

	// Calculate remaining height and size edit

	GetClientRect(hWnd, &rcClient);

	iEditHeight = rcClient.bottom - iToolHeight;

	hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
*/
//	SetWindowPos(hTool, NULL, 0, 200, 100, 100, SWP_NOZORDER);
//	SetWindowPos(hWnd, NULL, 400, 400, rcClient.right, iEditHeight, SWP_NOZORDER);

	// Show window and force a paint.
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop.
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		if (! TranslateAccelerator(msg.hwnd, hAccelerators, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}
