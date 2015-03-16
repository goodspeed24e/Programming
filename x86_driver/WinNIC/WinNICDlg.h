// WinNICDlg.h : header file
//

#if !defined(AFX_WINNICDLG_H__0CF4586E_5E83_42B8_AE1B_30E8D4E1C7E0__INCLUDED_)
#define AFX_WINNICDLG_H__0CF4586E_5E83_42B8_AE1B_30E8D4E1C7E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWinNICDlg dialog

class CWinNICDlg : public CDialog
{
// Construction
public:
	int connect_flag;
	
	void OnOffItem(BOOL sw);
	
	CWinNICDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinNICDlg)
	enum { IDD = IDD_WINNIC_DIALOG };
	CStatic	m_self_ip;
	CButton	m_s_bt;
	CButton	m_logoff;
	CButton	m_reboot;
	CButton	m_off;
	CButton	m_connect;
	CIPAddressCtrl	m_ip;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinNICDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinNICDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnCntButton();
	afx_msg void OnOffRadio();
	afx_msg void OnRebootRadio();
	afx_msg void OnLogoffRadio();
	afx_msg void OnSButton();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINNICDLG_H__0CF4586E_5E83_42B8_AE1B_30E8D4E1C7E0__INCLUDED_)
