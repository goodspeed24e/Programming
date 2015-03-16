// WinLPTDlg.h : header file
//

#if !defined(AFX_WINLPTDLG_H__6D28EBE0_7FF1_420C_BEA8_54AC5C2195AB__INCLUDED_)
#define AFX_WINLPTDLG_H__6D28EBE0_7FF1_420C_BEA8_54AC5C2195AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWinLPTDlg dialog

class CWinLPTDlg : public CDialog
{
// Construction
public:
	HICON m_hOnIcon;
	HICON m_hOffIcon;
	BYTE ctrl_data_byte;
	int send_flag;
	
	HANDLE m_hThread;//新建立的執行緒
	DWORD  m_thisThreadID;//新建立執行緒的 ID
	
	int HandSharking(void);
	void WriteState(char *str);
	void OnOffGroup1(int sw);
	void OnOffGroup2(int sw);
	void OnOffGroup3(int sw);
	void OnOffGroup4(int sw);
	void OffMainRadio(void);
	
	friend DWORD __stdcall MLTProc(void *p);//拉咧用
	
	CWinLPTDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinLPTDlg)
	enum { IDD = IDD_WINLPT_DIALOG };
	CEdit	m_name;
	CButton	m_send_lb;
	CButton	m_send;
	CEdit	m_send_data;
	CEdit	m_list;
	CStatic	m_led5;
	CStatic	m_led4;
	CStatic	m_led3;
	CStatic	m_led2;
	CStatic	m_led1;
	CButton	m_db8;
	CButton	m_db7;
	CButton	m_db6;
	CButton	m_db5;
	CButton	m_db4;
	CButton	m_db3;
	CButton	m_db2;
	CButton	m_db1;
	CButton	m_data;
	CButton	m_ctrl;
	CButton	m_send_ft;
	CButton	m_status;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinLPTDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinLPTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnStatusRadio();
	afx_msg void OnSendFtRadio();
	afx_msg void OnCtrlRadio();
	afx_msg void OnDataRadio();
	afx_msg void OnSendLbRadio();
	afx_msg void OnSendRadio();
	afx_msg void OnRunButton();
	afx_msg void OnCloseButton();
	afx_msg void OnDb1Radio();
	afx_msg void OnDb2Radio();
	afx_msg void OnDb3Radio();
	afx_msg void OnDb4Radio();
	afx_msg void OnDb5Radio();
	afx_msg void OnDb6Radio();
	afx_msg void OnDb7Radio();
	afx_msg void OnDb8Radio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINLPTDLG_H__6D28EBE0_7FF1_420C_BEA8_54AC5C2195AB__INCLUDED_)
