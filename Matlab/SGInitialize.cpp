#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <ShellApi.h>
#include <Windowsx.h>
#include "mex.h"
using namespace std;


int main()
{	
	mexPrintf("[~] FeelTech Software Initialization\n");
	mexEvalString("drawnow;");
	
	const char SoftwareExe[100] = "C:\\Program Files (x86)\\FY2200 PC Sofware\\FY2200 PC Sofware.exe";//Note: Cannot use shortcut
	ShellExecute(NULL, "open", SoftwareExe, NULL, NULL, SW_SHOW);

	//For additional ShellExecute Commands
	//https://msdn.microsoft.com/en-us/library/windows/desktop/bb762153(v=vs.85).aspx


	Sleep(1000);										      //Wait for window to open
														      
	HWND hwndForm = FindWindowA("ThunderRT6FormDC", NULL);    //Handle of Main Window

	
	if (NULL != hwndForm)
	{
		PostMessage(hwndForm, WM_SYSCOMMAND, SC_MINIMIZE, 0); //Minimize
		mexPrintf("[~] Software Successfully Opened\n");
		mexEvalString("drawnow;");
		return 0;
	}
	else
	{
		mexPrintf("[!] Error Opening Software\n");
		mexEvalString("drawnow;");
		return 1;
	}
	
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


}

