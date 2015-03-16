#if !defined(AFX_DETAILDLG_H__7B65E804_AD05_4A28_B0AB_FACE9FA12DB6__INCLUDED_)
#define AFX_DETAILDLG_H__7B65E804_AD05_4A28_B0AB_FACE9FA12DB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Detaildlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDetaildlg dialog

class CDetaildlg : public CDialog
{
// Construction
public:
	void read_spd(void);
	BYTE addr;
	CDetaildlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDetaildlg)
	enum { IDD = IDD_DETAIL_DIALOG };
	CStatic	m_data;
	CStatic	m_ascii;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDetaildlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDetaildlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DETAILDLG_H__7B65E804_AD05_4A28_B0AB_FACE9FA12DB6__INCLUDED_)
