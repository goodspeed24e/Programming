// WinCMOSDlg.h : header file
//

#if !defined(AFX_WINCMOSDLG_H__BCEB02D3_FC86_4EA7_ADFD_7BD0A0637151__INCLUDED_)
#define AFX_WINCMOSDLG_H__BCEB02D3_FC86_4EA7_ADFD_7BD0A0637151__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWinCMOSDlg dialog

class CWinCMOSDlg : public CDialog
{
// Construction
public:
	int bank_no;
	
	void WaitBusy(void);
	void CheckBank(void);
	void Show_Data(void);
	void Show_ASCII(void);
	void Get_RTC(void);
	
	CWinCMOSDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinCMOSDlg)
	enum { IDD = IDD_WINCMOS_DIALOG };
	CButton	m_fresh;
	CEdit	m_show;
	CButton	m_b2;
	CButton	m_b1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinCMOSDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinCMOSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRefreshCheck();
	afx_msg void OnB1Radio();
	afx_msg void OnB2Radio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINCMOSDLG_H__BCEB02D3_FC86_4EA7_ADFD_7BD0A0637151__INCLUDED_)
