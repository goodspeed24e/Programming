// IPMIToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPMITool.h"
#include "MyIo.h"
#include "IPMIToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif 

#define	UDP_PORT_NO	0x26f //UDP通訊埠

/* for KCS */
#define BMC_TIMEOUT	50000

#define KCS_GET_STATUS	0x60
#define KCS_ABORT	0x60
#define KCS_WRITE_START	0x61
#define KCS_WRITE_END	0x62
#define KCS_READ	0x68

BYTE IPMI_request[100],IPMI_response[100];
int IPMI_reqlen,IPMI_rsplen;
void Delay(DWORD delay);
int hextoi(char *p, DWORD *data);


/* for IOL*/
BYTE RMCP_HEAD[]={0x6,0x0,0xFF,0x7};
char recv_buf[65535];

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
// CIPMIToolDlg dialog

CIPMIToolDlg::CIPMIToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPMIToolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPMIToolDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPMIToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPMIToolDlg)
	DDX_Control(pDX, IDC_USER_EDIT, m_user);
	DDX_Control(pDX, IDC_KCS_BT, m_kcs_bt);
	DDX_Control(pDX, IDC_KCS_RADIO, m_kcs);
	DDX_Control(pDX, IDC_IPADDRESS, m_ip);
	DDX_Control(pDX, IDC_IOL_RADIO, m_iol);
	DDX_Control(pDX, IDC_CN_BT, m_cn);
	DDX_Control(pDX, IDC_OFFSET_EDIT, m_offset);
	DDX_Control(pDX, IDC_SEND_BUTTON, m_send);
	DDX_Control(pDX, IDC_REPORT_EDIT, m_report);
	DDX_Control(pDX, IDC_CMD_EDIT, m_cmd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIPMIToolDlg, CDialog)
	//{{AFX_MSG_MAP(CIPMIToolDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND_BUTTON, OnSendButton)
	ON_EN_SETFOCUS(IDC_CMD_EDIT, OnSetfocusCmdEdit)
	ON_EN_KILLFOCUS(IDC_CMD_EDIT, OnKillfocusCmdEdit)
	ON_BN_CLICKED(IDC_IOL_RADIO, OnIolRadio)
	ON_BN_CLICKED(IDC_KCS_RADIO, OnKcsRadio)
	ON_BN_CLICKED(IDC_CN_BT, OnCnBt)
	ON_BN_CLICKED(IDC_KCS_BT, OnKcsBt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPMIToolDlg message handlers

BOOL CIPMIToolDlg::OnInitDialog()
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
	
	//預設
	cmd_in = 0;
	sSEQ=0;
	cmdSEQ=0;
	cn_flag = 0;
	
	m_iol.SetCheck(BST_CHECKED);
	m_ip.SetFieldFocus(0);
	
	OnOffCmd(1); //關閉
	OnIolRadio();
	
	//打開IO driver
	ShowStatus("Initial IO Driver....");
	if(OnMyIo()==0)
	{
		MessageBox("Fail to open IO driver","Error",MB_OK | MB_ICONSTOP);
		OnCancel();
	}
	
	ShowStatus("Idle");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIPMIToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIPMIToolDlg::OnPaint() 
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
HCURSOR CIPMIToolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CIPMIToolDlg::OnSendButton() 
{
	// TODO: Add your control notification handler code here
	int offset;
	char bb[10];
//		char buf[100];
	
	if(cn_flag==0)
	{
		if(m_offset.GetWindowText(bb,sizeof(bb))==0)
		{
			MessageBox("Fail to get OFFSET","Error",MB_OK | MB_ICONSTOP);
			m_offset.SetFocus();
			return;
		}
	
		offset = atoi(bb);
		KCS_STATUS = KCS_baseIO + offset;
		KCS_CTL = KCS_STATUS;
			
			//sprintf(buf,"da=%x ctrl=%x",KCS_baseIO,KCS_CTL);
			//AfxMessageBox(buf);
		if(GetCommandIntoBuf()!= 0)
		{
			ShowStatus("Process abort");
			return;
		}
		
		if(Send2KCS()!= 0)
		{
			return;
		}
		//sprintf(bb,"Got %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",IPMI_response[0],IPMI_response[1],IPMI_response[2],IPMI_response[3],IPMI_response[4],IPMI_response[5],IPMI_response[6],IPMI_response[7],IPMI_response[8],IPMI_response[9],IPMI_response[10],IPMI_response[11],IPMI_response[12]);
		//ShowStatus(bb);
		Show_Data();
		if(IPMI_response[2]!= 0)
		{
			ShowCompletionCode();
		}
		else
		{
			ShowStatus("done");
		}
	}
	else
	{//IOL
		if(GetCommandIntoBuf()!= 0)
		{
			ShowStatus("Process abort");
			return;
		}
		
		//
		if(IOL_Cmd(IPMI_request,IPMI_reqlen)==1)
		{
			return;
		}
		
		Show_Data();
		if(IPMI_response[2] != 0)
		{
			ShowCompletionCode();
		}
		else
		{
			ShowStatus("done");
		}
	}
}

int CIPMIToolDlg::GetCommandIntoBuf(void)
{
	int i,len;
	char buf[1024],tmp[10];
	DWORD cmd;
	
	len = m_cmd.GetWindowText(buf,sizeof(buf));
	if(len==0)
	{
		MessageBox("Please input command first");
		m_cmd.SetFocus();
		return 1;
	}
	
	IPMI_reqlen = 0;
	for(i = 0; i < len; i++)
	{
		if(buf[i] != ' ')
		{
			tmp[0] = buf[i];
			if(buf[i+1] != ' ')
			{
				i++;
				tmp[1] = buf[i];
				tmp[2] = '\0';
			}
			else
			{
				tmp[1] = '\0';
			}
			if(hextoi(tmp,&cmd)==1)
			{
				m_cmd.SetSel(0,-1,FALSE);
				return 1;
			}
			IPMI_request[IPMI_reqlen] = (BYTE)cmd;
			IPMI_reqlen++;
		}
	}
	return 0;
}

void CIPMIToolDlg::OnOK() 
{
	// TODO: Add extra validation here
	//CDialog::OnOK();
	if(cmd_in == 1)
	{
		OnSendButton();
	}
}

void CIPMIToolDlg::ShowCompletionCode(void)
{
	switch(IPMI_response[1])
	{
		case 0:
 			ShowStatus("Command Completed Normally");
 			break;
 		case 0xC0:
 			ShowStatus("Node Busy");
 			break;
 		case 0xC1:
 			ShowStatus("Invalid Command");
 			break;
 		case 0xC2:
 			ShowStatus("Command invalid for given LUN");
 			break;
 		case 0xC3:
 			ShowStatus("Timeout while processing command");
 			break;
 		case 0xC4:
 			ShowStatus("Out of space");
 			break;
 		case 0xC5:
 			ShowStatus("Reservation Canceled or Invalid Reservation ID");
 			break;
 		case 0xC6:
 			ShowStatus("Request data truncated");
 			break;
 		case 0xC7:
 			ShowStatus("Request data length invalid");
 			break;
 		case 0xC8:
 			ShowStatus("Request data field length limit exceeded");
 			break;
 		case 0xC9:
 			ShowStatus("Parameter out of range");
 			break;
 		case 0xCA:
 			ShowStatus("Cannot return number of requested data bytes");
 			break;
 		case 0xCB:
 			ShowStatus("Requested Sensor, data, or record not present");
 			break;
 		case 0xCC:
 			ShowStatus("Invalid data field in Request");
 			break;
 		case 0xCD:
 			ShowStatus("Command illegal for specified sensor or record type");
 			break;
 		case 0xCE:
 			ShowStatus("Command response could not be provided");
 			break;
 		case 0xCF:
 			ShowStatus("Cannot execute duplicated request");
 			break;
 		case 0xD0:
 			ShowStatus("Command response could not be provided;SDR Repository in update mode");
 			break;
 		case 0xD1:
 			ShowStatus("Command response could not be provided. Device in firmware update mode");
 			break;
 		case 0xD2:
 			ShowStatus("Command response could not be provided. BMC initialization or initialization agent in progress");
 			break;
 		case 0xD3:
 			ShowStatus("Destination unavailable. Cannot deliver request to selected destination");
 			break;
 		case 0xD4:
 			ShowStatus("Cannot execute command due to insufficient privilege level or other securitybased restriction");
 			break;
 		case 0xD5:
 			ShowStatus("Cannot execute command. Command, or request parameter(s), not supported in present state");
 			break;
 		case 0xD6:
 			ShowStatus("Cannot execute command. Parameter is illegal because command sub-function has been disabled or is unavailable");
 			break;
 			
 	}
}

void CIPMIToolDlg::Show_Data(void)
{
	int qty,i;
	char buf[1024],tmp[200];
	
	ZeroMemory(buf,sizeof(buf));
	//sprintf(buf,"Command Response:%02X,%02X\r\nData:",IPMI_response[0],IPMI_response[1]);
	strcpy(buf," Recv:");
	
	for(i = 0; i < IPMI_rsplen; i++)
	{
		sprintf(tmp," %02X",IPMI_response[i]);
		strcat(buf,tmp);
	}
	
	qty = m_report.GetWindowTextLength();
	m_report.SetSel(qty,qty,FALSE);
	m_report.ReplaceSel(buf,FALSE);
	m_report.ReplaceSel("\r\n",FALSE);
		
	qty = m_report.GetLineCount();
		
	if(qty > 1000)
	{
		m_report.SetReadOnly(FALSE);
		qty = m_report.LineIndex(qty-1000);
		m_report.SetSel(0,qty,TRUE);
		m_report.Clear();
		qty = m_report.GetWindowTextLength();
		m_report.SetReadOnly(TRUE);
		m_report.SetSel(qty,qty,FALSE);
	}
	
}

void CIPMIToolDlg::ShowStatus(char *str)
{
	GetDlgItem(IDC_STATUS_STATIC)->SetWindowText(str);
}

void CIPMIToolDlg::OnSetfocusCmdEdit() 
{
	// TODO: Add your control notification handler code here
	cmd_in = 1;
}

void CIPMIToolDlg::OnKillfocusCmdEdit() 
{
	// TODO: Add your control notification handler code here
	cmd_in = 0;
}

BOOL CIPMIToolDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	OffMyIo();
	return CDialog::DestroyWindow();
}

