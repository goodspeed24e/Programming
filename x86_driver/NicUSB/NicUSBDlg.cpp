// NicUSBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NicUSB.h"
#include "NicUSBDlg.h"
#include "nic.h"

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
// CNicUSBDlg dialog

CNicUSBDlg::CNicUSBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNicUSBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNicUSBDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNicUSBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNicUSBDlg)
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_IPADDRESS, m_ip);
	DDX_Control(pDX, IDC_EDIT, m_string);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNicUSBDlg, CDialog)
	//{{AFX_MSG_MAP(CNicUSBDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNicUSBDlg message handlers

BOOL CNicUSBDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNicUSBDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNicUSBDlg::OnPaint() 
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
HCURSOR CNicUSBDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNicUSBDlg::OnOK() 
{
	// TODO: Add extra validation here
	char buf[20];
	int len;
	BYTE ips[4];
	char ip[20];
	
	if(m_ip.GetAddress(ips[0],ips[1],ips[2],ips[3]) != 4)
	{
		MessageBox("Please input IP first","Error",MB_OK | MB_ICONSTOP);
		m_ip.SetFieldFocus(0);
		return;
	}
	
	sprintf(ip,"%d.%d.%d.%d",ips[0],ips[1],ips[2],ips[3]);
	if(NicOpen(ip,5678,SOCK_STREAM)==0) //¨Ï¥Î5678°ð
	{
		MessageBox("Fail at Open Networks","Error",MB_OK | MB_ICONSTOP);
		return; 
	}
	m_string.GetWindowText(buf,sizeof(buf));
	
	len = strlen(buf);
	Write(buf,len);
	
	NicClose();
	Terminate();
	//CDialog::OnOK();
}

void CNicUSBDlg::OnCancel() 
{
	// TODO: Add extra cleanup here

	CDialog::OnCancel();
}
