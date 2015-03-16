// NicUSB.h : main header file for the NICUSB application
//

#if !defined(AFX_NICUSB_H__4C8781D6_CF2F_4901_9D99_2F3724DA08FE__INCLUDED_)
#define AFX_NICUSB_H__4C8781D6_CF2F_4901_9D99_2F3724DA08FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNicUSBApp:
// See NicUSB.cpp for the implementation of this class
//

class CNicUSBApp : public CWinApp
{
public:
	CNicUSBApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNicUSBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNicUSBApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NICUSB_H__4C8781D6_CF2F_4901_9D99_2F3724DA08FE__INCLUDED_)
