#include "callbacks.h"
#include <math.h>
#include "resource.h"
const int R = 100;
// Window procedure for our main window.
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	PAINTSTRUCT ps;
		HDC hdc;
		int a, b, x, y;
		static int sx,sy;
		static HPEN hpen1, hpen2;
		switch (msg)
		{
			case WM_SIZE:
				sx = LOWORD(lParam);
				sy = HIWORD(lParam);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case WM_PAINT:
					hdc = BeginPaint (hWnd, &ps);
					a = sx/2;
					b = sy/2;
					SelectObject (hdc,hpen1);
					MoveToEx(hdc,0,b,NULL);
					LineTo (hdc,sx,b);
					MoveToEx(hdc,a,0,NULL);
					LineTo(hdc,a,sy);
					MoveToEx(hdc,a,b,NULL);
					SelectObject (hdc,hpen2);
					for (float angle = 0.0; angle < 2*M_PI; angle += 0.1)
					{
						x = a + R*(1 - cos(angle))*cos(angle);
						y = b - R*(1 - cos(angle))*sin(angle);
						LineTo(hdc, x, y);
					}

					//for (x=0; x<sx; x+=sx/10)
					//{
					//	MoveToEx(hdc,x,0,NULL);
					//	LineTo(hdc,x,sy);
					//}
					//for (y = 0; y <sy; y+= sy/10)
					//{
					//	MoveToEx(hdc,0,y,NULL);
					//	LineTo(hdc,sx,y);
					//}
					//Rectangle (hdc, sx/4, sy/4, sx*3/4, sy*3/4);
					//Ellipse (hdc, sx/3, sy/4, sx*2/3, sy*3/4);
					EndPaint (hWnd,&ps);
					break;
				case WM_COMMAND:
				{
					switch (LOWORD(wParam))
					{
						case ID_HELP_ABOUT:
						{
							DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTDIALOG), hWnd, &AboutDialogProc);
							return 0;
						}

						case ID_FILE_EXIT:
						{
							DestroyWindow(hWnd);
							return 0;
						}
					}
					break;
				}

				case WM_GETMINMAXINFO:
				{
					MINMAXINFO *minMax = (MINMAXINFO*) lParam;
					minMax->ptMinTrackSize.x = 220;
					minMax->ptMinTrackSize.y = 110;
					return 0;
				}
				case WM_SYSCOMMAND:
				{
					switch (LOWORD(wParam))
					{
						case ID_HELP_ABOUT:
						{
							DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTDIALOG), hWnd, &AboutDialogProc);
							return 0;
						}
					}
					break;
				}

				case WM_CREATE:
				{
					hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
					hpen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
					hInstance = ((LPCREATESTRUCT) lParam)->hInstance;
					return 0;
				}

				case WM_DESTROY:
				{
					PostQuitMessage(0);
					return 0;
				}
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
}


// Dialog procedure for our "about" dialog.
INT_PTR CALLBACK AboutDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDOK:
				case IDCANCEL:
				{
					EndDialog(hwndDlg, (INT_PTR) LOWORD(wParam));
					return (INT_PTR) TRUE;
				}
			}
			break;
		}

		case WM_INITDIALOG:
		return (INT_PTR) TRUE;
	}

	return (INT_PTR) FALSE;
}
