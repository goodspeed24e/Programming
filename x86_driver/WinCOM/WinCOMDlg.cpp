// WinCOMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinCOM.h"
#include "WinCOMDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void Delay_1us(DWORD delay);

//char com_no_list[10][7];

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
// CWinCOMDlg dialog

CWinCOMDlg::CWinCOMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinCOMDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinCOMDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinCOMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinCOMDlg)
	DDX_Control(pDX, IDC_SOURCE_COMBO, m_source);
	DDX_Control(pDX, IDOK, m_send_bt);
	DDX_Control(pDX, IDC_TARGET_COMBO, m_target);
	DDX_Control(pDX, IDC_STOP_COMBO, m_stop);
	DDX_Control(pDX, IDC_SEND_EDIT, m_send);
	DDX_Control(pDX, IDC_RECV_EDIT, m_recv);
	DDX_Control(pDX, IDC_RECV_CLR_BUTTON, m_recv_clr);
	DDX_Control(pDX, IDC_QTY_COMBO, m_qty);
	DDX_Control(pDX, IDC_PARITY_COMBO, m_parity);
	DDX_Control(pDX, IDC_ON_OFF_BUTTON, m_on_off);
	DDX_Control(pDX, IDC_FUNC3_RADIO, m_func3);
	DDX_Control(pDX, IDC_FUNC2_RADIO, m_func2);
	DDX_Control(pDX, IDC_FUNC1_RADIO, m_func1);
	DDX_Control(pDX, IDC_BAUDRATE_COMBO, m_baudrate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinCOMDlg, CDialog)
	//{{AFX_MSG_MAP(CWinCOMDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FUNC1_RADIO, OnFunc1Radio)
	ON_BN_CLICKED(IDC_FUNC2_RADIO, OnFunc2Radio)
	ON_BN_CLICKED(IDC_FUNC3_RADIO, OnFunc3Radio)
	ON_BN_CLICKED(IDC_ON_OFF_BUTTON, OnOnOffButton)
	ON_BN_CLICKED(IDC_RECV_CLR_BUTTON, OnRecvClrButton)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_SOURCE_COMBO, OnSelchangeSourceCombo)
	ON_CBN_SELCHANGE(IDC_TARGET_COMBO, OnSelchangeTargetCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinCOMDlg message handlers

BOOL CWinCOMDlg::OnInitDialog()
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
	int i,posi=0;
	char buf[1024];
	HANDLE hCom;

	func = 0;
	//ZeroMemory(com_no_list,sizeof(com_no_list));
	//檢查有幾個COM port
	i = 0;
	com_qty = 0;
	while(1)
	{
		sprintf(buf,"COM%d",i+1);
		
		hCom = CreateFile( buf,GENERIC_READ | GENERIC_WRITE,
		0, // must be opened with exclusive-access
		NULL, // no security attributes
		OPEN_EXISTING, // must use OPEN_EXISTING
		0, // not overlapped I/O
		NULL // htemplate must be NULL for comm devices
		);

		if (hCom == INVALID_HANDLE_VALUE) 
		{
			com_qty = i;
			break;
		}
		CloseHandle(hCom);
		m_source.AddString(buf);
		m_target.AddString(buf);
		i++;
	}
	
	if(com_qty == 0)
	{
		m_source.AddString("沒有COM port");
		m_target.AddString("沒有COM port");
		m_source.SetCurSel(0);
		m_target.SetCurSel(0);
		OffAll();
	}
	else
	{
		m_source.SetCurSel(0);
		m_target.SetCurSel(0);
		OnSelchangeSourceCombo();
	}
	
	m_baudrate.SetCurSel(MY_CBR_9600);
	m_qty.SetCurSel(3);
	m_parity.SetCurSel(MY_NOPARITY);
	m_stop.SetCurSel(MY_ONESTOPBIT);
	m_func1.SetCheck(MF_CHECKED);
	m_send.EnableWindow(FALSE);
	m_send_bt.EnableWindow(FALSE);
	on_off = 0;
	hCom1 = NULL;
	hCom2 = NULL;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinCOMDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	/*if(!m_target.GetCount())
	{
		int i;
		char buf[10];
	
		if(!com_qty)
		{
			m_target.AddString("沒有COM port");
			m_target.EnableWindow(FALSE);
			m_func1.EnableWindow(FALSE);
			m_func2.EnableWindow(FALSE);
			m_func3.EnableWindow(FALSE);
			m_on_off.EnableWindow(FALSE);
		}
		else if(com_qty == 1)
		{
			m_target.AddString("沒有其它COM port");
			m_target.EnableWindow(FALSE);
		}
		else
		{
			for(i = 0; i < com_qty; i++)
			{
				if(i != id)
				{
					sprintf(buf,"COM%d",i+1);
					m_target.AddString(buf);
				}
			}
			m_target.EnableWindow(TRUE);
		}
		m_target.SetCurSel(0);
	}*/
}

void CWinCOMDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWinCOMDlg::OnPaint() 
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
HCURSOR CWinCOMDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CWinCOMDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(hCom1 != NULL)
	{
		CloseHandle(hCom1);
	}
	if(hCom2 != NULL)
	{
		CloseHandle(hCom2);
	}
	return CDialog::DestroyWindow();
}

void CWinCOMDlg::OnFunc1Radio() 
{
	// TODO: Add your control notification handler code here
	func = 0;
	Item_ON_OFF();
}

void CWinCOMDlg::OnFunc2Radio() 
{
	// TODO: Add your control notification handler code here
	func = 1;
	Item_ON_OFF();
}

void CWinCOMDlg::OnFunc3Radio() 
{
	// TODO: Add your control notification handler code here
	func = 2;
	Item_ON_OFF();
}

void CWinCOMDlg::OnOK() 
{
	// TODO: Add extra validation here
	char buf[1024];
	char *p;
	UINT dwBytesToWrite=1;
	DWORD dwBytesWritten=0;
	OVERLAPPED osRead = {0};
	
	if(m_send.GetWindowText(buf,sizeof(buf)) != 0)
	{
		strcat(buf,"\r\0");
		p = buf;
		while(*p != '\0')
		{
			if(WriteFile(hCom1, p, dwBytesToWrite,&dwBytesWritten, &osRead )==0) //傳送失敗
			{
				if(GetLastError() == ERROR_IO_PENDING)
				{
					Delay_1us(2000);
					int tmp=GetOverlappedResult(hCom1, &osRead,&dwBytesWritten, TRUE );
					
					if (!tmp)
					{
						tmp = GetLastError();
					}
					else
					{
						p++;
					}
					while(!tmp) 
					{
						if(GetLastError() == ERROR_IO_INCOMPLETE)
						{
							// normal result if not finished
							goto send_next; 
						}
					}	
				}
				else
				{
					goto send_next;
				}
			}
			else
			{
send_next:
				Delay_1us(1000);
				p++;
			}
		}
		
		put_string(buf,0);
		m_send.SetSel(0,-1);
		m_send.Clear();
	}
	//CDialog::OnOK();
}

void CWinCOMDlg::OffAll(void)
{
	m_func1.EnableWindow(FALSE);
	m_func2.EnableWindow(FALSE);
	m_func3.EnableWindow(FALSE);
	m_source.EnableWindow(FALSE);
	m_target.EnableWindow(FALSE);
	m_baudrate.EnableWindow(FALSE);
	m_on_off.EnableWindow(FALSE);
	m_parity.EnableWindow(FALSE);
	m_qty.EnableWindow(FALSE);
	m_recv_clr.EnableWindow(FALSE);
	m_stop.EnableWindow(FALSE);
}

void CWinCOMDlg::OnOnOffButton() 
{
	// TODO: Add your control notification handler code here
	if(on_off==0) //準備連線
	{
		char buf[100];
		
		
		if(func==0)
		{//如果是單機自傳，也要設定另一個port
			if(m_target.GetCount() >= 2)
			{
				m_target.GetWindowText(buf,sizeof(buf));
				//	AfxMessageBox(buf);
				Init_COM(&hCom2,buf);
			}
			else
			{
				strcpy(buf,"您只有一個COM port，無法使用\'資料對傳(1台電腦2個埠)\'功能");
				MessageBox(buf,"錯誤",MB_OK | MB_ICONSTOP);
				return;
			}
		}
		
		m_on_off.SetWindowText("斷線");
		on_off = 1;
		
		//id = m_source.GetCurSel();
		
		//sprintf(buf,"COM%d",id+1);
		m_source.GetWindowText(buf,sizeof(buf));
		//	AfxMessageBox(buf);
		Init_COM(&hCom1,buf);
		
		m_send.EnableWindow(TRUE);
		m_send_bt.EnableWindow(TRUE);
		m_send.SetFocus();
		
		m_func1.EnableWindow(FALSE);
		m_func2.EnableWindow(FALSE);
		m_func3.EnableWindow(FALSE);
		m_source.EnableWindow(FALSE);
		m_target.EnableWindow(FALSE);
		m_baudrate.EnableWindow(FALSE);
		m_parity.EnableWindow(FALSE);
		m_qty.EnableWindow(FALSE);
		m_stop.EnableWindow(FALSE);
		
		m_hThread = CreateThread(NULL, 30000, ChildThread, (void*) this, CREATE_SUSPENDED, &m_thisThreadID);
		if (m_hThread == NULL)
		{
			MessageBox("Error trying to create ChildThread receiver thread","Error",MB_OK | MB_ICONERROR);
			return;
		}
		ResumeThread(m_hThread);
	}
	else
	{
		m_on_off.SetWindowText("連線");
		on_off = 0;
		SuspendThread(m_hThread);
		CloseHandle(hCom1);
		if(func==0)
		{
			CloseHandle(hCom2);
		}
		hCom1 = NULL;
		hCom2 = NULL;
		m_send.EnableWindow(FALSE);
		m_send_bt.EnableWindow(FALSE);
		
		m_func1.EnableWindow(TRUE);
		m_func2.EnableWindow(TRUE);
		m_func3.EnableWindow(TRUE);
		m_source.EnableWindow(TRUE);
		m_target.EnableWindow(TRUE);
		m_baudrate.EnableWindow(TRUE);
		m_parity.EnableWindow(TRUE);
		m_qty.EnableWindow(TRUE);
		m_stop.EnableWindow(TRUE);
	}
}

