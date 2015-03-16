// SMBIOSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "string.h"
#include "SMBIOS.h"
#include "def_smbios.h"
#include "myio.h"
#include "SMBIOSDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int tp_cnt,data_len,length_err;
DWORD SMB_addr;
DWORD tp_Addrs[100][2];
BYTE data_buf[0x1000];
float smb_ver;
int GetProcessorString(WORD PFamily);

extern char TableName[][33];
extern char tp0_str1[][90];
extern char tp0_str2[][34];
extern char tp0_str3[][52];
extern char tp1_str1[][18];
extern char tp2_str1[][55];
extern char tp2_str2[][49];
extern char tp3_str1[][22];
extern char tp3_str2[][16];
extern char tp3_str3[][30];
extern char tp4_str1[][18];
extern char tp4_str2[][76];
extern char tp4_str3[][9];
extern char tp4_str4[][23];
extern char tp4_str5[][15];
extern char tp5_str1[][13];
extern char tp5_str2[][28];
extern char tp5_str3[][23];
extern char tp5_str4[][8];
extern char tp6_str1[][15];
extern char tp6_str2[][52];
extern char tp7_str1[][15];
extern char tp7_str2[][15];
extern char tp7_str3[][12];
extern char tp7_str4[][23];
extern char tp8_str1[][33];
extern char tp8_str2[][31];
extern char tp9_str1[][29];
extern char tp9_str2[][11];
extern char tp9_str3[][10];
extern char tp9_str4[][13];
extern char tp9_str5[][43];
extern char tp9_str6[][55];
extern char tp10_str1[][16];
extern char tp15_str1[][78];
extern char tp15_str2[][38];
extern char tp16_str1[][28];
extern char tp16_str2[][16];
extern char tp16_str3[][15];
extern char tp17_str1[][17];
extern char tp17_str2[][13];
extern char tp17_str3[][14];
extern char tp18_str1[][27];
extern char tp18_str2[][23];
extern char tp18_str3[][14];
extern char tp21_str1[][15];
extern char tp21_str2[][23];
extern char tp22_str1[][21];
extern char tp26_str1[][25];
extern char tp27_str1[][25];
extern char tp28_str1[][25];
extern char tp29_str1[][25];
extern char tp34_str1[][28];
extern char tp34_str2[][9];
extern char tp37_str1[][9];
extern char tp38_str1[][39];
extern char tp39_str1[][10];
extern char tp39_str2[][64];
extern char tp39_str3[][17];

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
// CSMBIOSDlg dialog

CSMBIOSDlg::CSMBIOSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSMBIOSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSMBIOSDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSMBIOSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSMBIOSDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_STATUS_STATIC, m_status);
	DDX_Control(pDX, IDC_REPORT_LIST, m_report);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSMBIOSDlg, CDialog)
	//{{AFX_MSG_MAP(CSMBIOSDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMBIOSDlg message handlers

BOOL CSMBIOSDlg::OnInitDialog()
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
	int i;
	char buf[200];
	
	
	DWORD dwStyle = m_report.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	m_report.SetExtendedStyle(dwStyle);
	
	ShowStatus("Initial IO Driver....");
	if(OnMyIo()==0)
	{
		MessageBox("Fail to open MyIO","Error",MB_OK | MB_ICONSTOP);
		return TRUE;
	}
	
	ZeroMemory(tp_Addrs,sizeof(tp_Addrs));
	
	if(FindEntry()==0)
	{
		for(i = 0; i < tp_cnt; i++)
		{
			if(tp_Addrs[i][0] == 0)
			{
				sprintf(buf,"%s",TableName[tp_Addrs[i][0]]);
			}
			else if(tp_Addrs[i][0] > 0 && tp_Addrs[i][0] <= 40)
			{
				sprintf(buf,"%d - %s",tp_Addrs[i][0]-1,TableName[tp_Addrs[i][0]]);
			}
			else if(tp_Addrs[i][0] == 128)
			{
				strcpy(buf,"127 - End-of-table");
			}
			else if(tp_Addrs[i][0] == 127)
			{
				strcpy(buf,"126 - Inactive");
			}
			else
			{
				sprintf(buf,"%d - OEM",tp_Addrs[i][0]-1);
			}
			m_list.AddString(buf);
		}
		
		m_list.EnableWindow(TRUE);
		m_list.SetCurSel(0);
		OnSelchangeList();
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSMBIOSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSMBIOSDlg::OnPaint() 
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
HCURSOR CSMBIOSDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CSMBIOSDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	OffMyIo();
	
	return CDialog::DestroyWindow();
}

void CSMBIOSDlg::OnSelchangeList() 
{
	// TODO: Add your control notification handler code here
	int sld,i,nColumnCount;
	
	sld = m_list.GetCurSel();
	if(sld != -1)
	{
		//讀取
		SMB_addr = tp_Addrs[sld][1];
		
		//清除list原本的東西
		nColumnCount = m_report.GetHeaderCtrl()->GetItemCount();
		for(i = 0; i < nColumnCount; i++)
		{
			m_report.DeleteColumn(0);
		}
			
		m_report.DeleteAllItems();
	
		//加上欄位資料
		m_report.InsertColumn(0,"Name",LVCFMT_LEFT,200);
		m_report.InsertColumn(1,"Data",LVCFMT_LEFT,300);
		
		//顯示
		switch(tp_Addrs[sld][0])
		{
			case 0:
				ReportEntry();
				break;
			case 1:
				ReportTp0();
				break;
			case 2:
				ReportTp1();
				break;
			case 3:
				ReportTp2();
				break;
			case 4:
				ReportTp3();
				break;
			case 5:
				ReportTp4();
				break;
			case 6:
				ReportTp5();
				break;
			case 7:
				ReportTp6();
				break;
			case 8:
				ReportTp7();
				break;
			case 9:
				ReportTp8();
				break;
			case 10:
				ReportTp9();
				break;
			case 11:
				ReportTp10();
				break;
			case 12:
				ReportTp11();
				break;
			case 13:
				ReportTp12();
				break;
			case 14:
				ReportTp13();
				break;
			case 15:
				ReportTp14();
				break;
			case 16:
				ReportTp15();
				break;
			case 17:
				ReportTp16();
				break;
			case 18:
				ReportTp17();
				break;
			case 19:
				ReportTp18();
				break;
			case 20:
				ReportTp19();
				break;
			case 21:
				ReportTp20();
				break;
			case 22:
				ReportTp21();
				break;
			case 23:
				ReportTp22();
				break;
			case 24:
				ReportTp23();
				break;
			case 25:
				ReportTp24();
				break;
			case 26:
				ReportTp25();
				break;
			case 27:
				ReportTp26();
				break;
			case 28:
				ReportTp27();
				break;
			case 29:
				ReportTp28();
				break;
			case 30:
				ReportTp29();
				break;
			case 31:
				ReportTp30();
				break;
			case 33:
				ReportTp32();
				break;
			case 34:
				ReportTp33();
				break;
			case 35:
				ReportTp34();
				break;
			case 36:
				ReportTp35();
				break;
			case 37:
				ReportTp36();
				break;
			case 38:
				ReportTp37();
				break;
			case 39:
				ReportTp38();
				break;
			case 40:
				ReportTp39();
				break;
			case 127:
				ReportTp126();
				break;
			case 128:
				ReportEnd();
				break;
			default:
				ReportOEM();
				break;
		}
	}
	ShowStatus("done");
}

int CSMBIOSDlg::FindEntry(void)
{
	DWORD dwMemVal,min;
	int i,j,len;
	char bb[10];

//	BYTE data8;
	
	
	//找出SMBIOS entry point
	for(SMB_addr = 0xf0000; SMB_addr < 0xfffff; SMB_addr+=4)
	{
		read_mem_dword(SMB_addr, &dwMemVal);
		if(dwMemVal==0x5F4d535F) //顛倒的_SM_
		{
			tp_Addrs[0][0] = 0; //tp_Addrs是實際值+1, 所以[0][0] = -1
			tp_Addrs[0][1] = SMB_addr;
			
			ReadEntry();
			
			SMB_addr = 0;
			for(i = 0; i < 4; i++)
			{
				SMB_addr <<= 8;
				SMB_addr |= data_buf[27-i];
			}
			
			sprintf(bb,"%d",data_buf[6]);
			smb_ver = (float)atof(bb);
			sprintf(bb,"0.%d",data_buf[7]);
			smb_ver += (float)atof(bb);
				
			//找出各個type的entry address
			tp_cnt = 1;
			while(1)
			{
				read_mem_dword(SMB_addr, &dwMemVal);
				tp_Addrs[tp_cnt][0] = (dwMemVal & 0xff)+1; //為了使用string table才多加1
				tp_Addrs[tp_cnt][1] = SMB_addr;
					
				tp_cnt++;
				if(tp_Addrs[tp_cnt-1][0] == 128)
				{
					break;
				}
				len = (int)((BYTE)(dwMemVal >> 8));
				SMB_addr += len;
				Jump_str();
			}
			
			//排序
			
			for(i = 1; i < tp_cnt; i++)
			{
				min = tp_Addrs[i][0];
				for(j = i; j < tp_cnt; j++)
				{
					if(min > tp_Addrs[j][0])
					{
						tp_Addrs[i][0] = tp_Addrs[j][0];
						tp_Addrs[j][0] = min;
						min = tp_Addrs[i][1];
						tp_Addrs[i][1] = tp_Addrs[j][1];
						tp_Addrs[j][1] = min;
						min = tp_Addrs[i][0];
					}
				}
			}
			
			//Read_Entry();
			
			return 0;
		}
	}
	return 1;
}

void CSMBIOSDlg::ReadEntry(void)
{
	int i;
	DWORD dwMemVal;
	
	data_len = 0;
	ZeroMemory(data_buf,sizeof(data_buf));
	for(i = 0; i <= 0x1E; i+=4)
	{
//		data8 = MemRead8(EntryAddr+i);
//		data_buf[data_len] = data8;
//		data_len++;
		
		//read_mem_dword((PBYTE)SMB_addr, &dwMemVal);
		//len = (BYTE)(dwMemVal >> 8);
		read_mem_dword((SMB_addr+i), &dwMemVal);
		data_buf[i] = (BYTE)dwMemVal;
		data_buf[i+1] = (BYTE)(dwMemVal >> 8);
		data_buf[i+2] = (BYTE)(dwMemVal >> 16);
		data_buf[i+3] = (BYTE)(dwMemVal >> 24);
		data_len+=4;
	}
}

void CSMBIOSDlg::Jump_str(void)
{
	int j;
	BOOL flag;
	BYTE vv;
	DWORD	dwMemVal;
	
//	i = 0;
	flag = FALSE;
	while(1)
	{
		read_mem_dword(SMB_addr, &dwMemVal);
		for(j = 0; j < 4; j++)
		{
			vv = (BYTE)(dwMemVal >> (j*8));
			if(vv != 0)
			{
				flag = FALSE;
			}
			else
			{
				if(flag == TRUE)
				{//兩個00
					SMB_addr += j+1; //移到00的下一個，下一個應該是另一起點
					return;
				}
				else
				{
					flag = TRUE;
				}
				//break;
			}
		}
		SMB_addr+=4;
	}
}

int CSMBIOSDlg::FindTable(int sld)
{
	DWORD data32;
	//BYTE data8;
	int i,len,flag=0;
	
	read_mem_dword(SMB_addr,&data32);
	
	if(sld != -1)
	{//要進行type篩選
		if((BYTE)sld != (BYTE)data32)
		{//不是想要的
			return -1;
		}
	}
	
	if((BYTE)data32 >= 40) //end or OEM type
	{
		flag = 1;
	}
	
	data_len = 0;
	ZeroMemory(data_buf,sizeof(data_buf));
	
	//得到這個type的總大小
	len = (int)((BYTE)(data32 >> 8));
	
	//讀取資料
	for(i = 0; i < len; i++)
	{
		read_mem_dword(SMB_addr,&data32);
		data_buf[data_len] = (BYTE)data32;
		data_len++;
		SMB_addr++;
	}
	
	//判斷長度對不對
	length_err=0;
	switch(sld)
	{
		case 1:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4)
			{
				if(len < 0x1b)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.1)
			{
				if(len < 0x19)
				{
					length_err=1;
				}
			}
			break;
		case 3:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3)
			{
				if(len < 0x16)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.1)
			{
				if(len < 0xd)
				{
					length_err=1;
				}
			}
			break;
		case 4:
			if(smb_ver == 2.6)
			{
				if(len < 0x29)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.5)
			{
				if(len < 0x27)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.4 || smb_ver == 2.3)
			{
				if(len < 0x23)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.1)
			{
				if(len < 0x20)
				{
					length_err=1;
				}
			}
			break;
		case 5:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len <= (0xf+2*data_buf[0xe]))
				{
					length_err=1;
				}
			}
			break;
		case 7:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0xf)
				{
					length_err=1;
				}
			}
			break;
		case 9:
			if(smb_ver == 2.6)
			{
				if(len < 0x11)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0xd)
				{
					length_err=1;
				}
			}
			break;
		case 13:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0x16)
				{
					length_err=1;
				}
			}
			break;
		case 15:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0x15)
				{
					length_err=1;
				}
			}
			break;
		case 16:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0xf)
				{
					length_err=1;
				}
			}
			break;
		case 17:
			if(smb_ver == 2.6)
			{
				if(len < 0x1c)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3)
			{
				if(len < 0x1b)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.1)
			{
				if(len < 0x16)
				{
					length_err=1;
				}
			}
			break;
		case 18:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0x14)
				{
					length_err=1;
				}
			}
			break;
		case 19:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0xf)
				{
					length_err=1;
				}
			}
			break;
		case 20:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0x13)
				{
					length_err=1;
				}
			}
			break;
		case 21:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.1)
			{
				if(len < 0x7)
				{
					length_err=1;
				}
			}
			break;
		case 22:
			if(smb_ver == 2.6 || smb_ver == 2.5 || smb_ver == 2.4 || smb_ver == 2.3 || smb_ver == 2.2)
			{
				if(len < 0x1a)
				{
					length_err=1;
				}
			}
			else if(smb_ver == 2.1)
			{
				if(len < 0x10)
				{
					length_err=1;
				}
			}
			break;
	}
	
	return flag;
	
}

