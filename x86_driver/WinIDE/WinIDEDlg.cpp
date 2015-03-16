// WinIDEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinIDE.h"
#include "myio.h"
//#include "def.h"
#include "WinIDEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Controller_info c_info[10];
HDDpara Para_info;
CheckStruct HDDs[10]=
	{
	 {0x1F0,0},
	 {0x1F0,1},
	 {0x170,0},
	 {0x170,1},
	 {0,0},
	 {0,0},
	 {0,0},
	 {0,0},
	 {0,0},
	 {0,0}
	};

void Delay_1us(DWORD delay);

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
// CWinIDEDlg dialog

CWinIDEDlg::CWinIDEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinIDEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinIDEDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinIDEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinIDEDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinIDEDlg, CDialog)
	//{{AFX_MSG_MAP(CWinIDEDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinIDEDlg message handlers

BOOL CWinIDEDlg::OnInitDialog()
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
	DWORD dwStyle = m_list.GetExtendedStyle();

	dwStyle |= LVS_EX_FULLROWSELECT;
	m_list.SetExtendedStyle(dwStyle);

	if(OnMyIo() == 0)
	{
		MessageBox("Fail to open MyIO","Error",MB_OK | MB_ICONSTOP);
		CDialog::OnOK();
	}
	
	Get_IDE_info();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinIDEDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWinIDEDlg::OnPaint() 
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
HCURSOR CWinIDEDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CWinIDEDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}


void CWinIDEDlg::Get_IDE_info(void)
{
	int i,posi;
	char buf[1024];
	BYTE DataBuff[512];
	
	//加上欄位資料
	m_list.InsertColumn(0,"種類",LVCFMT_LEFT,70);
	m_list.InsertColumn(1,"型號",LVCFMT_LEFT,150);
	m_list.InsertColumn(2,"流水號",LVCFMT_LEFT,100);
	m_list.InsertColumn(3,"容量",LVCFMT_LEFT,100);
	m_list.InsertColumn(4,"韌體版本",LVCFMT_LEFT,70);
	m_list.InsertColumn(5,"基底位址",LVCFMT_LEFT,70);
	
	if(SearchIDEcontroller() != 0)
	{
		for(i = 2; i < controller_cnt; i++)
		{
			HDDs[i*2].Port = c_info[i].Pri_addr;
			HDDs[i*2].Drive = 0;
			HDDs[i*2+1].Port = c_info[i].Pri_addr;
			HDDs[i*2+1].Drive = 1;
			
		}
	}
	
	posi = 0;
	for(i = 0; i < controller_cnt*2; i++)
	{//先去抓電腦的所有裝置，並記錄起來，也記到記錄檔
		if(HDDs[i].Port != 0)
		{
			int status = IdentifyDevice(HDDs[i].Port,HDDs[i].Drive,DataBuff);
			if (status != 0)
			{
				ZeroMemory(&Para_info,sizeof(HDDpara));
				GetHDDpara(HDDs[i].Port,HDDs[i].Drive,&Para_info,DataBuff);
				
				switch(Para_info.Devicetype)
				{
					case 1:
						Write_list("硬碟",posi,0); //種類
						break;
					case 2:
						Write_list("光碟機",posi,0); //種類
						break;
					case 3:
						Write_list("磁帶機",posi,0); //種類
						break;
				}
						
				sprintf(buf,"%s",Para_info.Model);
				Write_list(buf,posi,1); //型號
				
				sprintf(buf,"%s",Para_info.Serial);
				Write_list(buf,posi,2); //流水號
				
				sprintf(buf,"%ldMB",Para_info.Size);
				Write_list(buf,posi,3); //容量
					
				sprintf(buf,"%s",Para_info.FW);
				Write_list(buf,posi,4); //韌體版本
						
				sprintf(buf,"%Xh",HDDs[i].Port);
				Write_list(buf,posi,5); //基底位址
						
				posi++;
			}
		}
	}//
	if(posi == 0)
	{
		AfxMessageBox("找不到任何IDE裝置");
	}
}