//
int CIPMIToolDlg::SearchIPMIBase(void)
{
	DWORD SMB_addr,dwMemVal;
	BOOL flag=FALSE,vv;
	int i,len,zz_cnt;
	char bb[100];
	BYTE dd;
	
		//AfxMessageBox("in");
	//找出SMBIOS entry point
	for(SMB_addr = 0xf0000; SMB_addr < 0xfffff; SMB_addr+=4)
	{
		read_mem_dword(SMB_addr, &dwMemVal);
		if(dwMemVal==0x5F4d535F) //顛倒的_SM_
		{
			//讀出table位址
			SMB_addr+=24;
			read_mem_dword(SMB_addr, &dwMemVal);
			SMB_addr = dwMemVal; //各table起始位址
				//sprintf(bb,"start addr=%08lX",SMB_addr);
				//AfxMessageBox(bb);
			flag = TRUE;
			break;
		}
	}
	
	if(flag == TRUE)
	{//找到entry point
		while(1)
		{
			//判斷是不是IPMI table
			read_mem_dword(SMB_addr, &dwMemVal);
			if((BYTE)(dwMemVal & 0xff) == 0x26) //IPMI table
			{
				//判斷IPMI介面型態(我們只支援KCS)
				SMB_addr += 4;
				read_mem_dword(SMB_addr, &dwMemVal);
				if((dwMemVal & 0xff) != 0x1)
				{//不是KCS
					MessageBox("This program support KCS interface only","Error",MB_OK | MB_ICONSTOP);
					return 1;
				}
				//取得base address
				SMB_addr += 4;
				read_mem_dword(SMB_addr, &dwMemVal);
				if((dwMemVal & 0x1) == 0x1)
				{
					KCS_baseIO = (WORD)(dwMemVal & 0x0000fffe);
						//sprintf(bb,"got %x",dwMemVal);
						//AfxMessageBox(bb);
					for(i = 1; i < 16 ;i++)
					{
						SMB_addr = (DWORD)(KCS_baseIO+i);
						read_io_byte((WORD)SMB_addr, &dd);
							//sprintf(bb,"Got: %08lX(%08lX)",dwMemVal,SMB_addr);
							//AfxMessageBox(bb);
						if((dd & 0xff) != 0xff)
						{
							sprintf(bb,"%d",i);
							m_offset.SetWindowText(bb);
							break;
						}
					}
					
					if(i == 16)
					{
						MessageBox("Can NOT found BMC Ctrl/Status port offset.\nPlease keyin it at main UI","Warning",MB_OK | MB_ICONSTOP);
						return 2;
					}
				}
				
				//	sprintf(bb,"KCS address is: %x",KCS_base);
				//	AfxMessageBox(bb);
				return 0;
			}
			else
			{
					//sprintf(bb,"get table is: %d",(int)((BYTE)dwMemVal));
					//AfxMessageBox(bb);
				if((BYTE)(dwMemVal & 0xff) == 0x7F) //end
				{
					MessageBox("Can NOT find IPMI table in SMBIOS","Error",MB_OK | MB_ICONSTOP);
					return 1;
				}
				
				//得到這個table的總大小(包含字串)，然後跳過它
				len = (int)(BYTE)(dwMemVal >> 8);
				SMB_addr += len;
				zz_cnt = 0;
				while(zz_cnt != 2)
				{
					//	sprintf(bb,"get data @: %08lX",SMB_addr);
					//	AfxMessageBox(bb);
					read_mem_dword(SMB_addr, &dwMemVal);
					for(i = 0; i < 4; i++)
					{
						vv = (BYTE)(dwMemVal & 0xff);
						if(vv==0)
						{
							zz_cnt++;
							if(zz_cnt == 2)
							{
								SMB_addr+=i+1;
								break;
							}
						}
						else
						{
							zz_cnt=0;
						}
						dwMemVal >>= 8;
					}
					if(i == 4)
					{
						SMB_addr+=4;
					}
				}
				
					//sprintf(bb,"new address: %08lX",SMB_addr);
					//AfxMessageBox(bb);
			}
		}
	}
	else
	{//找不到
		MessageBox("Can NOT find SMBIOS Entry point","Error",MB_OK | MB_ICONSTOP);
		return 1;
	}
	
}

