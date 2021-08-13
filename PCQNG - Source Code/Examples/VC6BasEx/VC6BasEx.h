// VC6BasEx.h : main header file for the VC6BASEX application
//

#if !defined(AFX_VC6BASEX_H__56AC91D6_3D54_41D7_919E_A3ADF0F6DE26__INCLUDED_)
#define AFX_VC6BASEX_H__56AC91D6_3D54_41D7_919E_A3ADF0F6DE26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVC6BasExApp:
// See VC6BasEx.cpp for the implementation of this class
//

class CVC6BasExApp : public CWinApp
{
public:
	CVC6BasExApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVC6BasExApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVC6BasExApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VC6BASEX_H__56AC91D6_3D54_41D7_919E_A3ADF0F6DE26__INCLUDED_)
