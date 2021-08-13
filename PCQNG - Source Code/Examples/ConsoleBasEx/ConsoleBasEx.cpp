// ConsoleBasEx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream.h"
#include "conio.h"

// #import directive using full path to "QWPCQNG.dll"
// "no_namespace" avoids the need to use namespace "QWPCQNG"
#import "C:\WINDOWS\system32\QWPCQNG.dll" no_namespace named_guids

int _tmain(int argc, _TCHAR* argv[])
{
    // Declare a smart pointer to PCQNG control
    IPCQNGPtr pPCQNG = 0;

    // Create instance of PCQNG control
    CoInitialize(NULL);
    pPCQNG.CreateInstance(CLSID_PCQNG);

    pPCQNG->Open();	// Open PCQNG

    // Get and print a uniform, normal, and 32 bit integer
    cout << "Uniform: " << pPCQNG->RandUniform << endl;
    cout << "Normal:  " << pPCQNG->RandNormal << endl;
    cout << "Int32:   " << pPCQNG->RandInt32 << endl << endl;

    pPCQNG->Close(); // Close PCQNG

    // Wait for a keypress
    cout << "A Key to Quit" << endl;
    while (!kbhit()); 

    return 0;
}