int CIPMIToolDlg::chktmout(void)
{
	// at least maxtime( must include the subroutines execution time in the loop! )
	if (tm > BMC_TIMEOUT)
	{
		return 1;
	}
	else
	{
		Delay(1);
		tm++;
	}
	return 0;
}

int CIPMIToolDlg::chkBMCbusy(void)
{
	BYTE dd;

	tm=0;
	while(1)
	{
		read_io_byte(KCS_STATUS,&dd);
		if((dd & 0xc0)==0)
		{//IDLE_STATE
			return 0;
		}
		if(chktmout()==1)
		{
			//ShowStatus("BMC busy timeout!");
			return 1;
		}
	}
}

int CIPMIToolDlg::chkBMCibfrdy(void)
{
	BYTE dd;
	
	tm=0;
	while(1)
	{
		read_io_byte(KCS_STATUS,&dd);
		
		if((dd & 0x02)==0)
		{//IBF ready
			return 0;
		}
		if(chktmout()==1)
		{
			//ShowStatus("BMC IBF timeout!");
			return 1;
		}
	}
}

BYTE CIPMIToolDlg::IPDATA(void)
{
	BYTE dd;
	
	read_io_byte(KCS_baseIO,&dd);
	return dd;
}

void CIPMIToolDlg::OPDATA(BYTE data)
{
	BYTE dd;
	
	write_io_byte(KCS_baseIO,data);
	read_io_byte(0x84,&dd);
}

