// WinSMBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinSMB.h"
#include "Detaildlg.h"
#include "WinSMBDlg.h"
#include "myio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NVIDIA_SMB_PRTCL	0x00       /* protocol, PEC */
#define NVIDIA_SMB_STS		0x01       /* status */
#define NVIDIA_SMB_ADDR		0x02       /* address */
#define NVIDIA_SMB_CMD		0x03       /* command */
#define NVIDIA_SMB_DATA		0x04       /* 32 data registers */
#define NVIDIA_SMB_BCNT		0x24       /* number of data bytes */
#define NVIDIA_SMB_ALRM_A	0x25       /* alarm address */
#define NVIDIA_SMB_ALRM_D	0x26       /* 2 bytes alarm data */
       
#define NVIDIA_SMB_STS_DONE	0x80
#define NVIDIA_SMB_STS_ALRM	0x40
#define NVIDIA_SMB_STS_RES	0x20
#define NVIDIA_SMB_STS_STATUS	0x1f

#define NVIDIA_SMB_PRTCL_WRITE	0x00
#define NVIDIA_SMB_PRTCL_READ	0x01
#define NVIDIA_SMB_PRTCL_QUICK	0x02
#define NVIDIA_SMB_PRTCL_BYTE	0x04
#define NVIDIA_SMB_PRTCL_BYTE_DATA	0x06
#define NVIDIA_SMB_PRTCL_WORD_DATA	0x08
#define NVIDIA_SMB_PRTCL_BLOCK_DATA	0x0a
#define NVIDIA_SMB_PRTCL_PROC_CALL	0x0c
#define NVIDIA_SMB_PRTCL_BLOCK_PROC_CALL	0x0d
#define NVIDIA_SMB_PRTCL_I2C_BLOCK_DATA		0x4a
#define NVIDIA_SMB_PRTCL_PEC	0x80

#define MAX_TIMEOUT 1000

#define SMBHSTSTS	0x0    // smbus host status register    
#define SMBHSTCNT	0x2    // smbus host control register   
#define SMBHSTCMD	0x3    // smbus host command register   
#define SMBHSTADD	0x4    // smbus host address register   
#define SMBHSTDAT0	0x5    // smbus host data 0 register    
#define SMBHSTDAT1	0x6    // smbus host data 1 register    
#define SMBBLKDAT	0x7    // smbus block data register 

#define START_RW	0x40   // Start R/W Command
#define SMB_HOST_BUSY		1      // smb host is busy              
#define SMB_INTERRUPT		2      // smb interrupt flag            
#define SMB_DEVICE_ERROR	4      // device error                  
#define SMB_BUS_COLLISION	8      // transation collision          
#define SMB_FAIL		16     // transation fail
#define BYTE_DATA_READ_OR_WRITE	(2*4)	// Byte data read or write

/*struct i2c_device
{
	BYTE addr;
	BYTE data;
};*/

WORD SMB_base;
BYTE bus,dev,func;
int smb_type;

//struct i2c_device devs[20];
BYTE read_nv_slave_data(BYTE slave_address, BYTE offset);
BYTE read_it_slave_data(BYTE slave_address, BYTE offset);
BOOL Search_Device( BYTE Classtype,BYTE Subclass1,BYTE Subclass2,WORD *vd,BYTE *Bus, BYTE *Dev, BYTE *Func );
void delay1us(DWORD delay);
int hextoi(char *p, DWORD *data);

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
// CWinSMBDlg dialog

CWinSMBDlg::CWinSMBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinSMBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinSMBDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinSMBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinSMBDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinSMBDlg, CDialog)
	//{{AFX_MSG_MAP(CWinSMBDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinSMBDlg message handlers

