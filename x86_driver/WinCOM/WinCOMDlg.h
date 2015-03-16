// WinCOMDlg.h : header file
//

#if !defined(AFX_WINCOMDLG_H__C37FC0E5_D76B_4CEB_AD5C_38CF7B3D8144__INCLUDED_)
#define AFX_WINCOMDLG_H__C37FC0E5_D76B_4CEB_AD5C_38CF7B3D8144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum
{
	MY_CBR_110,
	MY_CBR_300,
	MY_CBR_1200,
	MY_CBR_2400,
	MY_CBR_4800,
	MY_CBR_9600,
	MY_CBR_14400,
	MY_CBR_19200,
	MY_CBR_38400,
	MY_CBR_57600,
	MY_CBR_115200
};

enum
{
	MY_EVENPARITY,
	MY_ODDPARITY,
	MY_NOPARITY,
	MY_MARKPARITY, 
	MY_SPACEPARITY 
};

enum
{
	MY_ONESTOPBIT, 
	MY_ONE5STOPBITS,
	MY_TWOSTOPBITS 
};

/////////////////////////////////////////////////////////////////////////////
// CWinCOMDlg dialog

class CWinCOMDlg : public CDialog
{
// Construction
public:
//	int id;
	int com_qty;
	int func;
	int on_off;
	HANDLE hCom1;
	HANDLE hCom2;
	void Item_ON_OFF(void);
	BOOL Init_COM(HANDLE *hd,char *com_no);
	void OffAll(void);
	void put_string(char *buf,int dir);
	
	HANDLE m_hThread;
	DWORD m_thisThreadID;
	friend DWORD __stdcall ChildThread(void *p);
	CWinCOMDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinCOMDlg)
	enum { IDD = IDD_WINCOM_DIALOG };
	CComboBox	m_source;
	CButton	m_send_bt;
	CComboBox	m_target;
	CComboBox	m_stop;
	CEdit	m_send;
	CEdit	m_recv;
	CButton	m_recv_clr;
	CComboBox	m_qty;
	CComboBox	m_parity;
	CButton	m_on_off;
	CButton	m_func3;
	CButton	m_func2;
	CButton	m_func1;
	CComboBox	m_baudrate;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinCOMDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinCOMDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFunc1Radio();
	afx_msg void OnFunc2Radio();
	afx_msg void OnFunc3Radio();
	virtual void OnOK();
	afx_msg void OnOnOffButton();
	afx_msg void OnRecvClrButton();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeSourceCombo();
	afx_msg void OnSelchangeTargetCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINCOMDLG_H__C37FC0E5_D76B_4CEB_AD5C_38CF7B3D8144__INCLUDED_)
