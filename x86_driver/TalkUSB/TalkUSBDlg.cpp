// TalkUSBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TalkUSB.h"
#include "TalkUSBDlg.h"
#include "Dbt.h"
#include "nic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//字元與語音位址表
unsigned char AddrTb[]=
{
	0, //0
	5, //1
	10,//2
	15,//3
	20,//4
	25,//5
	30,//6
	35,//7
	40,//8
	45,//9
	50,//A
	55,//B
	60,//C
	65,//D
	70,//E
	75,//F
	80,//G
	85,//H
	90,//I
	95,//J
	100,//K
	105,//L
	110,//M
	115,//N
	120,//O
	125,//P
	130,//Q
	135,//R
	140,//S
	145,//T
	150,//U
	155,//V
	160,//W
	165,//X
	170,//Y
	175//Z
};

//-----------------------------------------------------------------------------
// Report IDs
//-----------------------------------------------------------------------------
#define OUT_Talk_Enable   0x01
#define IN_Talk_Stats   0x02
	
#define HID_Talker_VID 0x10C4
#define HID_Talker_PID 0x82CD

unsigned char recvBuf[256];
BYTE ip[4];
int RecvData(void);
void Check_Stats (unsigned char* Stat1);

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
// CTalkUSBDlg dialog

CTalkUSBDlg::CTalkUSBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTalkUSBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTalkUSBDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTalkUSBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTalkUSBDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTalkUSBDlg, CDialog)
	//{{AFX_MSG_MAP(CTalkUSBDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DEVICECHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTalkUSBDlg message handlers

BOOL CTalkUSBDlg::OnInitDialog()
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
	
	char buf[100];
	
	RegisterNotification();
	
	//取得自己IP
	GetHostIP(NULL,ip[0],ip[1],ip[2],ip[3]);
	sprintf(buf,"Not connected - %d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
	GetDlgItem(IDC_NET_STATIC)->SetWindowText(buf);
	
	if (HID_Talker.GetConnectedDeviceNum(HID_Talker_VID, HID_Talker_PID))
	{
		GetDlgItem(IDC_USB_STATIC)->SetWindowText("USB Connected");
		USBConnect();
	}
	else
	{
		GetDlgItem(IDC_USB_STATIC)->SetWindowText("USB Disconnected");
		
	}
	
	//NIC接收與傳送USB主程式
	m_hThread = CreateThread(NULL, 30000, MLTProc, (void*) this, CREATE_SUSPENDED, &m_thisThreadID);
	
	ResumeThread(m_hThread);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTalkUSBDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTalkUSBDlg::OnPaint() 
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
HCURSOR CTalkUSBDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTalkUSBDlg::RegisterNotification()
{
	// Register device notification
	DEV_BROADCAST_DEVICEINTERFACE devIF = {0};
	GUID		hidGuid;

	HidD_GetHidGuid(&hidGuid);

	devIF.dbcc_size = sizeof(devIF);
	devIF.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	devIF.dbcc_classguid  = hidGuid;

	m_hNotifyDevNode = RegisterDeviceNotification(GetSafeHwnd(),&devIF, DEVICE_NOTIFY_WINDOW_HANDLE);
}

void CTalkUSBDlg::UnregisterNotification()
{
	// Unegister device notification
	if(m_hNotifyDevNode != NULL)
	{
		UnregisterDeviceNotification(m_hNotifyDevNode);
		m_hNotifyDevNode = INVALID_HANDLE_VALUE;
	}
}

BOOL CTalkUSBDlg::OnDeviceChange(UINT nEventType, DWORD dwData)
{
	switch(nEventType)
	{
		// A device has been inserted and is now available.
		case DBT_DEVICEARRIVAL:
			// Check to see if newly connected device has VID and PID
			// matching HID_Talker's VID and PID
			if (HID_Talker.GetConnectedDeviceNum(HID_Talker_VID,HID_Talker_PID))
			{
				// Update Device Status text
				GetDlgItem(IDC_USB_STATIC)->SetWindowText("USB Connected");
				
				USBConnect();
			}
			break;

		// A device has been removed from USB.
		case DBT_DEVICEREMOVECOMPLETE:

			// Check that the HID_Talker device was the removed device
			if (!HID_Talker.GetConnectedDeviceNum(HID_Talker_VID,HID_Talker_PID))
			{
				GetDlgItem(IDC_USB_STATIC)->SetWindowText("USB Disconnected");
				
				USBDisconnect();
			}
			break;
	}

	return TRUE;
}

void CTalkUSBDlg::USBConnect()
{
	DWORD results;

	// Check to see if any HID Talker devices are attached to USB
	results = HID_Talker.GetConnectedDeviceNum(HID_Talker_VID, HID_Talker_PID);
	// Number of attached devices with matching PID and VID is stored
	// in results
	if (results != 0)
	{
		// Attempt to connect to attached device
		results = HID_Talker.Open(results - 1, HID_Talker_VID, HID_Talker_PID);

		// If successfully attached, initialize system for operation
		if (results == HID_DEVICE_SUCCESS)
		{
			// Set Get Report and Set Report time-out values to 100 ms
			HID_Talker.SetTimeouts (100,100);
		}
	}

}

void CTalkUSBDlg::USBDisconnect()
{
	if (HID_Talker.IsOpened())
	{
		HID_Talker.Close();
	}
}

void CTalkUSBDlg::SendOneChar(unsigned char ch)
{
	unsigned char OutputEnableBuffer[2];
	
	OutputEnableBuffer [0] = OUT_Talk_Enable;
	OutputEnableBuffer [1] = ch; //要發音的位址
	HID_Talker.SetReport_Control (OutputEnableBuffer, 2);
}

void CTalkUSBDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	NicClose();
	Terminate();
	USBDisconnect();
	UnregisterNotification();             // Close notification handle
	OnCancel();
	//CDialog::OnCancel();
}