void CIPMIToolDlg::OPCMD(BYTE data)
{
	BYTE dd;
	
	write_io_byte(KCS_CTL,data);
	read_io_byte(0x84,&dd);
}

int CIPMIToolDlg::chkBMCobfrdy_l(void)
{
	BYTE dd;
	
	tm=0; 
	while(1)
	{
		read_io_byte((KCS_STATUS),&dd);
		if((dd & 0x01)==0)
		{//OBF ready
			return 0;
		}
		IPDATA();
	 	if(chktmout()==1)
		{
			//ShowStatus("BMC OBF_L timeout!");
			return 1;
		}
	}
}

int CIPMIToolDlg::chkBMCobfrdy_h(void)
{
	BYTE dd;
	
	tm=0; 
	while(1)
	{
		read_io_byte(KCS_STATUS,&dd);
		if((dd & 0x01)==0x01)
		{//OBF ready
			return 0;
		}
		IPDATA();
	 	if(chktmout()==1)
		{
			//ShowStatus("BMC OBF_H timeout!");
			return 1;
		}
	}
}

int CIPMIToolDlg::chkBMCtxrdy(void)
{
	BYTE dd;

	tm=0;
	while(1)
	{
		read_io_byte(KCS_STATUS,&dd);
		if((dd & 0xc0)==0x80)
		{//IDLE_STATE
			return 0;
		}
		if(chktmout()==1)
		{
			//ShowStatus("BMC Tx timeout!");
			return 1;
		}
	}
}

int CIPMIToolDlg::chkBMCrxrdy(void)
{
	BYTE dd;

	tm=0;
	while(1)
	{
		read_io_byte(KCS_STATUS,&dd);
		if((dd & 0xc0)==0x40)
		{//IDLE_STATE
			return 0;
		}
		if(chktmout()==1)
		{
			//ShowStatus("BMC Rx timeout!");
			return 1;
		}
	}
}

int CIPMIToolDlg::Send2KCS(void)
{
	int n;
	BYTE dd;
	
	ZeroMemory(IPMI_response,sizeof(IPMI_response));
	
	//-------------------------------- request ------------------------------
	if(chkBMCibfrdy()==1)
	{
		ShowStatus("BMC IBF timeout! Err01");
		return 1;
	}
	
	if(chkBMCobfrdy_l()==1)
	{
		ShowStatus("BMC OBF_L timeout! Err02");
		return 1;
	}
	
	OPCMD(KCS_WRITE_START);
	
	if(chkBMCibfrdy()==1)
	{
		ShowStatus("BMC IBF timeout! Err03");
		return 1;
	}
	
	if(chkBMCtxrdy()==1)
	{
		ShowStatus("BMC TX timeout! Err04");
		return 1;
	}
	
	if(chkBMCobfrdy_l()==1)
	{
		ShowStatus("BMC OBF_L timeout! Err05");
		return 1;
	}
		
	n = 0;
	while( n < (IPMI_reqlen-1))
	{
		OPDATA(IPMI_request[n]);
		if(chkBMCibfrdy()==1)
		{
			ShowStatus("BMC IBF timeout! Err06");
			return 1;
		}
		
		if(chkBMCtxrdy()==1)
		{
			ShowStatus("BMC TX timeout! Err07");
			return 1;
		}
		
		if(chkBMCobfrdy_l()==1)
		{
			ShowStatus("BMC OBF_L timeout! Err08");
			return 1;
		}
		
		n++;
	}
	OPCMD(KCS_WRITE_END);
	if(chkBMCibfrdy()==1)
	{
		ShowStatus("BMC IBF timeout! Err9");
		return 1;
	}
	
	if(chkBMCtxrdy()==1)
	{
		ShowStatus("BMC TX timeout! Err10");
		return 1;
	}
	
	if(chkBMCobfrdy_l()==1)
	{
		ShowStatus("BMC OBF_L timeout! Err11");
		return 1;
	}
	
	OPDATA(IPMI_request[n]);
	
	//-------------------------------- response ------------------------------
	IPMI_rsplen=0;
	while(1)
	{
		if(chkBMCibfrdy()==1)
		{
			ShowStatus("BMC IBF timeout! Err12");
			return 1;
		}
		
		read_io_byte(KCS_STATUS,&dd);
		if((dd & 0x40)==0x40)
		{
			if(chkBMCobfrdy_h()==1)
			{
				ShowStatus("BMC OBF_H timeout! Err13");
				return 1;
			}
			
			IPMI_response[IPMI_rsplen] = IPDATA();
			OPDATA(KCS_READ);
		}
		else
		{
			if(chkBMCbusy()==1)
			{
				ShowStatus("BMC BUSY timeout! Err14");
				return 1;
			}
			
			if(chkBMCobfrdy_h()==1)
			{
				ShowStatus("BMC OBF_H timeout! Err15");
				return 1;
			}
			
			IPDATA();
			if(chkBMCbusy()==1)
			{
				ShowStatus("BMC BUSY timeout! Err16");
				return 1;
			}
			break;
		}
		IPMI_rsplen++;
	}
	
	return 0;
}