BOOL CWinSMBDlg::OnInitDialog()
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
	WORD vendor;
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	m_list.SetExtendedStyle(dwStyle);
	
	if(OnMyIo()==0)
	{
		MessageBox("開啟IO驅動程式失敗","錯誤",MB_OK | MB_ICONSTOP);
		OnCancel();
		return FALSE;
	}
	
	m_DetailDlg = new CDetaildlg;
	
	if(Search_Device(0x0c,0x05,0x05,&vendor,&bus,&dev,&func)==0) //SMBus
	{
		MessageBox("找不到SMBus控制器","錯誤",MB_OK | MB_ICONSTOP);
		OnCancel();
		return FALSE;
	}
	
	if(vendor == 0x10DE)
	{//NVidia
		smb_type = 0;
	}
	else if(vendor == 0x8086)
	{//Intel
		smb_type = 1;
	}
	else
	{
		MessageBox("本程式只支援NVidia與Intel的SMBus","Error",MB_OK | MB_ICONSTOP);
		OnCancel();
	}
	
	detect_device(); //偵測有幾個裝置
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinSMBDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWinSMBDlg::OnPaint() 
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
HCURSOR CWinSMBDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWinSMBDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnOK();
	*pResult = 0;
}

void CWinSMBDlg::OnOK() 
{
	// TODO: Add extra validation here
	POSITION p = m_list.GetFirstSelectedItemPosition()-1; //start from 0
	char buf[10];
	
	if((int)p >= 0)
	{
		DWORD addr;
		//addr
		m_list.GetItemText((int)p,1,buf,sizeof(buf));
		buf[2] = '\0';
		hextoi(buf,&addr);
		m_DetailDlg->addr = (BYTE)addr;
		m_DetailDlg->DoModal();
	}
	//CDialog::OnOK();
}

BOOL CWinSMBDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	OffMyIo(); //關閉IO driver
	return CDialog::DestroyWindow();
}

void CWinSMBDlg::Write_list(int posi, int col,char *value)
{
	LV_ITEM data;

	if(col==0)
	{
		data.mask = LVIF_TEXT;
		data.state = 0;
		data.stateMask = 0;
		data.iItem = posi;
		data.iImage = 0;
		data.iSubItem = 0;
		data.pszText = value;
		m_list.InsertItem(&data);
	}
	else
	{
		m_list.SetItemText(posi,col,value);
	}
}

void CWinSMBDlg::detect_device(void)
{
	BYTE addr,data;
	int i,p,cnt,len;
	char buf[20];
	
	//加上欄位資料
	for(i = 0; i < 3; i++)
	{
		memset(buf,0,sizeof(buf));
		switch(i)
		{
			case 0:
				strcpy(buf,"裝置號碼");
				len=80;
				break;
			case 1:
				strcpy(buf,"位址");
				len=70;
				break;
			case 2:
				strcpy(buf,"第一筆資料");
				len=120;
				break;
		}
		m_list.InsertColumn(i,buf,LVCFMT_LEFT,len);
	}
//	device_qty = 0;
//	memset(devs,0,sizeof(devs));
	
		
	p = 0;
	cnt = 0;
	for(addr = 0xA0; addr < 0xAf; addr+=2)
	{
		if(smb_type == 0)
		{//NVidia
			data = read_nv_slave_data(addr,0);
		}
		else
		{//intel
			data = read_it_slave_data(addr,0);
		}
		
		if(data != 0xff)
		{
			sprintf(buf,"%d",cnt+1);
			Write_list(p,0,buf);
			sprintf(buf,"%02Xh",addr);
			Write_list(p,1,buf);
			sprintf(buf,"%02Xh",data);
			Write_list(p,2,buf);
			
			cnt++;
			p++;
		}
	}
	
	//AfxMessageBox("done");
}

BYTE read_nv_slave_data(BYTE slave_address, BYTE offset)
{
	BYTE temp,tmp;//protocol,
	int timeout = 0;

	// for Nvidia
	write_io_byte((SMB_base+NVIDIA_SMB_STS),NVIDIA_SMB_STS_STATUS);

	//I2C_SMBUS_BYTE_DATA:
	write_io_byte((SMB_base+NVIDIA_SMB_CMD),offset);
	
	write_io_byte((SMB_base+NVIDIA_SMB_ADDR),(BYTE)(slave_address|0x01));

	write_io_byte((SMB_base+NVIDIA_SMB_PRTCL),0x07);

	do{
		delay1us(10);
		read_io_byte(SMB_base+NVIDIA_SMB_STS,&temp);

	} while (((temp & NVIDIA_SMB_STS_DONE) == 0) && (timeout++ < MAX_TIMEOUT));

	if(timeout > MAX_TIMEOUT)
	{
		return 0xff;
	}
	read_io_byte(SMB_base+NVIDIA_SMB_DATA,&tmp);

	return tmp;
}

