// VC6BasExDlg.h : header file
//
//{{AFX_INCLUDES()
#include "pcqng.h"
//}}AFX_INCLUDES

#if !defined(AFX_VC6BASEXDLG_H__319115BC_0912_4F66_B7DB_E89D6E00E064__INCLUDED_)
#define AFX_VC6BASEXDLG_H__319115BC_0912_4F66_B7DB_E89D6E00E064__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVC6BasExDlg dialog

class CVC6BasExDlg : public CDialog
{
// Construction
public:
	CVC6BasExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVC6BasExDlg)
	enum { IDD = IDD_VC6BASEX_DIALOG };
	CString	m_sValue;
	int		m_iSelection;
	CPCQNG	m_xPCQNG;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVC6BasExDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVC6BasExDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VC6BASEXDLG_H__319115BC_0912_4F66_B7DB_E89D6E00E064__INCLUDED_)
