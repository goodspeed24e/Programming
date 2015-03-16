// WinSMBDlg.h : header file
//

#if !defined(AFX_WINSMBDLG_H__A419617A_A83B_40B7_908C_2F597744647D__INCLUDED_)
#define AFX_WINSMBDLG_H__A419617A_A83B_40B7_908C_2F597744647D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDetaildlg;

/////////////////////////////////////////////////////////////////////////////
// CWinSMBDlg dialog

class CWinSMBDlg : public CDialog
{
// Construction
public:
	void Write_list(int posi, int col,char *value);
	void detect_device(void);
	
	CDetaildlg *m_DetailDlg;
	CWinSMBDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinSMBDlg)
	enum { IDD = IDD_WINSMB_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinSMBDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinSMBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSMBDLG_H__A419617A_A83B_40B7_908C_2F597744647D__INCLUDED_)
