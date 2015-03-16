// PGMer.h : main header file for the PGMER application
//

#if !defined(AFX_PGMER_H__21127442_2D89_485C_899D_5B43B0E1B27A__INCLUDED_)
#define AFX_PGMER_H__21127442_2D89_485C_899D_5B43B0E1B27A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPGMerApp:
// See PGMer.cpp for the implementation of this class
//

class CPGMerApp : public CWinApp
{
public:
	CPGMerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPGMerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPGMerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGMER_H__21127442_2D89_485C_899D_5B43B0E1B27A__INCLUDED_)
