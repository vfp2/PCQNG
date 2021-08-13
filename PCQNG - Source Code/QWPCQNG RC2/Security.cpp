#include "StdAfx.h"
#include "security.h"
#include <stdio.h>


CSecurity::CSecurity(void)
{
}

CSecurity::~CSecurity(void)
{
}

#pragma warning(disable : 4312)
int CSecurity::CheckDate(void)
{
	// Check if registry key exists
	HKEY RegKey;
	BOOL RegKeyExists = (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\QWC\\PCQNG\\License", NULL, KEY_READ, &RegKey)==ERROR_SUCCESS);
	RegCloseKey(RegKey);

	// Encodes seconds of QWPCQNG.dll creation to match rest of date
	HANDLE hFile;
	FILETIME ftCreate;
	SYSTEMTIME stCreate, stCurrent;

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

	// Reg key doesn't exists? tampering, since created on registration
    if (!RegKeyExists)
        return 0;
    
    // Read data from registry
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\QWC\\PCQNG\\License", NULL, KEY_ALL_ACCESS, &RegKey);
    DWORD KeyType = REG_SZ;
    DWORD KeySize = 23;
    char sTempLic[23];
    RegQueryValueEx(RegKey, "ProductKey", NULL, &KeyType, (BYTE*)sTempLic, &KeySize);
    RegCloseKey(RegKey);

    // Find 8 digit encrypted code in license
	char* Pos = NULL;
	Pos = strchr(sTempLic, '-');
    if (Pos != NULL)
    {
        Pos++;
    	Pos = strchr(Pos, '-');
        if (Pos != NULL)
            Pos++;
    	strcpy(sTempLic, Pos);
	    if (strlen(sTempLic)>=8)
		    sTempLic[8] = NULL;
    }
    int WrittenSeconds = (int)atoi(sTempLic);


	// If consistent, check expiration
	int DaysLeft = 0;
	if ((WrittenSeconds-CreatedSeconds)==0)
	{
		GetSystemTime(&stCurrent);
		DaysLeft = 14 - (30*(stCurrent.wMonth-stCreate.wMonth) + (stCurrent.wDay-stCreate.wDay));
		if ((DaysLeft<0) || (DaysLeft>14))
			DaysLeft = 0;
	}

	return DaysLeft;
}
#pragma warning(default : 4312)

int CSecurity::CheckLicense(void)
{
	// Open License in Registry
	HKEY RegKey;
	BOOL RegKeyExists = (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\QWC\\PCQNG\\License", NULL, KEY_READ, &RegKey)==ERROR_SUCCESS);

	// Read Licensee (usually an email)
	char sLicensee[80];
	DWORD Type = REG_SZ;
	DWORD Length = 80;
	RegQueryValueEx(RegKey, "Licensee", NULL, &Type, (LPBYTE)sLicensee, &Length);

	// Read Product Key
	char sProductKey[25];
	Length = 25;
	RegQueryValueEx(RegKey, "ProductKey", NULL, &Type, (LPBYTE)sProductKey, &Length);

	RegCloseKey(RegKey);

	// Find 8 digit encrypted code in license
	char* Pos = 0;
	Pos = strchr(sProductKey, '-');
    if (Pos != NULL)
    {
        Pos++;
    	Pos = strchr(Pos, '-');
        if (Pos != NULL)
            Pos++;
    	strcpy(sProductKey, Pos);
	    if (strlen(sProductKey)>=8)
		    sProductKey[8] = NULL;
    }

	char* pTermChar;
	unsigned __int64 ProductRegCode = strtoul(sProductKey, &pTermChar, 10);

	// Decode Licensee
	// Lowercase and trim whitespace
	strcpy(sLicensee, strlwr(sLicensee));
	while ((strlen(sLicensee)>0) && (sLicensee[0]==' '))
		strcpy(sLicensee, &sLicensee[1]);
	while ((strlen(sLicensee)>0) && (sLicensee[strlen(sLicensee)-1]==' '))
		sLicensee[strlen(sLicensee)-1] = ' ';

	unsigned __int64 ProductDecodeCode = 1;
	for (unsigned int i=0; i<strlen(sLicensee); i++)
	{
		ProductDecodeCode *= sLicensee[i];
		ProductDecodeCode %= 99999989;
	}

	ProductDecodeCode += 13117532;
	ProductDecodeCode %= 99999989;

	return (int)(ProductDecodeCode-ProductRegCode);
}
