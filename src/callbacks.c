#include "callbacks.h"
#include <commctrl.h>
#include <Commdlg.h>
#include <math.h>
#include "resource.h"
#include <winsock2.h>
#include <vectors.h>
//const int R = 100;

static struct tStimSetup StimSetup;
// Window procedure for our main window.
LRESULT CALLBACK MainWndProc(HWND hWnd,  UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	PAINTSTRUCT ps;
	HDC hdc;
	HWND g_hToolbar = NULL;
	int a, b, x, y;
	static int sx,sy;
	static HPEN hpen1, hpen2;
	switch (msg)
	{
		OPENFILENAME ofn;
		char szFileName[MAX_PATH] = "";
		case WM_LBUTTONDOWN:
		{
			//LoadTextFileToEdit();
			break;
		}

		case WM_SIZE:
		{
			extern HWND hTwindow;
			extern HWND hGwindow;
            RECT rcClient;
			extern HWND hTool;
			sx = LOWORD(lParam);
			sy = HIWORD(lParam);
			InvalidateRect(hWnd, NULL, TRUE);
			MoveWindow(hTwindow,0,0,sx,sy+20,TRUE);
			UpdateWindow(hTwindow);
			MoveWindow(hTool,0,0,sx,sy+20,TRUE);
			UpdateWindow(hTool);

            // Calculate remaining height and size edit

            GetClientRect(hWnd, &rcClient);

            hGwindow = GetDlgItem(hWnd, IDC_MAIN_MDI);
            SetWindowPos(hGwindow, NULL, 0, 30, rcClient.right, rcClient.bottom-30, SWP_NOZORDER);
			break;
		}
		case WM_PAINT:
				/*hdc = BeginPaint (hWnd, &ps);
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
				*/
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
						DestroyWindow(g_hToolbar);
						return 0;
					}
					case ID_PROPERTIES:
					{
						 g_hToolbar = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TOOLBAR),hWnd, ToolDlgProc);
						   if(g_hToolbar != NULL)
							{
								ShowWindow(g_hToolbar, SW_SHOW);
							}
							else
							{
								MessageBox(hWnd, "CreateDialog returned NULL", "Warning!", MB_OK | MB_ICONINFORMATION);
							}
						return 0;
					}

					case IDC_OPEN:
						ZeroMemory(&ofn, sizeof(ofn));

						ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
						ofn.hwndOwner = hWnd;
						ofn.lpstrFilter = "Text Files (*.txt)\0.txt\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = szFileName;
						ofn.nMaxFile = MAX_PATH;
						ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						ofn.lpstrDefExt = "txt";

						if(GetOpenFileName(&ofn))
						{
							LoadTextFileToEdit( hWnd, szFileName);
						}
					break;
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
				DestroyWindow(hWnd);
				PostQuitMessage(0);
				return 0;
			}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