void CWinCOMDlg::OnRecvClrButton() 
{
	// TODO: Add your control notification handler code here
	m_recv.SetReadOnly(FALSE);
	m_recv.SetSel(0,-1);
	m_recv.Clear();
	m_recv.SetReadOnly(TRUE);
	m_send.SetFocus();
}

void CWinCOMDlg::put_string(char *buf,int dir)
{
	int qty;
	
	qty = strlen(buf)-1;
	if(buf[qty] == '\r')
	{
		strcat(buf,"\n\0");
	}
	
	qty = m_recv.GetWindowTextLength();
	m_recv.SetSel(qty,qty,FALSE);
	if(dir==0) //傳送者
	{
		m_recv.ReplaceSel("Sender: ",FALSE);
	}
	else //收到的
	{
		m_recv.ReplaceSel("Reciver: ",FALSE);
	}
	m_recv.ReplaceSel(buf,FALSE);
		
	qty = m_recv.GetLineCount();
		
	if(qty > 500)
	{
		m_recv.SetReadOnly(FALSE);
		qty = m_recv.LineIndex(qty-500);
		m_recv.SetSel(0,qty,TRUE);
		m_recv.Clear();
		qty = m_recv.GetWindowTextLength();
		m_recv.SetReadOnly(TRUE);
		m_recv.SetSel(qty,qty,FALSE);
	}
}

void CWinCOMDlg::Item_ON_OFF(void)
{
	m_func1.SetCheck(BST_UNCHECKED);
	m_func2.SetCheck(BST_UNCHECKED);
	m_func3.SetCheck(BST_UNCHECKED);
	switch(func)
	{
		case 0:
			m_func1.SetCheck(BST_CHECKED);
			break;
		case 1:
			m_func2.SetCheck(BST_CHECKED);
			break;
		case 2:
			m_func3.SetCheck(BST_CHECKED);
	}
	m_target.EnableWindow(!func);
}

