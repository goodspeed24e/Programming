// MemoryDlg.h : header file
//

#if !defined(AFX_MEMORYDLG_H__83D3AD0E_0104_4F63_B2FD_E68C9C8F9D7A__INCLUDED_)
#define AFX_MEMORYDLG_H__83D3AD0E_0104_4F63_B2FD_E68C9C8F9D7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMemoryDlg dialog

class CSearchDlg;

class CMemoryDlg : public CDialog
{
// Construction
public:
	int mode;
	DWORD reg_start;
	
	HANDLE m_hThread;//新建立的執行緒
	DWORD  m_thisThreadID;//新建立執行緒的 ID
	
	CSearchDlg *m_search;
	
	LONG OnStatus(WPARAM wParam, LPARAM lParam);
	void Display(DWORD start_addr);
	void Set_Scroll(void);
	
	friend DWORD __stdcall MLTProc(void *p);//找尋
	
	CMemoryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMemoryDlg)
	enum { IDD = IDD_MEMORY_DIALOG };
	CButton	m_adv;
	CScrollBar	m_scroll;
	CEdit	m_input;
	CEdit	m_content;
	CButton	m_run;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMemoryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeInputEdit();
	afx_msg void OnButton();
	afx_msg void OnClose();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnAdvButton();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMORYDLG_H__83D3AD0E_0104_4F63_B2FD_E68C9C8F9D7A__INCLUDED_)
