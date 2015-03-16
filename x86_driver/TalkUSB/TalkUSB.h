// TalkUSB.h : main header file for the TALKUSB application
//

#if !defined(AFX_TALKUSB_H__FEBFF754_FCB7_461A_85FF_B1A9EF2628B3__INCLUDED_)
#define AFX_TALKUSB_H__FEBFF754_FCB7_461A_85FF_B1A9EF2628B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTalkUSBApp:
// See TalkUSB.cpp for the implementation of this class
//

class CTalkUSBApp : public CWinApp
{
public:
	CTalkUSBApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTalkUSBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTalkUSBApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TALKUSB_H__FEBFF754_FCB7_461A_85FF_B1A9EF2628B3__INCLUDED_)