void CSMBIOSDlg::GetAttachedString(char *str,int sw)
{
	int cnt;
	BYTE data;
//	DWORD dwMemVal;
	DWORD tmp_addr=SMB_addr;
	
	if(sw==0)
	{//沒有字串
		strcpy(str,"null\0");
		return;
	}
	
	//從sw來決定抓第幾個str
	if(sw != 1)
	{
		cnt = 1;
		while(1)
		{
			read_mem_byte(tmp_addr,&data);
			if(!data)
			{
				cnt++;
				if(cnt == sw)
				{
					tmp_addr++;
					break;
				}
			}
			tmp_addr++;
		}
	}
	
	cnt = 0;
	memset(str,0,sizeof(str));
	while(1)
	{
		read_mem_byte(tmp_addr,&data);
		str[cnt] = data;
		if(!data)
		{
			return;
		}
		tmp_addr++;
		cnt++;
	}
	
	/*cnt = 0;
	ZeroMemory(str,sizeof(str));
	while(1)
	{
		read_mem_dword(SMB_addr, &dwMemVal);
		str[cnt] = (char)dwMemVal;
		if(((BYTE)dwMemVal)==0)
		{
			SMB_addr++; //移到下一個字串起點
			return;
		}
		SMB_addr++;
		cnt++;
	}*/
}

void CSMBIOSDlg::ReportEntry(void)
{
	char tmp[1024];
	int i=0;
	BYTE vv;
	struct SMB_ENTRY_POINT *SMB_entry;
	
	ReadEntry();
	
	SMB_entry = (SMB_ENTRY_POINT *)data_buf;
	
	WriteReport(i,0,"Anchor String");
	sprintf(tmp,"%c%c%c%c",SMB_entry->anchor[0],SMB_entry->anchor[1],SMB_entry->anchor[2],SMB_entry->anchor[3]);
	WriteReport(i,1,tmp);
	i++;
			
	WriteReport(i,0,"Entry Point Structure Checksum");
	sprintf(tmp,"0x%02X",SMB_entry->checksum);
	WriteReport(i,1,tmp);
	i++;
			
	WriteReport(i,0,"Entry Point Length");
	sprintf(tmp,"0x%02X",SMB_entry->length);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"SMBIOS version");
	sprintf(tmp,"%d.%d",SMB_entry->majorVer,SMB_entry->minorVer);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Maximum Structure Size");
	sprintf(tmp,"0x%04X",SMB_entry->maxSize);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Entry Point Revision");
	sprintf(tmp,"0x%02X",SMB_entry->entryRev);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Formatted Area");
	sprintf(tmp,"0x%02X,0x%02X,0x%02X,0x%02X,0x%02X",SMB_entry->FA[0],SMB_entry->FA[1],SMB_entry->FA[2],SMB_entry->FA[3],SMB_entry->FA[4]);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Intermediate anchor string");
	sprintf(tmp,"%c%c%c%c%c",SMB_entry->dmi_anchor[0],SMB_entry->dmi_anchor[1],SMB_entry->dmi_anchor[2],SMB_entry->dmi_anchor[3],SMB_entry->dmi_anchor[4]);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Intermediate Checksum");
	sprintf(tmp,"0x%02X",SMB_entry->dmi_checksum);
	WriteReport(i,1,tmp);
	i++;
			
	WriteReport(i,0,"Structure Table Length");
	sprintf(tmp,"%d(0x%04X)",SMB_entry->tableLength,SMB_entry->tableLength);
	WriteReport(i,1,tmp);
	i++;
			
	WriteReport(i,0,"Structure Table Address");
	sprintf(tmp,"0x%08lX",SMB_entry->tableAddress);
	WriteReport(i,1,tmp);
	i++;
			
	WriteReport(i,0,"Number of SMBIOS Structure");
	sprintf(tmp,"%d(0x%04X)",SMB_entry->structureCount,SMB_entry->structureCount);
	WriteReport(i,1,tmp);
	i++;
			
	WriteReport(i,0,"SMBIOS BCD Revision");
	vv = SMB_entry->bcdRevision & 0x0F;
	sprintf(tmp,"%d.%d(0x%02X)",(BYTE)(SMB_entry->bcdRevision>>4),vv,SMB_entry->bcdRevision);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp0(void)
{
	char tmp[1024];
	int i=0,j,k;
	DWORD dd;
	struct SMBStructBIOSInformation *SMB_tp0;
	
	if(FindTable(0) == -1)
	{
		MessageBox("Something was wrong when reading Tp0","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp0 = (SMBStructBIOSInformation *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp0->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp0->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp0->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"BIOS Vendor");
	GetAttachedString(tmp,SMB_tp0->vendor);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp0->vendor);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"BIOS Version");
	GetAttachedString(tmp,SMB_tp0->version);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp0->version);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"BIOS Starting Address Segment");
	sprintf(tmp,"0x%04X",SMB_tp0->startSegment);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"BIOS Release Date");
	GetAttachedString(tmp,SMB_tp0->releaseDate);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp0->releaseDate);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"BIOS ROM Size");
	sprintf(tmp,"%ldKB (0x%02X)",(SMB_tp0->romSize+1)*64,SMB_tp0->romSize);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"BIOS Characteristics");
	sprintf(tmp,"%02X %02X %02X %02X %02X %02X %02X %02X [HEX];MSB->LSB",SMB_tp0->characteristics[7],SMB_tp0->characteristics[6],SMB_tp0->characteristics[5],SMB_tp0->characteristics[4],SMB_tp0->characteristics[3],SMB_tp0->characteristics[2],SMB_tp0->characteristics[1],SMB_tp0->characteristics[0]);
	WriteReport(i,1,tmp);
	i++;
	
	for(k = 0; k < 2; k++)
	{
		dd = SMB_tp0->characteristics[k*4];
		for(j = 3; j >= 0; j--)
		{
			dd <<= 8;
			dd |= SMB_tp0->characteristics[j+k*4];
		}
	
		for(j = 0; j < 32; j++)
		{
			if(dd & 0x1)
			{
				WriteReport(i,0," ");
				sprintf(tmp,"bit%d: %s",j+k*32,tp0_str1[j+k*32]);
				WriteReport(i,1,tmp);
				i++;
			}
			dd >>= 1;
		}
	}
	
	if(SMB_tp0->header.length >= 0x13)
	{
		WriteReport(i,0,"BIOS Characteristics Extension Byte 1");
		sprintf(tmp,"0x%02X",SMB_tp0->characteristicsExByte1);
		WriteReport(i,1,tmp);
		i++;
		
		dd = SMB_tp0->characteristicsExByte1;
	
		for(j = 0; j < 8; j++)
		{
			if(dd & 0x1)
			{
				WriteReport(i,0," ");
				sprintf(tmp,"bit%d: %s",j,tp0_str2[j]);
				WriteReport(i,1,tmp);
				i++;
			}
			dd >>= 1;
		}
		
	}
	
	if(SMB_tp0->header.length >= 0x14)
	{
		WriteReport(i,0,"BIOS Characteristics Extension Byte 2");
		sprintf(tmp,"0x%02X",SMB_tp0->characteristicsExByte2);
		WriteReport(i,1,tmp);
		i++;
		dd = SMB_tp0->characteristicsExByte2;
	
		for(j = 0; j < 8; j++)
		{
			if(dd & 0x1)
			{
				WriteReport(i,0," ");
				sprintf(tmp,"bit%d: %s",j,tp0_str3[j]);
				WriteReport(i,1,tmp);
				i++;
			}
			dd >>= 1;
		}
		
	}
	
	if(SMB_tp0->header.length >= 0x15)
	{
		WriteReport(i,0,"System BIOS Release");
		sprintf(tmp,"%d.%d",SMB_tp0->biosMajorRelease,SMB_tp0->biosMinorRelease);
		WriteReport(i,1,tmp);
		i++;
	}
}

void CSMBIOSDlg::ReportTp1(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructSystemInformation *SMB_tp1;
	
	if(FindTable(1) == -1)
	{
		MessageBox("Something was wrong when reading Tp1","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp1 = (SMBStructSystemInformation *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp1->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp1->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp1->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Manufacturer");
	GetAttachedString(tmp,SMB_tp1->manufacturer);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp1->manufacturer);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Product Name");
	GetAttachedString(tmp,SMB_tp1->productName);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp1->productName);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Version");
	GetAttachedString(tmp,SMB_tp1->version);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp1->version);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Serial Number");
	GetAttachedString(tmp,SMB_tp1->serialNumber);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp1->serialNumber);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"UUID");
	sprintf(tmp,"%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X [HEX]; MSB -> LSB",SMB_tp1->uuids[15],SMB_tp1->uuids[14],SMB_tp1->uuids[13],SMB_tp1->uuids[12],SMB_tp1->uuids[11],SMB_tp1->uuids[10],SMB_tp1->uuids[9],SMB_tp1->uuids[8],SMB_tp1->uuids[7],SMB_tp1->uuids[6],SMB_tp1->uuids[5],SMB_tp1->uuids[4],SMB_tp1->uuids[3],SMB_tp1->uuids[2],SMB_tp1->uuids[1],SMB_tp1->uuids[0]);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Wake-up Type");
	sprintf(tmp,"%s (0x%02X)",tp1_str1[SMB_tp1->wakeupType],SMB_tp1->wakeupType);
	WriteReport(i,1,tmp);
	i++;
		
	if(smb_ver >= 2.4)
	{
		WriteReport(i,0,"SKU Number");
		GetAttachedString(tmp,SMB_tp1->skuNumber);
		sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp1->skuNumber);
		WriteReport(i,1,tmp);
		i++;

		WriteReport(i,0,"Family");
		GetAttachedString(tmp,SMB_tp1->family);
		sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp1->family);
		WriteReport(i,1,tmp);
		i++;
	}
	
}

void CSMBIOSDlg::ReportTp2(void)
{
	char tmp[1024],bb[100];
	int i=0,j;
	WORD dd;
	struct SMBStructBaseBoardInformation *SMB_tp2;
	
	if(FindTable(2) == -1)
	{
		MessageBox("Something was wrong when reading Tp2","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp2 = (SMBStructBaseBoardInformation *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp2->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp2->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp2->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Manufacturer");
	GetAttachedString(tmp,SMB_tp2->manufacturer);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp2->manufacturer);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Product Name");
	GetAttachedString(tmp,SMB_tp2->product);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp2->product);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Version");
	GetAttachedString(tmp,SMB_tp2->version);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp2->version);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Serial Number");
	GetAttachedString(tmp,SMB_tp2->serialNumber);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp2->serialNumber);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Asset Tag");
	GetAttachedString(tmp,SMB_tp2->assetTag);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp2->assetTag);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Feature Flags");
	sprintf(tmp,"0x%02X",SMB_tp2->featureFlags);
	WriteReport(i,1,tmp);
	i++;
		
	dd = SMB_tp2->featureFlags;
	for(j = 0; j < 5; j++)
	{
		if(dd & 0x1)
		{
			WriteReport(i,0," ");
			sprintf(tmp,"bit%d: %s",j,tp2_str1[j]);
			WriteReport(i,1,tmp);
			i++;
		}
		dd >>= 1;
	}
	
	WriteReport(i,0,"Location in Chassis");
	GetAttachedString(tmp,SMB_tp2->locationInChassis);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp2->locationInChassis);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Chassis Handle");
	sprintf(tmp,"0x%04X",SMB_tp2->chassisHandle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Board Type");
	sprintf(tmp,"%s (0x%02X)",tp2_str2[SMB_tp2->boardType],SMB_tp2->boardType);
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0,"Number of Contained Object Handles");
	sprintf(tmp,"0x%02X",SMB_tp2->numberOfContainObjectHandles);
	WriteReport(i,1,tmp);
	i++;
	
	for(j = 0; j < SMB_tp2->numberOfContainObjectHandles; j++)
	{
		sprintf(bb,"Contained Object Handle(%d)",j+1);
		WriteReport(i,0,bb);
		sprintf(tmp,"0x%04X",SMB_tp2->containedObjectHandles[j]);
		WriteReport(i,1,tmp);
		i++;
	}
}

