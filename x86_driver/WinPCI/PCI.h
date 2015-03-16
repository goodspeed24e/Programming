// PCI.h : main header file for the PCI application
//

#if !defined(AFX_PCI_H__6FA11EFA_4F01_4890_8971_7AEDF8DECF6F__INCLUDED_)
#define AFX_PCI_H__6FA11EFA_4F01_4890_8971_7AEDF8DECF6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPCIApp:
// See PCI.cpp for the implementation of this class
//

class CPCIApp : public CWinApp
{
public:
	CPCIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPCIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCI_H__6FA11EFA_4F01_4890_8971_7AEDF8DECF6F__INCLUDED_)
