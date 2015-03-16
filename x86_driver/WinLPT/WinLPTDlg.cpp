// WinLPTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinLPT.h"
#include "WinLPTDlg.h"
#include "myio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CTRL_PORT 0x37A
#define STATUS_PORT 0x379
#define DATA_PORT 0x378 

int SendString(char *data);
int RecvByte(char *data);
int SendByte(char data);
void delay1ms(DWORD delay);

BITMAP bitmap11,bitmap12,bitmap21,bitmap22,bitmap31,bitmap32;
HBITMAP hbitmap11,hbitmap12,hbitmap21,hbitmap22,hbitmap31,hbitmap32;
HINSTANCE	hInstResource11,hInstResource12,hInstResource21,hInstResource22,hInstResource31,hInstResource32;

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
// CWinLPTDlg dialog

CWinLPTDlg::CWinLPTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinLPTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinLPTDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinLPTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinLPTDlg)
	DDX_Control(pDX, IDC_NAME_EDIT, m_name);
	DDX_Control(pDX, IDC_SEND_LB_RADIO, m_send_lb);
	DDX_Control(pDX, IDC_SEND_RADIO, m_send);
	DDX_Control(pDX, IDC_SEND_EDIT, m_send_data);
	DDX_Control(pDX, IDC_LIST_EDIT, m_list);
	DDX_Control(pDX, IDC_LED5_STATIC, m_led5);
	DDX_Control(pDX, IDC_LED4_STATIC, m_led4);
	DDX_Control(pDX, IDC_LED3_STATIC, m_led3);
	DDX_Control(pDX, IDC_LED2_STATIC, m_led2);
	DDX_Control(pDX, IDC_LED1_STATIC, m_led1);
	DDX_Control(pDX, IDC_DB8_RADIO, m_db8);
	DDX_Control(pDX, IDC_DB7_RADIO, m_db7);
	DDX_Control(pDX, IDC_DB6_RADIO, m_db6);
	DDX_Control(pDX, IDC_DB5_RADIO, m_db5);
	DDX_Control(pDX, IDC_DB4_RADIO, m_db4);
	DDX_Control(pDX, IDC_DB3_RADIO, m_db3);
	DDX_Control(pDX, IDC_DB2_RADIO, m_db2);
	DDX_Control(pDX, IDC_DB1_RADIO, m_db1);
	DDX_Control(pDX, IDC_DATA_RADIO, m_data);
	DDX_Control(pDX, IDC_CTRL_RADIO, m_ctrl);
	DDX_Control(pDX, IDC_SEND_FT_RADIO, m_send_ft);
	DDX_Control(pDX, IDC_STATUS_RADIO, m_status);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinLPTDlg, CDialog)
	//{{AFX_MSG_MAP(CWinLPTDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STATUS_RADIO, OnStatusRadio)
	ON_BN_CLICKED(IDC_SEND_FT_RADIO, OnSendFtRadio)
	ON_BN_CLICKED(IDC_CTRL_RADIO, OnCtrlRadio)
	ON_BN_CLICKED(IDC_DATA_RADIO, OnDataRadio)
	ON_BN_CLICKED(IDC_SEND_LB_RADIO, OnSendLbRadio)
	ON_BN_CLICKED(IDC_SEND_RADIO, OnSendRadio)
	ON_BN_CLICKED(IDC_RUN_BUTTON, OnRunButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnCloseButton)
	ON_BN_CLICKED(IDC_DB1_RADIO, OnDb1Radio)
	ON_BN_CLICKED(IDC_DB2_RADIO, OnDb2Radio)
	ON_BN_CLICKED(IDC_DB3_RADIO, OnDb3Radio)
	ON_BN_CLICKED(IDC_DB4_RADIO, OnDb4Radio)
	ON_BN_CLICKED(IDC_DB5_RADIO, OnDb5Radio)
	ON_BN_CLICKED(IDC_DB6_RADIO, OnDb6Radio)
	ON_BN_CLICKED(IDC_DB7_RADIO, OnDb7Radio)
	ON_BN_CLICKED(IDC_DB8_RADIO, OnDb8Radio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinLPTDlg message handlers

BOOL CWinLPTDlg::OnInitDialog()
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
	//int i;
	
	if(OnMyIo()==0)
	{
		MessageBox("Fail to open MyIO","Error",MB_OK | MB_ICONSTOP);
		CDialog::OnOK();
	}
	
	//文字圖檔
	hInstResource11 = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_PIC1_BITMAP), RT_BITMAP);
	hbitmap11=(HBITMAP)LoadImage(hInstResource11,MAKEINTRESOURCE(IDB_PIC1_BITMAP),IMAGE_BITMAP,0,0,0);
	GetObject(hbitmap11, sizeof(bitmap11), &bitmap11);
	
	hInstResource12 = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_PIC11_BITMAP), RT_BITMAP);
	hbitmap12=(HBITMAP)LoadImage(hInstResource12,MAKEINTRESOURCE(IDB_PIC11_BITMAP),IMAGE_BITMAP,0,0,0);
	GetObject(hbitmap12, sizeof(bitmap12), &bitmap12);
	
	hInstResource21 = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_PIC2_BITMAP), RT_BITMAP);
	hbitmap21=(HBITMAP)LoadImage(hInstResource21,MAKEINTRESOURCE(IDB_PIC2_BITMAP),IMAGE_BITMAP,0,0,0);
	GetObject(hbitmap21, sizeof(bitmap21), &bitmap21);
	
	hInstResource22 = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_PIC21_BITMAP), RT_BITMAP);
	hbitmap22=(HBITMAP)LoadImage(hInstResource22,MAKEINTRESOURCE(IDB_PIC21_BITMAP),IMAGE_BITMAP,0,0,0);
	GetObject(hbitmap22, sizeof(bitmap22), &bitmap22);
	
	hInstResource31 = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_PIC3_BITMAP), RT_BITMAP);
	hbitmap31=(HBITMAP)LoadImage(hInstResource31,MAKEINTRESOURCE(IDB_PIC3_BITMAP),IMAGE_BITMAP,0,0,0);
	GetObject(hbitmap31, sizeof(bitmap31), &bitmap31);
	
	hInstResource32 = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_PIC31_BITMAP), RT_BITMAP);
	hbitmap32=(HBITMAP)LoadImage(hInstResource32,MAKEINTRESOURCE(IDB_PIC31_BITMAP),IMAGE_BITMAP,0,0,0);
	GetObject(hbitmap32, sizeof(bitmap32), &bitmap32);
	
	//載入Icon
	m_hOnIcon = AfxGetApp()->LoadIcon(IDI_ON_ICON);
	m_hOffIcon = AfxGetApp()->LoadIcon(IDI_OFF_ICON);
	
	//預設值
	OnStatusRadio();
	m_ctrl.SetCheck(BST_CHECKED);
	
	ctrl_data_byte = 0;
	send_flag = 0;
	
	//啟動拉咧service
	m_hThread = CreateThread(NULL, 30000, MLTProc, (void*) this, CREATE_SUSPENDED, &m_thisThreadID);
	// check for successful thread creation
	if (m_hThread == NULL)
	{
		MessageBox("無法建立 拉咧 執行緒，拉咧功能將無法使用","警告",MB_OK | MB_ICONINFORMATION);
		m_send.EnableWindow(FALSE);
		OnOffGroup4(0);
	}
	else
	{
		ResumeThread(m_hThread);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinLPTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWinLPTDlg::OnPaint() 
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
		HDC mem_hdc11,mem_hdc12,mem_hdc21,mem_hdc22;
		CPaintDC dc(this);
	
		mem_hdc12=CreateCompatibleDC(dc);
		SelectObject(mem_hdc12,hbitmap12);
		BitBlt(dc,210,25,bitmap12.bmWidth,bitmap12.bmHeight,mem_hdc12,0,0,SRCPAINT);
		
		mem_hdc11=CreateCompatibleDC(dc);
		SelectObject(mem_hdc11,hbitmap11);
		BitBlt(dc,210,25,bitmap11.bmWidth,bitmap11.bmHeight,mem_hdc11,0,0,SRCAND);
		
		if(m_ctrl.GetCheck() == BST_CHECKED)
		{
			mem_hdc22=CreateCompatibleDC(dc);
			SelectObject(mem_hdc22,hbitmap22);
			BitBlt(dc,153,97,bitmap22.bmWidth,bitmap22.bmHeight,mem_hdc22,0,0,SRCPAINT);
		
			mem_hdc21=CreateCompatibleDC(dc);
			SelectObject(mem_hdc21,hbitmap21);
			BitBlt(dc,153,97,bitmap21.bmWidth,bitmap21.bmHeight,mem_hdc21,0,0,SRCAND);
		}
		else
		{
			mem_hdc22=CreateCompatibleDC(dc);
			SelectObject(mem_hdc22,hbitmap32);
			BitBlt(dc,140,106,bitmap32.bmWidth,bitmap32.bmHeight,mem_hdc22,0,0,SRCPAINT);
		
			mem_hdc21=CreateCompatibleDC(dc);
			SelectObject(mem_hdc21,hbitmap31);
			BitBlt(dc,140,106,bitmap31.bmWidth,bitmap31.bmHeight,mem_hdc21,0,0,SRCAND);
		}
		
		DeleteDC(mem_hdc11);
		DeleteDC(mem_hdc12);
		DeleteDC(mem_hdc21);
		DeleteDC(mem_hdc22);
		
		
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinLPTDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CWinLPTDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete m_hOnIcon;
	delete m_hOffIcon;
	
	OffMyIo();
	return CDialog::DestroyWindow();
}

