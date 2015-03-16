// WinNIC.h : main header file for the WINNIC application
//

#if !defined(AFX_WINNIC_H__82EF7C44_E4A3_4C47_AB11_CF84D4952D39__INCLUDED_)
#define AFX_WINNIC_H__82EF7C44_E4A3_4C47_AB11_CF84D4952D39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinNICApp:
// See WinNIC.cpp for the implementation of this class
//

class CWinNICApp : public CWinApp
{
public:
	CWinNICApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinNICApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinNICApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINNIC_H__82EF7C44_E4A3_4C47_AB11_CF84D4952D39__INCLUDED_)
