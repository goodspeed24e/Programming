// ListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCI.h"
#include "myio.h"
#include "def.h"
#include "RegDlg.h"
#include "ListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *ChangeVendor(WORD Vendor);
char *ChangeClass(WORD ClassID);
int hextoi(char *p, DWORD *data);

char work_path[1024];

struct SMBStructSystemSlots
{
	BYTE	type;
	BYTE	length;
	WORD	handle;
	BYTE	slotDesignation;
	BYTE	slotType;
	BYTE	slotDataBusWidth;
	BYTE	currentUsage;
	BYTE	slotLength;
	WORD	slotID;
	BYTE	slotCharactertics1;
	BYTE	slotCharactertics2;
	char	string[10][200];
};

struct SMBStructSystemSlots SMB_tp9[20];


/////////////////////////////////////////////////////////////////////////////
// CListDlg dialog


CListDlg::CListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListDlg, CDialog)
	//{{AFX_MSG_MAP(CListDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListDlg message handlers

BOOL CListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i;
	
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	m_list.SetExtendedStyle(dwStyle);
	
	m_regDlg = new CRegDlg;
	
	//取得 pci.ini path
	GetModuleFileName(NULL,work_path,1024);//取路徑
	i = strlen(work_path);
	while(work_path[i] != '\\')
	{
		i--;
	}
	work_path[i+1] = '\0';
	strcat(work_path,"PCI.ini");//完整路徑
	
	if(OnMyIo() == 0)
	{
		MessageBox("Fail to open MyIO","Error",MB_OK | MB_ICONSTOP);
		CDialog::OnOK();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CListDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	OffMyIo();
	return CDialog::DestroyWindow();
}

void CListDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CListDlg::Get_PCI_info(void)
{
	int i,j,k,len,posi=0;
	char buf[1024];
	WORD r_data,pp;
	BYTE tp,mm,dd;
	int nColumnCount;

	//清除list原本的東西
	nColumnCount = m_list.GetHeaderCtrl()->GetItemCount();
	for(i = 0; i < nColumnCount; i++)
	{
		m_list.DeleteColumn(0);
	}
			
	m_list.DeleteAllItems();
	
	//加上欄位資料
	for(i = 0; i < 7; i++)
	{
		memset(buf,0,sizeof(buf));
		switch(i)
		{
			case 0:
				strcpy(buf,"廠商");
				len=170;
				break;
			case 1:
				strcpy(buf,"裝置代號");
				len=80;
				break;
			case 2:
				strcpy(buf,"類別");
				len=170;
				break;
			case 3:
				strcpy(buf,"匯流排編號");
				len=120;
				break;
			case 4:
				strcpy(buf,"裝置編號");
				len=100;
				break;
			case 5:
				strcpy(buf,"功能");
				len=60;
				break;
			case 6:
				strcpy(buf,"備註");
				len=150;
				break;
		}
		m_list.InsertColumn(i,buf,LVCFMT_LEFT,len);
	}

	for(i = 0; i < 256; i++)
	{
		for(j = 0; j < 32; j++)
		{
			
			for(k = 0; k < 8; k++)
			{
				read_pci_word(i,j,k,0x00,&r_data);

				if(r_data != 0xffff)
				{
					if(k == 0)
					{//如果是第一次，判斷是否為單一功能裝置
						read_pci_byte(i,j,k,0x0e,&tp);
//							sprintf(buf,"tp=%02X",tp);
//							AfxMessageBox(buf);
						tp &= 0x80;
					}
					
					sprintf(buf,"%04X (%s)",r_data,ChangeVendor(r_data));
					Write_list(posi,0,buf);

					read_pci_word(i,j,k,0x02,&r_data);
					sprintf(buf,"%04X",r_data);
					Write_list(posi,1,buf);

					read_pci_word(i,j,k,0x0a,&r_data);
					sprintf(buf,"%04X (%s)",r_data,ChangeClass(r_data));
					Write_list(posi,2,buf);

					sprintf(buf,"%02X",i);
					Write_list(posi,3,buf);

					sprintf(buf,"%02X",j);
					Write_list(posi,4,buf);

					sprintf(buf,"%02X",k);
					Write_list(posi,5,buf);

					//檢查是不是PCI-E的裝置
					dd = 0;
					read_pci_byte(i,j,k,0x6,(BYTE *)(&pp));
					if(((pp>>4) & 0x01)==0x01)
					{
						read_pci_byte(i,j,k,0x34,&mm);
						mm &= 0xfc;
						while(mm)
						{
							read_pci_word(i,j,k,mm,&pp);
							mm = (unsigned char)((pp >> 8) & 0xff);
							if( (pp & 0x00ff) == 0x10)
							{
								dd = 1;
								break;
							}
						}
					}
					
					if(dd != 0)
					{
						Write_list(posi,6,"PCI-Express device");
					}
					
					posi++;
					
					if(k == 0 && tp != 0x80)
					{//單一功能裝置
						break;
					}
				}
			}
		}
	}
	m_dlg->PostMessage(WM_MSG_STATUS, 0, (LPARAM) AllocBuffer("Done"));
	
}

