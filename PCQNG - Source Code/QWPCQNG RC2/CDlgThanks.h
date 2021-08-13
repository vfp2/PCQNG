// CDlgThanks.h : Declaration of the CCDlgThanks

#pragma once

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "Security.h"
#include "DlgActivate.h"

// CCDlgThanks

class CCDlgThanks : 
	public CAxDialogImpl<CCDlgThanks>
{
public:
	CCDlgThanks()
	{
        isCancelled = false;
	}

	~CCDlgThanks()
	{
	}

	CDlgActivate DlgActivate;
	CSecurity Security;
    bool isCancelled;

	enum { IDD = IDD_CDLGTHANKS };

BEGIN_MSG_MAP(CCDlgThanks)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDACTIVATE, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	COMMAND_HANDLER(IDCONTINUETRIAL, BN_CLICKED, OnClickedContinue)
    COMMAND_HANDLER(IDBUY, BN_CLICKED, OnClickedBuy)
	CHAIN_MSG_MAP(CAxDialogImpl<CCDlgThanks>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HWND hCText = GetDlgItem(IDC_CHANGE_TEXT);
		char* sMainText = new char[500];
		strcpy(sMainText, "You have 14 days left on your free trial.");
		int ExpDate = Security.CheckDate();
		if (ExpDate<10)
		{
			sMainText[9] = '0';
			sMainText[10] = 48+ExpDate;
            if (sMainText[10] == 48)
            {
                HWND hContinue = GetDlgItem(IDCONTINUETRIAL);
                ::SetWindowText(hContinue, "Trial Expired");
				::EnableWindow(hContinue, FALSE);
                strcpy(sMainText, "Please purchase a license to contunue using the PCQNG.");
            }
		}
		else
		{
			sMainText[9] = '1';
			sMainText[10] = 38+ExpDate;
		}

		::SetWindowText(hCText, sMainText);		

		CAxDialogImpl<CCDlgThanks>::OnInitDialog(uMsg, wParam, lParam, bHandled);

		delete sMainText;

		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		DlgActivate.DoModal();
		if (!Security.CheckLicense())
			EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
        isCancelled = true;
		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedBuy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
    {
        ShellExecute(m_hWnd, "open", "http://www.ComScire.com/Products/", NULL, NULL, SW_SHOWDEFAULT);
        return 0;
    }

	LRESULT OnClickedContinue(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};