BOOL CALLBACK ToolDlgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{


    switch(Message)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_PRESS:
                    MessageBox(hWnd, "Hi!", "This is a message",
                        MB_OK | MB_ICONEXCLAMATION);
                break;
                case IDC_OTHER:
                    MessageBox(hWnd, "Bye!", "This is also a message",
                        MB_OK | MB_ICONEXCLAMATION);
                break;
                case IDC_CLOSE_SETT:
					GetDlgItemText(hWnd, IDC_BAR1_TXT, (LPTSTR)StimSetup.bar1offset, 9);
					GetDlgItemText(hWnd, IDC_BAR2_TXT, (LPTSTR)StimSetup.bar2offset, 9);
					GetDlgItemText(hWnd, IDC_BAR3_TXT, (LPTSTR)StimSetup.bar3offset, 9);
					GetDlgItemText(hWnd, IDC_BAR4_TXT, (LPTSTR)StimSetup.bar4offset, 9);
					GetDlgItemText(hWnd, IDC_BAR5_TXT, (LPTSTR)StimSetup.bar5offset, 9);
					GetDlgItemText(hWnd, IDC_BAR6_TXT, (LPTSTR)StimSetup.bar6offset, 9);
					GetDlgItemText(hWnd, IDC_LSB_AR_TXT, (LPTSTR)StimSetup.lsbAddrReg, 9);
					GetDlgItemText(hWnd, IDC_MSB_AR_TXT, (LPTSTR)StimSetup.msbAddrReg, 9);
					GetDlgItemText(hWnd, IDC_MSG_TXT, (LPTSTR)StimSetup.msgDataReg, 9);
					GetDlgItemText(hWnd, IDC_VECT_QNTY_TXT, (LPTSTR)StimSetup.vectQnty, 9);

					if (checkVectors(StimSetup, hWnd)) break;

					DestroyWindow(hWnd);
                break;
                case IDC_BAR1_EN:
                	StimSetup.bar1Ena = ~ StimSetup.bar1Ena;
					SendDlgItemMessage(hWnd, IDC_BAR1_TXT, EM_SETREADONLY,~StimSetup.bar1Ena, 0);
                	SendDlgItemMessage(hWnd, IDC_BAR1_EN, BM_SETCHECK,StimSetup.bar1Ena, 0);
				break;
                case IDC_BAR2_EN:
                	StimSetup.bar2Ena = ~ StimSetup.bar2Ena;
					SendDlgItemMessage(hWnd, IDC_BAR2_TXT, EM_SETREADONLY,~StimSetup.bar2Ena, 0);
                	SendDlgItemMessage(hWnd, IDC_BAR2_EN, BM_SETCHECK, StimSetup.bar2Ena, 0);
				break;
                case IDC_BAR3_EN:
                	StimSetup.bar3Ena = ~ StimSetup.bar3Ena;
					SendDlgItemMessage(hWnd, IDC_BAR3_TXT, EM_SETREADONLY,~StimSetup.bar3Ena, 0);
                	SendDlgItemMessage(hWnd, IDC_BAR3_EN, BM_SETCHECK, StimSetup.bar3Ena, 0);
				break;
                case IDC_BAR4_EN:
                	StimSetup.bar4Ena = ~ StimSetup.bar4Ena;
					SendDlgItemMessage(hWnd, IDC_BAR4_TXT, EM_SETREADONLY,~StimSetup.bar4Ena, 0);
                	SendDlgItemMessage(hWnd, IDC_BAR4_EN, BM_SETCHECK, StimSetup.bar4Ena, 0);
				break;
                case IDC_BAR5_EN:
                	StimSetup.bar5Ena = ~ StimSetup.bar5Ena;
					SendDlgItemMessage(hWnd, IDC_BAR5_TXT, EM_SETREADONLY,~StimSetup.bar5Ena, 0);
                	SendDlgItemMessage(hWnd, IDC_BAR5_EN, BM_SETCHECK, StimSetup.bar5Ena, 0);
				break;
                case IDC_BAR6_EN:
                	StimSetup.bar6Ena = ~ StimSetup.bar6Ena;
					SendDlgItemMessage(hWnd, IDC_BAR6_TXT, EM_SETREADONLY,~StimSetup.bar6Ena, 0);
                	SendDlgItemMessage(hWnd, IDC_BAR6_EN, BM_SETCHECK, StimSetup.bar6Ena, 0);
				break;
                case IDC_INT_ENA:
                	StimSetup.intEna = ~ StimSetup.intEna;
					SendDlgItemMessage(hWnd, IDC_LSB_AR_TXT, EM_SETREADONLY,~StimSetup.intEna, 0);
					SendDlgItemMessage(hWnd, IDC_MSB_AR_TXT, EM_SETREADONLY,~StimSetup.intEna, 0);
					SendDlgItemMessage(hWnd, IDC_MSG_TXT, EM_SETREADONLY,~StimSetup.intEna, 0);
                	SendDlgItemMessage(hWnd, IDC_INT_ENA, BM_SETCHECK, StimSetup.intEna, 0);
				break;
                case IDC_WR16_ENA:
                	StimSetup.W16Ena = ~ StimSetup.W16Ena;
                	SendDlgItemMessage(hWnd, IDC_WR16_ENA, BM_SETCHECK, StimSetup.W16Ena, 0);
				break;
                case IDC_WR32_ENA:
                	StimSetup.W32Ena = ~ StimSetup.W32Ena;
                	SendDlgItemMessage(hWnd, IDC_WR32_ENA, BM_SETCHECK, StimSetup.W32Ena, 0);
				break;
                case IDC_WR8_ENA:
                	StimSetup.W8Ena = ~ StimSetup.W8Ena;
                	SendDlgItemMessage(hWnd, IDC_WR8_ENA, BM_SETCHECK, StimSetup.W8Ena, 0);
				break;
                case IDC_WRBR_ENA:
                	StimSetup.WBrEna = ~ StimSetup.WBrEna;
                	SendDlgItemMessage(hWnd, IDC_WRBR_ENA, BM_SETCHECK, StimSetup.WBrEna, 0);
				break;
                case IDC_CH1_ENA:
                	StimSetup.ch1Ena = ~ StimSetup.ch1Ena;
                	SendDlgItemMessage(hWnd, IDC_CH1_ENA, BM_SETCHECK, StimSetup.ch1Ena, 0);
				break;
                case IDC_CH2_ENA:
                	StimSetup.ch2Ena = ~ StimSetup.ch2Ena;
                	SendDlgItemMessage(hWnd, IDC_CH2_ENA, BM_SETCHECK, StimSetup.ch2Ena, 0);
				break;

            }
			break;
		case WM_SHOWWINDOW :
		{
			char *pText = &StimSetup.bar1offset[0];
			int *pNum = &StimSetup.bar1Ena;
			for (int elNum = IDC_BAR1_TXT; elNum <= IDC_VECT_QNTY_TXT; elNum ++){
				SendDlgItemMessage(hWnd,elNum,EM_SETLIMITTEXT,8,0);
				SetDlgItemText(hWnd, elNum, (LPCTSTR)pText);
				pText = pText + 9;
				//tmp++;

			}

			SendDlgItemMessage(hWnd, IDC_BAR1_TXT, EM_SETREADONLY,~StimSetup.bar1Ena, 0);
			SendDlgItemMessage(hWnd, IDC_BAR2_TXT, EM_SETREADONLY,~StimSetup.bar2Ena, 0);
			SendDlgItemMessage(hWnd, IDC_BAR3_TXT, EM_SETREADONLY,~StimSetup.bar3Ena, 0);
			SendDlgItemMessage(hWnd, IDC_BAR4_TXT, EM_SETREADONLY,~StimSetup.bar4Ena, 0);
			SendDlgItemMessage(hWnd, IDC_BAR5_TXT, EM_SETREADONLY,~StimSetup.bar5Ena, 0);
			SendDlgItemMessage(hWnd, IDC_BAR6_TXT, EM_SETREADONLY,~StimSetup.bar6Ena, 0);

			SendDlgItemMessage(hWnd, IDC_LSB_AR_TXT, EM_SETREADONLY,~StimSetup.intEna, 0);
			SendDlgItemMessage(hWnd, IDC_MSB_AR_TXT, EM_SETREADONLY,~StimSetup.intEna, 0);
			SendDlgItemMessage(hWnd, IDC_MSG_TXT, EM_SETREADONLY,~StimSetup.intEna, 0);

			for (int elNum = IDC_BAR1_EN; elNum <= IDC_CH2_ENA; elNum ++){
				SendDlgItemMessage(hWnd, elNum, BM_SETCHECK,*pNum, 0);
				pNum ++;
			}
			//SendDlgItemMessage(hWnd, IDC_BAR1_EN, BM_SETCHECK,StimSetup.bar1Ena, 0);
			//SendDlgItemMessage(hWnd, IDC_BAR2_EN, BM_SETCHECK,StimSetup.bar2Ena, 0);
			//SendDlgItemMessage(hWnd, IDC_BAR3_EN, BM_SETCHECK,StimSetup.bar3Ena, 0);
			//SendDlgItemMessage(hWnd, IDC_BAR4_EN, BM_SETCHECK,StimSetup.bar4Ena, 0);
			//SendDlgItemMessage(hWnd, IDC_BAR5_EN, BM_SETCHECK,StimSetup.bar5Ena, 0);
			//SendDlgItemMessage(hWnd, IDC_BAR6_EN, BM_SETCHECK,StimSetup.bar6Ena, 0);

			break;
		}
        default:
            return FALSE;
            break;
    }
    return TRUE;
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

BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR pszFileName)
{
	BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR pszFileName)
	{
	    HANDLE hFile;
	    BOOL bSuccess = FALSE;

	    hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
	        OPEN_EXISTING, 0, NULL);
	    if(hFile != INVALID_HANDLE_VALUE)
	    {
	        DWORD dwFileSize;

	        dwFileSize = GetFileSize(hFile, NULL);
	        if(dwFileSize != 0xFFFFFFFF)
	        {
	            LPSTR pszFileText;

	            pszFileText = GlobalAlloc(GPTR, dwFileSize + 1);
	            if(pszFileText != NULL)
	            {
	                DWORD dwRead;

	                if(ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL))
	                {
	                    pszFileText[dwFileSize] = 0; // Add null terminator
	                    if(SetWindowText(hEdit, pszFileText))
	                        bSuccess = TRUE; // It worked!
	                }
	                GlobalFree(pszFileText);
	            }
	        }
	        CloseHandle(hFile);
	    }
	    return bSuccess;
	}
}