void CWinLPTDlg::OnOK() 
{
	// TODO: Add extra validation here
	OnRunButton();
	//CDialog::OnOK();
}

void CWinLPTDlg::OnStatusRadio() 
{//讀狀態埠
	// TODO: Add your control notification handler code here
	OffMainRadio();
	m_status.SetCheck(BST_CHECKED);
	
	OnOffGroup1(1);
	OnOffGroup2(0);
	OnOffGroup3(0);
	OnOffGroup4(0);
}

void CWinLPTDlg::OnSendFtRadio() 
{//傳送資料到測試器
	// TODO: Add your control notification handler code here
	OffMainRadio();
	m_send_ft.SetCheck(BST_CHECKED);
	
	OnOffGroup1(0);
	OnOffGroup2(1);
	OnOffGroup3(0);
	OnOffGroup4(0);
}

void CWinLPTDlg::OnCtrlRadio() 
{//透過ctrl port送資料到測試器
	// TODO: Add your control notification handler code here
	m_data.SetCheck(BST_UNCHECKED);
	
	m_db5.EnableWindow(FALSE);
	m_db6.EnableWindow(FALSE);
	m_db7.EnableWindow(FALSE);
	m_db8.EnableWindow(FALSE);
	//
	RedrawWindow(NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);//畫面重畫
}

