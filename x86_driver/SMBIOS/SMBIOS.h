// SMBIOS.h : main header file for the SMBIOS application
//

#if !defined(AFX_SMBIOS_H__03137B50_D2A4_44F6_B7DF_E446F1D2BDDD__INCLUDED_)
#define AFX_SMBIOS_H__03137B50_D2A4_44F6_B7DF_E446F1D2BDDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSMBIOSApp:
// See SMBIOS.cpp for the implementation of this class
//

class CSMBIOSApp : public CWinApp
{
public:
	CSMBIOSApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMBIOSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSMBIOSApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMBIOS_H__03137B50_D2A4_44F6_B7DF_E446F1D2BDDD__INCLUDED_)
