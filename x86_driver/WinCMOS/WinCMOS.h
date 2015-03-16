// WinCMOS.h : main header file for the WINCMOS application
//

#if !defined(AFX_WINCMOS_H__8A2488C9_A6C4_4757_AC8F_2BF54ED6B2AF__INCLUDED_)
#define AFX_WINCMOS_H__8A2488C9_A6C4_4757_AC8F_2BF54ED6B2AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinCMOSApp:
// See WinCMOS.cpp for the implementation of this class
//

class CWinCMOSApp : public CWinApp
{
public:
	CWinCMOSApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinCMOSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinCMOSApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINCMOS_H__8A2488C9_A6C4_4757_AC8F_2BF54ED6B2AF__INCLUDED_)