void CWinIDEDlg::Write_list(char *value, int posi, int col)
{
	LV_ITEM data;

	if(col==0)
	{
		data.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
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

int CWinIDEDlg::SearchIDEcontroller( void )
{
	WORD i,j,k;
	BYTE gclass,gsclass,tp;
	WORD vendor,add;
	int done=0;
	
	controller_cnt = 0;
	ZeroMemory(c_info, sizeof(c_info));
	for(i = 0; i < 256; i++)
	{
		for(j = 0; j < 32; j++)
		{
			for(k = 0; k < 8; k++)
			{
				if(k == 0)
				{
					read_pci_byte((BYTE)i,(BYTE)j,(BYTE)k,0x0e,&tp);
					tp &= 0x80;
				}
				read_pci_word((BYTE)i,(BYTE)j,(BYTE)k,0x00,&vendor);
				if(vendor != 0xffff)
				{
					read_pci_byte((BYTE)i,(BYTE)j,(BYTE)k,0x0B,&gclass);
					if(gclass == 0x01)
					{//大量儲存媒體控制器
						read_pci_byte((BYTE)i,(BYTE)j,(BYTE)k,0x0a,&gsclass);
						if(gsclass == 0x01 || gsclass == 0x04)
						{//IDE controller or RAID controller
							done = 0;

							//去暫存器讀位址
							read_pci_word((BYTE)i,(BYTE)j,(BYTE)k,0x10,&add);
							if((add & 0x0001) == 0x0001)
							{
								add &= 0xfffe;
								
								if(add != 0 && add != 0x1f0 && add != 0x170)
								{
									c_info[controller_cnt].Pri_addr = add;
								}
								else
								{
									goto qq;
								}
							}
							
							
							//去暫存器讀位址
							read_pci_word((BYTE)i,(BYTE)j,(BYTE)k,0x14,&add);
							if((add & 0x0001) == 0x0001)
							{
								add &= 0xfffe;
								if(add!= 0 && add != 0x1f0 && add != 0x170)
								{
									c_info[controller_cnt].Sec_addr = add;
								}
							}
							done++;
							
							c_info[controller_cnt].Bus = i;
							c_info[controller_cnt].Dev = j;
							c_info[controller_cnt].Func = k;
						}

qq:					
						if(done != 0)
						{
							controller_cnt++;
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
	
	controller_cnt += 2;
	if(controller_cnt < 3)
	{
		return 0;
	}
	return 1;
}

BYTE CWinIDEDlg::IdentifyDevice(WORD Port,BYTE Device,BYTE *Data)
{
	BYTE Status;
	DWORD i;
	BYTE cmd,nu;
	
//	BYTE er;
//1. Get CMD chip bus info
//2. Get chennel address PM : 0x10, PS :0x14, SM : 0x18, SS : 0x1C
//3. Send command.(Set requirt register)
///	_disable();
	
	cmd = 0xEC;	//do IDENTIFY DEVICE first
	write_io_byte(0x70,0x80);
	
get_again:
	if(cmd == 0xA1)
	{
		//reset device
		write_io_byte(Port+HDD_DRIVE_HEAD  ,(0xA0|(Device<<4))); //Drive/Head
		write_io_byte(Port+HDD_CMD ,0x08); //Command Register (drive 0)
		read_io_byte(0x84,&nu);
		Delay_1us(15000);//必須長一點，避免有些裝置來不及
	}
	else
	{
		Delay_1us(5000);//一般裝置reset
	}
	
	write_io_byte(Port+HDD_FEATURE,0);//Feature
	write_io_byte(Port+HDD_SECTOR_COUNT,0);//Sector Count
	write_io_byte(Port+HDD_SECTOR_NUM  ,0); //Sector Number
	write_io_byte(Port+HDD_CYL_LOW     ,0); //Cylinder Low
	write_io_byte(Port+HDD_CYL_HI      ,0); //Cylinder High
	write_io_byte(Port+HDD_DRIVE_HEAD  ,(0xA0|(Device<<4))); //Drive/Head
	write_io_byte(Port+HDD_CMD         ,cmd); //Command Register (drive 0)

	read_io_byte(0x84,&nu);
	//check status. Busy must set.
	read_io_byte(Port+HDD_STATUS,&Status);
		
	if((Status & STS_ERR)==STS_ERR)
	{//檢查是否有 error 產生
		return false;
	}
	if ((Status & STS_BSY)==0 )
	{
		return false;//No drive connected.
	}
	
	if(((Status & STS_BSY)==0)&&((Status & STS_DRQ)==0))//Idel
	{
		if (IsPacketSignature(Port) != 0)
		{//每次都必須去讀取，不然裝置會失效，下次就讀不到了
			cmd = 0xA1;	//do IDENTIFY PACKET DEVICE
			goto get_again;//return ABORT;//Packet device found;
		}
		else
		{
			return false;
		}
	}

	//Wait to enter Transfer Data state
	for(i = 0 ; i < 0x100000; i++)
	{
		read_io_byte(Port+HDD_STATUS,&Status);
		if((Status & STS_BSY)==0) //Busy bit clear.
		{
			break;
		}
		Delay_1us(10000);
	}
	if(((Status & STS_BSY)==0)&&((Status & STS_DRQ)==0))//Idel
	{
		if (IsPacketSignature(Port) != 0)
		{//每次都必須去讀取，不然裝置會失效，下次就讀不到了
			cmd = 0xA1;	//do IDENTIFY PACKET DEVICE
			goto get_again;//return ABORT;//Packet device found;
		}
		else
		{
			return false;
		}
	}
	//Enter Transfer Data state.
	//make sure
	if((((Status & STS_BSY)==0)&&((Status & STS_DRQ)==STS_DRQ))==0)//Transfer Data
	{
		return false;//Unexpect error happen;
	}
	Status = GetIdentifyData(Port,Data);

	write_io_byte(0x70,0x00);

	return Status;
}

BYTE CWinIDEDlg::IsPacketSignature(WORD Port)
{//檢查是不是 packet device
	BYTE dd;
	
	read_io_byte(Port+HDD_CYL_LOW,&dd);
	if( dd!= 0x14)
	{
		return false; //Cylinder Low
	}
	
	read_io_byte(Port+HDD_CYL_HI,&dd);
	if(dd != 0xEB)
	{
		return false; //Cylinder High
	}
	
	read_io_byte(Port+HDD_DRIVE_HEAD,&dd);
	switch(dd)
	{
		case 0x00 :
		case 0x10 :
		case 0xA0 ://
		case 0xB0 ://Some device return A0,B0 signature as Packet device.
			return true;//Match Packet signature.
		default:
			return false;
	}
}


//Get 512 byte form port
//check check sum when byte 511 = 0xA5
// true  1
// false 0
// Packet 0x80
BYTE CWinIDEDlg::GetIdentifyData(WORD Port,BYTE *Data)
{//檢查 checksum 對不對
	WORD i;
	WORD *pt;
	BYTE CheckSum;
	
	pt = (WORD *)Data;
	for( i = 0 ; i < 256; i++)
	{
		read_io_word(Port+HDD_DATA,pt);
		pt++;
	}

	if(Data[511] == 0xA5)//The byte 510 is checksum
	{
		CheckSum = 0;
		for( i = 0; i < 512; i++)
		{
			CheckSum += Data[i];
		}
		if(CheckSum != 0)//Check != 0 means error.
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	//No check sum require
	return true;
}

void CWinIDEDlg::GetHDDpara(WORD Port,BYTE Device,HDDpara *Para,BYTE *DataBuff)
{
	DEVICE_TBL *pt;
	PACKET_TBL *pt2;
	WORD i,j;
	BYTE *p;
	BYTE tmp[50];
	double size,size2;

	if((DataBuff[1] & 0x0F) == 0x05)
	{//如果是CD-ROM
		Para->Devicetype = 2;//是cd-rom

up:
		pt2 = (PACKET_TBL *)DataBuff;
		Para->Sector  = 0;
		Para->Cylinder= 0;
		Para->Head    = 0;

		memset(tmp,0,sizeof(tmp));
		for( i = 0; i < 40; i+=2)
		{//兩個一組，相反放，要改回來
			tmp[i]= pt2->Model[i + 1];
			tmp[i+1]=pt2->Model[i];
		}
		memset(Para->Model,0,sizeof(Para->Model));
		//清除中間的空白處，只保留一個
		p = &(Para->Model[0]);
		for(i = 0; i < 40; i++)
		{
			*p = tmp[i];
			if(tmp[i] == ' ' && tmp[i + 1] == ' ')
			{
				for(j = i; j < 40; j++)
				{
					if(tmp[j] != ' ')
					{
						i = j - 1;
						break;
					}
				}
				if(j == 40)
				{
//					p++;
					break;
				}
			}
			p++;
		}
		*p = '\0';
		
		memset(tmp,0,sizeof(tmp));
		memset(Para->Serial,0,sizeof(Para->Serial));
		for( i = 0; i < 20; i+=2)
		{//兩個一組，相反放，要改回來
			tmp[i]= pt2->Serial[i + 1];//跳過前面的空白
			tmp[i+1]=pt2->Serial[i];
		}
		p = tmp;//因為存放位置有前後之分，所以要先搬到最前面
		j = 0;
		for(i = 0; i < 20; i++)
		{
			if(*p != ' ')
			{
				Para->Serial[j] = *p;
				j++;
			}
			p++;
		}
		Para->Serial[j] = '\0';//在空白處補上結束符號
		
		memset(Para->FW,0,sizeof(Para->FW));
		for( i = 0; i < 8; i+=2)
		{//兩個一組，相反放，要改回來
			Para->FW[i]= pt2->FW[i +1];
			Para->FW[i+1]=pt2->FW[i];
		}
		p = &(Para->FW[0]);//在空白處補上結束符號
		for(i = 0; i < 8; i++)
		{
			if(*p == ' ')
			{
				*p = '\0';
			}
			p++;
		}
		Para->Size = 0;
		Para->Installed = 1;
	}
	else if((DataBuff[1] & 0x0F) == 0x01)
	{
		Para->Devicetype = 3;//是tape
		goto up;
	}
	else //HDD
	{
		pt = (DEVICE_TBL *)DataBuff;
		Para->Sector  = pt->Sector;
		Para->Cylinder= pt->Cylinder;
		Para->Head    = pt->Head;
		
		memset(tmp,0,sizeof(tmp));
		for( i = 0; i < 40; i+=2)
		{//兩個一組，相反放，要改回來
			tmp[i]= pt->Model[i + 1];
			tmp[i+1]=pt->Model[i];
		}
		
		memset(Para->Model,0,sizeof(Para->Model));
		//清除中間的空白處，只保留一個
		p = &(Para->Model[0]);
		for(i = 0; i < 40; i++)
		{
			*p = tmp[i];
			if(tmp[i] == ' ' && tmp[i + 1] == ' ')
			{
				for(j = i; j < 40; j++)
				{
					if(tmp[j] != ' ')
					{
						i = j - 1;
						break;
					}
				}
				if(j == 40)
				{
					break;
				}
			}
			p++;
		}
		*p = '\0';
		
		memset(tmp,0,sizeof(tmp));
		memset(Para->Serial,0,sizeof(Para->Serial));
		for( i = 0; i < 20; i+=2)
		{//兩個一組，相反放，要改回來
			tmp[i]= pt->Serial[i + 1];//跳過前面的空白
			tmp[i+1]=pt->Serial[i];
		}
		p = tmp;//因為存放位置有前後之分，所以要先搬到最前面
		j = 0;
		for(i = 0; i < 20; i++)
		{
			if(*p != ' ')
			{
				Para->Serial[j] = *p;
				j++;
			}
			p++;
		}
		Para->Serial[j] = '\0';//在空白處補上結束符號
		
		memset(Para->FW,0,sizeof(Para->FW));
		for( i = 0; i < 8; i+=2)
		{//兩個一組，相反放，要改回來
			Para->FW[i]= pt->FW[i +1];
			Para->FW[i+1]=pt->FW[i];
		}
		p = &(Para->FW[0]);//在空白處補上結束符號
		for(i = 0; i < 8; i++)
		{
			if(*p == ' ')
			{
				*p = '\0';
			}
			p++;
		}
		
		if(pt->LBA != 0x0fffffff)
		{
			Para->LBA = pt->LBA;
			size2 = 0;
		}
		else //超過137G
		{
			Para->LBA = pt->Ex_LBA1;
			Para->Ex_LBA = pt->Ex_LBA2;
			
			size2 = (double)Para->Ex_LBA;
			size2 *= 512.0;//512byte per track.
			size2 /= 1024.0; //單位KB
			size2 /= 1024.0; //單位MB
			size2 *= 2097151.99951; //回復真正值
		}
		
		size = (double)Para->LBA;
		size *= 512.0;//512byte per track.
		size /= 1024.0; //單位KB
		size /= 1024.0; //單位MB
		size += size2;
		Para->Size = (DWORD)size;
		Para->Installed = 1;
		Para->Devicetype = 1;//是HDD
		
	}
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
