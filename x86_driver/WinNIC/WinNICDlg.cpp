// WinNICDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinNIC.h"
#include "WinNICDlg.h"
#include "nic.h"

//#pragma comment(lib, "ws2_32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinNICDlg dialog

CWinNICDlg::CWinNICDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinNICDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinNICDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinNICDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinNICDlg)
	DDX_Control(pDX, IDC_IP_STATIC, m_self_ip);
	DDX_Control(pDX, IDC_S_BUTTON, m_s_bt);
	DDX_Control(pDX, IDC_LOGOFF_RADIO, m_logoff);
	DDX_Control(pDX, IDC_REBOOT_RADIO, m_reboot);
	DDX_Control(pDX, IDC_OFF_RADIO, m_off);
	DDX_Control(pDX, IDC_CNT_BUTTON, m_connect);
	DDX_Control(pDX, IDC_IPADDRESS, m_ip);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinNICDlg, CDialog)
	//{{AFX_MSG_MAP(CWinNICDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CNT_BUTTON, OnCntButton)
	ON_BN_CLICKED(IDC_OFF_RADIO, OnOffRadio)
	ON_BN_CLICKED(IDC_REBOOT_RADIO, OnRebootRadio)
	ON_BN_CLICKED(IDC_LOGOFF_RADIO, OnLogoffRadio)
	ON_BN_CLICKED(IDC_S_BUTTON, OnSButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinNICDlg message handlers

BOOL CWinNICDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	BYTE ip[4];
	char buf[100];
	
	//取得自己IP
	GetHostIP(NULL,ip[0],ip[1],ip[2],ip[3]);
	sprintf(buf,"IP:%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
	m_self_ip.SetWindowText(buf);
	m_off.SetCheck(BST_CHECKED);
	connect_flag = 0;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinNICDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinNICDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinNICDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWinNICDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CWinNICDlg::OnCntButton() 
{
	// TODO: Add your control notification handler code here
	BYTE ips[4];
	char ip[20];
//			BYTE pp[3];
//			int ff;
	
	if(connect_flag==0)
	{
		if(m_ip.GetAddress(ips[0],ips[1],ips[2],ips[3]) != 4)
		{
			MessageBox("Please input IP first","Error",MB_OK | MB_ICONSTOP);
			m_ip.SetFieldFocus(0);
			return;
		}
	
		sprintf(ip,"%d.%d.%d.%d",ips[0],ips[1],ips[2],ips[3]);
		if(NicOpen(ip,5678,SOCK_STREAM)==0) //使用5678埠
		{
			MessageBox("Fail at Open Networks","Error",MB_OK | MB_ICONSTOP);
			return; 
 		}
 		
 		OnOffItem(TRUE);
 		
 		m_connect.SetWindowText("斷線");
 		connect_flag = 1;
 		m_ip.EnableWindow(FALSE);
	}
	else
	{
		NicClose();
		Terminate();
		
		OnOffItem(FALSE);
		
		m_connect.SetWindowText("連線");
		connect_flag = 0;
		m_ip.EnableWindow(TRUE);
	}
}

void CWinNICDlg::OnOffRadio() 
{
	// TODO: Add your control notification handler code here
	//m_off.SetCheck(BST_UNCHECKED);
	m_reboot.SetCheck(BST_UNCHECKED);
	m_logoff.SetCheck(BST_UNCHECKED);
}

void CWinNICDlg::OnRebootRadio() 
{
	// TODO: Add your control notification handler code here
	m_off.SetCheck(BST_UNCHECKED);
	//m_reboot.SetCheck(BST_UNCHECKED);
	m_logoff.SetCheck(BST_UNCHECKED);
}

void CWinNICDlg::OnLogoffRadio() 
{
	// TODO: Add your control notification handler code here
	m_off.SetCheck(BST_UNCHECKED);
	m_reboot.SetCheck(BST_UNCHECKED);
	//m_logoff.SetCheck(BST_UNCHECKED);
}

void CWinNICDlg::OnSButton() 
{
	// TODO: Add your control notification handler code here
	char buf[20];
	int len;
	
	if(m_off.GetCheck() == BST_CHECKED)
	{
		strcpy(buf,"Intra#OFF");
	}
	else if(m_reboot.GetCheck() == BST_CHECKED)
	{
		strcpy(buf,"Intra#REBOOT");
	}
	else if(m_logoff.GetCheck() == BST_CHECKED)
	{
		strcpy(buf,"Intra#LOGOFF");
	}
	
	len = strlen(buf);
	Write(buf,len);
	
}

BOOL CWinNICDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	/*if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) 
		{
			//AfxMessageBox("Enter down");
			
			//pMsg->wParam = VK_TAB;
		}
	}*/
	return CDialog::PreTranslateMessage(pMsg);
}

void CWinNICDlg::OnOffItem(BOOL sw)
{
	m_s_bt.EnableWindow(sw);
	m_logoff.EnableWindow(sw);
	m_reboot.EnableWindow(sw);
	m_off.EnableWindow(sw);
}

void CWinNICDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(connect_flag==1)
	{//如果已開啟nic要先關閉
		NicClose();
		Terminate();
	}
	CDialog::OnCancel();
}
