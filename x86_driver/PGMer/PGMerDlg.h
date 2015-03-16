// PGMerDlg.h : header file
//

#if !defined(AFX_PGMERDLG_H__2B29B390_5764_49EB_8657_4183E8E0B160__INCLUDED_)
#define AFX_PGMERDLG_H__2B29B390_5764_49EB_8657_4183E8E0B160__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPGMerDlg dialog

class CPGMerDlg : public CDialog
{
// Construction
public:
	
	void AsmData(BYTE *data);
	void Show_Data(char *str);
	HANDLE m_hThread;//新建立的執行緒
	DWORD  m_thisThreadID;//新建立執行緒的 ID
	friend DWORD __stdcall Prog_Proc(void *p);
	
	CPGMerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPGMerDlg)
	enum { IDD = IDD_PGMER_DIALOG };
	CButton	m_bw;
	CButton	m_93;
	CButton	m_24;
	CButton	m_write_r;
	CButton	m_read_r;
	CEdit	m_report;
	CEdit	m_file;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPGMerDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPGMerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void On24Radio();
	afx_msg void On93Radio();
	afx_msg void OnReadRadio();
	afx_msg void OnWriteRadio();
	afx_msg void OnBwButton();
	virtual void OnOK();
	afx_msg void OnRunButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGMERDLG_H__2B29B390_5764_49EB_8657_4183E8E0B160__INCLUDED_)
