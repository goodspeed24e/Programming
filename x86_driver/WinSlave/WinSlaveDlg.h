// WinSlaveDlg.h : header file
//

#if !defined(AFX_WINSLAVEDLG_H__ED387ED9_C409_4646_8940_3D95562C493D__INCLUDED_)
#define AFX_WINSLAVEDLG_H__ED387ED9_C409_4646_8940_3D95562C493D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWinSlaveDlg dialog

class CWinSlaveDlg : public CDialog
{
// Construction
public:
	DWORD  m_thisThreadID;//新建立執行緒的 ID
	HANDLE m_hThread;//新建立的執行緒
	
	friend DWORD __stdcall MLTProc(void *p);//主程式
	CWinSlaveDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinSlaveDlg)
	enum { IDD = IDD_WINSLAVE_DIALOG };
	CStatic	m_show;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinSlaveDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinSlaveDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSLAVEDLG_H__ED387ED9_C409_4646_8940_3D95562C493D__INCLUDED_)
