/*
 * vectors.c
 *
 *  Created on: 26.06.2017
 *      Author: grpa
 */
#include "vectors.h"
#include <resource.h>
#include "callbacks.h"
#include <commctrl.h>
#include <Commdlg.h>
#include <math.h>
#include <winsock2.h>
const char hexValue[]= "0123456789abcdefABCDEF";
int checkVectors (struct tStimSetup StimSetup,HWND hWnd){

		if ((strspn(StimSetup.bar1offset, hexValue) < strlen(StimSetup.bar1offset)) || strlen(StimSetup.bar1offset)<8)
		{
			if (StimSetup.bar1Ena){
				MessageBox(hWnd, "Wrong BAR1 offset value", "Error", MB_OK | MB_ICONEXCLAMATION);
				return 1;
			}
		}
		if ((strspn(StimSetup.bar2offset, hexValue) < strlen(StimSetup.bar2offset)))
		{
			if (StimSetup.bar2Ena){
				MessageBox(hWnd, "Wrong BAR2 offset value", "Error", MB_OK | MB_ICONEXCLAMATION);
				return 1;
			}
		}
		if ((strspn(StimSetup.bar3offset, hexValue) < strlen(StimSetup.bar3offset)))
		{
			if (StimSetup.bar3Ena){
				MessageBox(hWnd, "Wrong BAR3 offset value", "Error", MB_OK | MB_ICONEXCLAMATION);
				return 1;
			}
		}
		if ((strspn(StimSetup.bar4offset, hexValue) < strlen(StimSetup.bar4offset)))
		{
			if (StimSetup.bar4Ena){
				MessageBox(hWnd, "Wrong BAR4 offset value", "Error", MB_OK | MB_ICONEXCLAMATION);
				return 1;
			}
		}
		if ((strspn(StimSetup.bar5offset, hexValue) < strlen(StimSetup.bar5offset)))
		{
			if (StimSetup.bar5Ena){
				MessageBox(hWnd, "Wrong BAR5 offset value", "Error", MB_OK | MB_ICONEXCLAMATION);
				return 1;
			}
		}
		if ((strspn(StimSetup.bar6offset, hexValue) < strlen(StimSetup.bar6offset)))
		{
			if (StimSetup.bar6Ena){
				MessageBox(hWnd, "Wrong BAR6 offset value", "Error", MB_OK | MB_ICONEXCLAMATION);
				return 1;
			}
		}
		if ((strspn(StimSetup.lsbAddrReg, hexValue) < strlen(StimSetup.lsbAddrReg)))
		{
			if (StimSetup.intEna){
				MessageBox(hWnd, "Wrong LSB Interrupt value", "Error", MB_OK | MB_ICONEXCLAMATION);
				return 1;
			}
		}
		if ((strspn(StimSetup.msbAddrReg, hexValue) < strlen(StimSetup.msbAddrReg)))
		{
			if (StimSetup.intEna){
				MessageBox(hWnd, "Wrong MSB Interrupt value", "Error", MB_OK | MB_ICONEXCLAMATION);
				return 1;
			}
		}
		if ((strspn(StimSetup.msgDataReg, hexValue) < strlen(StimSetup.msgDataReg)))
		{
			if (StimSetup.intEna){
				MessageBox(hWnd, "Wrong Message value", "Error", MB_OK | MB_ICONEXCLAMATION);
				return 1;
			}
		}
		if (!StimSetup.W16Ena && !StimSetup.W32Ena && !StimSetup.W8Ena && !StimSetup.WBrEna)
		{
			MessageBox(hWnd, "Choose one or more write method", "Error", MB_OK | MB_ICONEXCLAMATION);
			return 1;
		}
		if (!StimSetup.ch1Ena && !StimSetup.ch2Ena)
		{
			MessageBox(hWnd, "Choose one or more channel", "Error", MB_OK | MB_ICONEXCLAMATION);
			return 1;
		}

		else	return 0;
}