void CListDlg::Write_list(int posi, int col,char *value)
{
	LV_ITEM data;

	if(col == 0)
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

void CListDlg::Get_Slot_info(void)
{
	int i,nColumnCount,len,zz_cnt,flag,tb_cnt=0;
	char buf[100],tmp[1000];
	DWORD dwMemVal;
	BYTE Tp9_TB[sizeof(SMBStructSystemSlots)+4],vv;

	//清除list原本的東西
	nColumnCount = m_list.GetHeaderCtrl()->GetItemCount();
	for(i = 0; i < nColumnCount; i++)
	{
		m_list.DeleteColumn(0);
	}
			
	m_list.DeleteAllItems();
	
	if(ReadEntry() == 1)
	{
		//加上欄位資料
		for(i = 0; i < 8; i++)
		{
			memset(buf,0,sizeof(buf));
			switch(i)
			{
				case 0:
					strcpy(buf,"項目");
					len=150;
					break;
				case 1:
					strcpy(buf,"值");
					len=150;
					break;
				case 2:
					strcpy(buf,"說明");
					len=200;
					break;
			}
			m_list.InsertColumn(i,buf,LVCFMT_LEFT,len);
		}
	
		flag = 0;
		while(1)
		{
			//判斷是不是System Slot
			read_mem_dword(SMB_addr, &dwMemVal);
			if((BYTE)(dwMemVal & 0xff) == 0x9) //System Slot table
			{
					//AfxMessageBox("In");
				flag = 1;
				//get all data
				len = (BYTE)(dwMemVal >> 8);
	
				for(i = 0; i < len; i+=4)
				{
					read_mem_dword((SMB_addr+i), &dwMemVal);
					Tp9_TB[i] = (BYTE)dwMemVal;
					Tp9_TB[i+1] = (BYTE)(dwMemVal >> 8);
					Tp9_TB[i+2] = (BYTE)(dwMemVal >> 16);
					Tp9_TB[i+3] = (BYTE)(dwMemVal >> 24);
				}
	
				memcpy(&(SMB_tp9[tb_cnt]),Tp9_TB,Tp9_TB[1]);
	
				SMB_addr += Tp9_TB[1]; //跳過前面table區，直接抓字串
	
				//get string attached
				if(SMB_tp9[tb_cnt].slotDesignation != 0)
				{
					GetAttachedString(SMB_tp9[tb_cnt].string[SMB_tp9[tb_cnt].slotDesignation-1]);
				}
	
				SMB_addr++; //table與table之間是2個00
				tb_cnt++; //遞增數量
				//break;
			}
			else
			{
				if((BYTE)(dwMemVal & 0xff) == 0x7F) //end
				{
					break;
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
			}
		}
		
		if(flag != 0)
		{
			//	sprintf(buf,"cnt = %d",tb_cnt);
			//	AfxMessageBox(buf);
			len = 0;
			for(i = 0; i < tb_cnt; i++)
			{
				Write_list(len,0,"Type");
				sprintf(tmp,"%d",SMB_tp9[i].type);
				Write_list(len,1,tmp);
				Write_list(len,2,"SMBIOS type編號");
				len++;
	
				Write_list(len,0,"Length");
				sprintf(tmp,"0x%02X",SMB_tp9[i].length);
				Write_list(len,1,tmp);
				Write_list(len,2,"Type 9的資料長度");
				len++;
	
				Write_list(len,0,"Handle");
				sprintf(tmp,"0x%04X",SMB_tp9[i].handle);	
				Write_list(len,1,tmp);
				len++;
	
				Write_list(len,0,"Slot Designation");
				sprintf(tmp,"%s (0x%02X)",SMB_tp9[i].string[SMB_tp9[i].slotDesignation-1],SMB_tp9[i].slotDesignation);
				Write_list(len,1,tmp);
				Write_list(len,2,"主機板上的PCI slot編號");
				len++;
	
				Write_list(len,0,"Slot Type");
				sprintf(tmp,"0x%02X",SMB_tp9[i].slotType);
				Write_list(len,1,tmp);
				switch(SMB_tp9[i].slotType)
				{
					case 1:
						Write_list(len,2,"Other");
						break;
					case 2:
						Write_list(len,2,"Unknown");
						break;
					case 3:
						Write_list(len,2,"ISA");
						break;
					case 4:
						Write_list(len,2,"MCA");
						break;
					case 5:
						Write_list(len,2,"EISA");
						break;
					case 6:
						Write_list(len,2,"PCI");
						break;
					case 7:
						Write_list(len,2,"PC Card(PCMCIA)");
						break;
					case 8:
						Write_list(len,2,"VL-VESA");
						break;
					case 9:
						Write_list(len,2,"Proprietary");
						break;
					case 0xA:
						Write_list(len,2,"Processor Card Slot");
						break;
					case 0xB:
						Write_list(len,2,"Proprietary Memory Card Slot");
						break;
					case 0xC:
						Write_list(len,2,"I/O Riser Card Slot");
						break;
					case 0xD:
						Write_list(len,2,"NuBus");
						break;
					case 0xE:
						Write_list(len,2,"PCI-66Mhz Capable");
						break;
					case 0xF:
						Write_list(len,2,"AGP");
						break;
					case 0x10:
						Write_list(len,2,"AGP 2X");
						break;
					case 0x11:
						Write_list(len,2,"AGP-4X");
						break;
					case 0x12:
						Write_list(len,2,"PCI-X");
						break;
					case 0x13:
						Write_list(len,2,"AGP 8X");
						break;
					case 0xA0:
						Write_list(len,2,"PC-98/C20");
						break;
					case 0xA1:
						Write_list(len,2,"PC-98/C24");
						break;
					case 0xA2:
						Write_list(len,2,"PC-98/E");
						break;
					case 0xA3:
						Write_list(len,2,"PC-98/Local Bus");
						break;
					case 0xA4:
						Write_list(len,2,"PC-98/Card");
						break;
					case 0xA5:
						Write_list(len,2,"PCI Express");
						break;
				}
				len++;
	
				Write_list(len,0,"Slot Data Bus Width");
				sprintf(tmp,"0x%02X",SMB_tp9[i].slotDataBusWidth);
				Write_list(len,1,tmp);
				switch(SMB_tp9[i].slotDataBusWidth)
				{
					case 1:
						Write_list(len,2,"Other");
						break;
					case 2:
						Write_list(len,2,"Unknown");
						break;
					case 3:
						Write_list(len,2,"8bit");
						break;
					case 4:
						Write_list(len,2,"16bit");
						break;
					case 5:
						Write_list(len,2,"32bit");
						break;
					case 6:
						Write_list(len,2,"64bit");
						break;
					case 7:
						Write_list(len,2,"128bit");
						break;
					case 8:
						Write_list(len,2,"1x or x1");
						break;
					case 9:
						Write_list(len,2,"2x or x2");
						break;
					case 0xA:
						Write_list(len,2,"4x or x4");
						break;
					case 0xB:
						Write_list(len,2,"8x ro x8");
						break;
					case 0xC:
						Write_list(len,2,"12x or x12");
						break;
					case 0xD:
						Write_list(len,2,"16x or x16");
						break;
					case 0xE:
						Write_list(len,2,"32x or x32");
						break;
				}
				len++;
	
				Write_list(len,0,"Current Usage");
				sprintf(tmp,"0x%02X",SMB_tp9[i].currentUsage);
				Write_list(len,1,tmp);
				switch(SMB_tp9[i].currentUsage)
				{
					case 1:
						Write_list(len,2,"Other");
						break;
					case 2:
						Write_list(len,2,"Unknown");
						break;
					case 3:
						Write_list(len,2,"Availiable");
						break;
					case 4:
						Write_list(len,2,"In use");
						break;
				}
				len++;
	
				Write_list(len,0,"Slot Length");
				sprintf(tmp,"0x%02X",SMB_tp9[i].slotLength);
				Write_list(len,1,tmp);
				switch(SMB_tp9[i].slotLength)
				{
					case 1:
						Write_list(len,2,"Other");
						break;
					case 2:
						Write_list(len,2,"Unknown");
						break;
					case 3:
						Write_list(len,2,"Short Length");
						break;
					case 4:
						Write_list(len,2,"Long Length");
						break;
				}
				len++;
	
				Write_list(len,0,"Slot ID");
				sprintf(tmp,"0x%04X",SMB_tp9[i].slotID);
				Write_list(len,1,tmp);
				len++;
	
				Write_list(len,0,"Slot Characteristics1");
				sprintf(tmp,"0x%02X",SMB_tp9[i].slotCharactertics1);
				Write_list(len,1,tmp);
				ZeroMemory(tmp,sizeof(tmp));
				if((SMB_tp9[i].slotCharactertics1 & 0x01)==0x01)
				{
					strcpy(tmp,"Characteristics Unknown,");
				}
				if((SMB_tp9[i].slotCharactertics1 & 0x02)==0x02)
				{
					strcat(tmp,"Provides 5.0 Volts,");
				}
				if((SMB_tp9[i].slotCharactertics1 & 0x04) == 0x04)
				{
					strcat(tmp,"Provides 3.3 Volts,");
				}
				if((SMB_tp9[i].slotCharactertics1 & 0x08) == 0x08)
				{
					strcat(tmp,"Slot\'s opening is shared with another slot");
				}
				if((SMB_tp9[i].slotCharactertics1 & 0x10) == 0x10)
				{
					strcat(tmp,"PC Card slot supports PC Card-16");
				}
				if((SMB_tp9[i].slotCharactertics1 & 0x20) == 0x20)
				{
					strcat(tmp,"PC Card slot supports CardBus");
				}
				if((SMB_tp9[i].slotCharactertics1 & 0x40) == 0x40)
				{
					strcat(tmp,"PC Card slot supports Zoom Video");
				}
				if((SMB_tp9[i].slotCharactertics1 & 0x80) == 0x80)
				{
					strcat(tmp,"PC Card slot supports Modem Ring Resume");
				}
				Write_list(len,2,tmp);
				len++;
	
				Write_list(len,0,"Slot Characteristics1");
				sprintf(tmp,"0x%02X",SMB_tp9[i].slotCharactertics2);
				Write_list(len,1,tmp);
				ZeroMemory(tmp,sizeof(tmp));
				if((SMB_tp9[i].slotCharactertics2 & 0x01) == 0x01)
				{
					strcat(tmp,"PCI slot supports Power Management Enable(PME#) signal");
				}
				if((SMB_tp9[i].slotCharactertics2 & 0x02) == 0x02)
				{
					strcat(tmp,"Slot supports hot-plug devices");
				}
				if((SMB_tp9[i].slotCharactertics2 & 0x04) == 0x04)
				{
					strcat(tmp,"PCI slot supports SMBus signal");
				}
				Write_list(len,2,tmp);
				len++;

				if(tb_cnt > 1)
				{
					Write_list(len,0,"----------------------------------");
					Write_list(len,1,"-------------------------");
					len++;
				}
			}
		}
	}
	else
	{
		m_list.InsertColumn(0,"Note",LVCFMT_LEFT,200);
		Write_list(0,0,"找不到 SMBIOS table 9");
	}
}

void CListDlg::GetAttachedString(char *str)
{
	int i,j;
	BOOL flag;
	BYTE vv;
	DWORD	dwMemVal;
	
	i = 0;
	flag = FALSE;
	while(1)
	{
		read_mem_dword(SMB_addr, &dwMemVal);
		for(j = 0; j < 4; j++)
		{
			vv = (BYTE)(dwMemVal >> (j*8));
			if(vv != 0)
			{
				str[i+j] = vv;
			}
			else
			{
				flag = TRUE;
				break;
			}
		}
			
		if(flag != 0)
		{
			SMB_addr += j+1; //移到00的下一個，下一個可能是另一字串起點或00
			break;
		}
		i+=4;
		SMB_addr+=4;
	}
}

void CListDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if(func == 0)
	{
		Get_PCI_info();
	}
	else
	{
		Get_Slot_info();
	}
}

void CListDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(func==0)
	{
		DWORD dd;
		char buf[100];
		
		POSITION p = m_list.GetFirstSelectedItemPosition()-1; //start from 0
		if((int)p >= 0)
		{
			//vendor
			m_list.GetItemText((int)p,0,buf,sizeof(buf));
			strcpy(m_regDlg->para[0],buf);
			
			//device
			m_list.GetItemText((int)p,1,buf,sizeof(buf));
			strcpy(m_regDlg->para[1],buf);
			
			//class
			m_list.GetItemText((int)p,2,buf,sizeof(buf));
			strcpy(m_regDlg->para[2],buf);
			
			//bus
			m_list.GetItemText((int)p,3,buf,sizeof(buf));
			hextoi(buf,&dd);
			m_regDlg->bus = (BYTE)dd;
				
			//device no
			m_list.GetItemText((int)p,4,buf,sizeof(buf));
			hextoi(buf,&dd);
			m_regDlg->dev = (BYTE)dd;
				
			//function
			m_list.GetItemText((int)p,5,buf,sizeof(buf));
			hextoi(buf,&dd);
			m_regDlg->func = (BYTE)dd;
		
			ZeroMemory(buf,sizeof(buf));
			m_list.GetItemText((int)p,6,buf,sizeof(buf));
			if(buf[0] != 0)
			{
				m_regDlg->pci_express = 1;
			}
			else
			{
				m_regDlg->pci_express = 0;
			}
			
			m_regDlg->DoModal();
		}
	}
	
	*pResult = 0;
}

