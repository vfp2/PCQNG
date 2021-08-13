// DlgActivate.h : Declaration of the CDlgActivate

#pragma once

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "security.h"

// CDlgActivate

class CDlgActivate : 
	public CAxDialogImpl<CDlgActivate>
{
public:
	CDlgActivate()
	{
	}

	~CDlgActivate()
	{
	}

	enum { IDD = IDD_DLGACTIVATE };

BEGIN_MSG_MAP(CDlgActivate)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	CHAIN_MSG_MAP(CAxDialogImpl<CDlgActivate>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CDlgActivate>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		return 1;  // Let the system set the focus
	}

	CSecurity Security;

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
        // Get items
        char sProductKey[31];
        char sProductKeyPrev[31];
        char sLicensee[51];
        char sLicenseePrev[51];
        GetDlgItemText(IDC_USER_ID, sLicensee, 50);
        GetDlgItemText(IDC_PRODUCT_KEY, sProductKey, 30);

        // Get previous License
        HKEY RegKeyPrev;
        DWORD KeyType = REG_SZ;
        DWORD KeySize = 30;
		BOOL RegKeyExists = (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\QWC\\PCQNG\\License", NULL, KEY_ALL_ACCESS, &RegKeyPrev)==ERROR_SUCCESS);
        if (RegKeyExists)
        {
            RegQueryValueEx(RegKeyPrev, "ProductKey", NULL, &KeyType, (BYTE*)sProductKeyPrev, &KeySize);
            KeySize = 50;
            RegQueryValueEx(RegKeyPrev, "Licensee", NULL, &KeyType, (BYTE*)sLicenseePrev, &KeySize);
        }

        // Trim whitespace
        while (sLicensee[0] == ' ')
            strcpy(sLicensee, &sLicensee[1]);
        while (sProductKey[0] == ' ')
            strcpy(sProductKey, &sProductKey[1]);
        while (sProductKey[strlen(sLicensee)-1] == ' ')
            sProductKey[strlen(sLicensee)-1] = NULL;
        while (sProductKey[strlen(sProductKey)-1] == ' ')
            sProductKey[strlen(sProductKey)-1] = NULL;

    	// Create Registry Keys
    	HKEY RegKey;
        RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\QWC\\PCQNG\\License", NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &RegKey, NULL);
        RegSetValueEx(RegKey, "Licensee", NULL, REG_SZ, (BYTE*)sLicensee, (DWORD)strlen(sLicensee)+1);
        if (RegSetValueEx(RegKey, "ProductKey", NULL, REG_SZ, (BYTE*)sProductKey, (DWORD)strlen(sProductKey)+1)!=ERROR_SUCCESS)
        {
            MessageBox("There was an error during license activation. You must be logged on as an Administrator to activate license.", "PCQNG 2.0 Activation Error", MB_OK);
            if (RegKeyExists)
            {
                RegSetValueEx(RegKeyPrev, "Licensee", NULL, REG_SZ, (BYTE*)sLicenseePrev, (DWORD)strlen(sLicenseePrev)+1);
                RegSetValueEx(RegKeyPrev, "ProductKey", NULL, REG_SZ, (BYTE*)sProductKeyPrev, (DWORD)strlen(sProductKeyPrev)+1);
            }
            RegCloseKey(RegKeyPrev);
            EndDialog(wID);
            return 0;
        };
        RegCloseKey(RegKey);

        if (Security.CheckLicense())
        {
            MessageBox("Invalid License. Please confirm your license, or email support@comscire.com for assistance", "PCQNG 2.0", MB_OK);
            if (RegKeyExists)
            {
                RegSetValueEx(RegKeyPrev, "Licensee", NULL, REG_SZ, (BYTE*)sLicenseePrev, (DWORD)strlen(sLicenseePrev)+1);
                RegSetValueEx(RegKeyPrev, "ProductKey", NULL, REG_SZ, (BYTE*)sProductKeyPrev, (DWORD)strlen(sProductKeyPrev)+1);
                RegCloseKey(RegKeyPrev);
            }
        }
        else
        {
            MessageBox("License successfully activated. Thank you for purchasing PCQNG 2.0", "PCQNG 2.0", MB_OK);
            EndDialog(wID);
        }
        RegCloseKey(RegKeyPrev);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};