void CSMBIOSDlg::ReportTp3(void)
{
	char tmp[1024],bb[100];
	int i=0,j,k;
	struct SMBStructSystemEnclosure *SMB_tp3;
	
	if(FindTable(3) == -1)
	{
		MessageBox("Something was wrong when reading Tp3","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp3 = (SMBStructSystemEnclosure *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp3->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp3->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp3->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Manufacturer");
	GetAttachedString(tmp,SMB_tp3->manufacturer);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp3->manufacturer);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Type");
	if(SMB_tp3->type & 0x80)
	{
		sprintf(tmp,"Chassis lock present(0x%02X)",SMB_tp3->type);
	}
	else
	{
		sprintf(tmp,"%s (0x%02X)",tp3_str1[SMB_tp3->type],SMB_tp3->type);
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Version");
	GetAttachedString(tmp,SMB_tp3->version);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp3->version);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Serial Number");
	GetAttachedString(tmp,SMB_tp3->serialNumber);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp3->serialNumber);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Asset Tag Number");
	GetAttachedString(tmp,SMB_tp3->assetTagNumber);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp3->assetTagNumber);
	WriteReport(i,1,tmp);
	i++;
	
	if(smb_ver >= 2.1)
	{
		WriteReport(i,0,"Boot-up State");
		sprintf(tmp,"%s (0x%02X)",tp3_str2[SMB_tp3->bootupState],SMB_tp3->bootupState);
		WriteReport(i,1,tmp);
		i++;
	
		WriteReport(i,0,"Power Supply State");
		sprintf(tmp,"%s (0x%02X)",tp3_str2[SMB_tp3->powerSupplyState],SMB_tp3->powerSupplyState);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Thermal State");
		sprintf(tmp,"%s (0x%02X)",tp3_str2[SMB_tp3->thermalState],SMB_tp3->thermalState);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Security State");
		sprintf(tmp,"%s (0x%02X)",tp3_str3[SMB_tp3->securityStatus],SMB_tp3->securityStatus);
		WriteReport(i,1,tmp);
		i++;
	}
	
	if(smb_ver >= 2.3)
	{
		WriteReport(i,0,"OEM-defined");
		sprintf(tmp,"0x%08lX",SMB_tp3->oemDefined);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Height");
		sprintf(tmp,"0x%02X",SMB_tp3->height);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Number of Power Cords");
		sprintf(tmp,"0x%02X",SMB_tp3->numberOfCords);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Contained Element Count");
		sprintf(tmp,"0x%02X",SMB_tp3->containedElementCount);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Contained Element Record Length");
		sprintf(tmp,"0x%02X",SMB_tp3->containedElementRecordLength);
		WriteReport(i,1,tmp);
		i++;
		
		for(j = 0; j < SMB_tp3->containedElementCount; j++)
		{
			for(k = 0; k < SMB_tp3->containedElementRecordLength; k++)
			{
				sprintf(bb,"Contained Elements(%d)",((j*255)+k)+1);
				WriteReport(i,0,bb);
				sprintf(tmp,"0x%04X",SMB_tp3->containedElements[j][k]);
				WriteReport(i,1,tmp);
				i++;
			}
		}
	}
}

void CSMBIOSDlg::ReportTp4(void)
{
	char tmp[1024];
	int i=0,j;
	WORD dd;
	struct SMBStructProcessorInformation *SMB_tp4;
	
	if(FindTable(4) == -1)
	{
		MessageBox("Something was wrong when reading Tp4","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp4 = (SMBStructProcessorInformation *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp4->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp4->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp4->header.handle);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Socket Designation");
	GetAttachedString(tmp,SMB_tp4->socketDesignation);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp4->socketDesignation);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Processor Type");
	sprintf(tmp,"%s (0x%02X)",tp4_str1[SMB_tp4->processorType],SMB_tp4->processorType);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Processor family");
	j = GetProcessorString(SMB_tp4->processorFamily);
	if(j == -1)
	{
		j = 0;
	}
	
	sprintf(tmp,"%s (0x%02X)",tp4_str2[j],SMB_tp4->processorFamily);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Processor Manufacturer");
	GetAttachedString(tmp,SMB_tp4->manufacturer);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp4->manufacturer);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Processor ID");
	sprintf(tmp,"%02X %02X %02X %02X %02X %02X %02X %02X [HEX]; MSB->LSB",SMB_tp4->processorID[0],SMB_tp4->processorID[1],SMB_tp4->processorID[2],SMB_tp4->processorID[3],SMB_tp4->processorID[4],SMB_tp4->processorID[5],SMB_tp4->processorID[6],SMB_tp4->processorID[7]);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Processor Version");
	GetAttachedString(tmp,SMB_tp4->processorVersion);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp4->processorVersion);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Voltage");
	sprintf(tmp,"0x%02X",SMB_tp4->voltage);
	WriteReport(i,1,tmp);
	i++;
	
	dd = SMB_tp4->voltage;
	for(j = 0; j < 4; j++)
	{
		if(dd & 0x1)
		{
			WriteReport(i,0," ");
			sprintf(tmp,"bit%d: %s",j,tp4_str3[j]);
			WriteReport(i,1,tmp);
			i++;
		}
		dd >>= 1;
	}
		
	WriteReport(i,0,"External Clock");
	sprintf(tmp,"%dMhz (0x%04X)",SMB_tp4->externalClock,SMB_tp4->externalClock);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Max Speed");
	sprintf(tmp,"%dMHz (0x%04X)",SMB_tp4->maximumClock,SMB_tp4->maximumClock);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Current Speed");
	sprintf(tmp,"%dMHz (0x%04X)",SMB_tp4->currentClock,SMB_tp4->currentClock);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Status");
	sprintf(tmp,"0x%02X",SMB_tp4->status);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	strcpy(tmp,"bit7: Reserved");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	dd = SMB_tp4->status & 0x40;
	if(dd == 0x40)
	{
		strcpy(tmp,"bit6: CPU Socked Populated");
	}
	else
	{
		strcpy(tmp,"bit6: CPU Socked Unopulated");
	}
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0," ");
	strcpy(tmp,"bit5-3: Reserved");
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0," ");
	dd = SMB_tp4->status & 0x07;
	switch(dd)
	{
		case 0:
			strcpy(tmp,"bit2-0: CPU Status - Unknown");
			break;
		case 1:
			strcpy(tmp,"bit2-0: CPU Status - CPU Enable");
			break;
		case 2:
			strcpy(tmp,"bit2-0: CPU Status - CPU Disabled by User via BIOS Setup");
			break;
		case 3:
			strcpy(tmp,"bit2-0: CPU Status - CPU Disabled by BIOS(POST Error)");
			break;
		case 4:
			strcpy(tmp,"bit2-0: CPU Status - CPU is Idle, waiting to be enabled");
			break;
		case 5:
		case 6:
			strcpy(tmp,"bit2-0: CPU Status - Reserved");
			break;
		case 7:
			strcpy(tmp,"bit2-0: CPU Status - Other");
			break;
	}
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0,"Processor Upgrade");
	sprintf(tmp,"%s (0x%02X)",tp4_str4[SMB_tp4->processorUpgrade],SMB_tp4->processorUpgrade);
	WriteReport(i,1,tmp);
	i++;

	if(smb_ver >= 2.1)
	{
		WriteReport(i,0,"L1 Cache Handle");
		sprintf(tmp,"0x%04X",SMB_tp4->L1CacheHandle);
		WriteReport(i,1,tmp);
		i++;
	
		WriteReport(i,0,"L2 Cache Handle");
		sprintf(tmp,"0x%04X",SMB_tp4->L2CacheHandle);
		WriteReport(i,1,tmp);
		i++;
	
		WriteReport(i,0,"L3 Cache Handle");
		sprintf(tmp,"0x%04X",SMB_tp4->L3CacheHandle);
		WriteReport(i,1,tmp);
		i++;
	}
	
	if(smb_ver >= 2.3)
	{
		WriteReport(i,0,"Serial Number");
		GetAttachedString(tmp,SMB_tp4->serialNumber);
		sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp4->serialNumber);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Asset Tag");
		GetAttachedString(tmp,SMB_tp4->assetTag);
		sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp4->assetTag);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Part Number");
		GetAttachedString(tmp,SMB_tp4->partNumber);
		sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp4->partNumber);
		WriteReport(i,1,tmp);
		i++;
	}
	
	if(smb_ver >= 2.5)
	{
		WriteReport(i,0,"Core Count");
		sprintf(tmp,"0x%02X",SMB_tp4->coreCount);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Core Enable");
		sprintf(tmp,"0x%02X",SMB_tp4->coreEnabled);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Thread Count");
		sprintf(tmp,"0x%02X",SMB_tp4->threadCount);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Processor Characteristics");
		sprintf(tmp,"0x%04X",SMB_tp4->processorCharacteristics);
		WriteReport(i,1,tmp);
		i++;
			
		dd = SMB_tp4->processorCharacteristics;
		for(j = 0; j < 3; j++)
		{
			if(dd & 0x1)
			{
				WriteReport(i,0," ");
				sprintf(tmp,"bit%d: %s",j,tp4_str5[j]);
				WriteReport(i,1,tmp);
				i++;
			}
			dd >>= 1;
		}
	}
	
	if(smb_ver >= 2.6)
	{
		WriteReport(i,0,"Processor Family 2");
		j = GetProcessorString(SMB_tp4->processorFamily2);
		if(j == -1)
		{
			j = 0;
		}
		sprintf(tmp,"%s (0x%04X)\n",tp4_str2[j],SMB_tp4->processorFamily2);
		WriteReport(i,1,tmp);
	}
}