BYTE read_it_slave_data(BYTE slave_address, BYTE offset)
{
	BYTE temp;
	int timeout=0;
	//clear all status bits
	write_io_byte((SMBHSTSTS + SMB_base),0x1E);
		
	// write the offset
	write_io_byte((SMBHSTCMD + SMB_base),(BYTE)offset);
	
	// write the slave address 
	write_io_byte((SMBHSTADD + SMB_base),(BYTE)(slave_address|1));
	
	//Read byte protocol and Start
	write_io_byte((SMBHSTCNT + SMB_base),0x48);
	

	while(1)
	{
		delay1us(10);
		read_io_byte(SMB_base + SMBHSTSTS,&temp);
		//if((temp & 0x1E)==0x1E)
		if((temp & 0x42)==0x42)
		{
			break;
		}
		timeout++;
		
		if(timeout > MAX_TIMEOUT)
		{
			//	sprintf(buf,"addr=%x timeout1",slave_address);
			//	AfxMessageBox(buf);
			return 0xff;
		}
	}
		
	if((temp & 0x1c)==0)
	{//ok
		read_io_byte((SMBHSTDAT0 + SMB_base),&temp);
			//sprintf(buf,"addr=%x data=%x",slave_address,temp);
			//AfxMessageBox(buf);
		return temp;
	}
	
		//sprintf(buf,"addr=%x timeout2",slave_address);
		//AfxMessageBox(buf);
	return 0xff;	
}

BOOL Search_Device( BYTE Classtype,BYTE Subclass1,BYTE Subclass2,WORD *vd,BYTE *Bus, BYTE *Dev, BYTE *Func )
{
	WORD i;
	BYTE gclass,tp,gsclass,j,k;
	WORD vendor,dvc;
		//char buf[100];
	
	for(i = 0; i < 256; i++)
	{
		for(j = 0; j < 32; j++)
		{
			for(k = 0; k < 8; k++)
			{
				if(k == 0)
				{
					read_pci_byte((BYTE)i,j,k,0x0e,&tp);
					tp &= 0x80;
				}
				read_pci_word((BYTE)i,j,k,0x0,&vendor);
				if(vendor != 0xffff)//If vendor is valid
				{
					read_pci_word((BYTE)i,j,k,0x2,&dvc);
					read_pci_byte((BYTE)i,j,k,0x0B,&gclass);
					if(gclass == Classtype)//If find device
					{
						read_pci_byte((BYTE)i,j,k,0x0A,&gsclass);
						if(gsclass == Subclass1 || gsclass == Subclass2)
						{//Log Bus, Device, Func
							*Bus = (BYTE)i;
							*Dev = (BYTE)j;
							*Func = (BYTE)k;
							*vd = vendor;
							if(vendor == 0x10de)
							{
								if(dvc == 0x52)
								{
									read_pci_word(bus,dev,func,0x50,&SMB_base);
									SMB_base &= 0xfffe;
								}
							}
							else if(vendor == 0x8086)
							{
								read_pci_word(bus,dev,func,0x20,&SMB_base);
								SMB_base &= 0xfffe;
									//sprintf(buf,"b=%d d=%d f=%d %x",bus,dev,func,SMB_base);
									//AfxMessageBox(buf);
							}
							else
							{
								return 0;
							}
							
							return 1;
						}
					}
				}//end of if(vendor != 0xffff)
				if(k == 0 && tp != 0x80)
				{
					break;
				}
			}//end of for(k = 0; k < 8; k++)
		}//end of for(j = 0; j < 32; j++)
	}//end of for(i = 0; i < 256; i++)
	return 0;
}

void delay1us(DWORD delay)
{
	LARGE_INTEGER start,end,Freq;
 
	QueryPerformanceFrequency(&Freq);                      
	//end.QuadPart = (delay*Freq.QuadPart)/1000;        //1ms
	end.QuadPart = (delay*Freq.QuadPart)/1000000;        //1us
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
