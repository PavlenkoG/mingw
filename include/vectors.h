/*
 * vectors.h
 *
 *  Created on: 26.06.2017
 *      Author: grpa
 */
#include <windows.h>


struct tVector {
	char channelSel;
	char moduleNum;
	char dataLen;
	char data[28];
};

static struct tStimSetup {
	int bar1Ena;
	int bar2Ena;
	int bar3Ena;
	int bar4Ena;
	int bar5Ena;
	int bar6Ena;
	int intEna;
	int W32Ena;
	int W16Ena;
	int W8Ena;
	int WBrEna;
	int ch1Ena;
	int ch2Ena;
	char bar1offset[9];
	char bar2offset[9];
	char bar3offset[9];
	char bar4offset[9];
	char bar5offset[9];
	char bar6offset[9];
	char lsbAddrReg[9];
	char msbAddrReg[9];
	char msgDataReg[9];
	char vectQnty[9];
}StimSetup;

int checkVectors ( struct tStimSetup StimSetup, HWND hWnd);