void CWinLPTDlg::OnDataRadio() 
{//透過data port送資料到測試器
	// TODO: Add your control notification handler code here
	m_ctrl.SetCheck(BST_UNCHECKED);
	
	m_db5.EnableWindow(TRUE);
	m_db6.EnableWindow(TRUE);
	m_db7.EnableWindow(TRUE);
	m_db8.EnableWindow(TRUE);
	//
	RedrawWindow(NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);//畫面重畫
}

void CWinLPTDlg::OnSendLbRadio() 
{//迴路器送資料
	// TODO: Add your control notification handler code here
	OffMainRadio();
	m_send_lb.SetCheck(BST_CHECKED);
	
	OnOffGroup1(0);
	OnOffGroup2(0);
	OnOffGroup3(1);
	OnOffGroup4(0);
}

void CWinLPTDlg::OnSendRadio() 
{//兩台電腦傳輸
	// TODO: Add your control notification handler code here
	OffMainRadio();
	m_send.SetCheck(BST_CHECKED);
	
	OnOffGroup1(0);
	OnOffGroup2(0);
	OnOffGroup3(0);
	OnOffGroup4(1);
	
	write_io_byte(DATA_PORT,0x0);
}

void CWinLPTDlg::OnRunButton() 
{//執行
	// TODO: Add your control notification handler code here
	BYTE data8,data_in8;
	int i;
	char buf[200];
	
	if(m_status.GetCheck() == BST_CHECKED)
	{//狀態燈
		write_io_byte(DATA_PORT,0xff); //送出高電位到data port, 再由外部電路接到status port
		read_io_byte(STATUS_PORT,&data8);
		
		if((data8 & 0x8) == 0x8)
		{
			m_led5.SetIcon(m_hOnIcon);
		}
		else
		{
			m_led5.SetIcon(m_hOffIcon);
		}
		if((data8 & 0x10) == 0x10)
		{
			m_led4.SetIcon(m_hOnIcon);
		}
		else
		{
			m_led4.SetIcon(m_hOffIcon);
		}
		if((data8 & 0x20) == 0x20)
		{
			m_led3.SetIcon(m_hOnIcon);
		}
		else
		{
			m_led3.SetIcon(m_hOffIcon);
		}
		if((data8 & 0x40) == 0x40)
		{
			m_led2.SetIcon(m_hOnIcon);
		}
		else
		{
			m_led2.SetIcon(m_hOffIcon);
		}
		if((data8 & 0x80)==0x80) //這個bit顛倒
		{
			m_led1.SetIcon(m_hOnIcon);
		}
		else
		{
			m_led1.SetIcon(m_hOffIcon);
		}		
	}
	else if(m_send_ft.GetCheck() == BST_CHECKED)
	{//測試器
		data8 = 0;
		
		if(m_db1.GetCheck() == BST_CHECKED)
		{
			data8 |= 1;
		}
		if(m_db2.GetCheck() == BST_CHECKED)
		{
			data8 |= 2;
		}
		if(m_db3.GetCheck() == BST_CHECKED)
		{
			data8 |= 4;
		}
		if(m_db4.GetCheck() == BST_CHECKED)
		{
			data8 |= 8;
		}
		
		if(m_data.GetCheck()==BST_CHECKED) //資料埠才需要這4個bit
		{
			if(m_db5.GetCheck() == BST_CHECKED)
			{
				data8 |= 0x10;
			}
			if(m_db6.GetCheck() == BST_CHECKED)
			{
				data8 |= 0x20;
			}
			if(m_db7.GetCheck() == BST_CHECKED)
			{
				data8 |= 0x40;
			}
			if(m_db8.GetCheck() == BST_CHECKED)
			{
				data8 |= 0x80;
			}
		}
		
		if(m_ctrl.GetCheck()==BST_CHECKED) //控制埠
		{
			write_io_byte(CTRL_PORT,data8);
		}
		else //資料埠
		{
			write_io_byte(DATA_PORT,data8);
		}
	}
	else if(m_send_lb.GetCheck() == BST_CHECKED)
	{//迴路
		//測試資料埠
		//data8 = 0x80;
		//write_io_byte(DATA_PORT,data8);
		
		data8 = 0x0;
		write_io_byte(CTRL_PORT,data8); //讓SELECT為0，輸出1
		write_io_byte(DATA_PORT,data8);
			
		read_io_byte(STATUS_PORT,&data_in8);
		if((data_in8 & 0x08) == 0x08)
		{
			sprintf(buf,"測試 資料埠 失敗 %02Xh -> %02Xh",data8,data_in8);
			WriteState(buf);
			return;
		}
			
		data8 = 0x01;
		for(i = 0; i < 8; i++)
		{
			write_io_byte(DATA_PORT,data8);
				
			read_io_byte(STATUS_PORT,&data_in8);
			
			if( (data_in8 & 0x08)==0x08 && i != 7)
			{
				sprintf(buf,"測試 資料埠 失敗 %02Xh -> %02Xh",data8,data_in8);
				WriteState(buf);
				return;
			}
			data8 <<= 1;
			data8 |= 1;
		}
			
		//測試
		data8 = 0x0e;
		write_io_byte(CTRL_PORT,data8);
		write_io_byte(DATA_PORT,0xff);
		read_io_byte(STATUS_PORT,&data_in8);
		if( (data_in8 & 0xf0) == 0x20)
		{
			data8 = 0x01;
			write_io_byte(CTRL_PORT,data8);
			read_io_byte(STATUS_PORT,&data_in8);
			if( (data_in8 & 0xf0) == 0xd0)
			{
				WriteState("資料傳送完成");
				return;
			}
			else
			{
				sprintf(buf,"測試 控制埠 -> 狀態埠 失敗 %02Xh -> %02Xh",data8,data_in8);
				WriteState(buf);
				return;
			}
		}
		else
		{
			sprintf(buf,"測試 控制埠 -> 狀態埠 失敗 %02Xh -> %02Xh",data8,data_in8);
			WriteState(buf);
			return;
		}
	}
	else
	{//兩台電腦傳輸
		send_flag = 1;
	}
}