void CSMBIOSDlg::ReportTp5(void)
{
	char tmp[1024],bb[10];
	int i=0,j;
	BYTE dd;
	struct SMBStructMemoryController *SMB_tp5;
	
	if(FindTable(5) == -1)
	{
		MessageBox("Something was wrong when reading Tp5","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp5 = (SMBStructMemoryController *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp5->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp5->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp5->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Error Detecting Method");
	sprintf(tmp,"%s (0x%02X)",tp5_str1[SMB_tp5->errorDetectingMethod],SMB_tp5->errorDetectingMethod);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Error Correcting Capability");
	if(SMB_tp5->errorCorrectingCapability & 0x1)
	{
		sprintf(tmp,"%s (0x%02X)",tp5_str2[0],SMB_tp5->errorCorrectingCapability);
	}
	else if(SMB_tp5->errorCorrectingCapability & 0x2)
	{
		sprintf(tmp,"%s (0x%02X)",tp5_str2[1],SMB_tp5->errorCorrectingCapability);
	}
	else if(SMB_tp5->errorCorrectingCapability & 0x4)
	{
		sprintf(tmp,"%s (0x%02X)",tp5_str2[2],SMB_tp5->errorCorrectingCapability);
	}
	else if(SMB_tp5->errorCorrectingCapability & 0x8)
	{
		sprintf(tmp,"%s (0x%02X)",tp5_str2[3],SMB_tp5->errorCorrectingCapability);
	}
	else if(SMB_tp5->errorCorrectingCapability & 0x10)
	{
		sprintf(tmp,"%s (0x%02X)",tp5_str2[4],SMB_tp5->errorCorrectingCapability);
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Support Interleave");
	sprintf(tmp,"0x%02X",SMB_tp5->supportedInterleave);
	WriteReport(i,1,tmp);
	i++;
	
	dd = SMB_tp5->supportedInterleave;
	for(j = 0; j < 7; j++)
	{
		if(dd & 0x1)
		{
			WriteReport(i,0," ");
			sprintf(tmp,"%s",tp5_str3[j+1]);
			WriteReport(i,1,tmp);
			i++;
		}
		dd >>= 1;
	}
	
	WriteReport(i,0,"Current Interleave");
	sprintf(tmp,"%s (0x%02X)",tp5_str3[SMB_tp5->currentInterleave],SMB_tp5->currentInterleave);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Maximum Memory Module Size");
	sprintf(tmp,"%02X",SMB_tp5->maximumMemoryModuleSize);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Support Speeds");
	if(SMB_tp5->supportedSpeeds & 0x1)
	{
		sprintf(tmp,"%s (0x%04X)",tp5_str4[0],SMB_tp5->supportedSpeeds);
	}
	else if(SMB_tp5->supportedSpeeds & 0x2)
	{
		sprintf(tmp,"%s (0x%04X)",tp5_str4[1],SMB_tp5->supportedSpeeds);
	}
	else if(SMB_tp5->supportedSpeeds & 0x4)
	{
		sprintf(tmp,"%s (0x%04X)",tp5_str4[2],SMB_tp5->supportedSpeeds);
	}
	else if(SMB_tp5->supportedSpeeds & 0x8)
	{
		sprintf(tmp,"%s (0x%04X)",tp5_str4[3],SMB_tp5->supportedSpeeds);
	}
	else if(SMB_tp5->supportedSpeeds & 0x10)
	{
		sprintf(tmp,"%s (0x%04X)",tp5_str4[4],SMB_tp5->supportedSpeeds);
	}
	//sprintf(tmp,"0x%04X",SMB_tp5->supportedSpeeds);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Supported Memory Type");
	sprintf(tmp,"0x%04X",SMB_tp5->supportedMemoryTypes);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Memory Module Voltage");
	
	if((SMB_tp5->memoryModuleVoltage & 0x7) == 1)
	{
		sprintf(tmp,"5V (0x%02X)",SMB_tp5->memoryModuleVoltage);
	}
	else if((SMB_tp5->memoryModuleVoltage & 0x7) == 2)
	{
		sprintf(tmp,"3->3V (0x%02X)",SMB_tp5->memoryModuleVoltage);
	}
	else if((SMB_tp5->memoryModuleVoltage & 0x7) == 4)
	{
		sprintf(tmp,"2->9V (0x%02X)",SMB_tp5->memoryModuleVoltage);
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Number of Associated Memory Slots");
	sprintf(tmp,"0x%02X",SMB_tp5->numberOfAssociatedMemorySlot);
	WriteReport(i,1,tmp);
	i++;
	
	for(j = 0; j < SMB_tp5->numberOfAssociatedMemorySlot ;j++)
	{
		sprintf(bb,"Memory Module Configuration Handles(%d)",j+1);
		WriteReport(i,0,bb);
		sprintf(tmp,"0x%04X",SMB_tp5->memoryModuleConfigurationHandles[j]);
		WriteReport(i,1,tmp);
		i++;
	}
	
	if(smb_ver >= 2.1)
	{
		WriteReport(i,0,"Enabled Error Correcting Capabilities");
		//sprintf(tmp,"0x%02X",SMB_tp5->enabledErrorCorrectingCapabilites);
		if(SMB_tp5->enabledErrorCorrectingCapabilites & 0x1)
		{
			sprintf(tmp,"%s (0x%04X)",tp5_str4[0],SMB_tp5->enabledErrorCorrectingCapabilites);
		}
		else if(SMB_tp5->enabledErrorCorrectingCapabilites & 0x2)
		{
			sprintf(tmp,"%s (0x%04X)",tp5_str4[1],SMB_tp5->enabledErrorCorrectingCapabilites);
		}
		else if(SMB_tp5->enabledErrorCorrectingCapabilites & 0x4)
		{
			sprintf(tmp,"%s (0x%04X)",tp5_str4[2],SMB_tp5->enabledErrorCorrectingCapabilites);
		}
		else if(SMB_tp5->enabledErrorCorrectingCapabilites & 0x8)
		{
			sprintf(tmp,"%s (0x%04X)",tp5_str4[3],SMB_tp5->enabledErrorCorrectingCapabilites);
		}
		else if(SMB_tp5->enabledErrorCorrectingCapabilites & 0x10)
		{
			sprintf(tmp,"%s (0x%04X)",tp5_str4[4],SMB_tp5->enabledErrorCorrectingCapabilites);
		}
		WriteReport(i,1,tmp);
		i++;
	}
}

void CSMBIOSDlg::ReportTp6(void)
{
	char tmp[1024],buf[30];
	int i=0,j;
	WORD dd;
	struct SMBStructMemoryModule *SMB_tp6;
	
	if(FindTable(6) == -1)
	{
		MessageBox("Something was wrong when reading Tp6","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp6 = (SMBStructMemoryModule *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp6->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp6->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp6->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Socket Designation");
	GetAttachedString(tmp,SMB_tp6->socketDesignation);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp6->socketDesignation);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Bank Connections");
	sprintf(tmp,"0x%02X",SMB_tp6->bankConnections);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Current Speed");
	sprintf(tmp,"0x%02X",SMB_tp6->currentSpeed);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Current Memory Type");
	dd = SMB_tp6->currentMemoryType;
	for(j = 0; j < 11; j++)
	{
		if(dd & 0x1)
		{
			sprintf(tmp,"%s (0x%04X)",tp6_str1[j],SMB_tp6->currentMemoryType);
			break;
		}
		dd >>= 1;
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Installed Size");
	if(SMB_tp6->installedSize & 0x80)
	{
		strcpy(buf,"double-bank");
	}
	else
	{
		strcpy(buf,"single-bank");
	}
	if((SMB_tp6->installedSize & 0x7F) == 0x7D)
	{
		sprintf(tmp,"%s (0x%02X) - %s",tp6_str2[0],SMB_tp6->installedSize,buf);
	}
	else if((SMB_tp6->installedSize & 0x7F) == 0x7E)
	{
		sprintf(tmp,"%s (0x%02X) - %s",tp6_str2[1],SMB_tp6->installedSize,buf);
	}
	else if((SMB_tp6->installedSize & 0x7F) == 0x7F)
	{
		sprintf(tmp,"%s (0x%02X) - %s",tp6_str2[2],SMB_tp6->installedSize,buf);
	}
	else
	{
		sprintf(tmp,"Size 0x%02X - %s",SMB_tp6->installedSize,buf);
	}
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Enabled Size");
	if(SMB_tp6->enabledSize & 0x80)
	{
		strcpy(buf,"double-bank");
	}
	else
	{
		strcpy(buf,"single-bank");
	}
	if((SMB_tp6->enabledSize & 0x7F) == 0x7D)
	{
		sprintf(tmp,"%s (0x%02X) - %s",tp6_str2[0],SMB_tp6->enabledSize,buf);
	}
	else if((SMB_tp6->enabledSize & 0x7F) == 0x7E)
	{
		sprintf(tmp,"%s (0x%02X) - %s",tp6_str2[1],SMB_tp6->enabledSize,buf);
	}
	else if((SMB_tp6->enabledSize & 0x7F) == 0x7F)
	{
		sprintf(tmp,"%s (0x%02X) - %s",tp6_str2[2],SMB_tp6->enabledSize,buf);
	}
	else
	{
		sprintf(tmp,"Size 0x%02X - %s",SMB_tp6->enabledSize,buf);
	}
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Error Status");
	sprintf(tmp,"0x%02X",SMB_tp6->errorStatus);
	WriteReport(i,1,tmp);
	i++;
		
	if(SMB_tp6->errorStatus & 0x4)
	{
		WriteReport(i,0," ");
		strcpy(tmp,"Error status information obtained from event log");
		WriteReport(i,1,tmp);
		i++;
	}
		
	if(SMB_tp6->errorStatus & 0x2)
	{
		WriteReport(i,0," ");
		strcpy(tmp,"Correctable errors received from module");
		WriteReport(i,1,tmp);
		i++;
	}
		
	if(SMB_tp6->errorStatus & 0x1)
	{
		WriteReport(i,0," ");
		strcpy(tmp,"Uncorrectable errors received from module");
		WriteReport(i,1,tmp);
		i++;
	}
		
}

void CSMBIOSDlg::ReportTp7(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructCacheInformation *SMB_tp7;
	
	if(FindTable(7) == -1)
	{
		MessageBox("Something was wrong when reading Tp7","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp7 = (SMBStructCacheInformation *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp7->header.type);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp7->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp7->header.handle);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Socket Designation");
	GetAttachedString(tmp,SMB_tp7->socketDesignation);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp7->socketDesignation);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Cache Configuration");
	sprintf(tmp,"0x%04X",SMB_tp7->cacheConfiguration);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	if(!(SMB_tp7->cacheConfiguration & 0x300))
	{
		strcpy(tmp,"bit9-8: Operational Mode - Write through");
	}
	else if((SMB_tp7->cacheConfiguration & 0x300)==0x100)
	{
		strcpy(tmp,"bit9-8: Operational Mode - Write Back");
	}
	else if((SMB_tp7->cacheConfiguration & 0x300)==0x200)
	{
		strcpy(tmp,"bit9-8: Operational Mode - Varies with Memory Adress");
	}
	else
	{
		strcpy(tmp,"bit9-8: Operational Mode - Unknown");
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	if(!(SMB_tp7->cacheConfiguration & 0x80))
	{
		strcpy(tmp,"bit7: Disable");
	}
	else
	{
		strcpy(tmp,"bit7: Enable");
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	if(!(SMB_tp7->cacheConfiguration & 0x60))
	{
		strcpy(tmp,"bit6-5: Location - Internal");
	}
	else if((SMB_tp7->cacheConfiguration & 0x60)==0x20)
	{
		strcpy(tmp,"bit6-5: Location - External");
	}
	else if((SMB_tp7->cacheConfiguration & 0x60)==0x40)
	{
		strcpy(tmp,"bit6-5: Location - Resvered");
	}
	else
	{
		strcpy(tmp,"bit6-5: Location - Unknown");
	}
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0," ");
	strcpy(tmp,"bit4: Reserved");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	if(!(SMB_tp7->cacheConfiguration & 0x8))
	{
		strcpy(tmp,"bit3: Cache Socketed - Not Socketed");
	}
	else
	{
		strcpy(tmp,"bit3: Cache Socketed - Socketed");
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	strcpy(tmp,"bit2-0: Cache Level");
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Maximum Cache Size");
	if(SMB_tp7->maximumCacheSize & 0x8000)
	{
		sprintf(tmp,"64K granularity - 0x%04X in granularity",SMB_tp7->maximumCacheSize&0x7fff);
	}
	else
	{
		sprintf(tmp,"1K granularity - 0x%04X in granularity",SMB_tp7->maximumCacheSize&0x7fff);
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Installed Size");
	if(SMB_tp7->installedSize & 0x8000)
	{
		sprintf(tmp,"64K granularity - 0x%04X in granularity",SMB_tp7->installedSize&0x7fff);
	}
	else
	{
		sprintf(tmp,"1K granularity - 0x%04X in granularity",SMB_tp7->installedSize&0x7fff);
	}
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Supported SRAM Type");
	if(SMB_tp7->supportedSRAMType & 0x01)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[0],SMB_tp7->supportedSRAMType);
	}
	else if(SMB_tp7->supportedSRAMType & 0x02)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[1],SMB_tp7->supportedSRAMType);
	}
	else if(SMB_tp7->supportedSRAMType & 0x04)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[2],SMB_tp7->supportedSRAMType);
	}
	else if(SMB_tp7->supportedSRAMType & 0x08)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[3],SMB_tp7->supportedSRAMType);
	}
	else if(SMB_tp7->supportedSRAMType & 0x10)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[4],SMB_tp7->supportedSRAMType);
	}
	else if(SMB_tp7->supportedSRAMType & 0x20)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[5],SMB_tp7->supportedSRAMType);
	}
	else if(SMB_tp7->supportedSRAMType & 0x40)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[6],SMB_tp7->supportedSRAMType);
	}
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Current SRAM Type");
	if(SMB_tp7->currentSRAMType & 0x01)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[0],SMB_tp7->currentSRAMType);
	}
	else if(SMB_tp7->currentSRAMType & 0x02)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[1],SMB_tp7->currentSRAMType);
	}
	else if(SMB_tp7->currentSRAMType & 0x04)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[2],SMB_tp7->currentSRAMType);
	}
	else if(SMB_tp7->currentSRAMType & 0x08)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[3],SMB_tp7->currentSRAMType);
	}
	else if(SMB_tp7->currentSRAMType & 0x10)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[4],SMB_tp7->currentSRAMType);
	}
	else if(SMB_tp7->currentSRAMType & 0x20)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[5],SMB_tp7->currentSRAMType);
	}
	else if(SMB_tp7->currentSRAMType & 0x40)
	{
		sprintf(tmp,"%s (0x%04X)",tp7_str1[6],SMB_tp7->currentSRAMType);
	}
	WriteReport(i,1,tmp);
	i++;
	
	if(smb_ver >= 2.1)
	{
		WriteReport(i,0,"Cache Speed");
		sprintf(tmp,"0x%02X",SMB_tp7->cacheSpeed);
		WriteReport(i,1,tmp);
		i++;
	
		WriteReport(i,0,"Error Correction Type");
		sprintf(tmp,"%s (0x%02X)",tp7_str2[SMB_tp7->errorCorrectionType],SMB_tp7->errorCorrectionType);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"System Cache Type");
		sprintf(tmp,"%s (0x%02X)",tp7_str3[SMB_tp7->systemCacheType],SMB_tp7->systemCacheType);
		WriteReport(i,1,tmp);
		i++;
	
		WriteReport(i,0,"Associativity");
		sprintf(tmp,"%s (0x%02X)",tp7_str4[SMB_tp7->associativity],SMB_tp7->associativity);
		WriteReport(i,1,tmp);
		i++;
	}
}

