// IPMIToolDlg.h : header file
//

#if !defined(AFX_IPMITOOLDLG_H__3991C68E_6747_446D_BC6D_55AD0ED2E33C__INCLUDED_)
#define AFX_IPMITOOLDLG_H__3991C68E_6747_446D_BC6D_55AD0ED2E33C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIPMIToolDlg dialog

class CIPMIToolDlg : public CDialog
{
// Construction
public:
	int cmd_in; //是不是在cmd位置
	WORD KCS_baseIO; //KCS data port
	WORD KCS_STATUS;
	WORD KCS_CTL;
	WORD tm; //KCS time-out
	int cn_flag; //是否IOL連線
	
	DWORD mssID; //manaed System Session ID from BMC
	DWORD sSEQ;
	BYTE cmdSEQ;
	char userID[16];
	int server_length;						/* Length of server struct */
	WSADATA w;
	SOCKET sd;
	struct sockaddr_in server;				/* Information about the server */
	struct sockaddr_in client;				/* Information about the client */

	/*IPMI KCS function*/
	int SearchIPMIBase(void);
	int Send2KCS(void);
	int chktmout(void);
	int chkBMCbusy(void);
	int chkBMCibfrdy(void);
	int chkBMCobfrdy_l(void);
	int chkBMCobfrdy_h(void);
	BYTE IPDATA(void);
	void OPDATA(BYTE data);
	void OPCMD(BYTE data);
	int chkBMCtxrdy(void);
	int chkBMCrxrdy(void);
	
	/*IOL*/
	int CreateUDP(BYTE ip1,BYTE ip2, BYTE ip3, BYTE ip4);
	int PingPong(void);
	int OpenSession(void);
	int RAKP(int sld);
	int IOL_Cmd(BYTE *cmd,int cmdlen);
	int CloseSession15(void);
	int asm_20_iol_package(BYTE *buf,BYTE pd_type,DWORD ssID,DWORD sSQ, WORD pd_len, BYTE *buf2);
	void conn_fail(int sld);
	
	void OnOffCmd(int sld);
	void ShowStatus(char *str);
	void Show_Data(void);
	void ShowCompletionCode(void);
	int GetCommandIntoBuf(void);
	CIPMIToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIPMIToolDlg)
	enum { IDD = IDD_IPMITOOL_DIALOG };
	CEdit	m_user;
	CButton	m_kcs_bt;
	CButton	m_kcs;
	CIPAddressCtrl	m_ip;
	CButton	m_iol;
	CButton	m_cn;
	CEdit	m_offset;
	CButton	m_send;
	CEdit	m_report;
	CEdit	m_cmd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPMIToolDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIPMIToolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSendButton();
	virtual void OnOK();
	afx_msg void OnSetfocusCmdEdit();
	afx_msg void OnKillfocusCmdEdit();
	afx_msg void OnIolRadio();
	afx_msg void OnKcsRadio();
	afx_msg void OnCnBt();
	afx_msg void OnKcsBt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPMITOOLDLG_H__3991C68E_6747_446D_BC6D_55AD0ED2E33C__INCLUDED_)