BOOL CWinCOMDlg::Init_COM(HANDLE *hd,char *com_no)
{
	//設定COM port
	DCB dcb;
	BOOL fSuccess;
	COMMTIMEOUTS CommTimeouts;
	int sld;
	DWORD dwEvtMask=0;
	OVERLAPPED osRead = {0};

//	sprintf(com_no,"COM%d",port_no+1);
	*hd = CreateFile( com_no,
	GENERIC_READ | GENERIC_WRITE,
	0, // must be opened with exclusive-access
	NULL, // no security attributes
	OPEN_EXISTING, // must use OPEN_EXISTING
	FILE_FLAG_OVERLAPPED, // overlapped I/O
	NULL // htemplate must be NULL for comm devices
	);

	if (*hd == INVALID_HANDLE_VALUE) 
	{
		// Handle the error.
		MessageBox("OPEN COM port failed","Error",MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	SetCommMask(*hd, EV_RXCHAR | EV_TXEMPTY);
	// EV_RXCHAR: A character was received and placed in the input buffer. 
	// EV_TXEMPTY: The last character in the output buffer was sent. 
	SetupComm(*hd,0x100000,0x1000) ; // setup buffer area size of input and output
	PurgeComm(*hd, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR ); 
	// PURGE_TXABORT Terminates all outstanding overlapped write operations and returns
	// immediately, even if the write operations have not been completed. 
	//
	// PURGE_RXABORT Terminates all outstanding overlapped read operations and returns 
	// immediately, even if the read operations have not been completed. 
	//
	// PURGE_TXCLEAR Clears the output buffer (if the device driver has one). 
	//
	// PURGE_RXCLEAR Clears the input buffer (if the device driver has one). 
	// clear buffer area size of input and output

// ============= Change the COMMTIMEOUTS structure settings. ================= //

	// Retrieve the time-out parameters for all read and write operations on the port. 
	GetCommTimeouts (*hd, &CommTimeouts);

	//  單位都是ms
	CommTimeouts.ReadIntervalTimeout = 100;            //  接收時每個byte跟byte的間隔時間
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;    // 總時間乘數，接收N個byte，TIMEOUT時間為0的N次方
	CommTimeouts.ReadTotalTimeoutConstant = 100;  // 總時間倍數，接收N個byte，TIMEOUT時間為N*100
	CommTimeouts.WriteTotalTimeoutMultiplier = 0;    //總時間乘數，傳送N個byte，TIMEOUT時間為0的N次方
	CommTimeouts.WriteTotalTimeoutConstant = 100;  //總時間倍數，傳送N個byte，TIMEOUT時間為N*100
	//PortDCB.fRtsControl= RTS_CONTROL_TOGGLE;  // RTS flow control 

	// Set the time-out parameters for all read and write operations
	// on the port. 
	if (!SetCommTimeouts (*hd, &CommTimeouts))
	{
		// Could not create the read thread.
		MessageBox ("Unable to set the time-out parameters","Error", MB_OK | MB_ICONSTOP);
		//dwError = GetLastError ();
		return FALSE;
	}

	// Build on the current configuration, and skip setting the size
	// of the input and output buffers with SetupComm.

	fSuccess = GetCommState(*hd, &dcb);

	if (!fSuccess) 
	{
		// Handle the error.
		MessageBox("GetCommState failed","Error",MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	// Fill in DCB: 57,600 bps, 8 data bits, no parity, and 1 stop bit.

	sld = m_baudrate.GetCurSel();
	switch(sld)
	{
		case MY_CBR_110:
			dcb.BaudRate = CBR_110; // set the baud rate
			break;
		case MY_CBR_300:
			dcb.BaudRate = CBR_300; // set the baud rate
			break;
		case MY_CBR_1200:
			dcb.BaudRate = CBR_1200; // set the baud rate
			break;
		case MY_CBR_2400:
			dcb.BaudRate = CBR_2400; // set the baud rate
			break;
		case MY_CBR_4800:
			dcb.BaudRate = CBR_4800; // set the baud rate
			break;
		case MY_CBR_9600:
			dcb.BaudRate = CBR_9600; // set the baud rate
			break;
		case MY_CBR_14400:
			dcb.BaudRate = CBR_14400; // set the baud rate
			break;
		case MY_CBR_19200:
			dcb.BaudRate = CBR_19200; // set the baud rate
			break;
		case MY_CBR_38400:
			dcb.BaudRate = CBR_38400; // set the baud rate
			break;
		case MY_CBR_57600:
			dcb.BaudRate = CBR_57600; // set the baud rate
			break;
		case MY_CBR_115200:
			dcb.BaudRate = CBR_115200; // set the baud rate
			break;
	}
	
	sld = m_qty.GetCurSel();
	switch(sld)
	{
		case 0:
			dcb.ByteSize = 5; // data size, xmit, and rcv
			break;
		case 1:
			dcb.ByteSize = 6; // data size, xmit, and rcv
			break;
		case 2:
			dcb.ByteSize = 7; // data size, xmit, and rcv
			break;
		case 3:
			dcb.ByteSize = 8; // data size, xmit, and rcv
			break;
	}
	
	sld = m_parity.GetCurSel();
	switch(sld)
	{
		case MY_EVENPARITY:
			dcb.Parity = EVENPARITY; // 偶同位
			break;
		case MY_ODDPARITY:
			dcb.Parity = ODDPARITY; // 奇同位
			break;
		case MY_NOPARITY:
			dcb.Parity = NOPARITY; // no parity bit
			break;
		case MY_MARKPARITY:
			dcb.Parity = MARKPARITY; // 標記
			break; 
		case MY_SPACEPARITY:
			dcb.Parity = SPACEPARITY; // 空白
			break;
	}
	
	sld = m_stop.GetCurSel();
	switch(sld)
	{
		case MY_ONESTOPBIT: 
			dcb.StopBits = ONESTOPBIT; // one stop bit
			break;
		case MY_ONE5STOPBITS:
			dcb.StopBits = ONE5STOPBITS; // one.five stop bit
			break;
		case MY_TWOSTOPBITS:
			dcb.StopBits = TWOSTOPBITS; // two stop bit
			break;
	}
	
	//dcb.fRtsControl= RTS_CONTROL_TOGGLE;  // RTS flow control 
	//dcb.fDtrControl = DTR_CONTROL_ENABLE;
	//dcb.fRtsControl = RTS_CONTROL_ENABLE;
//	dcb.fOutxDsrFlow = TRUE;
	//dcb.fOutxDsrFlow = FALSE;
	fSuccess = SetCommState(*hd, &dcb);
	if (!fSuccess) 
	{
		// Handle the error.
		printf ("SetCommState failed","Error",MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	
	SetCommMask( *hd, EV_RXCHAR|EV_TXEMPTY ); //有哪些埠事件需要監視？
	WaitCommEvent( *hd, &dwEvtMask, &osRead );
		
	return TRUE;
}

DWORD __stdcall ChildThread(void *p)
{
	CWinCOMDlg *hd=(CWinCOMDlg *)p;
	//DWORD dwEvtMask=0;
	unsigned long dwErrorFlags = 0;
	COMSTAT ComStat;
	DWORD dwLength;
	HANDLE hPort; //要讀取的port
	OVERLAPPED osRead = {0};
	BOOL fReadStat;
	char lpBuffer[1024];
	DWORD dwBytesRead=0;
	int cnt;
	BOOL modify_falg;
	
	if(hd->func==0) //自己對傳
	{
		hPort = hd->hCom2;
	}
	else
	{
		hPort = hd->hCom1;
	}
	
	cnt = 0;
	modify_falg = FALSE;
	while(1)
	{
		ClearCommError(hPort, &dwErrorFlags, &ComStat );
		dwLength = ComStat.cbInQue;//輸入緩衝區有多少數據？
		if(dwLength > 0)
		{
			fReadStat = ReadFile( hPort, &(lpBuffer[cnt]), 1, &dwBytesRead,&osRead);
			cnt++;
			lpBuffer[cnt]='\0';
			modify_falg = TRUE;
		}
		else
		{
			if(modify_falg != 0)
			{
				//strcat(lpBuffer,"\n\0");
				hd->put_string(lpBuffer,1);
				cnt = 0;
				modify_falg = FALSE;
			}
		}
		Delay_1us(1);
	}
	return 0;
}

void Delay_1us(DWORD delay)
{
	LARGE_INTEGER start,end,Freq;
 
	QueryPerformanceFrequency(&Freq);                      
	//end.QuadPart = (delay*Freq.QuadPart)/10000;        //0.1ms
	end.QuadPart = (delay*Freq.QuadPart)/1000000;        //1us
	QueryPerformanceCounter(&start);
	end.QuadPart = end.QuadPart+start.QuadPart;/*-System_test()*2;*/
	do
	{
		QueryPerformanceCounter(&Freq);
	}while (Freq.QuadPart<=end.QuadPart);
}



void CWinCOMDlg::OnSelchangeSourceCombo() 
{
	// TODO: Add your control notification handler code here
	int sld,tld;
	
	if(com_qty==1)
	{
		//m_source.AddString("沒有COM port");
		//m_source.EnableWindow(FALSE);
		m_target.AddString("沒有COM port");
		m_target.EnableWindow(FALSE);
	}
	else
	{
		sld = m_source.GetCurSel();
		tld = m_target.GetCurSel();
		
		if(sld == tld)
		{
			if(tld == (com_qty-1))
			{
				tld--;
			}
			else
			{
				tld++;
			}
			m_target.SetCurSel(tld);
		}
	}
	//m_target.SetCurSel(0);
}

void CWinCOMDlg::OnSelchangeTargetCombo() 
{
	// TODO: Add your control notification handler code here
	int sld,tld;
	
	if(com_qty==1)
	{
		m_source.AddString("沒有COM port");
		m_source.EnableWindow(FALSE);
		//m_target.AddString("沒有COM port");
		//m_target.EnableWindow(FALSE);
	}
	else
	{
		sld = m_target.GetCurSel();
		tld = m_source.GetCurSel();
		
		if(sld == tld)
		{
			if(tld == (com_qty-1))
			{
				tld--;
			}
			else
			{
				tld++;
			}
			m_source.SetCurSel(tld);
		}
	}
}
