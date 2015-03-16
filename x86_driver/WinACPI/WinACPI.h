// WinACPI.h : main header file for the WINACPI application
//

#if !defined(AFX_WINACPI_H__800D532C_487C_47B0_825B_D22F53570ADF__INCLUDED_)
#define AFX_WINACPI_H__800D532C_487C_47B0_825B_D22F53570ADF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinACPIApp:
// See WinACPI.cpp for the implementation of this class
//

class CWinACPIApp : public CWinApp
{
public:
	CWinACPIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinACPIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWinACPIApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINACPI_H__800D532C_487C_47B0_825B_D22F53570ADF__INCLUDED_)
