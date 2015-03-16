// WinSlaveDlg.cpp : implementation file
//
#define _WIN32_WINNT 0x0500

#include "stdafx.h"
#include "WinSlave.h"
#include "WinSlaveDlg.h"
#include "nic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

unsigned char recvBuf[256];
int OS_version;
BOOL GetOSVersion(void);
int Shutdown( unsigned int flag );
int RecvData(void);

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
// CWinSlaveDlg dialog

CWinSlaveDlg::CWinSlaveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinSlaveDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinSlaveDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinSlaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinSlaveDlg)
	DDX_Control(pDX, IDC_SHOW_STATIC, m_show);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinSlaveDlg, CDialog)
	//{{AFX_MSG_MAP(CWinSlaveDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinSlaveDlg message handlers

BOOL CWinSlaveDlg::OnInitDialog()
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
	sprintf(buf,"等待中 - IP:%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
	
	m_show.SetWindowText(buf);
	
	GetOSVersion(); //取得OS版本

	m_hThread = CreateThread(NULL, 30000, MLTProc, (void*) this, CREATE_SUSPENDED, &m_thisThreadID);
	
	ResumeThread(m_hThread);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinSlaveDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWinSlaveDlg::OnPaint() 
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
HCURSOR CWinSlaveDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CWinSlaveDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}

DWORD __stdcall MLTProc(void *p)
{//
	CWinSlaveDlg *hd=(CWinSlaveDlg *)p;
	//
	
	//hd->ShowStr("File transfer service start...");
	//MessageBox(NULL,"Listen","note",MB_OK);
	while(1) //永遠執行
	{
		SOCKET socket;

		if(NicListen(5678,SOCK_STREAM)==0)
			return 0;
		
		if (Accept(socket)==0)
			continue;
			
		BkSocket(); //先備份Socket
		SetSocket(socket);

		if(WaitInputData(10) != 0)
		{// 10秒內有回應就處理資料
			char tmp[20];

			RecvData();
			strcpy(tmp,(char *)&(recvBuf[6]));
			if(stricmp(tmp,"OFF") == 0)
			{
				hd->m_show.SetWindowText("準備關機");
				Shutdown(EWX_SHUTDOWN | EWX_FORCEIFHUNG);
			}
			else if(stricmp(tmp,"REBOOT") == 0)
			{
				hd->m_show.SetWindowText("準備重新開機");
				Shutdown(EWX_REBOOT | EWX_FORCEIFHUNG);
			}
			else if(stricmp(tmp,"LOGOFF") == 0)
			{
				hd->m_show.SetWindowText("準備登出");
				Shutdown(EWX_LOGOFF | EWX_FORCEIFHUNG);
			}
		}
 		NicClose();
		RsSocket(); //還原socket
	}
	return 0;
}

int RecvData(void)
{
	int ret_len;
	
	memset(recvBuf,0,sizeof(recvBuf));
	if(Read(recvBuf,256,&ret_len)==0)
	{
			//MessageBox(NULL,"read rtn=0","error",MB_OK);
		return -1;
	}
	
	/*if(!ret_len)
	{
			MessageBox(NULL,"len=0","error",MB_OK);
		return -1;
	}*/
	
	return ret_len;
}

int Shutdown( unsigned int flag )
{//關機主程式
	if(OS_version > 0)
	{//NT serial
		HANDLE hToken; 
		TOKEN_PRIVILEGES tkp; 
 
		// Get a token for this process. 
		if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		{
			MessageBox(NULL,"OpenProcessToken Error!!","FAIL",MB_OK);
			return 1;
		}
 
		// Get the LUID for the shutdown privilege. 
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 
 
		tkp.PrivilegeCount = 1;  // one privilege to set
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 
		// Set the shutdown privilege for this process. 
 		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); 
 
		// Cannot test the return value of AdjustTokenPrivileges. 
		if (GetLastError() != ERROR_SUCCESS) 
		{
			MessageBox(NULL,"AdjustTokenPrivileges Error!!","FAIL",MB_OK);
			return 1;
		}
	}
	
	// Shut down the system and force all applications to close. 
 	if (!ExitWindowsEx(flag, 0)) 
	{
		MessageBox(NULL,"ExitWindowsEx Error!!","FAIL",MB_OK); 
	}
	return 0;
}

BOOL GetOSVersion(void)
{
	OSVERSIONINFOEX osvi;
	BOOL bOsVersionInfoEx;

	memset(&osvi,0,sizeof(osvi));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if( (bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) ==0)
	{
		// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
		osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
		if( GetVersionEx ( (OSVERSIONINFO *) &osvi) ==0)
		{
			return FALSE;
		}
	}

	switch (osvi.dwPlatformId)
	{
		// Tests for Windows NT product family.
		case VER_PLATFORM_WIN32_NT:
			//   "Microsoft Windows NT"         "Microsoft Windows 2000 "
			//if( osvi.dwMajorVersion <= 4 || ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 ))
			{
				OS_version = 1;
			}
			break;

		// Test for the Windows 95 product family.
		case VER_PLATFORM_WIN32_WINDOWS:
			OS_version = 0;
			break;
	}
	return TRUE;
}
