// WinIDE.h : main header file for the WINIDE application
//

#if !defined(AFX_WINIDE_H__E25CA54D_8947_44E6_A56A_E5A41DE49BCD__INCLUDED_)
#define AFX_WINIDE_H__E25CA54D_8947_44E6_A56A_E5A41DE49BCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinIDEApp:
// See WinIDE.cpp for the implementation of this class
//

class CWinIDEApp : public CWinApp
{
public:
	CWinIDEApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinIDEApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinIDEApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINIDE_H__E25CA54D_8947_44E6_A56A_E5A41DE49BCD__INCLUDED_)
