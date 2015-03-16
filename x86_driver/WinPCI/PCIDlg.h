// PCIDlg.h : header file
//

#if !defined(AFX_PCIDLG_H__41147AAB_7D20_44AD_8131_F488202515F3__INCLUDED_)
#define AFX_PCIDLG_H__41147AAB_7D20_44AD_8131_F488202515F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPCIDlg dialog

class CListDlg;

class CPCIDlg : public CDialog
{
// Construction
public:
	int m_curTab;
	CListDlg *m_listDlg;
	LONG OnStatus(WPARAM wParam, LPARAM lParam);
	CPCIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPCIDlg)
	enum { IDD = IDD_PCI_DIALOG };
	CTabCtrl	m_tab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPCIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCIDLG_H__41147AAB_7D20_44AD_8131_F488202515F3__INCLUDED_)