int CIPMIToolDlg::CreateUDP(BYTE ip1,BYTE ip2, BYTE ip3, BYTE ip4)
{
	char buf[1024];
//	BYTE ip[4];
	char host_name[256];					/* Host name of this computer */
	struct hostent *hp;						/* Information about the server */
	
	sprintf(buf,"Connecting to %d.%d.%d.%d....",ip1,ip2,ip3,ip4);
	ShowStatus(buf);
		
	//Open windows connection
	if (WSAStartup(0x0101, &w) != 0)
	{
		ShowStatus("Could not open Windows connection.");
		return 1;
	}
	
	//Open a datagram socket
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == INVALID_SOCKET)
	{
		ShowStatus("Could not create socket.");
		WSACleanup();
		return 1;
	}
		
	//Clear out server struct
	ZeroMemory((void *)&server, sizeof(struct sockaddr_in));
		
	//Set family and port
	server.sin_family = AF_INET;
	server.sin_port = htons(UDP_PORT_NO);
		
	//Set server address
	server.sin_addr.S_un.S_un_b.s_b1 = ip1;
	server.sin_addr.S_un.S_un_b.s_b2 = ip2;
	server.sin_addr.S_un.S_un_b.s_b3 = ip3;
	server.sin_addr.S_un.S_un_b.s_b4 = ip4;
	
		
	//Clear out client struct 
	ZeroMemory((void *)&client, sizeof(struct sockaddr_in));

	// Set family and port
	client.sin_family = AF_INET;
	client.sin_port = htons(0);
		
	//Get host name of this computer
	gethostname(host_name, sizeof(host_name));
	hp = gethostbyname(host_name);

	//Check for NULL pointer
	if (hp == NULL)
	{
		ShowStatus("Could not get host name.");
		closesocket(sd);
		WSACleanup();
		return 1;
	}

	//Assign the address
	client.sin_addr.S_un.S_un_b.s_b1 = hp->h_addr_list[0][0];
	client.sin_addr.S_un.S_un_b.s_b2 = hp->h_addr_list[0][1];
	client.sin_addr.S_un.S_un_b.s_b3 = hp->h_addr_list[0][2];
	client.sin_addr.S_un.S_un_b.s_b4 = hp->h_addr_list[0][3];
		
	//Bind local address to socket
	if(bind(sd, (struct sockaddr *)&client, sizeof(struct sockaddr_in)) == -1)
	{
		ShowStatus("Cannot bind address to socket.");
		closesocket(sd);
		WSACleanup();
		return 1;
	}
	
	server_length = sizeof(struct sockaddr_in);
	
	ShowStatus("UDP Connected.");
	
	return 0;
}


int CIPMIToolDlg::PingPong(void)
{
	BYTE RMCP_ping[12];
  
  ZeroMemory((char *)RMCP_ping,sizeof(RMCP_ping));
	memcpy(RMCP_ping,RMCP_HEAD,4);
	RMCP_ping[6] = 0x11;
	RMCP_ping[7] = 0xBE;
	RMCP_ping[8] = 0x80;
  
  //Tranmsit data to server
//	server_length = sizeof(struct sockaddr_in);
	if (sendto(sd, (char *)RMCP_ping, sizeof(RMCP_ping), 0, (struct sockaddr *)&server, server_length) == -1)
	{
		ShowStatus("Error on Pinging BMC.");
		closesocket(sd);
		WSACleanup();
		return 1;
	}
	ShowStatus("Pinging sent");
	
	//Receive data from Server
	//server_length = 65535;
	if(recvfrom(sd, recv_buf, (int)sizeof(recv_buf), 0, (struct sockaddr *)&server, &server_length) < 0)
	{
		ShowStatus("Error on receiving Pong data.");
		closesocket(sd);
		WSACleanup();
		return 1;
	}
	ShowStatus("Pong received");
	
	return 0;
}

int CIPMIToolDlg::OpenSession(void)
{
	//         Max Privilege Level
	//          Msg-Tag |
	//             |    |     Rsvd       console S-ID            Authentication Payload                    Integrity payload                    Confidentiality payload
	//             |    |    +----+    +--------------+    +----------------------------------+    +----------------------------------+    +----------------------------------+
	BYTE buf2[]={0x00,0x04,0x00,0x00,0xF1,0xA2,0x45,0x2B,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x08,0x00,0x00,0x00,0x00};
	//             0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31 
	BYTE session_tb[48];
	int i;
//		FILE *fp;
		
	//memcpy(session_tb,RMCP_HEAD,4);
	srand((unsigned)time(NULL));	//調整亂數
	
	buf2[4] = (BYTE)(rand() % 255);
	buf2[5] = (BYTE)(rand() % 255);
	buf2[6] = (BYTE)(rand() % 255);
	buf2[7] = (BYTE)(rand() % 255);
	
	asm_20_iol_package(session_tb,0x10,0,0,0x20,buf2);
	
		/*fp = fopen("d:\\ipmi.bin","w+b");
		fwrite(session_tb,sizeof(session_tb),1,fp);
		fclose(fp);*/
	if (sendto(sd, (char *)session_tb, sizeof(session_tb), 0, (struct sockaddr *)&server, server_length) == -1)
	{
		ShowStatus("Error on Open Session.");
		closesocket(sd);
		WSACleanup();
		return 1;
	}
	ShowStatus("Session opened");
	
	//Receive data from BMC
	//server_length = 65535;
	if(recvfrom(sd, recv_buf, (int)sizeof(recv_buf), 0, (struct sockaddr *)&server, &server_length) < 0)
	{
		ShowStatus("Error on receiving open session response.");
		closesocket(sd);
		WSACleanup();
		return 1;
	}
	
	if(recv_buf[1] != 0)
	{
		conn_fail(recv_buf[1]);
	}
	
	mssID = 0;
	for(i = 0; i < 4; i++)
	{
		mssID <<= 8;
		mssID |= recv_buf[27-i];
	}
	
	sSEQ = 3; //sequence no started from 3
	
	ShowStatus("Open session Response received");
	return 0;
}