DWORD __stdcall MLTProc(void *p)
{//	
	CTalkUSBDlg *hd=(CTalkUSBDlg *)p;
	char tmp[50],buf[100];
	unsigned char state;
	int i,cnt;
	
	if(NicListen(5678,SOCK_STREAM)==0)
			return 0;
	while(1) //永遠執行
	{
		SOCKET socket;
			
		if (Accept(socket)==0)
			continue;
		BkSocket(); //先備份Socket
		SetSocket(socket);

		if(WaitInputData(5) == FALSE)
		{// 5秒內沒有回應就結束
			NicClose();
			RsSocket(); //還原socket
			continue;
		}

		RecvData();
		
		sprintf(tmp,"Connected by %d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
		hd->GetDlgItem(IDC_NET_STATIC)->SetWindowText(tmp);
		
		strcpy(tmp,(char *)recvBuf);
		hd->GetDlgItem(IDC_STATE_STATIC)->SetWindowText(tmp);
		
		NicClose();
		RsSocket(); //還原socket
 		
 		strupr(tmp); //全部轉大寫
 		cnt = strlen(tmp);
 		//送出資料
 		for(i = 0; i < cnt; i++)
 		{
 			if(tmp[i] >= '0' && tmp[i] <= '9')
 			{
 				state = AddrTb[tmp[i]-0x30];
 			}
 			else if(tmp[i] >= 'A' && tmp[i] <= 'Z')
 			{
 				state = AddrTb[tmp[i]-0x37];
 			}
 			else
 			{
 				continue;
 			}
 			hd->SendOneChar(state);
 			
 			while(1)
 			{
 				hd->Check_Stats(&state);
				if(state == 1)
				{
					//hd->GetDlgItem(IDC_STATE_STATIC)->SetWindowText(&(tmp[i]));
					//AfxMessageBox("Ready");
					break;
				}
				else
				{
					//AfxMessageBox("Not ready");
					hd->GetDlgItem(IDC_STATE_STATIC)->SetWindowText("Waiting for USB response");
				}
			}
			//Sleep(1);
			//continue;
 		}
 		sprintf(buf,"%s sent",tmp);
 		hd->GetDlgItem(IDC_STATE_STATIC)->SetWindowText(buf);
	}
	return 0;
}

int RecvData(void)
{
	int ret_len;
	
	memset(recvBuf,0,sizeof(recvBuf));
	if(Read(recvBuf,256,&ret_len)==0)
	{
		return -1;
	}
	
	return ret_len;
}

void CTalkUSBDlg::Check_Stats (unsigned char* Stat1)
{
	unsigned char OutputEnableBuffer[256];

	// For GetReport_Control, the buffer's first element must contain the
	// report ID of the report that the function is supposed to retrieve
	OutputEnableBuffer [0] = IN_Talk_Stats;
	// Retrieve buffer
	HID_Talker.GetReport_Control (OutputEnableBuffer, HID_Talker.GetOutputReportBufferLength ());

	*Stat1 = OutputEnableBuffer [1];   // Return data received from report
}

