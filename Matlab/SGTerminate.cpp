#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <ShellApi.h>
#include <Windowsx.h>
#include "mex.h"
using namespace std;


int main()
{
	mexPrintf("[~] Application Terminated\n");
	mexEvalString("drawnow;");

	//For additional ShellExecute Commands
	//https://msdn.microsoft.com/en-us/library/windows/desktop/bb762153(v=vs.85).aspx


										      //Wait for window to open

	HWND hwndForm = FindWindowA("ThunderRT6FormDC", NULL);    //Handle of Main Window


	SendMessage(hwndForm, WM_SYSCOMMAND, SC_CLOSE, 0);
	Sleep(1000);
	
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
	main();


}