int CListDlg::ReadEntry(void)
{
	DWORD dwMemVal;
	BOOL flag=FALSE;
	
	for(SMB_addr = 0xf0000; SMB_addr < 0xfffff; SMB_addr+=4)
	{
		read_mem_dword(SMB_addr, &dwMemVal);
		if(dwMemVal==0x5F4d535F) //顛倒的_SM_
		{
			flag = TRUE;
			break;
		}
	}
	
	if(flag==TRUE)
	{
		SMB_addr+=24; //table 0 address
		read_mem_dword(SMB_addr, &dwMemVal);
		SMB_addr = dwMemVal;
		return 1;
	}
	return 0;
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

char *ChangeClass(WORD ClassID)
{
	WORD mclass,sclass;
	
	mclass = ClassID >> 8;
	sclass = ClassID & 0x00ff;
	
	switch(mclass)
	{
		case 0:
			return "Old Device(PCI 2.0)";
			
		case 1:
			if(sclass == 0)
			{
				return "SCSI Bus Controller";
			}
			else if(sclass == 1)
			{
				return "IDE Controller";
			}
			else if(sclass == 2)
			{
				return "Floppy Controller";
			}
			else if(sclass == 3)
			{
				return "IPI Controller";
			}
			else if(sclass == 4)
			{
				return "RAID Controller";
			}
			else
			{
				return "Another Controller";
			}
			
		case 2:
			if(sclass == 0)
			{
				return "Ethernet Network";
			}
			else if(sclass == 1)
			{
				return "Token Ring";
			}
			else if(sclass == 2)
			{
				return "FDDI Controller";
			}
			else if(sclass == 3)
			{
				return "ATM Controller";
			}
			else if(sclass == 4)
			{
				return "ISDN Controller";
			}
			else
			{
				return "Other network";
			}
			
		case 3:
			if(sclass == 0)
			{
				return "VGA Graphics";
			}
			else if(sclass == 1)
			{
				return "XGA Graphics";
			}
			else if(sclass == 2)
			{
				return "3D Graphics";
			}
			else
			{
				return "Other Graphics";
			}
			
		case 4:
			if(sclass == 0)
			{
				return "Video Multimedia";
			}
			else if(sclass == 1)
			{
				return "Audeo Multimedia";
			}
			else if(sclass == 2)
			{
				return "Phone Multimedia";
			}
			else
			{
				return "Other Multimedia";
			}
			
		case 6:
			if(sclass == 0)
			{
				return "Host to PCI Bridge";
			}
			else if(sclass == 1)
			{
				return "PCI to ISA Bridge";
			}
			else if(sclass == 2)
			{
				return "PCI to EISA Bridge";
			}
			else if(sclass == 3)
			{
				return "PCI to Micro Channel Bridge";
			}
			else if(sclass == 4)
			{
				return "PCI to PCI Bridge";
			}
			else if(sclass == 5)
			{
				return "PCI to PCMCIA Bridge";
			}
			else if(sclass == 6)
			{
				return "PCI to NuBus Bridge";
			}
			else if(sclass == 7)
			{
				return "PCI to CardBus Bridge";
			}
			else if(sclass == 8)
			{
				return "RACEway Bridge";
			}
			else
			{
				return "Other Bridge";
			}
			
		case 12:
			if(sclass == 0)
			{
				return "IEEE 1394";
			}
			else if(sclass == 1)
			{
				return "ACCESS.bus";
			}
			else if(sclass == 2)
			{
				return "Serial Storage Architecture";
			}
			else if(sclass == 3)
			{
				return "Universal Serial Bus[USB]";
			}
			else if(sclass == 4)
			{
				return "Fiber Channel";
			}
			else if(sclass == 5)
			{
				return "System Management Bus";
			}
		
		default:
			return "Unknown/Reserved";
	}
}

char *ChangeVendor(WORD Vendor)
{
	char buf[100];
	static char tmp[100];
	
	sprintf(buf,"%04X",Vendor);
	
	GetPrivateProfileString("PCI_INI",buf,"Unknown",tmp,sizeof(tmp),work_path);
	return tmp;
}