int CIPMIToolDlg::RAKP(int sld)
{
	BYTE buf2[50];
	BYTE buf[100];
	WORD i,len;
	
	if(sld==1)
	{
		len = (WORD)strlen(userID);
		
		buf2[0] = 0x01;
		buf2[1] = 0x00;
		buf2[2] = 0x00;
		buf2[3] = 0x00;
		buf2[4] = (BYTE)mssID;
		buf2[5] = (BYTE)(mssID>>8);
		buf2[6] = (BYTE)(mssID>>16);
		buf2[7] = (BYTE)(mssID>>24);
		buf2[24] = 0x14;
		buf2[25] = 0x00;
		buf2[26] = 0x00;
		buf2[27] = (BYTE)len;
		for(i = 0; i < len; i++)
		{
			buf2[28+i] = userID[i];
		}
		len = len+28; //package length
		
		asm_20_iol_package(buf,0x12,0x0,0x0,len,buf2); //BYTE *buf,BYTE pd_type,DWORD ssID,DWORD sSQ, WORD pd_len, BYTE *buf2)
		len += 16; //total package length
	}
	else
	{
		ZeroMemory(buf2,sizeof(buf2));
		buf2[0] = 0x01;
		buf2[4] = (BYTE)mssID;
		buf2[5] = (BYTE)(mssID>>8);
		buf2[6] = (BYTE)(mssID>>16);
		buf2[7] = (BYTE)(mssID>>24);
		
		asm_20_iol_package(buf,0x14,0x0,0x0,8,buf2); //BYTE *buf,BYTE pd_type,DWORD ssID,DWORD sSQ, WORD pd_len, BYTE *buf2)
		len = 24;
	}
	
	if (sendto(sd, (char *)buf,len , 0, (struct sockaddr *)&server, server_length) == -1)
	{
		sprintf((char *)buf,"Error on send RAKP %d.",sld);
		ShowStatus((char *)buf);
		closesocket(sd);
		WSACleanup();
		return 1;
	}
	ShowStatus("RAKP sent");
	
	if(recvfrom(sd, recv_buf, (int)sizeof(recv_buf), 0, (struct sockaddr *)&server, &server_length) < 0)
	{
		sprintf((char *)buf,"Error on receiving RAKP %d.",sld+1);
		ShowStatus((char *)buf);
		closesocket(sd);
		WSACleanup();
		return 1;
	}
	
	if(recv_buf[1] != 0)
	{
		conn_fail(recv_buf[1]);
	}
	
	return 0;
}

int CIPMIToolDlg::IOL_Cmd(BYTE *cmd,int cmdlen) //cmdlen是cmd陣列的總長度，不包含checksum
{
	BYTE tmp[]={0x20,0x00,0x00,0x21,0x00}; //BMC,NetFn,checksum,sender,cmsSEQ
	BYTE buf2[50];
	BYTE buf[100];
	BYTE chks;
	int i,len;
	
	cmdSEQ += 4;
	
	tmp[1] = cmd[0];
	tmp[2] = (BYTE)(0x100-tmp[0]-tmp[1]);
	tmp[4] = cmdSEQ;
	
	chks = 0;
	for(i = 3; i < 5; i++)
	{
		chks += tmp[i];
	}
	for(i = 1; i < cmdlen; i++)
	{
		chks += cmd[i];
	}
	chks = (BYTE)(0x100-chks); //補上zero-checksum
	
	ZeroMemory(buf2,sizeof(buf2));
	memcpy(buf2,tmp,5);

	for( i = 0 ;i < cmdlen-1; i++)
	{
		buf2[5+i] = cmd[i+1];
	}
	buf2[5+cmdlen-1] = chks;
	
	i = cmdlen + 5;
	
	asm_20_iol_package(buf,0x00,mssID,sSEQ,i,buf2); //BYTE *buf,BYTE pd_type,DWORD ssID,DWORD sSQ, WORD pd_len, BYTE *buf2)
	
	if (sendto(sd, (char *)buf,i +16, 0, (struct sockaddr *)&server, server_length) == -1)
	{
		ShowStatus("Error on send cmd");
		closesocket(sd);
		WSACleanup();
		return 1;
	}
	
	if(recvfrom(sd, recv_buf, (int)sizeof(recv_buf), 0, (struct sockaddr *)&server, &server_length) < 0)
	{
		ShowStatus("Error on receiving data");
		closesocket(sd);
		WSACleanup();
		return 1;
	}
	
	//把傳回的資料放到IPMI_response中
	ZeroMemory(IPMI_response,sizeof(IPMI_response));
	IPMI_response[0] = recv_buf[17];
	len = recv_buf[15];
	len <<= 8;
	len |= recv_buf[14];
	len -= 6; //前5碼+最後1碼
	IPMI_rsplen = len+1;
	for(i = 0; i < len; i++)
	{
		IPMI_response[1+i] = recv_buf[21+i];
	}
	
	sSEQ ++;
	return 0;
}

