// WinCMOSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinCMOS.h"
#include "myio.h"
#include "WinCMOSDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char version[10]="1.0";
BYTE data_source[256];
BYTE old_sec;

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
	virtual BOOL OnInitDialog();
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

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char buf[200];

	sprintf(buf,"CMOS 版本: %s",version);
	GetDlgItem(IDC_VER_STATIC)->SetWindowText(buf);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinCMOSDlg dialog

CWinCMOSDlg::CWinCMOSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinCMOSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinCMOSDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinCMOSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinCMOSDlg)
	DDX_Control(pDX, IDC_REFRESH_CHECK, m_fresh);
	DDX_Control(pDX, IDC_EDIT, m_show);
	DDX_Control(pDX, IDC_B2_RADIO, m_b2);
	DDX_Control(pDX, IDC_B1_RADIO, m_b1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinCMOSDlg, CDialog)
	//{{AFX_MSG_MAP(CWinCMOSDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_REFRESH_CHECK, OnRefreshCheck)
	ON_BN_CLICKED(IDC_B1_RADIO, OnB1Radio)
	ON_BN_CLICKED(IDC_B2_RADIO, OnB2Radio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinCMOSDlg message handlers

BOOL CWinCMOSDlg::OnInitDialog()
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
	char buf[200];

	sprintf(buf,"CMOS 版本: %s",version);
	SetWindowText(buf);
	
	if(OnMyIo()==0)
	{
		MessageBox("Fail to open MyIO","Error",MB_OK | MB_ICONSTOP);
		CDialog::OnOK();
	}
	bank_no = 0;
	old_sec = 0xff;
	CheckBank();
	Get_RTC();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinCMOSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWinCMOSDlg::OnPaint() 
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
HCURSOR CWinCMOSDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CWinCMOSDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	OffMyIo();
	return CDialog::DestroyWindow();
}

void CWinCMOSDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	Get_RTC();
	
	CDialog::OnTimer(nIDEvent);
}

void CWinCMOSDlg::OnRefreshCheck() 
{
	// TODO: Add your control notification handler code here
	if(m_fresh.GetCheck() == BST_CHECKED)
	{
		SetTimer(1,500,0);
	}
	else
	{
		KillTimer(1);
	}
}

void CWinCMOSDlg::OnB1Radio() 
{
	// TODO: Add your control notification handler code here
	m_b2.SetCheck(BST_UNCHECKED);
	bank_no = 0;
}

void CWinCMOSDlg::OnB2Radio() 
{
	// TODO: Add your control notification handler code here
	m_b1.SetCheck(BST_UNCHECKED);
	bank_no = 1;
}

void CWinCMOSDlg::Get_RTC(void)
{
	int i;
	WORD addr;
	BYTE dd;
	
	if(old_sec==0xff)
	{
		ZeroMemory(data_source,sizeof(data_source));
	}
	for(i = 0; i < 128; i++)
	{
		WaitBusy();
		
		addr = 0x70 + bank_no*2;
		write_io_byte(addr,(BYTE)i);
		read_io_byte((WORD)(addr+1),&dd);
		data_source[i] = dd;
		
		if(i==0)
		{
			if(dd == old_sec)
			{
				return;
			}
			else
			{
				old_sec = dd;
			}
		}
	}
	
	Show_Data();

}

void CWinCMOSDlg::Show_Data(void)
{//顯示得到的資料
	char buf[1024],tmp[100];
	int i,j,qty;
	
	qty = m_show.GetWindowTextLength();
	m_show.SetReadOnly(FALSE);
	m_show.SetSel(0,-1,TRUE);
	m_show.Clear();
	m_show.SetReadOnly(TRUE);
	
	for(i = 0; i < 8; i++)
	{
		ZeroMemory(buf,sizeof(buf));
		for(j = 0; j < 16; j++)
		{
			sprintf(tmp,"%02X",data_source[i*16+j]);
			strcat(buf,tmp);
			
			if(j < 15)
			{
				strcat(buf," ");
			}
		}
		if(i < 7)
		{
			strcat(buf,"\r\n");
		}
		
		qty = m_show.GetWindowTextLength();
		m_show.SetSel(qty,qty,FALSE);
		m_show.ReplaceSel(buf,FALSE);
	}
	Show_ASCII();
}

void CWinCMOSDlg::Show_ASCII(void)
{//將得到的資料轉為ASCII code顯示出來
	char buf[1024],tmp[100];
	int i,j;
	
	ZeroMemory(buf,sizeof(buf));
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 16; j++)
		{
			if(data_source[i*16+j] >= 0x20)
			{//如果是一般的字元
				sprintf(tmp,"%c",data_source[i*16+j]);
			}
			else
			{//特殊字元，用.表示
				strcpy(tmp,".");
			}
			strcat(buf,tmp);
		}
		strcat(buf,"\n");
	}
	
	GetDlgItem(IDC_ASC_STATIC)->SetWindowText(buf);
}

void CWinCMOSDlg::CheckBank(void)
{//檢查各bank是否存在
	BYTE dd;
	
	WaitBusy();
	write_io_byte(0x70,(BYTE)0);
	read_io_byte((WORD)0x71,&dd);
	
	if(dd != 0xff)
	{
		m_b1.SetCheck(BST_CHECKED);
	}
	
	WaitBusy();
	write_io_byte(0x72,(BYTE)0);
	read_io_byte((WORD)0x73,&dd);
	
	if(dd != 0xff)
	{
		m_b2.EnableWindow(TRUE);
	}
}

void CWinCMOSDlg::WaitBusy(void)
{
	BYTE dd;
	
	do
	{
		write_io_byte(0x70,0xa);
		read_io_byte(0x71,&dd);
	}while((dd & 0x80) != 0);
}
