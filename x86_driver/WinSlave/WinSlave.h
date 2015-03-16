// WinSlave.h : main header file for the WINSLAVE application
//

#if !defined(AFX_WINSLAVE_H__A7F54521_4E11_4609_B7B4_E33219E5C794__INCLUDED_)
#define AFX_WINSLAVE_H__A7F54521_4E11_4609_B7B4_E33219E5C794__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinSlaveApp:
// See WinSlave.cpp for the implementation of this class
//

class CWinSlaveApp : public CWinApp
{
public:
	CWinSlaveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinSlaveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinSlaveApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSLAVE_H__A7F54521_4E11_4609_B7B4_E33219E5C794__INCLUDED_)