int CIPMIToolDlg::CloseSession15(void)
{//斷線
	//                                                                                               
	//                                                                              payload-len  NetFn
	//                     RMCP head      none      Session Seq          Session ID      |   BMC   |                       msS-ID 
	//                  +--------------+    |    +--------------+    +--------------+    |    |    |  chks  SID  cmd   +--------------+  chks
	BYTE close_buf[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0B,0x20,0x18,0xC8,0x21,0x3C,0x00,0x00,0x00,0x00,0x00};
	//                  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23
	BYTE chks;
	int i;
	
	close_buf[5] = (BYTE)sSEQ;
	close_buf[6] = (BYTE)(sSEQ>>8);
	close_buf[7] = (BYTE)(sSEQ>>16);
	close_buf[8] = (BYTE)(sSEQ>>24);
	
	close_buf[9] = (BYTE)mssID;
	close_buf[10] = (BYTE)(mssID>>8);
	close_buf[11] = (BYTE)(mssID>>16);
	close_buf[12] = (BYTE)(mssID>>24);
	
	close_buf[20] = (BYTE)mssID;
	close_buf[21] = (BYTE)(mssID>>8);
	close_buf[22] = (BYTE)(mssID>>16);
	close_buf[23] = (BYTE)(mssID>>24);
	
	chks=0;
	for(i = 0; i < 7; i++)
	{
		chks += close_buf[17+i];
	}
	
	close_buf[24] = chks;
	
	if (sendto(sd, (char *)close_buf, sizeof(close_buf), 0, (struct sockaddr *)&server, server_length) == -1)
	{
		ShowStatus("Error on close Session.");
		closesocket(sd);
		WSACleanup();
		return 1;
	}
	ShowStatus("Session closed");
	return 0;
}

void CIPMIToolDlg::conn_fail(int sld)
{
	switch(sld)
	{
		case 0x1:
			ShowStatus("Insufficient resources to create a session");
			break;
		case 0x2:
			ShowStatus("Invalid Session ID");
			break;
		case 0x3:
			ShowStatus("Invalid payload type");
			break;
		case 0x4:
			ShowStatus("Invalid authentication algorithm");
			break;
		case 0x5:
			ShowStatus("Invalid integrity algorithm");
			break;
		case 0x6:
			ShowStatus("No matching authentication payload");
			break;
		case 0x7:
			ShowStatus("No matching integrity payload");
			break;
		case 0x8:
			ShowStatus("Inactive Session ID");
			break;
		case 0x9:
			ShowStatus("Invalid role");
			break;
		case 0xA:
			ShowStatus("Unauthorized role or privilege level requested");
			break;
		case 0xB:
			ShowStatus("Insufficient resources to create a session at the requested role");
			break;
		case 0xC:
			ShowStatus("Invalid name length");
			break;
		case 0xD:
			ShowStatus("Unauthorized name");
			break;
		case 0xE:
			ShowStatus("Unauthorized GUID");
			break;
		case 0xF:
			ShowStatus("Invalid integrity check value");
			break;
		case 0x10:
			ShowStatus("Invalid confidentiality algorithm");
			break;
		case 0x11:
			ShowStatus("No Cipher Suite match with proposed security algorithms");
			break;
		case 0x12:
			ShowStatus("Illegal or unrecognized parameter");
			break;
		default:
			ShowStatus("Reserved for future definition by this specification");
			break;
	}
}

int CIPMIToolDlg::asm_20_iol_package(BYTE *buf,BYTE pd_type,DWORD ssID,DWORD sSQ, WORD pd_len, BYTE *buf2)
{
	//                                                                                             Max Privilege Level
	//                                   payload-type                                              Msg-Tag |
	//                   RMCP head     RMCP+   |       Session ID         Session Seq     payload-len |    |     Rsvd       console S-ID            Authentication Payload                    Integrity payload                    Confidentiality payload
	//                +--------------+   |     |    +--------------+    +--------------+    +----+    |    |    +----+    +--------------+    +----------------------------------+    +----------------------------------+    +----------------------------------+
	//session_tb[]={0x00,0x00,0x00,0x00,0x06,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x04,0x00,0x00,0xF1,0xA2,0x45,0x2B,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x08,0x00,0x00,0x00,0x00};
	//                0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45   46   47
	
	ZeroMemory(buf,sizeof(buf));
	memcpy(buf,RMCP_HEAD,4);
	buf[4] = 0x06; //RMCP+ format
	buf[5] = pd_type; //payload-type
	buf[6] = (BYTE)ssID;
	buf[7] = (BYTE)(ssID>>8);
	buf[8] = (BYTE)(ssID>>16);
	buf[9] = (BYTE)(ssID>>24);
	buf[10] = (BYTE)sSQ;
	buf[11] = (BYTE)(sSQ >> 8);
	buf[12] = (BYTE)(sSQ >> 16);
	buf[13] = (BYTE)(sSQ >> 24);
	buf[14] = (BYTE)pd_len;
	buf[15] = (BYTE)(pd_len >> 8);
	
	memcpy(&(buf[16]),buf2,pd_len);
	return 0;
}


