#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include "mex.h"
using namespace std;



int ftostr(float value, char buffer[], int bufferSize)
{
	for (int i = 0; i < bufferSize; i++)
	{
		buffer[i] = '0';
	}
	return snprintf(buffer, bufferSize, "%f", value);
}

void SendSignalGenMessage(float &amplitude)
{
	cout << "[~] SendingInfo..." << endl;

	cout << "[~] Finding FY2200s PC Software" << endl;

	TCHAR title[251];
	HWND hwndForm = FindWindowA("ThunderRT6FormDC", NULL);//Handle of Main Window


	if (NULL != hwndForm)
	{
		cout << "[~] Collecting Handles" << endl;
		HWND hwndFrame = GetDlgItem(hwndForm, 33);
		HWND hwndFreq = GetDlgItem(hwndFrame, 35);//Freq
		HWND hwndAmp = GetDlgItem(hwndFrame, 47);//Amp
		
		HWND hwndMType = GetDlgItem(hwndForm, 7);
		HWND hwndCombo = GetDlgItem(hwndMType, 10);
		HWND hwndCOM = GetDlgItem(hwndCombo, 1001);

		if (NULL != hwndFrame || NULL != hwndMType)
		{
				//cout << "- get text length" << endl;
				int textLen = (int)SendMessage(hwndFreq, WM_GETTEXTLENGTH, 0, 0);

				
				//AMPLITUDE
				cout << endl << "[~] Receiving Current Amplitude Input from Signal Generator" << endl;
				SendMessage(hwndAmp, WM_GETTEXT, (WPARAM)bufferSize, (LPARAM)textBuffer);//Receiving GUI Input

				cout << "[~] Current Amplitude: " << textBuffer << endl;

				cout << "[~] Sending New Amplitude Input to Signal Generator" << endl;

				ftostr(amplitude, textBuffer, bufferSize);
				SendMessage(hwndAmp, WM_SETTEXT, 1, ' ');                                //Resetting GUI Input to 0
				SendMessage(hwndAmp, WM_SETTEXT, (WPARAM)bufferSize, (LPARAM)textBuffer);//Sending New GUI Input

				cout << "[~] Verifying Message Delivery" << endl;
				SendMessage(hwndAmp, WM_GETTEXT, (WPARAM)bufferSize, (LPARAM)textBuffer);//Receiving GUI Input
				cout << "[~] New Amplitude: " << textBuffer << endl;
			
		}
		else
		{
			cerr << "[!] One or more handles not collected - Close and Restart FY2200S PC Software Application" << endl;
		}
	}
	else
	{
		cerr << "[!] Signal Generator Application Not Open" << endl;
	}

	cout << endl << "[~] COMMUNICATION COMPLETE!" << endl;
}

int main(double* PtrAmplitude)
{
	float Amplitude = (float)*PtrAmplitude;
	
	mexPrintf("C++ function Called\n");
	mexEvalString("drawnow;");
	
	SendSignalGenMessage(Amplitude);
	//system("Pause");
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


	//First argument is Amplitude Input
	double *Amplitude = mxGetPr(prhs[0]);

	//Call the C++ Subroutine
	main(Amplitude);
}


