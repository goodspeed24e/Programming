// WinSMB.h : main header file for the WINSMB application
//

#if !defined(AFX_WINSMB_H__83C68401_84DB_46DD_A613_CD922DC7D42C__INCLUDED_)
#define AFX_WINSMB_H__83C68401_84DB_46DD_A613_CD922DC7D42C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinSMBApp:
// See WinSMB.cpp for the implementation of this class
//

class CWinSMBApp : public CWinApp
{
public:
	CWinSMBApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinSMBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinSMBApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSMB_H__83C68401_84DB_46DD_A613_CD922DC7D42C__INCLUDED_)
