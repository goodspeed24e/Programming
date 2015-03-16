// WinLPT.h : main header file for the WINLPT application
//

#if !defined(AFX_WINLPT_H__6BAC2FB4_3AAD_40DC_9EB4_40AE8898C977__INCLUDED_)
#define AFX_WINLPT_H__6BAC2FB4_3AAD_40DC_9EB4_40AE8898C977__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinLPTApp:
// See WinLPT.cpp for the implementation of this class
//

class CWinLPTApp : public CWinApp
{
public:
	CWinLPTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinLPTApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinLPTApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINLPT_H__6BAC2FB4_3AAD_40DC_9EB4_40AE8898C977__INCLUDED_)
