// Memory.h : main header file for the MEMORY application
//

#if !defined(AFX_MEMORY_H__663397DB_06D1_4691_904D_A02B75F85338__INCLUDED_)
#define AFX_MEMORY_H__663397DB_06D1_4691_904D_A02B75F85338__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMemoryApp:
// See Memory.cpp for the implementation of this class
//

class CMemoryApp : public CWinApp
{
public:
	CMemoryApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMemoryApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMORY_H__663397DB_06D1_4691_904D_A02B75F85338__INCLUDED_)
