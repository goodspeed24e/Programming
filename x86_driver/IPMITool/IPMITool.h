// IPMITool.h : main header file for the IPMITOOL application
//

#if !defined(AFX_IPMITOOL_H__F5943AF8_B4DF_4676_9F70_0DCE35F60304__INCLUDED_)
#define AFX_IPMITOOL_H__F5943AF8_B4DF_4676_9F70_0DCE35F60304__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIPMIToolApp:
// See IPMITool.cpp for the implementation of this class
//

class CIPMIToolApp : public CWinApp
{
public:
	CIPMIToolApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPMIToolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIPMIToolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPMITOOL_H__F5943AF8_B4DF_4676_9F70_0DCE35F60304__INCLUDED_)
