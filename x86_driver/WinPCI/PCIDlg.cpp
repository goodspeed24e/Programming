// PCIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCI.h"
#include "def.h"
#include "ListDlg.h"
#include "PCIDlg.h"

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
// CPCIDlg dialog

CPCIDlg::CPCIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPCIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPCIDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPCIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPCIDlg)
	DDX_Control(pDX, IDC_TAB, m_tab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPCIDlg, CDialog)
	//{{AFX_MSG_MAP(CPCIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MSG_STATUS, OnStatus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPCIDlg message handlers

BOOL CPCIDlg::OnInitDialog()
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
	TC_ITEM item;
	CRect   rect;
	
	m_listDlg = new CListDlg ;
	
	/*標籤的字*/
	item.mask = TCIF_TEXT;

	item.pszText = "PCI裝置";
	m_tab.InsertItem(0, &item);

	item.pszText = "PCI插槽";
	m_tab.InsertItem(1, &item);

	//設定顯示位置
	m_tab.GetClientRect(&rect);
	rect.DeflateRect(5,5);
	rect.top += 25;

	//建立各設定視窗
	m_listDlg->Create(IDD_LIST_DIALOG, &m_tab);
	m_listDlg->MoveWindow(&rect);
	
	m_listDlg->m_dlg = this;
	
	//顯示視窗
	m_listDlg->func = 0;
	m_listDlg->ShowWindow(SW_SHOW);
	m_curTab = 0;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPCIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPCIDlg::OnPaint() 
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
HCURSOR CPCIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPCIDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int newTab;

	// see which tab was clicked on
	newTab = m_tab.GetCurSel();

	// if it's not the current tab, make the switch by showing and hiding the various sub-dialogs
	if (newTab != m_curTab)//如果不是目前的頁籤
	{//切換頁籤
		GetDlgItem(IDC_STATUS_STATIC)->SetWindowText("Loading, please wait...");
		
		m_listDlg->ShowWindow(SW_HIDE);

		m_listDlg->func = newTab;
		m_listDlg->ShowWindow(SW_SHOW);

		m_curTab = newTab;
		
	}
	*pResult = 0;
}

LONG CPCIDlg::OnStatus(WPARAM wParam, LPARAM lParam)
{
	char* pMsg = (char*) lParam;
	
	GetDlgItem(IDC_STATUS_STATIC)->SetWindowText(pMsg);
	delete pMsg;
	return 0;
}
