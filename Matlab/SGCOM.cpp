#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <ShellApi.h>
#include <Windowsx.h>
#include "mex.h"
using namespace std;


int main()
{
	
	mexPrintf("[~] SGCOM - Collecting Handles\n");
	mexEvalString("drawnow;");
	
	int Index = 1;
	TCHAR title[251];

	HWND hwndForm = FindWindowA("ThunderRT6FormDC", NULL);             //Handle of Main Window
	HWND hwndMType = GetDlgItem(hwndForm, 7);                          //Model Type
	HWND hwndCOM = GetDlgItem(hwndMType, 10);                          //COM Combobox
	HWND hwndCH1 = GetDlgItem(hwndForm, 33);                           //CH1
	HWND hwndFreq = GetDlgItem(hwndCH1, 35);                           //Freq
	HWND hwndInvalidPortdlg;										   //Used for popup

	if (NULL == hwndForm || NULL == hwndMType || NULL == hwndCOM)
	{
		mexPrintf("[!] Error assigning Handles: Could not find required software\n");
		mexEvalString("drawnow;");
		return 1;
	}


	hwndInvalidPortdlg = GetWindow(hwndForm, GW_ENABLEDPOPUP);
	if (NULL != hwndInvalidPortdlg);
		SendMessage(hwndInvalidPortdlg, WM_SYSCOMMAND, SC_CLOSE, 0); //close dialog before starting


	while (true)
	{
		//COM Port Connect
		int res = ComboBox_SetCurSel(hwndCOM, Index);
		PostMessage(GetParent(hwndCOM), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(hwndCOM), CBN_SELENDOK), (LPARAM)hwndCOM);
		PostMessage(GetParent(hwndCOM), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(hwndCOM), CBN_SELCHANGE), (LPARAM)hwndCOM);

		Sleep(20); //Wait for Dialog box
		hwndInvalidPortdlg = GetWindow(hwndForm, GW_ENABLEDPOPUP);
		//Check if correct COM Port has been selected
		if (NULL != hwndInvalidPortdlg)
		{
			//Invalid COM Port
			if (Index == 255)
			{
				SendMessage(hwndInvalidPortdlg, WM_SYSCOMMAND, SC_CLOSE, 0);
				mexPrintf("[!] Error Connecting: Verify that Signal Generator is properly connected\n");
				mexEvalString("drawnow;");
				return 1;
			}
			
			SendMessage(hwndInvalidPortdlg, WM_SYSCOMMAND, SC_CLOSE, 0);  //Close Dialog
			Index++;
		}
		else
		{
			//Correct COM Port: Exit
			mexPrintf("[~] Successfully Connected: Ready\n");
			mexEvalString("drawnow;");
			break;
		}
	}

	mexPrintf("TEST");
	mexEvalString("drawnow;");

	return 0;
}

// The gateway routine
void mexFunction(int nlhs, mxArray *plhs[],
	int nrhs, const mxArray *prhs[])
{
	//nlhs : Number of Expected output mxArrays
	//plhs : Array of pointers to the expected ouput mxArrays
	//nrhs : Number of input mxArrays
	//prhs : Array of pointers to the input mxArrays. Do not modify any prhs values in your mex file. Changing the data in these read-only mxArrays can produce undesired side effects.

	//Call the C++ Subroutine
	int value = 0;
	plhs[0] = mxCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
	int* data = (int*)mxGetData(plhs[0]);
	
	value = main();
	data[0] = value;


	return;

}