void CSMBIOSDlg::ReportTp8(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructPortConnectorInformation *SMB_tp8;
	
	if(FindTable(8) == -1)
	{
		MessageBox("Something was wrong when reading Tp8","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp8 = (SMBStructPortConnectorInformation *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp8->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp8->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp8->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Internal Reference Designator");
	GetAttachedString(tmp,SMB_tp8->internalReferenceDesignator);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp8->internalReferenceDesignator);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Internal Connector Type");
	if(SMB_tp8->internalConnectorType <= 0x22)
	{
		sprintf(tmp,"%s (0x%02X)",tp8_str1[SMB_tp8->internalConnectorType],SMB_tp8->internalConnectorType);
	}
	else if(SMB_tp8->internalConnectorType >= 0xA0 && SMB_tp8->internalConnectorType <= 0xA4)
	{
		sprintf(tmp,"%s (0x%02X)",tp8_str1[SMB_tp8->internalConnectorType-126],SMB_tp8->internalConnectorType);
	}
	else
	{
		sprintf(tmp,"%s (0x%02X)",tp8_str1[39],SMB_tp8->internalConnectorType);
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"External Reference Designator");
	GetAttachedString(tmp,SMB_tp8->externalReferenceDesignator);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp8->externalReferenceDesignator);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"External Connector Type");
	if(SMB_tp8->externalConnectorType <= 0x22)
	{
		sprintf(tmp,"%s (0x%02X)",tp8_str1[SMB_tp8->externalConnectorType],SMB_tp8->externalConnectorType);
	}
	else if(SMB_tp8->externalConnectorType >= 0xA0 && SMB_tp8->externalConnectorType <= 0xA4)
	{
		sprintf(tmp,"%s (0x%02X)",tp8_str1[SMB_tp8->externalConnectorType-126],SMB_tp8->externalConnectorType);
	}
	else
	{
		sprintf(tmp,"%s (0x%02X)",tp8_str1[39],SMB_tp8->externalConnectorType);
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Port Type");
	sprintf(tmp,"0x%02X",SMB_tp8->portType);
	if(SMB_tp8->portType <= 0x22)
	{
		sprintf(tmp,"%s (0x%02X)",tp8_str2[SMB_tp8->portType],SMB_tp8->portType);
	}
	else if(SMB_tp8->portType >= 0xA0 && SMB_tp8->portType <= 0xA1)
	{
		sprintf(tmp,"%s (0x%02X)",tp8_str2[SMB_tp8->portType-127],SMB_tp8->portType);
	}
	else
	{
		sprintf(tmp,"%s (0x%02X)",tp8_str2[35],SMB_tp8->portType);
	}
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp9(void)
{
	char tmp[1024];
	int i=0,j;
	BYTE dd;
	struct SMBStructSystemSlots *SMB_tp9;
	
	if(FindTable(9) == -1)
	{
		MessageBox("Something was wrong when reading Tp9","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp9 = (SMBStructSystemSlots *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp9->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp9->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp9->header.handle);	
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Slot Designation");
	GetAttachedString(tmp,SMB_tp9->slotDesignation);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp9->slotDesignation);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Slot Type");
	if(SMB_tp9->slotType <= 0x13)
	{
		sprintf(tmp,"%s (0x%02X)",tp9_str1[SMB_tp9->slotType],SMB_tp9->slotType);
	}
	else
	{
		sprintf(tmp,"%s (0x%02X)",tp9_str1[SMB_tp9->slotType-140],SMB_tp9->slotType);
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Slot Data Bus Width");
	sprintf(tmp,"%s (0x%02X)",tp9_str2[SMB_tp9->slotDataBusWidth],SMB_tp9->slotDataBusWidth);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Current Usage");
	sprintf(tmp,"%s (0x%02X)",tp9_str3[SMB_tp9->currentUsage],SMB_tp9->currentUsage);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Slot Length");
	sprintf(tmp,"%s (0x%02X)",tp9_str4[SMB_tp9->slotLength],SMB_tp9->slotLength);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Slot ID");
	sprintf(tmp,"0x%04X",SMB_tp9->slotID);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Slot Characteristics1");
	sprintf(tmp,"0x%02X",SMB_tp9->slotCharactertics1);
	WriteReport(i,1,tmp);
	i++;
		
	dd = SMB_tp9->slotCharactertics1;
	for(j = 0; j < 8; j++)
	{
		if(dd & 0x1)
		{
			WriteReport(i,0," ");
			sprintf(tmp,"bit%d: %s",j,tp9_str5[j]);
			WriteReport(i,1,tmp);
			i++;
		}
		dd >>= 1;
	}
	
	if(smb_ver >= 2.1)
	{
		WriteReport(i,0,"Slot Characteristics2");
		sprintf(tmp,"0x%02X",SMB_tp9->slotCharactertics2);
		WriteReport(i,1,tmp);
		i++;
			
		dd = SMB_tp9->slotCharactertics2;
		for(j = 0; j < 3; j++)
		{
			if(dd & 0x1)
			{
				WriteReport(i,0," ");
				sprintf(tmp,"bit%d: %s",j,tp9_str6[j]);
				WriteReport(i,1,tmp);
				i++;
			}
			dd >>= 1;
		}
	}
	
	if(smb_ver >= 2.6)
	{
		
		WriteReport(i,0,"Segment Group Number");
		sprintf(tmp,"0x%04X\n",SMB_tp9->segmentGroupNumber);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Bus Number");
		sprintf(tmp,"0x%02X\n",SMB_tp9->busNumber);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Device/Function Number");
		sprintf(tmp,"Device:0x%02X Function:0x%X (0x%02X)\n",(SMB_tp9->deviceFunctionNumber) >> 2,(SMB_tp9->deviceFunctionNumber) & 0x3, SMB_tp9->deviceFunctionNumber);
		WriteReport(i,1,tmp);
		i++;
		
	}
}

void CSMBIOSDlg::ReportTp10(void)
{
	char tmp[1024],bb[100];
	int i=0,j,cnt;
	struct SMBStructOnBoardDeviceInformation *SMB_tp10;
	
	if(FindTable(10) == -1)
	{
		MessageBox("Something was wrong when reading Tp10","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp10 = (SMBStructOnBoardDeviceInformation *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp10->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp10->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp10->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	cnt = (SMB_tp10->header.length-4)/2;
	for(j = 0; j < cnt; j++)
	{
		sprintf(bb,"Device %d Type",j+1);
		WriteReport(i,0,bb);
		if(SMB_tp10->devices[j].deviceType & 0x80)
		{
			sprintf(tmp,"%s (0x%02X)- Device Enable",tp10_str1[SMB_tp10->devices[j].deviceType & 0x7f],SMB_tp10->devices[j].deviceType);
		}
		else
		{
			sprintf(tmp,"%s (0x%02X)- Device Disable",tp10_str1[SMB_tp10->devices[j].deviceType & 0x7f],SMB_tp10->devices[j].deviceType);
		}
		WriteReport(i,1,tmp);
		i++;
		
		sprintf(bb,"Device %d String",j+1);
		WriteReport(i,0,bb);
		GetAttachedString(tmp,j+1);
		sprintf(tmp,"%s",tmp);
		WriteReport(i,1,tmp);
		i++;
	}
}

void CSMBIOSDlg::ReportTp11(void)
{
	char tmp[1024],bb[20];
	int i=0,j;
	struct SMBStructOEMString *SMB_tp11;
	
	if(FindTable(11) == -1)
	{
		MessageBox("Something was wrong when reading Tp11","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp11 = (SMBStructOEMString *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp11->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp11->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp11->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Count");
	sprintf(tmp,"0x%02X",SMB_tp11->count);
	WriteReport(i,1,tmp);
	i++;
	for(j = 0; j < SMB_tp11->count; j++)
	{
		sprintf(bb,"String %d Type",j+1);
		WriteReport(i,0,bb);
		GetAttachedString(tmp,j+1);
		sprintf(tmp,"%s",tmp);
		WriteReport(i,1,tmp);
		i++;
	}
}

void CSMBIOSDlg::ReportTp12(void)
{
	char tmp[1024],bb[20];
	int i=0,j;
	struct SMBStructSystemConfigurationOptions *SMB_tp12;
	
	if(FindTable(12) == -1)
	{
		MessageBox("Something was wrong when reading Tp12","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp12 = (SMBStructSystemConfigurationOptions *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp12->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp12->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp12->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Count");
	sprintf(tmp,"0x%02X",SMB_tp12->count);
	WriteReport(i,1,tmp);
	i++;
	
	for(j = 0; j < SMB_tp12->count; j++)
	{
		sprintf(bb,"String %d Type",j+1);
		WriteReport(i,0,bb);
		GetAttachedString(tmp,j+1);
		sprintf(tmp,"%s",tmp);
		WriteReport(i,1,tmp);
		i++;
	}
}

void CSMBIOSDlg::ReportTp13(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructBIOSLanguageInformation *SMB_tp13;
	
	if(FindTable(13) == -1)
	{
		MessageBox("Something was wrong when reading Tp13","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp13 = (SMBStructBIOSLanguageInformation *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp13->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp13->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp13->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Installable Language");
	sprintf(tmp,"0x%02X",SMB_tp13->installableLanguages);
	WriteReport(i,1,tmp);
	i++;
	
	if(smb_ver >= 2.1)
	{
		WriteReport(i,0,"Flags");
		sprintf(tmp,"0x%02X",SMB_tp13->flags);
		WriteReport(i,1,tmp);
		i++;
	}
	else
	{
		//SMB_tp13->reserved = (BYTE *)&(data_buf[5]);
		SMB_tp13->sub = (subSMBStructBIOSLanguageInformation *)&(data_buf[5]);
	}
	
	WriteReport(i,0,"Reserved");
	sprintf(tmp,"%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X [HEX]; MSB -> LSB",SMB_tp13->sub->reserved[14],SMB_tp13->sub->reserved[13],SMB_tp13->sub->reserved[12],SMB_tp13->sub->reserved[11],SMB_tp13->sub->reserved[10],SMB_tp13->sub->reserved[9],SMB_tp13->sub->reserved[8],SMB_tp13->sub->reserved[7],SMB_tp13->sub->reserved[6],SMB_tp13->sub->reserved[5],SMB_tp13->sub->reserved[4],SMB_tp13->sub->reserved[3],SMB_tp13->sub->reserved[2],SMB_tp13->sub->reserved[1],SMB_tp13->sub->reserved[0]);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Current Language");
	sprintf(tmp,"0x%02X",SMB_tp13->sub->currentLanguage);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp14(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructGroupAssociations *SMB_tp14;
	
	if(FindTable(14) == -1)
	{
		MessageBox("Something was wrong when reading Tp14","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp14 = (SMBStructGroupAssociations *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp14->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp14->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp14->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Group Name");
	GetAttachedString(tmp,SMB_tp14->groupName);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp14->groupName);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Item Type");
	sprintf(tmp,"0x%02X",SMB_tp14->itemType);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Item Handle");
	sprintf(tmp,"0x%04X",SMB_tp14->itemHandle);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp15(void)
{
	char tmp[1024],bb[100];
	int i=0,j;
	struct SMBStructSystemEventLog *SMB_tp15;
	
	if(FindTable(15) == -1)
	{
		MessageBox("Something was wrong when reading Tp15","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp15 = (SMBStructSystemEventLog *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp15->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp15->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp15->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Log Area Length");
	sprintf(tmp,"0x%04X",SMB_tp15->logAreaLength);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Log Header Start Offset");
	sprintf(tmp,"0x%04X",SMB_tp15->logHeaderStartOffset);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Log Data Start offset");
	sprintf(tmp,"0x%04X",SMB_tp15->logDataStartOffset);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Access Method");
	if(!SMB_tp15->accessMethod)
	{
		sprintf(tmp,"1 8-bit index port, 1 8-bit data port (0x%02X)",SMB_tp15->accessMethod);
	}
	else if(SMB_tp15->accessMethod==1)
	{
		sprintf(tmp,"2 8-bit index port, 1 8-bit data port (0x%02X)",SMB_tp15->accessMethod);
	}
	else if(SMB_tp15->accessMethod==2)
	{
		sprintf(tmp,"1 16-bit index port, 1 8-bit data port (0x%02X)",SMB_tp15->accessMethod);
	}
	else if(SMB_tp15->accessMethod==3)
	{
		sprintf(tmp,"Memory-mapped physical 32-bbit address (0x%02X)",SMB_tp15->accessMethod);
	}
	else if(SMB_tp15->accessMethod==4)
	{
		sprintf(tmp,"Available via General-Purpose NonVolatile Data functions (0x%02X)",SMB_tp15->accessMethod);
	}
	else if(SMB_tp15->accessMethod>=5 && SMB_tp15->accessMethod<=0x7f)
	{
		sprintf(tmp,"Available for future as signment via specification (0x%02X)",SMB_tp15->accessMethod);
	}
	else
	{
		sprintf(tmp,"BIOS Vendor/OEM-specific (0x%02X)",SMB_tp15->accessMethod);
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Log Status");
	sprintf(tmp,"0x%02X",SMB_tp15->logStatus);
	WriteReport(i,1,tmp);
	i++;
	
	if(SMB_tp15->logStatus & 0x1)
	{
		WriteReport(i,0," ");
		strcpy(tmp,"bit0: Log area vaild");
		WriteReport(i,1,tmp);
		i++;
	}
	
	if(SMB_tp15->logStatus & 0x2)
	{
		WriteReport(i,0," ");
		strcpy(tmp,"bit1: Log area full");
		WriteReport(i,1,tmp);
		i++;
	}
	
	WriteReport(i,0,"Log Change Token");
	sprintf(tmp,"0x%08lX",SMB_tp15->logChangeToken);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Access Method Address");
	sprintf(tmp,"0x%08lX",SMB_tp15->accessMethodAddress);
	WriteReport(i,1,tmp);
	i++;
	
	if(smb_ver >= 2.1)
	{
		WriteReport(i,0,"Log Header Format");
		sprintf(tmp,"0x%02X",SMB_tp15->logHeaderFormat);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Number of Supported Log Type Descriptors");
		sprintf(tmp,"0x%02X",SMB_tp15->numberOfSupportedLogTypeDescription);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Length of each Log Type Descriptor");
		sprintf(tmp,"0x%02X",SMB_tp15->lengthOfEachLogTypeDescriptor);
		WriteReport(i,1,tmp);
		i++;
		
		for(j = 0; j < SMB_tp15->numberOfSupportedLogTypeDescription; j++)
		{
			sprintf(bb,"List of Supported Event Log Type Descriptors %d",j+1);
			WriteReport(i,0,bb);
			sprintf(tmp,"Log Type:0x%02X; Data Type:0x%02X",SMB_tp15->eventLog[j].logType,SMB_tp15->eventLog[j].variableDataFromatType);
			WriteReport(i,1,tmp);
			i++;
		}
	}
}

void CSMBIOSDlg::ReportTp16(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructPhysicalMemoryArray *SMB_tp16;
	
	if(FindTable(16) == -1)
	{
		MessageBox("Something was wrong when reading Tp16","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp16 = (SMBStructPhysicalMemoryArray *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp16->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp16->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp16->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Location");
	if(SMB_tp16->physicalLocation <=0xA)
	{
		sprintf(tmp,"%s (0x%02X)",tp16_str1[SMB_tp16->physicalLocation],SMB_tp16->physicalLocation);
	}
	else
	{
		sprintf(tmp,"%s (0x%02X)",tp16_str1[SMB_tp16->physicalLocation-148],SMB_tp16->physicalLocation);
	}
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Use");
	sprintf(tmp,"%s (0x%02X)",tp16_str2[SMB_tp16->arrayUse],SMB_tp16->arrayUse);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Memory Error Correction");
	sprintf(tmp,"%s (0x%02X)",tp16_str3[SMB_tp16->errorCorrection],SMB_tp16->errorCorrection);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Maximum Capacity");
	sprintf(tmp,"0x%08lX",SMB_tp16->maximumCapacity);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Memory Error Information Handle");
	sprintf(tmp,"0x%04X",SMB_tp16->errorHandle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Number of Memory Device");
	sprintf(tmp,"0x%04X",SMB_tp16->numMemoryDevices);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp17(void)
{
	char tmp[1024],bb[20];
	int i=0,j;
	WORD dd;
	struct SMBStructMemoryDevice *SMB_tp17;
	
	if(FindTable(17) == -1)
	{
		MessageBox("Something was wrong when reading Tp17","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp17 = (SMBStructMemoryDevice *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp17->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp17->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp17->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Physical Memory Array Handle");
	sprintf(tmp,"0x%04X",SMB_tp17->arrayHandle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Memory Error Information Handle");
	sprintf(tmp,"0x%04X",SMB_tp17->errorHandle);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Total Width");
	sprintf(tmp,"0x%04X(%u-bits)",SMB_tp17->totalWidth,SMB_tp17->totalWidth);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Data Width");
	sprintf(tmp,"0x%04X(%u-bits)",SMB_tp17->dataWidth,SMB_tp17->dataWidth);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Size");
	CalSize(bb,SMB_tp17->memorySize);
	sprintf(tmp,"0x%04X(%s)",SMB_tp17->memorySize,bb);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Form Factor");
	sprintf(tmp,"%s (0x%02X)",tp17_str1[SMB_tp17->formFactor],SMB_tp17->formFactor);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Device Set");
	sprintf(tmp,"0x%02X",SMB_tp17->deviceSet);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Device Locator");
	GetAttachedString(tmp,SMB_tp17->deviceLocator);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp17->deviceLocator);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Bank Locator");
	GetAttachedString(tmp,SMB_tp17->bankLocator);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp17->bankLocator);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Memory Type");
	sprintf(tmp,"%s (0x%02X)",tp17_str2[SMB_tp17->memoryType],SMB_tp17->memoryType);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Type Detail");
	dd = SMB_tp17->memoryTypeDetail;
	for(j = 0; j < 13; j++)
	{
		if(dd & 0x1)
		{
			sprintf(tmp,"%s (0x%04X)",tp17_str3[j],SMB_tp17->memoryTypeDetail);
			break;
		}
		dd >>= 1;
	}
	WriteReport(i,1,tmp);
	i++;

	if(smb_ver >= 2.3)
	{
		WriteReport(i,0,"Speed");
		sprintf(tmp,"0x%04X(%uMHz)",SMB_tp17->memorySpeed,SMB_tp17->memorySpeed);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Manufacturer");
		GetAttachedString(tmp,SMB_tp17->manufacturer);
		sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp17->manufacturer);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Serial Number");
		GetAttachedString(tmp,SMB_tp17->serialNumber);
		sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp17->serialNumber);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Asset Tag");
		GetAttachedString(tmp,SMB_tp17->assetTag);
		sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp17->assetTag);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Part Number");
		GetAttachedString(tmp,SMB_tp17->partNumber);
		sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp17->partNumber);
		WriteReport(i,1,tmp);
		i++;
	}
	
	if(smb_ver >= 2.6)
	{
		WriteReport(i,0,"Attributes");
		sprintf(tmp,"0x%02X\n",SMB_tp17->attributes);
		WriteReport(i,1,tmp);
		i++;
	}
}

void CSMBIOSDlg::CalSize(char *tmp,WORD dd)
{
	
	if(dd & 0x8000)
	{
		dd &= 0x7fff;
		sprintf(tmp,"%dKB",dd);
	}
	else
	{
		sprintf(tmp,"%dMB",dd);
	}
}

void CSMBIOSDlg::ReportTp18(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStruct32MemoryErrorInformation *SMB_tp18;
	
	if(FindTable(18) == -1)
	{
		MessageBox("Something was wrong when reading Tp18","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp18 = (SMBStruct32MemoryErrorInformation *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp18->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp18->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp18->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Error Type");
	sprintf(tmp,"%s (0x%02X)",tp18_str1[SMB_tp18->errorType],SMB_tp18->errorType);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Error Granularity");
	sprintf(tmp,"%s (0x%02X)",tp18_str2[SMB_tp18->errorGranularity],SMB_tp18->errorGranularity);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Error Operation");
	sprintf(tmp,"%s (0x%02X)",tp18_str3[SMB_tp18->errorOperation],SMB_tp18->errorOperation);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Vendor Syndrome");
	sprintf(tmp,"0x%08lX",SMB_tp18->vendorSyndrome);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Memory Array Error Address");
	sprintf(tmp,"0x%08lX",SMB_tp18->memoryArrayErrorAddress);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Device Error Address");
	sprintf(tmp,"0x%08lX",SMB_tp18->deviceErrorAddress);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Error Resolution");
	sprintf(tmp,"0x%08lX",SMB_tp18->errorResolution);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp19(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructMemoryArrayMappedAddress *SMB_tp19;
	
	if(FindTable(19) == -1)
	{
		MessageBox("Something was wrong when reading Tp19","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp19 = (SMBStructMemoryArrayMappedAddress *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp19->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp19->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp19->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Starting Address");
	sprintf(tmp,"0x%08lX",SMB_tp19->startingAddress);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Ending Address");
	sprintf(tmp,"0x%08lX",SMB_tp19->endingAddress);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Memory Array Hnadle");
	sprintf(tmp,"0x%04X",SMB_tp19->memoryArrayHandle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Partition Width");
	sprintf(tmp,"0x%02X",SMB_tp19->partitionWidth);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp20(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructMemoryDeviceMappedAddress *SMB_tp20;
	
	if(FindTable(20) == -1)
	{
		MessageBox("Something was wrong when reading Tp20","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp20 = (SMBStructMemoryDeviceMappedAddress *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp20->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp20->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp20->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Starting Address");
	sprintf(tmp,"0x%08lX",SMB_tp20->startingAddress);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Ending Address");
	sprintf(tmp,"0x%08lX",SMB_tp20->endingAddress);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Memory Device Hnadle");
	sprintf(tmp,"0x%04X",SMB_tp20->memoryDeviceHandle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Memory Array Mapped Address Hnadle");
	sprintf(tmp,"0x%04X",SMB_tp20->memoryArrayMappedAddressHandle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Partition Row Position");
	sprintf(tmp,"0x%02X",SMB_tp20->partitionRowPosition);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Interleave Position");
	sprintf(tmp,"0x%02X",SMB_tp20->interleavePosition);
	WriteReport(i,1,tmp);
	i++;

	WriteReport(i,0,"Interleaved Data Depth");
	sprintf(tmp,"0x%02X",SMB_tp20->interleaveDataDepth);
	WriteReport(i,1,tmp);
	i++;
		
}

void CSMBIOSDlg::ReportTp21(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructBuildInPointingDevice *SMB_tp21;
	
	if(FindTable(21) == -1)
	{
		MessageBox("Something was wrong when reading Tp21","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp21 = (SMBStructBuildInPointingDevice *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp21->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp21->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp21->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%s (0x%02X)",tp21_str1[SMB_tp21->type],SMB_tp21->type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Interface");
	if(SMB_tp21->interfaceType <= 8)
	{
		sprintf(tmp,"%s (0x%02X)",tp21_str2[SMB_tp21->interfaceType],SMB_tp21->interfaceType);
	}
	else
	{
		sprintf(tmp,"%s (0x%02X)",tp21_str2[SMB_tp21->interfaceType-150],SMB_tp21->interfaceType);
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Number of Buttons");
	sprintf(tmp,"0x%02X",SMB_tp21->numberOfButtons);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp22(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructPortableBattery *SMB_tp22;
	
	if(FindTable(22) == -1)
	{
		MessageBox("Something was wrong when reading Tp22","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp22 = (SMBStructPortableBattery *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp22->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp22->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp22->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Location");
	GetAttachedString(tmp,SMB_tp22->location);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp22->location);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Manufacturer");
	GetAttachedString(tmp,SMB_tp22->manufacturer);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp22->manufacturer);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Mamufacture Date");
	GetAttachedString(tmp,SMB_tp22->manufactureDate);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp22->manufactureDate);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Serial Number");
	GetAttachedString(tmp,SMB_tp22->serialNumber);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp22->serialNumber);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Device Name");
	GetAttachedString(tmp,SMB_tp22->deviceName);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp22->deviceName);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Device Chemistry");
	sprintf(tmp,"%s (0x%02X)",tp22_str1[SMB_tp22->deviceChemistry],SMB_tp22->deviceChemistry);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Device Capacity");
	sprintf(tmp,"0x%04X",SMB_tp22->designCapacity);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Design Voltage");
	sprintf(tmp,"0x%04X",SMB_tp22->designVlotage);
	WriteReport(i,1,tmp);
	i++;
	
	if(smb_ver >= 2.2)
	{
		WriteReport(i,0,"SBDS Version Number");
		GetAttachedString(tmp,SMB_tp22->SBDSVersionNumber);
		sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp22->SBDSVersionNumber);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Maximum Error in Battery Data");
		sprintf(tmp,"0x%02X",SMB_tp22->maximumErrorInBatteryData);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"SBDS Serial Number");
		sprintf(tmp,"0x%04X",SMB_tp22->SBDSSerialNumber);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"SBDS Manufacture Date");
		sprintf(tmp,"%d/%d/%d (0x%04X)",1980+((SMB_tp22->SBDSManufactureDate&0xFE00)>>9),(SMB_tp22->SBDSManufactureDate&0x1E0)>>5,(SMB_tp22->SBDSManufactureDate&0x1F),SMB_tp22->SBDSManufactureDate);
		WriteReport(i,1,tmp);
		i++;
			
		WriteReport(i,0,"SBDS Device Chemistry");
		GetAttachedString(tmp,SMB_tp22->SBDSDeviceChemistry);
		sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp22->SBDSDeviceChemistry);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"Design Capacity");
		sprintf(tmp,"0x%02X",SMB_tp22->designCapacityMultiplier);
		WriteReport(i,1,tmp);
		i++;
		
		WriteReport(i,0,"OEM-specific");
		sprintf(tmp,"0x%08lX",SMB_tp22->OEM);
		WriteReport(i,1,tmp);
		i++;
	}
}

void CSMBIOSDlg::ReportTp23(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructSystemReset *SMB_tp23;
	
	if(FindTable(23) == -1)
	{
		MessageBox("Something was wrong when reading Tp23","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp23 = (SMBStructSystemReset *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp23->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp23->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp23->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Capabilities");
	sprintf(tmp,"0x%02X",SMB_tp23->capabilities);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	strcpy(tmp,"Bits 7-6: Reserved");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	if(SMB_tp23->capabilities & 0x20)
	{
		strcpy(tmp,"System contains a watchdog timer");
	}
	else
	{
		strcpy(tmp,"System does not contain a watchdog timer");
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	switch((SMB_tp23->capabilities & 0x18))
	{
		case 0x00:
			strcpy(tmp,"Boot Option on Limit - Reserved");
			break;
		case 0x08:
			strcpy(tmp,"Boot Option on Limit - Operating system");
			break;
		case 0x10:
			strcpy(tmp,"Boot Option on Limit - System utilities");
			break;
		case 0x18:
			strcpy(tmp,"Boot Option on Limit - Do not reboot");
			break;
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	switch((SMB_tp23->capabilities & 0x6))
	{
		case 0x00:
			strcpy(tmp,"Boot Option - Reserved");
			break;
		case 0x02:
			strcpy(tmp,"Boot Option - Operating system");
			break;
		case 0x04:
			strcpy(tmp,"Boot Option - System utilities");
			break;
		case 0x6:
			strcpy(tmp,"Boot Option - Do not reboot");
			break;
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	if(SMB_tp23->capabilities & 0x01)
	{
		strcpy(tmp,"The system reset is enabled by the user");
	}
	else
	{
		strcpy(tmp,"The system reset is not enabled by the user");
	}
	WriteReport(i,1,tmp);
	i++;
	
	
	WriteReport(i,0,"Reset Count");
	sprintf(tmp,"0x%04X",SMB_tp23->resetCount);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Reset Limit");
	sprintf(tmp,"0x%04X",SMB_tp23->resetLimit);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Timer Interval");
	sprintf(tmp,"0x%04X",SMB_tp23->timerInterval);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Timeout");
	sprintf(tmp,"0x%04X",SMB_tp23->timeout);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp24(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructHardwareSecurity *SMB_tp24;
	
	if(FindTable(24) == -1)
	{
		MessageBox("Something was wrong when reading Tp24","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp24 = (SMBStructHardwareSecurity *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp24->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp24->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp24->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Hardware Security Setting");
	sprintf(tmp,"0x%02X",SMB_tp24->hardwareSecuritySettings);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	switch((SMB_tp24->hardwareSecuritySettings & 0xc0))
	{
		case 0x00:
			strcpy(tmp,"Power-on Password Status - Disabled");
			break;
		case 0x40:
			strcpy(tmp,"Power-on Password Status - Enabled");
			break;
		case 0x80:
			strcpy(tmp,"Power-on Password Status - Not Implemented");
			break;
		case 0xc0:
			strcpy(tmp,"Power-on Password Status - Unknown");
			break;
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	switch((SMB_tp24->hardwareSecuritySettings & 0x30))
	{
		case 0x00:
			strcpy(tmp,"Keyboard Password Status - Disabled");
			break;
		case 0x10:
			strcpy(tmp,"Keyboard Password Status - Enabled");
			break;
		case 0x20:
			strcpy(tmp,"Keyboard Password Status - Not Implemented");
			break;
		case 0x40:
			strcpy(tmp,"Keyboard Password Status - Unknown");
			break;
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	switch((SMB_tp24->hardwareSecuritySettings & 0x0c))
	{
		case 0x00:
			strcpy(tmp,"Administrator Password Status - Disabled");
			break;
		case 0x04:
			strcpy(tmp,"Administrator Password Status - Enabled");
			break;
		case 0x08:
			strcpy(tmp,"Administrator Password Status - Not Implemented");
			break;
		case 0x0c:
			strcpy(tmp,"Administrator Password Status - Unknown");
			break;
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	switch((SMB_tp24->hardwareSecuritySettings & 0x03))
	{
		case 0x00:
			strcpy(tmp,"Front Panel Reset Status - Disabled");
			break;
		case 0x01:
			strcpy(tmp,"Front Panel Reset Status - Enabled");
			break;
		case 0x02:
			strcpy(tmp,"Front Panel Reset Status - Not Implemented");
			break;
		case 0x03:
			strcpy(tmp,"Front Panel Reset Status - Unknown");
			break;
	}
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp25(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructSystemPowerControls *SMB_tp25;
	
	if(FindTable(25) == -1)
	{
		MessageBox("Something was wrong when reading Tp25","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp25 = (SMBStructSystemPowerControls *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp25->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp25->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp25->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Next Scheduled Power-on Month");
	sprintf(tmp,"0x%02X",SMB_tp25->nextScheduledPowerOnMonth);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Next Scheduled Power-on Day of Month");
	sprintf(tmp,"0x%02X",SMB_tp25->nextScheduledPowerOnDayOfMonth);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Next Scheduled Power-on Hour");
	sprintf(tmp,"0x%02X",SMB_tp25->nextScheduledPowerOnHour);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Next Scheduled Power-on Minute");
	sprintf(tmp,"0x%02X",SMB_tp25->nextScheduledPowerOnMinute);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Next Scheduled Power-on Second");
	sprintf(tmp,"0x%02X",SMB_tp25->nextScheduledPowerOnSecond);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp26(void)
{
	char tmp[1024];
	int i=0;
	BYTE dd;
	struct SMBStructVoltageProbe *SMB_tp26;
	
	if(FindTable(26) == -1)
	{
		MessageBox("Something was wrong when reading Tp26","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp26 = (SMBStructVoltageProbe *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp26->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp26->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp26->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Description");
	GetAttachedString(tmp,SMB_tp26->description);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp26->description);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Location and Status");
	sprintf(tmp,"0x%02X",SMB_tp26->locationAndStatus);
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0," ");
	dd = (SMB_tp26->locationAndStatus & 0xe0) >> 5;
	sprintf(tmp,"Status: %s",tp26_str1[dd]);
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0," ");
	dd = (SMB_tp26->locationAndStatus & 0x1f)+5;
	sprintf(tmp,"Lcation: %s",tp26_str1[dd]);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Maximum Value");
	sprintf(tmp,"0x%04X",SMB_tp26->maximumValue);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Minimum Value");
	sprintf(tmp,"0x%04X",SMB_tp26->minimumValue);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Resolution");
	sprintf(tmp,"0x%04X",SMB_tp26->resolution);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Tolerance");
	sprintf(tmp,"0x%04X",SMB_tp26->tolerance);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Accuracy");
	sprintf(tmp,"0x%04X",SMB_tp26->accuracy);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"OEM-defined");
	sprintf(tmp,"0x%08lX",SMB_tp26->OEM);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Nominal Value");
	sprintf(tmp,"0x%04X",SMB_tp26->nominalValue);
	WriteReport(i,1,tmp);
	i++;
	
}

void CSMBIOSDlg::ReportTp27(void)
{
	char tmp[1024];
	int i=0;
	BYTE dd;
	struct SMBStructCoolingDevice *SMB_tp27;
	
	if(FindTable(27) == -1)
	{
		MessageBox("Something was wrong when reading Tp27","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp27 = (SMBStructCoolingDevice *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp27->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp27->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp27->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Temperature Probe Handle");
	sprintf(tmp,"0x%04X",SMB_tp27->temperatureProbeHandle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Device Type and Status");
	sprintf(tmp,"0x%02X",SMB_tp27->deviceTypeAndStatus);
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0," ");
	dd = (SMB_tp27->deviceTypeAndStatus & 0xe0) >> 5;
	sprintf(tmp,"Status: %s",tp27_str1[dd]);
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0," ");
	dd = (SMB_tp27->deviceTypeAndStatus & 0x1f)+5;
	sprintf(tmp,"Device Type: %s",tp27_str1[dd]);
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0,"Cooling Unit Group");
	sprintf(tmp,"0x%02X",SMB_tp27->coolingUnitGroup);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"OEM-define");
	sprintf(tmp,"0x%08lX",SMB_tp27->OEM);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Nominal Speed");
	sprintf(tmp,"0x%04X",SMB_tp27->nominalSpeed);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp28(void)
{
	char tmp[1024];
	int i=0;
	BYTE dd;
	struct SMBStructTemperatureProbe *SMB_tp28;
	
	if(FindTable(28) == -1)
	{
		MessageBox("Something was wrong when reading Tp28","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp28 = (SMBStructTemperatureProbe *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp28->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp28->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp28->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Description");
	GetAttachedString(tmp,SMB_tp28->description);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp28->description);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Location and Status");
	sprintf(tmp,"0x%02X",SMB_tp28->locationAndStatus);
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0," ");
	dd = (SMB_tp28->locationAndStatus & 0xe0) >> 5;
	sprintf(tmp,"Status: %s",tp28_str1[dd]);
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0," ");
	dd = (SMB_tp28->locationAndStatus & 0x1f)+5;
	sprintf(tmp,"Location: %s",tp28_str1[dd]);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Maximum Value");
	sprintf(tmp,"0x%04X",SMB_tp28->maximumValue);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Minimum Value");
	sprintf(tmp,"0x%04X",SMB_tp28->minimumValue);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Resolution");
	sprintf(tmp,"0x%04X",SMB_tp28->resolution);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Tolerance");
	sprintf(tmp,"0x%04X",SMB_tp28->tolerance);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Accuracy");
	sprintf(tmp,"0x%04X",SMB_tp28->accuracy);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"OEM-defined");
	sprintf(tmp,"0x%08lX",SMB_tp28->OEM);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Nominal Value");
	sprintf(tmp,"0x%04X",SMB_tp28->nominalValue);
	WriteReport(i,1,tmp);
	i++;
		
}

void CSMBIOSDlg::ReportTp29(void)
{
	char tmp[1024];
	int i=0;
	BYTE dd;
	struct SMBStructElectricalCurrentProbe *SMB_tp29;
	
	if(FindTable(29) == -1)
	{
		MessageBox("Something was wrong when reading Tp29","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp29 = (SMBStructElectricalCurrentProbe *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp29->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp29->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp29->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Description");
	GetAttachedString(tmp,SMB_tp29->description);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp29->description);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Location and Status");
	sprintf(tmp,"0x%02X",SMB_tp29->locationAndStatus);
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0," ");
	dd = (SMB_tp29->locationAndStatus & 0xe0) >> 5;
	sprintf(tmp,"Status: %s",tp29_str1[dd]);
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0," ");
	dd = (SMB_tp29->locationAndStatus & 0x1f)+5;
	sprintf(tmp,"Location: %s",tp29_str1[dd]);
	WriteReport(i,1,tmp);
	i++;
		
	WriteReport(i,0,"Maximum Value");
	sprintf(tmp,"0x%04X",SMB_tp29->maximumValue);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Minimum Value");
	sprintf(tmp,"0x%04X",SMB_tp29->minimumValue);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Resolution");
	sprintf(tmp,"0x%04X",SMB_tp29->resolution);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Tolerance");
	sprintf(tmp,"0x%04X",SMB_tp29->tolerance);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Accuracy");
	sprintf(tmp,"0x%04X",SMB_tp29->accuracy);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"OEM-defined");
	sprintf(tmp,"0x%08lX",SMB_tp29->OEM);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Nominal Value");
	sprintf(tmp,"0x%04X",SMB_tp29->nominalValue);
	WriteReport(i,1,tmp);
	i++;
	
}

void CSMBIOSDlg::ReportTp30(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructOutOfBandRemoteAccess *SMB_tp30;
	
	if(FindTable(30) == -1)
	{
		MessageBox("Something was wrong when reading Tp30","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp30 = (SMBStructOutOfBandRemoteAccess *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp30->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp30->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp30->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Manufacturer Name");
	GetAttachedString(tmp,SMB_tp30->manufacturerName);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp30->manufacturerName);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Connections");
	sprintf(tmp,"0x%02X",SMB_tp30->connections);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	strcpy(tmp,"bits 7-2: Reserved");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	if(SMB_tp30->connections & 0x2)
	{
		strcpy(tmp,"Outbound Connection Enabled");
	}
	else
	{
		strcpy(tmp,"Outbound Connection Disabled");
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	if(SMB_tp30->connections & 0x1)
	{
		strcpy(tmp,"Inbound Connection Enabled");
	}
	else
	{
		strcpy(tmp,"Inbound Connection Disabled");
	}
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp32(void)
{
	char tmp[1024],bb[100];
	int i=0,j;
	struct SMBStructSystemBootInformation *SMB_tp32;
	
	if(FindTable(32) == -1)
	{
		MessageBox("Something was wrong when reading Tp32","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp32 = (SMBStructSystemBootInformation *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp32->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp32->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp32->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Reserved");
	sprintf(tmp,"%02X %02X %02X %02X %02X %02X [HEX]; MSB -> LSB",SMB_tp32->reserved[5],SMB_tp32->reserved[4],SMB_tp32->reserved[3],SMB_tp32->reserved[2],SMB_tp32->reserved[1],SMB_tp32->reserved[0]);
	WriteReport(i,1,tmp);
	i++;
	
	for(j = 0; j < SMB_tp32->header.length-10; j++)
	{
		sprintf(bb,"Boot Status(%d)",j+1);
		WriteReport(i,0,bb);
		sprintf(tmp,"0x%02X",SMB_tp32->bootStatus[j]);
		WriteReport(i,1,tmp);
		i++;
	}
}

void CSMBIOSDlg::ReportTp33(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructMemoryErrorInformation *SMB_tp33;
	
	if(FindTable(33) == -1)
	{
		MessageBox("Something was wrong when reading Tp33","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp33 = (SMBStructMemoryErrorInformation *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp33->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp33->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp33->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Error Type");
	sprintf(tmp,"0x%02X",SMB_tp33->errorType);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Error Granularity");
	sprintf(tmp,"0x%02X",SMB_tp33->errorGranularity);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Error Operation");
	sprintf(tmp,"0x%02X",SMB_tp33->errorOperation);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Vendor Syndrome");
	sprintf(tmp,"0x%08lX",SMB_tp33->vendorSyndrome);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Memory Array Error Address");
	sprintf(tmp,"0x%02X%02X%02X%02X%02X%02X%02X%02X",SMB_tp33->memoryArrayErrorAddress[7],SMB_tp33->memoryArrayErrorAddress[6],SMB_tp33->memoryArrayErrorAddress[5],SMB_tp33->memoryArrayErrorAddress[4],SMB_tp33->memoryArrayErrorAddress[3],SMB_tp33->memoryArrayErrorAddress[2],SMB_tp33->memoryArrayErrorAddress[1],SMB_tp33->memoryArrayErrorAddress[0]);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Device Error Address");
	sprintf(tmp,"0x%02X%02X%02X%02X%02X%02X%02X%02X",SMB_tp33->deviceErrorAddress[7],SMB_tp33->deviceErrorAddress[6],SMB_tp33->deviceErrorAddress[5],SMB_tp33->deviceErrorAddress[4],SMB_tp33->deviceErrorAddress[3],SMB_tp33->deviceErrorAddress[2],SMB_tp33->deviceErrorAddress[1],SMB_tp33->deviceErrorAddress[0]);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Error Resolution");
	sprintf(tmp,"0x%08lX",SMB_tp33->errorResolution);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp34(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructManagementDevice *SMB_tp34;
	
	if(FindTable(34) == -1)
	{
		MessageBox("Something was wrong when reading Tp34","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp34 = (SMBStructManagementDevice *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp34->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp34->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp34->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Description");
	GetAttachedString(tmp,SMB_tp34->description);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp34->description);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%s (0x%02X)",tp34_str1[SMB_tp34->type],SMB_tp34->type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Address");
	sprintf(tmp,"0x%08lX",SMB_tp34->address);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Address Type");
	sprintf(tmp,"%s (0x%02X)",tp34_str2[SMB_tp34->addressType],SMB_tp34->addressType);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp35(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructManagementDeviceComponent *SMB_tp35;
	
	if(FindTable(35) == -1)
	{
		MessageBox("Something was wrong when reading Tp35","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp35 = (SMBStructManagementDeviceComponent *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp35->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp35->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp35->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Description");
	GetAttachedString(tmp,SMB_tp35->description);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp35->description);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Management Device Handle");
	sprintf(tmp,"0x%04X",SMB_tp35->managementDeviceHandle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Component Handle");
	sprintf(tmp,"0x%04X",SMB_tp35->componentHandle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Threshold Handle");
	sprintf(tmp,"0x%04X",SMB_tp35->thresholdHandle);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp36(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructManagementDeviceThresholdData *SMB_tp36;
	
	if(FindTable(36) == -1)
	{
		MessageBox("Something was wrong when reading Tp36","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp36 = (SMBStructManagementDeviceThresholdData *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp36->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp36->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp36->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Lower Threshold - Non-critical");
	sprintf(tmp,"0x%04X",SMB_tp36->lowerThreshold_non_Critical);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Upper Threshold - Non-critical");
	sprintf(tmp,"0x%04X",SMB_tp36->upperThreshold_non_Critical);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Lower Threshold - Critical");
	sprintf(tmp,"0x%04X",SMB_tp36->lowerThreshold_Critical);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Upper Threshold - Critical");
	sprintf(tmp,"0x%04X",SMB_tp36->upperThreshold_Critical);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Lower Threshold - Non-recoverable");
	sprintf(tmp,"0x%04X",SMB_tp36->lowerThreshold_non_Recoverable);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Upper Threshold - Non-recoverable");
	sprintf(tmp,"0x%04X",SMB_tp36->upperThreshold_non_Recoverable);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp37(void)
{
	char tmp[1024];
	int i=0,j;
	struct SMBStructMemoryChannel *SMB_tp37;
	
	if(FindTable(37) == -1)
	{
		MessageBox("Something was wrong when reading Tp37","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp37 = (SMBStructMemoryChannel *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp37->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp37->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp37->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Channel Type");
	sprintf(tmp,"%s (0x%02X)",tp37_str1[SMB_tp37->channelType],SMB_tp37->channelType);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Maximum Channel Load");
	sprintf(tmp,"0x%02X",SMB_tp37->maximumChannelLoad);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Memory Device Count");
	sprintf(tmp,"0x%02X",SMB_tp37->memoryDeviceCount);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Memory Device Load");
	sprintf(tmp,"0x%02X",SMB_tp37->memoryDeviceLoad);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Memory Device Handle");
	sprintf(tmp,"0x%04X",SMB_tp37->memoryDeviceHandle);
	WriteReport(i,1,tmp);
	i++;
	
	for(j = 0; j < SMB_tp37->memoryDeviceCount-1; j++)
	{
		WriteReport(i,0,"Memory Device Load");
		sprintf(tmp,"0x%02X",SMB_tp37->memoryDeviceN[j].memoryDeviceLoad);
		WriteReport(i,1,tmp);
		i++;
	
		WriteReport(i,0,"Memory Device Handle");
		sprintf(tmp,"0x%04X",SMB_tp37->memoryDeviceN[j].memoryDeviceHandle);
		WriteReport(i,1,tmp);
		i++;
	}
}

void CSMBIOSDlg::ReportTp38(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructIPMIDeviceInformation *SMB_tp38;
	
	if(FindTable(38) == -1)
	{
		MessageBox("Something was wrong when reading Tp38","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp38 = (SMBStructIPMIDeviceInformation *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp38->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp38->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp38->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Interface Type");
	if(SMB_tp38->interfaceType <= 3)
	{
		sprintf(tmp,"%s (0x%02X)",tp38_str1[SMB_tp38->interfaceType],SMB_tp38->interfaceType);
	}
	else
	{
		sprintf(tmp,"Reserved (0x%02X)",SMB_tp38->interfaceType);
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"IPMI Specification Revision");
	sprintf(tmp,"0x%02X",SMB_tp38->ipmiSpecificationRevision);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"I2C Slave Address");
	sprintf(tmp,"0x%02X",SMB_tp38->i2cSlaveAddress);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"NV Storage Device Address");
	sprintf(tmp,"0x%02X",SMB_tp38->nvStorageDeviceAddress);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Base Address");
	sprintf(tmp,"0x%02X%02X%02X%02X%02X%02X%02X%02X",SMB_tp38->baseAddress[7],SMB_tp38->baseAddress[6],SMB_tp38->baseAddress[5],SMB_tp38->baseAddress[4],SMB_tp38->baseAddress[3],SMB_tp38->baseAddress[2],SMB_tp38->baseAddress[1],SMB_tp38->baseAddress[0]);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp39(void)
{
	char tmp[1024];
	int i=0;
	BYTE dd;
	struct SMBStructSystemPowerSupply *SMB_tp39;
	
	if(FindTable(39) == -1)
	{
		MessageBox("Something was wrong when reading Tp39","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp39 = (SMBStructSystemPowerSupply *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d",SMB_tp39->header.type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp39->header.length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp39->header.handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Power Unit Group");
	sprintf(tmp,"0x%02X",SMB_tp39->powerUnitGroup);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Location");
	GetAttachedString(tmp,SMB_tp39->location);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp39->location);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Device Name");
	GetAttachedString(tmp,SMB_tp39->deviceName);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp39->deviceName);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Manufacturer");
	GetAttachedString(tmp,SMB_tp39->manufacturer);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp39->manufacturer);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Serial Number");
	GetAttachedString(tmp,SMB_tp39->serialNumber);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp39->serialNumber);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Asset Tag Number");
	GetAttachedString(tmp,SMB_tp39->assetTagNumber);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp39->assetTagNumber);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Model Part Number");
	GetAttachedString(tmp,SMB_tp39->modelPartNumber);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp39->modelPartNumber);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Revision Level");
	GetAttachedString(tmp,SMB_tp39->revisionLevel);
	sprintf(tmp,"%s (0x%02X)",tmp,SMB_tp39->revisionLevel);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Max Power Capacity");
	sprintf(tmp,"0x%04X",SMB_tp39->maxPowerCapacity);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Power Supply Characteristics");
	sprintf(tmp,"0x%04X",SMB_tp39->powerSupplyCharacteristics);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	dd = (SMB_tp39->powerSupplyCharacteristics & 0x3C00)>>10;
	if(dd <= 8)
	{
		sprintf(tmp,"bit13-10: DMTF Power Supply Type - %s",tp39_str1[dd-1]);
	}
	else
	{
		strcpy(tmp,"bit13-10: DMTF Power Supply Type - Reserved");
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	dd = (SMB_tp39->powerSupplyCharacteristics & 0x380)>>7;
	if(dd <= 5)
	{
		sprintf(tmp,"bit9-7: Status - %s",tp39_str2[dd-1]);
	}
	else
	{
		strcpy(tmp,"bit9-7: Status - ??");
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	dd = (SMB_tp39->powerSupplyCharacteristics & 0x78)>>3;
	if(dd <= 6)
	{
		sprintf(tmp,"bit6-3: DMTF Input Voltage Range Switching - %s",tp39_str3[dd-1]);
	}
	else
	{
		strcpy(tmp,"bit6-3: Status - ??");
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	if(SMB_tp39->powerSupplyCharacteristics & 0x4)
	{
		strcpy(tmp,"bit2: Power supply is unplugged from wall");
	}
	else
	{
		strcpy(tmp,"bit2: Power supply is plugged from wall");
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	if(SMB_tp39->powerSupplyCharacteristics & 0x2)
	{
		strcpy(tmp,"bit2: Power supply is present");
	}
	else
	{
		strcpy(tmp,"bit2: Power supply is not present");
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0," ");
	if(SMB_tp39->powerSupplyCharacteristics & 0x1)
	{
		strcpy(tmp,"bit2: Power supply is hot replaceable");
	}
	else
	{
		strcpy(tmp,"bit2: Power supply is not replaceable");
	}
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Input Voltage Probe Handle");
	sprintf(tmp,"0x%04X",SMB_tp39->inputVoltageProbeHandle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Cooling Device Handle");
	sprintf(tmp,"0x%04X",SMB_tp39->coolingDeviceHandle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Input Current Probe Handle");
	sprintf(tmp,"0x%04X",SMB_tp39->inputCurrentProbeHandle);
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportTp126(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructHeader *SMB_tp126;
	
	if(FindTable(126) == -1)
	{
		MessageBox("Something was wrong when reading Tp126","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp126 = (SMBStructHeader *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d - Inactive",SMB_tp126->type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X %s",SMB_tp126->length,length_err ? "(Length wrong)" : "");
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp126->handle);
	WriteReport(i,1,tmp);
}

void CSMBIOSDlg::ReportOEM(void)
{
	char tmp[1024],bb[10];
	int i=0,j;
	struct SMBStructHeader *SMB_oem;
	
	FindTable(-1);
	
	SMB_oem = (SMBStructHeader *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d - OEM",SMB_oem->type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X",SMB_oem->length);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_oem->handle);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Data");
	ZeroMemory(tmp,sizeof(tmp));
	for( j = 4; j < data_len; j++)
	{
		sprintf(bb," %02X",data_buf[j]);
		strcat(tmp,bb);
	}
	WriteReport(i,1,tmp);
	i++;
}

void CSMBIOSDlg::ReportEnd(void)
{
	char tmp[1024];
	int i=0;
	struct SMBStructHeader *SMB_tp127;
	
	if(FindTable(127) == -1)
	{
		MessageBox("Something was wrong when reading Tp127","Error",MB_OK | MB_ICONSTOP);
		return;
	}
	
	SMB_tp127 = (SMBStructHeader *)data_buf;
	
	WriteReport(i,0,"Type");
	sprintf(tmp,"%d - End-of-table",SMB_tp127->type);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Length");
	sprintf(tmp,"0x%02X",SMB_tp127->length);
	WriteReport(i,1,tmp);
	i++;
	
	WriteReport(i,0,"Handle");
	sprintf(tmp,"0x%04X",SMB_tp127->handle);
	WriteReport(i,1,tmp);
}

void CSMBIOSDlg::WriteReport(int posi, int col, char *value)
{
	LV_ITEM data;

	if(!col)
	{
		data.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
		data.state = 0;
		data.stateMask = 0;
		data.iItem = posi;
		data.iImage = 0;
		data.iSubItem = 0;
		data.pszText = value;
		m_report.InsertItem(&data);
	}
	else
	{
		m_report.SetItemText(posi,col,value);
	}
}

void CSMBIOSDlg::ShowStatus(char *str)
{
	m_status.SetWindowText(str);
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);//畫面重畫
}

void CSMBIOSDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
	if( m_list.GetSafeHwnd() && IsWindow(m_list) )
	{
		//m_report.MoveWindow(0,48, cx,cy-110);
		//                       起點x,起點y,寬,高, 1:1.75左右(圖與實際顯示)
		m_list.SetWindowPos(NULL,0,0,270,cy-52,SWP_NOMOVE | SWP_NOZORDER);
	}
	
	if( m_report.GetSafeHwnd() && IsWindow(m_report) )
	{
		m_report.SetWindowPos(NULL,0,0,cx-273,cy-30,SWP_NOMOVE | SWP_NOZORDER);
	}

	if( m_status.GetSafeHwnd() && IsWindow(m_status) )
	{
		m_status.SetWindowPos(NULL,0,cy-18,cx,18,SWP_NOZORDER);
	}
}


int GetProcessorString(WORD PFamily)
{
	DWORD i;
	int cnt;
	
	cnt = -1;
	for(i = 1; i <= 0xffff; i++)
	{
		if( i < 0x14)
		{
			cnt++;
		}
		else if(i >= 0x18 && i <= 0x27)
		{
			cnt++;
		}
		else if(i >= 0x30 && i <= 0x37)
		{
			cnt++;
		}
		else if(i >= 0x40 && i <= 0x45)
		{
			cnt++;
		}
		else if(i >= 0x50 && i <= 0x58)
		{
			cnt++;
		}
		else if(i >= 0x60 && i <= 0x65)
		{
			cnt++;
		}
		else if(i == 0x70)
		{
			cnt++;
		}
		else if(i >= 0x78 && i <= 0x7A)
		{
			cnt++;
		}
		else if(i == 0x80)
		{
			cnt++;
		}
		else if(i >= 0x82 && i <= 0x89)
		{
			/*if(smb_ver <= 2.5 && i==0x89)
				{}
			else*/
				cnt++;
		}
		else if(i >= 0x90 && i <= 0x96)
		{
			cnt++;
		}
		else if(i == 0xA0)
		{
			cnt++;
		}
		else if(i >= 0xB0 && i <= 0xBF)
		{
			/*if(smb_ver <= 2.5 && (i>=0xBD && i <=0xBF))
				{}
			else*/
				cnt++;
		}
		else if(i >= 0xC8 && i <= 0xCC)
		{
			/*if(smb_ver <= 2.5 && (i>=0xCB && i <=0xCC))
				{}
			else*/
				cnt++;
		}
		else if(i >= 0xD2 && i <= 0xD5)
		{
			//if(smb_ver >= 2.6)
				cnt++;
		}
		else if(i >= 0xFA && i <= 0xFB)
		{
			cnt++;
		}
		else if(i >= 0xFE && i <= 0xFF /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i >= 0x104 && i <= 0x105 /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i >= 0x118 && i <= 0x119 /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i >= 0x12C && i <= 0x12E /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i == 0x140 /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i == 0x15E /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i == 0x1f4 /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		else if(i >= 0xFFFE && i <= 0xFFFF /*&& smb_ver >= 2.6*/)
		{
			cnt++;
		}
		
		if(i == (DWORD)PFamily)
		{
			break;
		}
	}
	return cnt;
}