void Delay(DWORD delay)
{
	LARGE_INTEGER start,end,Freq;
 
	QueryPerformanceFrequency(&Freq);                      
	//end.QuadPart = (delay*Freq.QuadPart)/10000;        //0.1ms
	end.QuadPart = (delay*Freq.QuadPart)/100000;        //0.01ms
	QueryPerformanceCounter(&start);
	end.QuadPart = end.QuadPart+start.QuadPart;/*-System_test()*2;*/
	do
	{
		QueryPerformanceCounter(&Freq);
	}while (Freq.QuadPart<=end.QuadPart);
}

int hextoi(char *p, DWORD *data)                   // convert Hex ASCII to integer
{
	DWORD v=0,tmp=0;
	int count=0;
	
	while(1)
	{
		if (*p >= '0' && *p <= '9' )
		{
			tmp = *p - 0x30;
		}
		else if(*p >= 'A' && *p <= 'F')
		{
			tmp = *p - 0x37;
		}
		else if(*p >= 'a' && *p <= 'f' )
		{
			tmp = *p - 0x57;
		}
		else if(*p == '\0')
		{
			break;
		}
		else
		{
			MessageBox(NULL,"( Hex ASCII to Int )Input is not in the Hex range!","Error",MB_OK | MB_ICONSTOP);
			return 1;
		}
		count++;
		if(count > 8)
		{
			break;
		}
		v <<= 4;
		v |= tmp;
		p++;
	}

	*data = v;
	return 0;
}



void CIPMIToolDlg::OnIolRadio() 
{
	// TODO: Add your control notification handler code here
	if(m_iol.GetCheck()==BST_CHECKED)
	{
		m_kcs.SetCheck(BST_UNCHECKED);
		
		m_ip.EnableWindow(TRUE);
		m_cn.EnableWindow(TRUE);
	
		m_offset.EnableWindow(FALSE);
		m_kcs_bt.EnableWindow(FALSE);
		m_ip.SetFieldFocus(0);
	}
}

void CIPMIToolDlg::OnKcsRadio() 
{
	// TODO: Add your control notification handler code here
	if(m_kcs.GetCheck()==BST_CHECKED)
	{
		m_iol.SetCheck(BST_UNCHECKED);
		m_ip.EnableWindow(FALSE);
		m_cn.EnableWindow(FALSE);
	
		m_cmd.EnableWindow(TRUE);
		m_send.EnableWindow(TRUE);
		m_offset.EnableWindow(TRUE);
		m_kcs_bt.EnableWindow(TRUE);
	}
}

void CIPMIToolDlg::OnCnBt() 
{
	// TODO: Add your control notification handler code here
	if(cn_flag == 0)
	{//connect
		BYTE ip[4];
//			BYTE pp[3];
//			int ff;
		
		if(m_ip.GetAddress(ip[0],ip[1],ip[2],ip[3]) != 4)
		{
			MessageBox("Please input IP first","Error",MB_OK | MB_ICONSTOP);
			m_ip.SetFieldFocus(0);
			return;
		}
		
		if(m_user.GetWindowText(userID,sizeof(userID))==0)
		{
			MessageBox("Please input User name first","Error",MB_OK | MB_ICONSTOP);
			m_user.SetFocus();
			return;
		}
		
		if(CreateUDP(ip[0],ip[1],ip[2],ip[3])!= 0)
		{
			return;
		}
		
		if(OpenSession()!= 0)
		{
			goto cut_off;
		}
		
		if(RAKP(1)!= 0)
		{
			goto cut_off;
		}
		if(RAKP(3)!= 0)
		{
			goto cut_off;
		}
		
		m_cmd.EnableWindow(TRUE);
		m_send.EnableWindow(TRUE);
		m_cn.SetWindowText("Dis-connect");
		cn_flag = 1;
		ShowStatus("Connected");
		m_cmd.SetFocus();
	}
	else
	{//
cut_off:
		cn_flag = 0;
		
		m_cmd.EnableWindow(FALSE);
		m_send.EnableWindow(FALSE);
		m_cn.SetWindowText("Connect");
		ShowStatus("Dis-connected");
	}
}

void CIPMIToolDlg::OnKcsBt() 
{
	// TODO: Add your control notification handler code here
	int st;
	
	ShowStatus("Detecting KCS interface....");
	st = SearchIPMIBase();
	if(st ==1)
	{//失敗
		//MessageBox("Can NOT find IPMI base in SMBIOS table");
		m_kcs.EnableWindow(FALSE);
		m_offset.EnableWindow(FALSE);
	}
	else if(st == 2)
	{
		m_offset.SetFocus();
	}
	ShowStatus("Idle");
}

void CIPMIToolDlg::OnOffCmd(int sld)
{
	if(sld == 0)
	{
		m_cmd.EnableWindow(TRUE);
		m_send.EnableWindow(TRUE);
		m_cmd.SetFocus();
	}
	else
	{
		m_cmd.EnableWindow(FALSE);
		m_send.EnableWindow(FALSE);
	}
}


