//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved.
//

// Version History:
// 2003.07.01    PAW    Creation

// QWPCQNG.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "QWPCQNG.h"
#include "dlldatax.h"
#include <stdio.h>

class CQWPCQNGModule : public CAtlDllModuleT< CQWPCQNGModule >
{
public :
	DECLARE_LIBID(LIBID_QWPCQNGLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_QWPCQNG, "{8BFC3C02-E4C0-4431-B561-AD7CCC60EDCF}")
};

CQWPCQNGModule _AtlModule;


// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
#ifdef _MERGE_PROXYSTUB
    if (!PrxDllMain(hInstance, dwReason, lpReserved))
        return FALSE;
#endif
	hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}


// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
    HRESULT hr = PrxDllCanUnloadNow();
    if (FAILED(hr))
        return hr;
#endif
    return _AtlModule.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
    if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
        return S_OK;
#endif
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// Create Secutiy date code
#pragma warning(disable : 4312)
void CreateSecurityDate()
{
	// Check if control has been formally registered
	HKEY RegKey;
	BOOL RegKeyExists = (RegOpenKeyEx(HKEY_CLASSES_ROOT, "CLSID\\{59DA5E62-69A4-4505-A9D0-CAEE53C49E07}", NULL, KEY_READ, &RegKey)==ERROR_SUCCESS);
	RegCloseKey(RegKey);

	// Check if trying to cheat by re-registering control
	if (!RegKeyExists)
	{
		RegKeyExists = (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\QWC\\PCQNG\\License", NULL, KEY_READ, &RegKey)==ERROR_SUCCESS);
		RegCloseKey(RegKey);
	}

	// Not registered yet? Then create security codes.
	if (!RegKeyExists)
	{
	    // Encodes seconds of QWPCQNG.dll creation to match rest of date
	    HANDLE hFile;
	    FILETIME ftCreate;
	    SYSTEMTIME stCreate;

        // Get the file time of QWPCQNG.dll
	    OFSTRUCT OfStruct;
	    char sPath[500];
	    GetModuleFileName(GetModuleHandle("QWPCQNG.dll"), sPath, 500);
	    hFile = (HANDLE)OpenFile(sPath, &OfStruct, OF_READ);
	    GetFileTime(hFile, &ftCreate, NULL, NULL);
	    FileTimeToSystemTime(&ftCreate, &stCreate);
    	int CreatedSeconds = (stCreate.wYear+stCreate.wMonth+stCreate.wDay+stCreate.wSecond) % 32767;
	    SystemTimeToFileTime(&stCreate, &ftCreate);
	    CloseHandle(hFile);

        // Create temporary license number with seconds code
        char sTempLic[23];
        sprintf(sTempLic, "PCQNG-20-%08u-0000", (unsigned long)CreatedSeconds);
        RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\QWC\\PCQNG\\License", NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &RegKey, NULL);
        RegSetValueEx(RegKey, "Licensee", NULL, REG_SZ, (BYTE*)"Temporary", 10);
        RegSetValueEx(RegKey, "ProductKey", NULL, REG_SZ, (BYTE*)sTempLic, (DWORD)strlen(sTempLic)+1);
        RegCloseKey(RegKey);
	}
}
#pragma warning(default : 4312)

// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	// Security enhancement here
	CreateSecurityDate();

    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _AtlModule.DllRegisterServer();
#ifdef _MERGE_PROXYSTUB
    if (FAILED(hr))
        return hr;
    hr = PrxDllRegisterServer();
#endif
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	// Remove security settings

	HRESULT hr = _AtlModule.DllUnregisterServer();
#ifdef _MERGE_PROXYSTUB
    if (FAILED(hr))
        return hr;
    hr = PrxDllRegisterServer();
    if (FAILED(hr))
        return hr;
    hr = PrxDllUnregisterServer();
#endif
	return hr;
}