void CWinLPTDlg::OnCloseButton() 
{//關閉程式
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CWinLPTDlg::OffMainRadio(void)
{
	m_status.SetCheck(BST_UNCHECKED);
	m_send_ft.SetCheck(BST_UNCHECKED);
	m_send_lb.SetCheck(BST_UNCHECKED);
	m_send.SetCheck(BST_UNCHECKED);
}

void CWinLPTDlg::OnOffGroup1(int sw)
{
	/*m_led1.ShowWindow(SW_HIDE);
	m_led2.ShowWindow(SW_HIDE);
	m_led3.ShowWindow(SW_HIDE);
	m_led4.ShowWindow(SW_HIDE);
	m_led5.ShowWindow(SW_HIDE);*/
}

void CWinLPTDlg::OnOffGroup2(int sw)
{
	m_ctrl.EnableWindow(sw);
	m_data.EnableWindow(sw);
	m_db1.EnableWindow(sw);
	m_db2.EnableWindow(sw);
	m_db3.EnableWindow(sw);
	m_db4.EnableWindow(sw);
	if(m_ctrl.GetCheck()==BST_UNCHECKED)
	{
		m_db5.EnableWindow(sw);
		m_db6.EnableWindow(sw);
		m_db7.EnableWindow(sw);
		m_db8.EnableWindow(sw);
	}
}

void CWinLPTDlg::OnOffGroup3(int sw)
{
	//
}

void CWinLPTDlg::OnOffGroup4(int sw)
{
	m_send_data.EnableWindow(sw);
	m_name.EnableWindow(sw);
	m_name.SetFocus();
}

void CWinLPTDlg::WriteState(char *str)
{
	int qty;
	SYSTEMTIME st;
	char times[100];
						
	GetLocalTime(&st);
	sprintf(times,"%d/%02d/%02d %02d:%02d:%02d  ",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	
	qty = m_list.GetWindowTextLength();
	m_list.SetSel(qty,qty,FALSE);
	
	//加上時間
	m_list.ReplaceSel(times,FALSE);
	
	m_list.ReplaceSel(str,FALSE);
	m_list.ReplaceSel("\r\n",FALSE);
		
	qty = m_list.GetLineCount();
		
	if(qty > 1000)
	{
		m_list.SetReadOnly(FALSE);
		qty = m_list.LineIndex(qty-1000);
		m_list.SetSel(0,qty,TRUE);
		m_list.Clear();
		qty = m_list.GetWindowTextLength();
		m_list.SetReadOnly(TRUE);
		m_list.SetSel(qty,qty,FALSE);
	}
}

int CWinLPTDlg::HandSharking(void)
{
	BYTE data;
	int step=0;
	
	read_io_byte(STATUS_PORT, &data);
	if((data & 0xF8) == 0xf8)
	{//對方在等待
		//puts("Connecting...(Press ESC to quit)");
		
		while(1)
		{
			if(m_send.GetCheck()==BST_UNCHECKED)
			{
				return 1;
			}
			switch(step)
			{
				case 0:
					write_io_byte(DATA_PORT,0x0f);
					step = 1;
					break;
				case 1:
					read_io_byte(STATUS_PORT,&data);
					if((data & 0xF8) == 0x50)
					{
						write_io_byte(DATA_PORT,0x1A);
						WriteState("已連上線");
						return 0;
					}
					break;
			}
		}
		
	}
	else
	{//我等待
		write_io_byte(DATA_PORT,0x0f);
		//puts("Waiting for connect...(Press ESC to quit)");
		while(1)
		{
			if(m_send.GetCheck()==BST_UNCHECKED)
			{
				return 1;
			}
			read_io_byte(STATUS_PORT,&data);
			switch(step)
			{
				case 0:
					if((data & 0xF8) == 0xf8)
					{//對方有回應
						write_io_byte(DATA_PORT,0x1A);
						step = 1;
					}
					break;
				case 1:
					if((data & 0xF8) == 0x50)
					{//對方有回應
						WriteState("已連上線");
						return 0;
					}
					break;
			}
		}
	}
	return 0;
}

DWORD __stdcall MLTProc(void *p)
{//拉咧 的主程式
	CWinLPTDlg *hd=(CWinLPTDlg *)p;
	int ch,rec_cnt=0;
	char data;
	char rec_buf[1024],send_buf[1024],name[50],chars[1024];
	
	while(1)
	{
		//先等使用者點選此功能
		while(1)
		{
			Sleep(100);
			if(hd->m_send.GetCheck()==BST_CHECKED)
			{
				Sleep(100);
				break;
			}
		}
		
		//交握
		if(hd->HandSharking() != 0)
		{//取消
			write_io_byte(DATA_PORT,0x0);
		}
		else
		{//已連上線
			while(1)
			{//先收垃圾
				if(RecvByte(&data)==1)
				{
					break;
				}
				delay1ms(1);
			}
			while(1)
			{
				if(hd->m_send.GetCheck()==BST_UNCHECKED)
				{
					write_io_byte(DATA_PORT,0x0);
					break;
				}
				
				if(hd->send_flag != 0)
				{//送出字
					//ZeroMemory(send_buf,sizeof(send_buf));
					hd->m_name.GetWindowText(name,sizeof(name));
					hd->m_send_data.GetWindowText(chars,sizeof(chars));
  				sprintf(send_buf,"%s: %s",name,chars);
  				hd->WriteState(send_buf);
  				SendString(send_buf);//送出
  				//memset(tmp_buf,0,sizeof(tmp_buf));
					hd->send_flag = 0;
					hd->m_send_data.SetWindowText("");
					hd->m_send_data.SetFocus();
				}
				
				//做收的檢查
				ch = RecvByte(&data);
				if(ch==0)
				{
					rec_buf[rec_cnt] = (char)data;
					rec_cnt++;
				}
				else if(ch == 1)
				{
					if(rec_cnt != 0)
					{
						hd->WriteState(rec_buf);
						ZeroMemory(rec_buf,sizeof(rec_buf));
						rec_cnt = 0;
					}
				}
			}
		}
	}
	
	return 0;
}

int SendString(char *data)
{
	int status=0;
  
  while (*data != '\0')
  {
    status = SendByte(*data);
    if(status != 0)
    {
    	break;
    }
    data++;
  }
  return status;
}


int SendByte(char data)
{
	/*
	1. 先將high byte送出(busy:0->1)
	2. 等對方的busy:0->1
	3. 把busy:1->0
	4. 等對方的busy:1->0
	5. 送low byte(busy:0->1)
	6. 重覆2-4
	*/
	int i,cnt;
	BYTE dd;
	
	
	for(i = 0; i < 2; i++)
	{
		cnt = 0;
tx_again:
		dd = (BYTE)data;
		if(i==0)
		{
			dd >>= 4;
		}
		else
		{
			dd &= 0xf;
		}
		write_io_byte(DATA_PORT,dd);
//		delay1ms();
		read_io_byte(STATUS_PORT,&dd);
		if((dd & 0x80)==0) //對方未ready
		{
			cnt++;
			if(cnt < 50000)
			{
				goto tx_again;
			}
			return 1;
		}
		
		write_io_byte(DATA_PORT,0x10); //把busy拉low
		cnt = 0;
tx2_again:
		//delay1ms();
		read_io_byte(STATUS_PORT,&dd);
		if((dd & 0x80)==0x80) //對方未ready
		{
			cnt++;
			if(cnt < 500)
			{
				goto tx2_again;
			}
			return 1;
		}
		
	}
	
	return 0;

}

int RecvByte(char *data)
{
	/*
  1. 先檢查是否busy:0->1，沒有則離開
	2. 收high byte (busy:0->1)
	3. 設busy:0->1
	3. 等對方busy:1->0
	4. 設定busy:1->0
	5. 等待對方busy:0->1
	6. 收low byte (busy:0->1)
	7. 等對方busy:1->0
	8. 設定busy:1->0
	*/
	BYTE value;
	BYTE dd;
	int cnt,cc;
	
	cnt = 0;
	value=0;
	while(1)
	{
		cc = 0;
rx_again:
		read_io_byte(STATUS_PORT,&dd);
		if((dd & 0x80)==0)
		{//沒有東西
			cc++;
			
				*data = value;
			if(cnt != 0)
			{
				if(cc < 5000)
				{
					goto rx_again;
				}
				return -2;
			}
			else
			{
				if(cc < 500)
				{
					goto rx_again;
				}
				return 1;
			}
		}
		
		dd &= 0x78;
		if(cnt==0)
		{//high byte
			dd <<= 1;
		}
		else
		{//low byte
			dd >>= 3;
		}
		value |= dd;
		cnt++;
		
		cc = 0;
		write_io_byte(DATA_PORT,0x0); //把busy拉high
rx2_again:
		read_io_byte(STATUS_PORT,&dd);
		if((dd & 0x80) == 0x80)
		{
			cc++;
			if(cc < 500)
			{
				goto rx2_again;
			}
				*data = value;
			return -1;
		}
		
		write_io_byte(DATA_PORT,0x10); //把busy拉low
		
		if(cnt == 2)
		{
			break;
		}
		delay1ms(1);
	}
	*data = value;
	return 0;
}

void delay1ms(DWORD delay)
{
	LARGE_INTEGER start,end,Freq;
 
	QueryPerformanceFrequency(&Freq);                      
	end.QuadPart = (delay*Freq.QuadPart)/1000;        //1ms
	//end.QuadPart = (delay*Freq.QuadPart)/1000000;        //1us
	QueryPerformanceCounter(&start);
	end.QuadPart = end.QuadPart+start.QuadPart;/*-System_test()*2;*/
	do
	{
		QueryPerformanceCounter(&Freq);
	}while (Freq.QuadPart<=end.QuadPart);
}

void CWinLPTDlg::OnDb1Radio() 
{
	// TODO: Add your control notification handler code here
	if((ctrl_data_byte & 0x1) == 0x1)
	{
		m_db1.SetCheck(BST_UNCHECKED);
		ctrl_data_byte &= 0xfe;
	}
	else
	{
		m_db1.SetCheck(BST_CHECKED);
		ctrl_data_byte |= 0x01;
	}
}

void CWinLPTDlg::OnDb2Radio() 
{
	// TODO: Add your control notification handler code here
	if((ctrl_data_byte & 0x2) == 0x2)
	{
		m_db2.SetCheck(BST_UNCHECKED);
		ctrl_data_byte &= 0xfd;
	}
	else
	{
		m_db2.SetCheck(BST_CHECKED);
		ctrl_data_byte |= 0x02;
	}
}

void CWinLPTDlg::OnDb3Radio() 
{
	// TODO: Add your control notification handler code here
	if((ctrl_data_byte & 0x4) == 0x4)
	{
		m_db3.SetCheck(BST_UNCHECKED);
		ctrl_data_byte &= 0xfb;
	}
	else
	{
		m_db3.SetCheck(BST_CHECKED);
		ctrl_data_byte |= 0x04;
	}
}

void CWinLPTDlg::OnDb4Radio() 
{
	// TODO: Add your control notification handler code here
	if((ctrl_data_byte & 0x8) == 0x8)
	{
		m_db4.SetCheck(BST_UNCHECKED);
		ctrl_data_byte &= 0xf7;
	}
	else
	{
		m_db4.SetCheck(BST_CHECKED);
		ctrl_data_byte |= 0x08;
	}
}

void CWinLPTDlg::OnDb5Radio() 
{
	// TODO: Add your control notification handler code here
	if((ctrl_data_byte & 0x10)==0x10)
	{
		m_db5.SetCheck(BST_UNCHECKED);
		ctrl_data_byte &= 0xEF;
	}
	else
	{
		m_db5.SetCheck(BST_CHECKED);
		ctrl_data_byte |= 0x10;
	}
}

void CWinLPTDlg::OnDb6Radio() 
{
	// TODO: Add your control notification handler code here
	if((ctrl_data_byte & 0x20) == 0x20)
	{
		m_db6.SetCheck(BST_UNCHECKED);
		ctrl_data_byte &= 0xdF;
	}
	else
	{
		m_db6.SetCheck(BST_CHECKED);
		ctrl_data_byte |= 0x20;
	}
}

void CWinLPTDlg::OnDb7Radio() 
{
	// TODO: Add your control notification handler code here
	if((ctrl_data_byte & 0x40) == 0x40)
	{
		m_db7.SetCheck(BST_UNCHECKED);
		ctrl_data_byte &= 0xbF;
	}
	else
	{
		m_db7.SetCheck(BST_CHECKED);
		ctrl_data_byte |= 0x40;
	}
}

void CWinLPTDlg::OnDb8Radio() 
{
	// TODO: Add your control notification handler code here
	if((ctrl_data_byte & 0x80) == 0x80)
	{
		m_db8.SetCheck(BST_UNCHECKED);
		ctrl_data_byte &= 0x7F;
	}
	else
	{
		m_db8.SetCheck(BST_CHECKED);
		ctrl_data_byte |= 0x80;
	}
}
