// DetailView.cpp : implementation file
//

#include "stdafx.h"
#include "WinACPI.h"
#include "myio.h"
#include "acpi_def.h"
#include "DetailView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern struct RSDP rsdp;
int str_to_hex(char *p, DWORD *data);

char acpi_str[][40]=
{
	"Processor Local APIC",
	"I/O APIC",
	"Interrupt Source Override",
	"Non-maskable Interrupt Source[NMI]",
	"Local APIC NMI Structure",
	"Local APIC Address Override Structure",
	"I/O SAPIC",
	"Local SAPIC",
	"Platform Interrupt Sources"
};

/////////////////////////////////////////////////////////////////////////////
// CDetailView

IMPLEMENT_DYNCREATE(CDetailView, CFormView)

CDetailView::CDetailView()
	: CFormView(CDetailView::IDD)
{
	//{{AFX_DATA_INIT(CDetailView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDetailView::~CDetailView()
{
}

void CDetailView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDetailView)
	DDX_Control(pDX, IDC_SHOW_STATIC, m_show);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDetailView, CFormView)
	//{{AFX_MSG_MAP(CDetailView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDetailView diagnostics

#ifdef _DEBUG
void CDetailView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDetailView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDetailView message handlers

void CDetailView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	
	m_list.SetExtendedStyle(dwStyle);
}

void CDetailView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if( m_list.GetSafeHwnd() != 0)
	{
		//                       起點x,起點y,寬,高, 1:1.75左右(圖與實際顯示)
		m_list.SetWindowPos(NULL,0,0,cx,cy-22,SWP_NOMOVE | SWP_NOZORDER);
	}
	if( m_show.GetSafeHwnd() != 0)
	{
		//                       起點x,起點y,寬,高, 1:1.75左右(圖與實際顯示)
		m_show.SetWindowPos(NULL,0,0,cx,22,SWP_NOMOVE | SWP_NOZORDER);
	}
	
}


void CDetailView::GetTable(char *name,DWORD addr)
{
	char buf[100];
	BYTE data_buf[100];
	int i,nColumnCount,size;
	
	//清除list原本的東西
	nColumnCount = m_list.GetHeaderCtrl()->GetItemCount();
	for(i = 0; i < nColumnCount; i++)
	{
		m_list.DeleteColumn(0);
	}		
	m_list.DeleteAllItems();
	
	//加上欄位資料
	for(i = 0; i < 2; i++)
	{
		memset(buf,0,sizeof(buf));
		switch(i)
		{
			case 0:
				strcpy(buf,"欄位");
				size=120;
				break;
			case 1:
				strcpy(buf,"內容");
				size=650;
				break;
		}
		m_list.InsertColumn(i,buf,LVCFMT_LEFT,size);
	}
	
	posi=0;
	if(stricmp(name,"RSDP")==0)
	{//這個table沒有header
		expend_rsdp();
	}
	else if(stricmp(name,"FACS")==0)
	{//這個table沒有header
		size = sizeof(FACS);
		ReadData(addr,size,data_buf);
		expend_facs(data_buf);
	}
	else
	{
		size = sizeof(DESC_TABLE_HEAD);
		//header區data
		ReadData(addr,size,data_buf);
		expend_header(data_buf); //header區
		
		if(memcmp(data_buf,"RSDT",4)==0)
		{
			m_show.SetWindowText("Root System Description Table (RSDT)");
			//依signature來讀其餘資料
			expend_rsdt(addr,data_buf);
		}
		else if(memcmp(data_buf,"XSDT",4)==0)
		{
			m_show.SetWindowText("Extened System Description Table (XSDT)");
			//依signature來讀其餘資料
			expend_xsdt(addr,data_buf);
		}
		else if(memcmp(data_buf,"FADT",4)==0 || memcmp(data_buf,"FACP",4)==0)
		{
			m_show.SetWindowText("Fixed ACPI Description Table (FADT)");
			//依signature來讀其餘資料
			expend_fadt(addr,data_buf);
		}
		else if(memcmp(data_buf,"DSDT",4)==0)
		{
			m_show.SetWindowText("Differentiated System Description Table (DSDT)");
			//依signature來讀其餘資料
			expend_dsdt(addr,data_buf);
		}
		else if(memcmp(data_buf,"SSDT",4)==0 || memcmp(data_buf,"PSDT",4)==0)
		{
			m_show.SetWindowText("Secondary System Description Table (SSDT)");
			//依signature來讀其餘資料
			expend_ssdt(addr,data_buf);
		}
		else if(memcmp(data_buf,"MADT",4)==0 || memcmp(data_buf,"APIC",4)==0)
		{
			m_show.SetWindowText("Multiple APIC Description Table (MADT)");
			//依signature來讀其餘資料
			expend_madt(addr,data_buf);
		}
		else if(memcmp(data_buf,"SBST",4)==0)
		{
			m_show.SetWindowText("Smart Battery Specification Table (SBST)");
			//依signature來讀其餘資料
			expend_sbst(addr,data_buf);
		}
		else if(memcmp(data_buf,"ECDT",4)==0)
		{
			m_show.SetWindowText("Embedded Controller Boot Resources Table (ECDT)");
			//依signature來讀其餘資料
			expend_ecdt(addr,data_buf);
		}
		else if(memcmp(data_buf,"SRAT",4)==0)
		{
			m_show.SetWindowText("System Resource Affinity Table (SRAT)");
			//依signature來讀其餘資料
			expend_srat(addr,data_buf);
		}
		else if(memcmp(data_buf,"SLIT",4)==0)
		{
			m_show.SetWindowText("System Locality Distance Information Table (SLIT)");
			//依signature來讀其餘資料
			expend_slit(addr,data_buf);
		}
		else if(memcmp(data_buf,"MCFG",4)==0)
		{
			m_show.SetWindowText("PIC express Memory mapped ConFiGuration space base address description Table (MCFG)");
			//依signature來讀其餘資料
			expend_mcfg(addr,data_buf);
		}
		else if(memcmp(data_buf,"BOOT",4)==0)
		{
			m_show.SetWindowText("Simple Boot Flag Table (BOOT)");
			//依signature來讀其餘資料
			expend_boot(addr,data_buf);
		}
		else if(memcmp(data_buf,"HPET",4)==0 || memcmp(data_buf,"ETDT",4)==0)
		{
			m_show.SetWindowText("IA-PC High Precision Event Timer Table (HPET)");
			//依signature來讀其餘資料
			expend_hpet(addr,data_buf);
		}
		else if(memcmp(data_buf,"CPEP",4)==0)
		{
			m_show.SetWindowText("Corrected Platform Error Polling Table (CPEP)");
			//依signature來讀其餘資料
			expend_cpep(addr,data_buf);
		}
		else if(memcmp(data_buf,"DBGP",4)==0)
		{
			m_show.SetWindowText("Debug Port Table (DBGP)");
			//依signature來讀其餘資料
			expend_dbgp(addr,data_buf);
		}
		else if(memcmp(data_buf,"SPCR",4)==0)
		{
			m_show.SetWindowText("Serial Port Console Redirection Table (SPCR)");
			//依signature來讀其餘資料
			expend_spcr(addr,data_buf);
		}
		else if(memcmp(data_buf,"SPMI",4)==0)
		{
			m_show.SetWindowText("Service Processor Management Interface Description Table (SPMI)");
			//依signature來讀其餘資料
			expend_spmi(addr,data_buf);
		}
		else if(memcmp(data_buf,"TCPA",4)==0)
		{
			m_show.SetWindowText("Trusted Computing Platform Alliance Capabilities Table (TCPA)");
			//依signature來讀其餘資料
			expend_tcpa(addr,data_buf);
		}
		else if(memcmp(data_buf,"WDAT",4)==0)
		{
			m_show.SetWindowText("Watch Dog Action Table (WDAT)");
			//依signature來讀其餘資料
			expend_wdat(addr,data_buf);
		}
		else if(memcmp(data_buf,"WDRT",4)==0)
		{
			m_show.SetWindowText("Watchdog Resource Table (WDRT)");
			//依signature來讀其餘資料
			expend_wdrt(addr,data_buf);
		}
		else if(memcmp(data_buf,"WSPT",4)==0)
		{
			m_show.SetWindowText("Windows Specific Properties Table (WSPT)");
			//依signature來讀其餘資料
			expend_wspt(addr,data_buf);
		}
		else if(memcmp(data_buf,"ERST",4)==0)
		{
			m_show.SetWindowText("Error Record Serialization Table (ERST)");
			//依signature來讀其餘資料
			expend_erst(addr,data_buf);
		}
		else if(memcmp(data_buf,"BERT",4)==0)
		{
			m_show.SetWindowText("BOOT Error Record Table (BERT)");
			//依signature來讀其餘資料
			expend_bert(addr,data_buf);
		}
		else if(memcmp(data_buf,"HEST",4)==0)
		{
			m_show.SetWindowText("Hardware Error Source Table (HEST)");
			//依signature來讀其餘資料
			expend_hest(addr,data_buf);
		}
		else if(memcmp(data_buf,"EINJ",4)==0)
		{
			m_show.SetWindowText("Error Injection Table (EINJ)");
			//依signature來讀其餘資料
			expend_einj(addr,data_buf);
		}
		
		
		else
		{//未知的
			m_show.SetWindowText("Unknown");
			Write_list(0,0,"");
			Write_list(0,1,"Spec Not found");
		}
	}
}

void CDetailView::ReadData(DWORD addr,int size,BYTE *buff)
{
	int i;
	DWORD dwMemVal;
	
	//取得header大小
	//size = sizeof(DESC_TABLE_HEAD);
	
	ZeroMemory(buff,sizeof(buff));
	
	//取得資料
	for(i = 0; i < size; i+=4)
	{
		read_mem_dword((addr+i), &dwMemVal);
		buff[i] = (BYTE)dwMemVal;
		buff[i+1] = (BYTE)(dwMemVal >> 8);
		buff[i+2] = (BYTE)(dwMemVal >> 16);
		buff[i+3] = (BYTE)(dwMemVal >> 24);
	}
}

void CDetailView::Write_list(int posi, int col,char *value)
{
	LV_ITEM data;

	if(col==0)
	{
		data.mask = LVIF_TEXT;// | LVIF_PARAM | LVIF_STATE;
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

void CDetailView::expend_rsdp(void)
{
	//int posi=0;
	char buf[100];
	
	m_show.SetWindowText("Root System Description Pointer structure (RSDP)");
		
	Write_list(posi,0,"Signature");
	ZeroMemory(buf,sizeof(buf));
	memcpy(buf,rsdp.signature,8);
	Write_list(posi,1,buf);
	posi++;
		
	Write_list(posi,0,"Checksum");
	sprintf(buf,"%X (HEX)",rsdp.checksum);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"OEMID");
	ZeroMemory(buf,sizeof(buf));
	memcpy(buf,rsdp.OEMID,6);
	Write_list(posi,1,buf);
	posi++;
		
	Write_list(posi,0,"Revision");
	sprintf(buf,"%X (HEX)",rsdp.revision);
	Write_list(posi,1,buf);
	posi++;
		
	Write_list(posi,0,"RsdtAddress");
	sprintf(buf,"%08lX (HEX)",rsdp.rsdt_addr);
	Write_list(posi,1,buf);
	posi++;
		
	Write_list(posi,0,"Length");
	sprintf(buf,"%lX (HEX)",rsdp.length);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"XsdtAddress");
	sprintf(buf,"%08lX%08lX (HEX)",rsdp.xsdt_addr[1],rsdp.xsdt_addr[0]);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"Extended");
	sprintf(buf,"%X (HEX)",rsdp.ex_checksum);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%02X%02X%02X (HEX)",rsdp.reserved[2],rsdp.reserved[1],rsdp.reserved[0]);
	Write_list(posi,1,buf);
}

void CDetailView::expend_header(BYTE *buff)
{
	char buf[200],buf2[100];
	
	Write_list(posi,0,"Signature");
	ZeroMemory(buf,sizeof(buf));
	memcpy(buf,&(buff[0]),4);
	Write_list(posi,1,buf);
	posi++;
		
	Write_list(posi,0,"Length");
	sprintf(buf,"%02X%02X%02X%02X (HEX)",buff[7],buff[6],buff[5],buff[4]);
	Write_list(posi,1,buf);
	posi++;
		
	Write_list(posi,0,"Revision");
	sprintf(buf,"%02X (HEX)",buff[8]);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"Checksum");
	sprintf(buf,"%02X (HEX)",buff[9]);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"OEMID");
	ZeroMemory(buf2,sizeof(buf2));
	memcpy(buf2,&(buff[10]),6);
	sprintf(buf,"%s(%02X%02X%02X%02X%02X%02X hex)",buf2,buff[15],buff[14],buff[13],buff[12],buff[11],buff[10]);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"OEM Table ID");
	ZeroMemory(buf2,sizeof(buf2));
	memcpy(buf2,&(buff[16]),8);
	sprintf(buf,"%s(%02X%02X%02X%02X%02X%02X%02X%02X hex)",buf2,buff[23],buff[22],buff[21],buff[20],buff[19],buff[18],buff[17],buff[16]);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"OEM Revision");
	sprintf(buf,"%02X%02X%02X%02X (HEX)",buff[27],buff[26],buff[25],buff[24]);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"Creatot ID");
	ZeroMemory(buf2,sizeof(buf2));
	memcpy(buf2,&(buff[28]),4);
	sprintf(buf,"%s(%02X%02X%02X%02X hex)",buf2,buff[31],buff[30],buff[29],buff[28]);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"Creatot Revision");
	sprintf(buf,"%02X%02X%02X%02X (HEX)",buff[35],buff[34],buff[33],buff[32]);
	Write_list(posi,1,buf);
	posi++;
}

void CDetailView::expend_rsdt(DWORD addr,BYTE *buff)
{
	int i,cnt;
	char buf[100];
	DWORD start_addr,dwMemVal;
	
	sprintf(buf,"%02x%02x%02x%02x",buff[7],buff[6],buff[5],buff[4]);
	str_to_hex(buf,&dwMemVal);
	cnt = (dwMemVal - sizeof(DESC_TABLE_HEAD))/4;
	
		//sprintf(buf,"cnt=%d %ld %d",cnt,dwMemVal,sizeof(DESC_TABLE_HEAD));
		//AfxMessageBox(buf);
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	for(i = 0; i < cnt; i++)
	{
		read_mem_dword(start_addr, &dwMemVal);
		
		sprintf(buf,"Entry%d",i+1);
		Write_list(posi,0,buf);
		sprintf(buf,"%08lX (HEX)",dwMemVal);
		Write_list(posi,1,buf);
		posi++;
		
		start_addr+=4;
	}
}

void CDetailView::expend_xsdt(DWORD addr,BYTE *buff)
{
	Write_list(posi,0,"Not supported");
}

void CDetailView::expend_fadt(DWORD addr,BYTE *buff)
{
	char buf[100];
	DWORD start_addr,dwMemVal;
	BYTE btMemVal;
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);

	read_mem_dword(start_addr, &dwMemVal);	
	Write_list(posi,0,"Firmware Ctrl");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	start_addr+=4;

	read_mem_dword(start_addr, &dwMemVal);	
	Write_list(posi,0,"DSDT");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	start_addr+=4;
	
	read_mem_byte(start_addr, &btMemVal);	
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
}

void CDetailView::expend_facs(BYTE *buff)
{
	char tmp[5],buf[100];
	int i;
	
	m_show.SetWindowText("Firmware ACPI Control Structure(FACS)");
		
	Write_list(posi,0,"Signature");
	ZeroMemory(buf,sizeof(buf));
	memcpy(buf,&(buff[0]),4);
	Write_list(posi,1,buf);
	posi++;
		
	Write_list(posi,0,"Length");
	sprintf(buf,"%02X%02X%02X%02X (HEX)",buff[7],buff[6],buff[5],buff[4]);
	Write_list(posi,1,buf);
	posi++;
		
	Write_list(posi,0,"Hardware Signature");
	ZeroMemory(buf,sizeof(buf));
	sprintf(buf,"%02X%02X%02X%02X (HEX)",buff[11],buff[10],buff[9],buff[8]);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"Firmware Waking Vector");
	sprintf(buf,"%02X%02X%02X%02X (HEX)",buff[15],buff[14],buff[13],buff[12]);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"Global Lock");
	sprintf(buf,"%02X (HEX)",buff[19],buff[18],buff[17],buff[16]);
	Write_list(posi,1,buf);
	posi++;
	
	if((buff[16] & 0x1) == 0x1)
	{
		sprintf(buf,"Pending");
	}
	else
	{
		sprintf(buf,"Not pending");
	}
	Write_list(posi,0,"");
	Write_list(posi,1,buf);
	posi++;
	
	if((buff[16] & 0x2) == 0x2)
	{
		sprintf(buf,"Owned");
	}
	else
	{
		sprintf(buf,"Not owned");
	}
	Write_list(posi,0,"");
	Write_list(posi,1,buf);
	posi++;
	
	
	Write_list(posi,0,"Flags");
	sprintf(buf,"%02X (HEX)",buff[23],buff[22],buff[21],buff[20]);
	Write_list(posi,1,buf);
	posi++;
	
	if((buff[20] & 0x1) == 0x1)
	{
		sprintf(buf,"The platform supports S4BIOS_REQ");
	}
	else
	{
		sprintf(buf,"The platform does not support S4BIOS_REQ");
	}
	Write_list(posi,0,"");
	Write_list(posi,1,buf);
	posi++;
	
	
	Write_list(posi,0,"X firmware Waking Vector");
	sprintf(buf,"%02X%02X%02X%02X%02X%02X%02X%02X (HEX)",buff[31],buff[30],buff[29],buff[28],buff[27],buff[26],buff[25],buff[24]);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"Revision");
	sprintf(buf,"%X (HEX)",buff[32]);
	Write_list(posi,1,buf);
	posi++;
	
	ZeroMemory(buf,sizeof(buf));
	for(i = 0; i < 31; i++)
	{
		sprintf(tmp,"%02X",buff[33+i]);
		strcat(buf,tmp);
		if(i < 30)
		{
			strcat(buf," ");
		}
		else
		{
			strcat(buf," (HEX)");
		}
	}
	Write_list(posi,0,"Reserved");
	Write_list(posi,1,buf);
}

void CDetailView::expend_dsdt(DWORD addr,BYTE *buff)
{
	int cnt;
	char buf[100];
	DWORD start_addr,dwMemVal;
	
	sprintf(buf,"%02x%02x%02x%02x",buff[7],buff[6],buff[5],buff[4]);
	str_to_hex(buf,&dwMemVal);
	cnt = dwMemVal - sizeof(DESC_TABLE_HEAD);
	
		//sprintf(buf,"cnt=%d %ld %d",cnt,dwMemVal,sizeof(DESC_TABLE_HEAD));
		//AfxMessageBox(buf);
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	sprintf(buf,"Too many data, please use WinMem to see it at:%08lX, length:%d",start_addr,cnt);
	
	Write_list(posi,0,"Definition Block");
	Write_list(posi,1,buf);
}

void CDetailView::expend_ssdt(DWORD addr,BYTE *buff)
{
	int cnt;
	char buf[100];
	DWORD start_addr,dwMemVal;
	
	sprintf(buf,"%02x%02x%02x%02x",buff[7],buff[6],buff[5],buff[4]);
	str_to_hex(buf,&dwMemVal);
	cnt = dwMemVal - sizeof(DESC_TABLE_HEAD);
	
		//sprintf(buf,"cnt=%d %ld %d",cnt,dwMemVal,sizeof(DESC_TABLE_HEAD));
		//AfxMessageBox(buf);
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	sprintf(buf,"Too many data, please use WinMem to see it at:%08lX, length:%d",start_addr,cnt);
	
	Write_list(posi,0,"Definition Block");
	Write_list(posi,1,buf);
}

void CDetailView::expend_madt(DWORD addr,BYTE *buff)
{
	int i,j,k,cnt,cntt=1;
	char buf[200];
	BYTE tmp[200];
	BYTE btMemVal;
	DWORD start_addr,dwMemVal;
	
	sprintf(buf,"%02x%02x%02x%02x",buff[7],buff[6],buff[5],buff[4]);
	str_to_hex(buf,&dwMemVal);
	cnt = dwMemVal - sizeof(MADT); //附加list的總byte數
	
		//sprintf(buf,"cnt=%d %ld %d",cnt,dwMemVal,sizeof(DESC_TABLE_HEAD));
		//AfxMessageBox(buf);
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
	read_mem_dword(start_addr, &dwMemVal);	
	Write_list(posi,0,"Locak APIC Address");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	start_addr+= 4;
	
	read_mem_dword(start_addr, &dwMemVal);	
	Write_list(posi,0,"Plags");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	if((dwMemVal & 0x00000001) == 0x00000001)
	{
		Write_list(posi,0,"");
		Write_list(posi,1,"System has a PC-AT-compatible dual-8259 setup");
		posi++;
	}
	
	start_addr += 4;
	
//		return;
	
	for(i = 0; i < cnt; i++)
	{
		ZeroMemory(tmp,sizeof(tmp));
		
		//種類
		read_mem_byte(start_addr, &btMemVal);
		tmp[0] = btMemVal;
		start_addr ++;
		
		//數量
		read_mem_byte(start_addr, &btMemVal);
		tmp[1] = btMemVal;
		start_addr ++;
		
		k = 2;
		for(j = 0; j < tmp[1]-2; j++)
		{
			read_mem_byte(start_addr, &btMemVal);
			tmp[k] = btMemVal;
			start_addr ++;
			k++;
		}
			//start_addr += tmp[1]-2;
		i+=tmp[1]-1;
		
		Write_list(posi,0,"");
		sprintf(buf,"************** APIC structure %d *****************",cntt);
		Write_list(posi,1,buf);
		posi++;
		
		Write_list(posi,0,"Type");
		if(tmp[0] <= 8)
		{
			sprintf(buf,"%d (%s)",tmp[0],acpi_str[tmp[0]]);
		}
		else if(tmp[0] > 8 && tmp[0] < 128)
		{
			strcpy(buf,"Reserved. OSPM skips structure of the reserved type");
		}
		else
		{
			strcpy(buf,"Reserved for OEM use");
		}
		Write_list(posi,1,buf);
		posi++;
		
		Write_list(posi,0,"Length");
		sprintf(buf,"%d(%X hex)",tmp[1],tmp[1]);
		Write_list(posi,1,buf);
		posi++;
		
		switch(tmp[0])
		{
			case 0:
				Write_list(posi,0,"APIC Processor ID");
				sprintf(buf,"%X (HEX)",tmp[2]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"APIC ID");
				sprintf(buf,"%X (HEX)",tmp[3]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Flags");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[7],tmp[6],tmp[5],tmp[4]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"");
				if((tmp[4] & 0x1) == 0x1)
				{
					Write_list(posi,1,"Processor usable");
				}
				else
				{
					Write_list(posi,1,"Processor unusable");
				}
				posi++;
				
				break;
			case 1:
				Write_list(posi,0,"I/O APIC ID");
				sprintf(buf,"%X (HEX)",tmp[2]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Reserved");
				sprintf(buf,"%X (HEX)",tmp[3]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"I/O APIC Address");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[7],tmp[6],tmp[5],tmp[4]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Global System Interrupt Base");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[11],tmp[10],tmp[9],tmp[8]);
				Write_list(posi,1,buf);
				posi++;
				break;
			case 2:
				Write_list(posi,0,"Bus");
				sprintf(buf,"%X (HEX)",tmp[2]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Source");
				sprintf(buf,"%X (HEX)",tmp[3]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Global System Interrupt");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[7],tmp[6],tmp[5],tmp[4]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Flags");
				sprintf(buf,"%02X%02X (HEX)",tmp[9],tmp[8]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"");
				switch(tmp[8] & 0x3)
				{
					case 0:
						Write_list(posi,1,"Polarity - Conforms to specifications of the bus");
						break;
					case 1:
						Write_list(posi,1,"Polarity - Active high");
						break;
					case 2:
						Write_list(posi,1,"Polarity - Reserved");
						break;
					case 3:
						Write_list(posi,1,"Polarity - Active low");
						break;
				}
				posi++;
				
				Write_list(posi,0,"");
				switch(tmp[8] & 0xC)
				{
					case 0x0:
						Write_list(posi,1,"Trigger Mode - Conforms to specifications of the bus");
						break;
					case 0x4:
						Write_list(posi,1,"Trigger Mode - Edge-triggered");
						break;
					case 0x8:
						Write_list(posi,1,"Trigger Mode - Reserved");
						break;
					case 0xc:
						Write_list(posi,1,"Trigger Mode - Level-triggered");
						break;
				}
				posi++;
				break;
			case 3:
				Write_list(posi,0,"Flags");
				sprintf(buf,"%02X%02X (HEX)",tmp[3],tmp[2]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"");
				switch(tmp[2] & 0x3)
				{
					case 0:
						Write_list(posi,1,"Polarity - Conforms to specifications of the bus");
						break;
					case 1:
						Write_list(posi,1,"Polarity - Active high");
						break;
					case 2:
						Write_list(posi,1,"Polarity - Reserved");
						break;
					case 3:
						Write_list(posi,1,"Polarity - Active low");
						break;
				}
				posi++;
				
				Write_list(posi,0,"");
				switch(tmp[2] & 0xC)
				{
					case 0x0:
						Write_list(posi,1,"Trigger Mode - Conforms to specifications of the bus");
						break;
					case 0x4:
						Write_list(posi,1,"Trigger Mode - Edge-triggered");
						break;
					case 0x8:
						Write_list(posi,1,"Trigger Mode - Reserved");
						break;
					case 0xc:
						Write_list(posi,1,"Trigger Mode - Level-triggered");
						break;
				}
				posi++;
				
				Write_list(posi,0,"Global System interrupt");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[7],tmp[6],tmp[5],tmp[4]);
				Write_list(posi,1,buf);
				posi++;
				break;
			case 4:
				Write_list(posi,0,"ACPI Processor ID");
				sprintf(buf,"%02X (HEX)",tmp[2]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Flags");
				sprintf(buf,"%02X%02X (HEX)",tmp[4],tmp[3]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"");
				switch(tmp[3] & 0x3)
				{
					case 0:
						Write_list(posi,1,"Polarity - Conforms to specifications of the bus");
						break;
					case 1:
						Write_list(posi,1,"Polarity - Active high");
						break;
					case 2:
						Write_list(posi,1,"Polarity - Reserved");
						break;
					case 3:
						Write_list(posi,1,"Polarity - Active low");
						break;
				}
				posi++;
				
				Write_list(posi,0,"");
				switch(tmp[3] & 0xC)
				{
					case 0x0:
						Write_list(posi,1,"Trigger Mode - Conforms to specifications of the bus");
						break;
					case 0x4:
						Write_list(posi,1,"Trigger Mode - Edge-triggered");
						break;
					case 0x8:
						Write_list(posi,1,"Trigger Mode - Reserved");
						break;
					case 0xc:
						Write_list(posi,1,"Trigger Mode - Level-triggered");
						break;
				}
				posi++;
				
				Write_list(posi,0,"Local APIC LINT#");
				sprintf(buf,"%02X (HEX)",tmp[5]);
				Write_list(posi,1,buf);
				posi++;
				break;
			case 5:
				Write_list(posi,0,"Reserved");
				sprintf(buf,"%02X%02X (HEX)",tmp[3],tmp[2]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Local ACPI Address");
				sprintf(buf,"%02X%02X%02X%02X%02X%02X%02X%02X (HEX)",tmp[11],tmp[10],tmp[9],tmp[8],tmp[7],tmp[6],tmp[5],tmp[4]);
				Write_list(posi,1,buf);
				posi++;
				break;
			case 6:
				Write_list(posi,0,"I/O APIC ID");
				sprintf(buf,"%02X (HEX)",tmp[2]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Reserved");
				sprintf(buf,"%02X (HEX)",tmp[3]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Global system Interrupt Base");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[7],tmp[6],tmp[5],tmp[4]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"I/O SAPIC Address");
				sprintf(buf,"%02X%02X%02X%02X%02X%02X%02X%02X (HEX)",tmp[15],tmp[14],tmp[13],tmp[12],tmp[11],tmp[10],tmp[9],tmp[8]);
				Write_list(posi,1,buf);
				posi++;
				break;
			case 7:
				Write_list(posi,0,"APIC Processor ID");
				sprintf(buf,"%02X (HEX)",tmp[2]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Local SAPIC ID");
				sprintf(buf,"%02X (HEX)",tmp[3]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Local SAPIC EID");
				sprintf(buf,"%02X (HEX)",tmp[4]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Reserved");
				sprintf(buf,"%02X%02X%02X (HEX)",tmp[7],tmp[6],tmp[5]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Flags");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[11],tmp[10],tmp[9],tmp[8]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"");
				if((tmp[8] & 0x1) == 0x1)
				{
					Write_list(posi,1,"Processor usable");
				}
				else
				{
					Write_list(posi,1,"Processor unusable");
				}
				posi++;
				
				Write_list(posi,0,"ACPI Processor UID Vlaue");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[15],tmp[14],tmp[13],tmp[12]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"ACPI Processor UID String");
				sprintf(buf,"%s",&tmp[16]);
				Write_list(posi,1,buf);
				posi++;
				break;
			case 8:
				Write_list(posi,0,"Flags");
				sprintf(buf,"%02X%02X (HEX)",tmp[3],tmp[2]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"");
				switch(tmp[2] & 0x3)
				{
					case 0:
						Write_list(posi,1,"Polarity - Conforms to specifications of the bus");
						break;
					case 1:
						Write_list(posi,1,"Polarity - Active high");
						break;
					case 2:
						Write_list(posi,1,"Polarity - Reserved");
						break;
					case 3:
						Write_list(posi,1,"Polarity - Active low");
						break;
				}
				posi++;
				
				Write_list(posi,0,"");
				switch(tmp[2] & 0xC)
				{
					case 0x0:
						Write_list(posi,1,"Trigger Mode - Conforms to specifications of the bus");
						break;
					case 0x4:
						Write_list(posi,1,"Trigger Mode - Edge-triggered");
						break;
					case 0x8:
						Write_list(posi,1,"Trigger Mode - Reserved");
						break;
					case 0xc:
						Write_list(posi,1,"Trigger Mode - Level-triggered");
						break;
				}
				posi++;
				
				Write_list(posi,0,"Interrupt Type");
				sprintf(buf,"%02X (HEX)",tmp[4]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"");
				switch(tmp[4])
				{
					case 1:
						Write_list(posi,1,"PMI");
						break;
					case 2:
						Write_list(posi,1,"INIT");
						break;
					case 3:
						Write_list(posi,1,"Correntd Platform error Interrupt");
						break;
					default:
						Write_list(posi,1,"Reserved");
						break;
				}
				posi++;
				
				Write_list(posi,0,"Processor ID");
				sprintf(buf,"%02X (HEX)",tmp[5]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Processor EID");
				sprintf(buf,"%02X (HEX)",tmp[6]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"I/O SAPIC Vector");
				sprintf(buf,"%02X (HEX)",tmp[7]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Global System Interrupt");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[11],tmp[10],tmp[9],tmp[8]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Platform Interrupt Source Flags");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[15],tmp[14],tmp[13],tmp[12]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"");
				if((tmp[12] & 0x1) == 0x1)
				{
					Write_list(posi,1,"CPEI Processor Override - enable");
				}
				else
				{
					Write_list(posi,1,"CPEI Processor Override - disable");
				}
				posi++;
				break;
				
		}
		cntt++;
	}
}

void CDetailView::expend_sbst(DWORD addr,BYTE *buff)
{
	DWORD start_addr,dwMemVal;
	char buf[100];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
	read_mem_dword(start_addr, &dwMemVal);	
	Write_list(posi,0,"Warning Energy Level (mWh)");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	start_addr+=4;
	
	read_mem_dword(start_addr, &dwMemVal);	
	Write_list(posi,0,"Low Energy Level (mWh)");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	start_addr+=4;
	
	read_mem_dword(start_addr, &dwMemVal);	
	Write_list(posi,0,"Critical Energy Level (mWh)");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);

}

void CDetailView::expend_ecdt(DWORD addr,BYTE *buff)
{
	int i,j;
	char buf[100],tmp[20];
	DWORD start_addr,dwMemVal;
	BYTE btMemVal;
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
	for(i = 0; i < 2; i++)
	{
		ZeroMemory(buf,sizeof(buf));
		for(j = 0; j < 3; j++)
		{
			read_mem_dword(start_addr, &dwMemVal);
			sprintf(tmp,"%02X %02X %02X %02X",(BYTE)dwMemVal,(BYTE)(dwMemVal>>8),(BYTE)(dwMemVal>>16),(BYTE)(dwMemVal>>24));
			strcat(buf,tmp);
			if(i != 2)
			{
				strcat(buf," ");
			}
			start_addr += 4;
		}
		if(i == 0)
		{
			Write_list(posi,0,"EC_CONTROL");
		}
		else
		{
			Write_list(posi,0,"EC_DATA");
		}
	
		Write_list(posi,1,buf);
		posi++;
	}
	
	read_mem_dword(start_addr, &dwMemVal);	
	Write_list(posi,0,"UID");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	start_addr+=4;
	
	read_mem_byte(start_addr, &btMemVal);	
	Write_list(posi,0,"GPE_BIT");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	start_addr++;
	
	i = 0;
	ZeroMemory(buf,sizeof(buf));
	while(1)
	{
		read_mem_byte(start_addr, &btMemVal);
		start_addr++;
		if(btMemVal == '\0')
		{
			break;
		}
		buf[i] = (char)btMemVal;
		i++;
	}
	
	Write_list(posi,0,"EC_ID");
	Write_list(posi,1,buf);
}

void CDetailView::expend_srat(DWORD addr,BYTE *buff)
{
	int i,j,k,cntt=1,cnt;
	char buf[100];
	BYTE tmp[200];
	DWORD start_addr,dwMemVal;
	BYTE btMemVal;
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
	sprintf(buf,"%02x%02x%02x%02x",buff[7],buff[6],buff[5],buff[4]);
	str_to_hex(buf,&dwMemVal);
	cnt = dwMemVal - sizeof(SRAT); //附加struct的總byte數
	
	read_mem_dword(start_addr, &dwMemVal);	
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	start_addr+=4;
	
	ZeroMemory(buf,sizeof(buf));
	for(i = 0; i < 2; i++)
	{
		read_mem_dword(start_addr, &dwMemVal);
		sprintf((char *)tmp,"%02X%02X%02X%02X",(BYTE)dwMemVal,(BYTE)(dwMemVal>>8),(BYTE)(dwMemVal>>16),(BYTE)(dwMemVal>>24));
		start_addr+=4;
		strcat(buf,(char *)tmp);
		if(i == 1)
		{
			strcat(buf," (HEX)");
		}
	}
	Write_list(posi,0,"Reserved");
	Write_list(posi,1,buf);
	posi++;
	
	for(i = 0; i < cnt; i++)
	{
		ZeroMemory(tmp,sizeof(tmp));
		
		//種類
		read_mem_byte(start_addr, &btMemVal);
		tmp[0] = btMemVal;
		start_addr ++;
		
		//數量
		read_mem_byte(start_addr, &btMemVal);
		tmp[1] = btMemVal;
		start_addr ++;
		
		k = 2;
		for(j = 0; j < tmp[1]-2; j++)
		{
			read_mem_byte(start_addr, &btMemVal);
			tmp[k] = btMemVal;
			start_addr ++;
			k++;
		}
			//start_addr += tmp[1]-2;
		i+=tmp[1]-1;
		
		Write_list(posi,0,"");
		sprintf(buf,"************** Static Resource Allocation structure %d *****************",cntt);
		Write_list(posi,1,buf);
		posi++;
		
		Write_list(posi,0,"Type");
		if(tmp[0] == 0)
		{
			strcpy(buf,"0 - Processor Local APIC/SAPIC Affinity Structure");
		}
		else
		{
			strcpy(buf,"1 - Memory Affinity Structure");
		}
		Write_list(posi,1,buf);
		posi++;
		
		Write_list(posi,0,"Length");
		sprintf(buf,"%d(%X hex)",tmp[1],tmp[1]);
		Write_list(posi,1,buf);
		posi++;
		
		switch(tmp[0])
		{
			case 0:
				Write_list(posi,0,"Proximity Domain[7:0]");
				sprintf(buf,"%X (HEX)",tmp[2]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"APIC ID");
				sprintf(buf,"%X (HEX)",tmp[3]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Flags");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[7],tmp[6],tmp[5],tmp[4]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"");
				if((tmp[4] & 0x1) == 0x1)
				{
					Write_list(posi,1,"OSPM use the contents of the Processor Local APIC/SAPIC Affinity structure");
				}
				else
				{
					Write_list(posi,1,"OSPM ignore the contents of the Processor Local APIC/SAPIC Affinity structure");
				}
				posi++;
				
				Write_list(posi,0,"Local SAPIC EID");
				sprintf(buf,"%X (HEX)",tmp[8]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Proximity Domain [31:8]");
				sprintf(buf,"%02X%02X%02X (HEX)",tmp[11],tmp[10],tmp[9]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Reserved");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[15],tmp[14],tmp[13],tmp[12]);
				Write_list(posi,1,buf);
				posi++;
				
				break;
			case 1:
				Write_list(posi,0,"Proximity Domain");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[5],tmp[4],tmp[3],tmp[2]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Reserved");
				sprintf(buf,"%02X%02X (HEX)",tmp[7],tmp[6]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Base Address Low");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[11],tmp[10],tmp[9],tmp[8]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Base Address High");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[15],tmp[14],tmp[13],tmp[12]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Length Low");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[19],tmp[18],tmp[17],tmp[16]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Length High");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[23],tmp[22],tmp[21],tmp[20]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Reserved");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[27],tmp[26],tmp[25],tmp[24]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"Flags");
				sprintf(buf,"%02X%02X%02X%02X (HEX)",tmp[31],tmp[30],tmp[29],tmp[28]);
				Write_list(posi,1,buf);
				posi++;
				
				Write_list(posi,0,"");
				if((tmp[28] & 0x1) == 0x1)
				{
					Write_list(posi,1,"OSPM use the contents of the Processor Local APIC/SAPIC Affinity structure");
				}
				else
				{
					Write_list(posi,1,"OSPM ignore the contents of the Processor Local APIC/SAPIC Affinity structure");
				}
				posi++;
				
				Write_list(posi,0,"");
				if((tmp[28] & 0x2) == 0x2)
				{
					Write_list(posi,1,"The system hardware supports hot-add and hot-remove");
				}
				else
				{
					Write_list(posi,1,"The system hardware does not support hot-add and hot-remove");
				}
				posi++;
				
				Write_list(posi,0,"Reserved");
				sprintf(buf,"%02X%02X%02X%02X%02X%02X%02X%02X (HEX)",tmp[39],tmp[38],tmp[37],tmp[36],tmp[35],tmp[34],tmp[33],tmp[32]);
				Write_list(posi,1,buf);
				posi++;
				break;
		}
		cntt++;
	}
}

void CDetailView::expend_slit(DWORD addr,BYTE *buff)
{
	DWORD start_addr,dwMemVal,cntt=1;
	BYTE btMemVal;
	char buf[100];
	_int64 i,j,no=0;
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
//	ZeroMemory(buf,sizeof(buf));
	
	for(i =0; i < 2; i++)
	{
		read_mem_dword(start_addr, &dwMemVal);	
		start_addr+=4;
		if(i == 0)
		{
			j = dwMemVal;
		}
		else
		{
			no = dwMemVal;
			no <<= 32;
			no |= j;
		}
	}
	
	Write_list(posi,0,"Number of System Localities");
	sprintf(buf,"%016llX (HEX)",no);
	Write_list(posi,1,buf);
	posi++;
	
	for(i = 0; i < no; i++)
	{
		for(j = 0; j < no; j++)
		{
			Write_list(posi,0,"");
			sprintf(buf,"************** System Locality %ld *****************",cntt);
			Write_list(posi,1,buf);
			posi++;
		
			read_mem_byte(start_addr, &btMemVal);
			start_addr++;
			
			sprintf(buf,"Entry[%lld][%lld]",i,j);
			Write_list(posi,0,buf);
			sprintf(buf,"%02X (HEX)",btMemVal);
			Write_list(posi,1,buf);
			posi++;
			
			cntt++;
		}
	}
	
}

void CDetailView::expend_mcfg(DWORD addr,BYTE *buff)
{
	DWORD start_addr,dwMemVal,m;
	WORD data16;
	BYTE btMemVal;
	_int64 r;
	int i,cnt;
	char buf[100];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
	sprintf(buf,"%02x%02x%02x%02x",buff[7],buff[6],buff[5],buff[4]);
	str_to_hex(buf,&dwMemVal);
	cnt = (dwMemVal - sizeof(MCFG) - 8)/16; //附加struct的總數量
	
	for(i =0; i < 2; i++)
	{
		read_mem_dword(start_addr, &dwMemVal);	
		start_addr+=4;
		if(i == 0)
		{
			m = dwMemVal;
		}
		else
		{
			r = dwMemVal;
			r <<= 32;
			r |= m;
		}
	}
	
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%016llX (HEX)",r);
	Write_list(posi,1,buf);
	posi++;
	
	//	sprintf(buf,"cnt=%d",cnt);
	//	AfxMessageBox(buf);
	for(i = 0; i < cnt; i++)
	{
		Write_list(posi,0,"");
		sprintf(buf,"************** Configuration space %d *****************",i+1);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &dwMemVal);
		start_addr+=4;
		m = dwMemVal;
		
		read_mem_dword(start_addr, &dwMemVal);
		start_addr+=4;
		r = dwMemVal;
		r <<= 32;
		r |= m;
		
		Write_list(posi,0,"Base Address");
		sprintf(buf,"%016llX (HEX)",r);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_word(start_addr, &data16);
		start_addr+=2;
		
		Write_list(posi,0,"PCI Segment Group Number");
		sprintf(buf,"%04X (HEX)",data16);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_byte(start_addr, &btMemVal);
		start_addr++;
		
		Write_list(posi,0,"Start Bus Number");
		sprintf(buf,"%02X (HEX)",btMemVal);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_byte(start_addr, &btMemVal);
		start_addr++;
		
		Write_list(posi,0,"End Bus Number");
		sprintf(buf,"%02X (HEX)",btMemVal);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &dwMemVal);
		start_addr+=4;
		
		Write_list(posi,0,"Reserved");
		sprintf(buf,"%08lX (HEX)",dwMemVal);
		Write_list(posi,1,buf);
		posi++;
	}
	
}

void CDetailView::expend_boot(DWORD addr,BYTE *buff)
{
	DWORD start_addr,dwMemVal;
	char buf[100];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	
	Write_list(posi,0,"CMOS Index");
	sprintf(buf,"%02X (HEX)",(BYTE)dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	dwMemVal>>= 8;
	
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%02X%02X%02X (HEX)",(BYTE)(dwMemVal>>16),(BYTE)(dwMemVal>>8),(BYTE)dwMemVal);
	Write_list(posi,1,buf);
	posi++;
}

void CDetailView::expend_hpet(DWORD addr,BYTE *buff)
{
	DWORD start_addr,dwMemVal,d1,d2;
	BYTE btMemVal;
	WORD data16;
	char buf[100];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	
	Write_list(posi,0,"Event Timer Block ID");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"");
	sprintf(buf,"PCI Vendor ID of 1st Timer Block - %04X",(WORD)(dwMemVal>>16));
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"");
	sprintf(buf,"Legacy Replacement IRQ Routing Capable - %d",(BYTE)((dwMemVal>>15)&0x1));
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"");
	sprintf(buf,"COUNT_SIZE_CAP counter size - %d",(BYTE)((dwMemVal>>13)&0x1));
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"");
	sprintf(buf,"Number of Comparators in 1st Timer Block - %X(HEX)",(BYTE)((dwMemVal>>8)&0x1F));
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"");
	sprintf(buf,"Hardware Rev ID - %02X(HEX)",(BYTE)dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &d1);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &d2);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	
	Write_list(posi,0,"Base Address Lower 32-bit");
	sprintf(buf,"%08lX%08lX%08lX (HEX)",dwMemVal,d2,d1);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"HPET Number");
	sprintf(buf,"%d",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_word(start_addr, &data16);	
	start_addr+=2;
	
	Write_list(posi,0,"Main Counter Minimum Clock_tick in Peridic Mode");
	sprintf(buf,"%02X (HEX)",data16);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Page Protection And OEM Attribute");
	sprintf(buf,"%X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	if((btMemVal & 0xf) == 0)
	{
		strcpy(buf,"[3:0] - no guarantee for page protection");
	}
	else if((btMemVal & 0xf) == 1)
	{
		strcpy(buf,"[3:0] - 4KB page protected...");
	}
	else if((btMemVal & 0xf) == 2)
	{
		strcpy(buf,"[3:0] - 64KB page protected...");
	}
	else
	{
		strcpy(buf,"[3:0] - Reserved for future use");
	}
	Write_list(posi,0,"");
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"");
	Write_list(posi,1,"[7:4] - OEM attributes");
	posi++;
}

void CDetailView::expend_cpep(DWORD addr,BYTE *buff)
{
	DWORD start_addr,dwMemVal,d1;
	char buf[100];
	int i,cnt;
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	sprintf(buf,"%02x%02x%02x%02x",buff[7],buff[6],buff[5],buff[4]);
	str_to_hex(buf,&dwMemVal);
	cnt = (dwMemVal - sizeof(MCFG) - 8)/8; //附加struct的總數量
	
	read_mem_dword(start_addr, &d1);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%08lX%08lX (HEX)",dwMemVal,d1);
	Write_list(posi,1,buf);
	posi++;
	
	for(i = 0; i < cnt; i++)
	{
		Write_list(posi,0,"");
		sprintf(buf,"************** CPEP structure %d *****************",i+1);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &dwMemVal);	
		start_addr+=4;
		Write_list(posi,0,"Type");
		sprintf(buf,"%02X (HEX)",(BYTE)dwMemVal);
		Write_list(posi,1,buf);
		posi++;
		
		dwMemVal >>= 8;
		Write_list(posi,0,"Length");
		sprintf(buf,"%02X (HEX)",(BYTE)dwMemVal);
		Write_list(posi,1,buf);
		posi++;
		
		dwMemVal >>= 8;
		Write_list(posi,0,"Processor ID");
		sprintf(buf,"%02X (HEX)",(BYTE)dwMemVal);
		Write_list(posi,1,buf);
		posi++;
		
		dwMemVal >>= 8;
		Write_list(posi,0,"Processor EID");
		sprintf(buf,"%02X (HEX)",(BYTE)dwMemVal);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &dwMemVal);	
		start_addr+=4;
		Write_list(posi,0,"Polling Interval");
		sprintf(buf,"%08lX (HEX)",dwMemVal);
		Write_list(posi,1,buf);
		posi++;
	}
}

void CDetailView::expend_dbgp(DWORD addr,BYTE *buff)
{
	DWORD start_addr,dwMemVal,d1,d2;
	BYTE btMemVal;
	char buf[100];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Interface Type");
	if(btMemVal == 0)
	{
		sprintf(buf,"%02X (HEX) - full 16550 interface",btMemVal);
	}
	else if(btMemVal == 1)
	{
		sprintf(buf,"%02X (HEX) - 16550 subset interface compatible with Microsoft Debug Port Specification",btMemVal);
	}
	else
	{
		sprintf(buf,"%02X (HEX) - reserved",btMemVal);
	}
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=3;
	dwMemVal &= 0x00FFFFFF;
	
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%06lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &d1);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &d2);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	
	Write_list(posi,0,"Base Address");
	sprintf(buf,"%08lX%08lX%08lX (HEX)",dwMemVal,d2,d1);
	Write_list(posi,1,buf);
	posi++;
}

void CDetailView::expend_spcr(DWORD addr,BYTE *buff)
{
	DWORD start_addr,dwMemVal,d1,d2;
	BYTE btMemVal;
	char buf[200];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Interface Type");
	if(btMemVal == 0)
	{
		sprintf(buf,"%02X (HEX) - full 16550 interface",btMemVal);
	}
	else if(btMemVal == 1)
	{
		sprintf(buf,"%02X (HEX) - 16550 subset interface compatible with Microsoft Debug Port Specification",btMemVal);
	}
	else
	{
		sprintf(buf,"%02X (HEX) - reserved",btMemVal);
	}
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=3;
	dwMemVal &= 0x00FFFFFF;
	
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%06lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &d1);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &d2);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	
	Write_list(posi,0,"Base Address");
	sprintf(buf,"%08lX%08lX%08lX (HEX)",dwMemVal,d2,d1);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Interrupt Type");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"");
	sprintf(buf,"bit[0] - PC-AT-compatible dual-8259 IRQ interrupt - %s",(btMemVal&0x1) ? "supported" : "not supported");
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"");
	sprintf(buf,"bit[1] - I/O APIC interrupt(Global System Interrupt) - %s",(btMemVal&0x2) ? "supported" : "not supported");
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"");
	sprintf(buf,"bit[2] - I/O SAPIC interrupt(Global System Interrupt)(IRQ) - %s",(btMemVal&0x4) ? "supported" : "not supported");
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"IRQ");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	
	Write_list(posi,0,"Global System Interrupt");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Baud Rate");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	if(btMemVal == 3)
	{
		strcpy(buf,"9600bps");
	}
	else if(btMemVal == 4)
	{
		strcpy(buf,"19200bps");
	}
	else if(btMemVal == 6)
	{
		strcpy(buf,"57600bps");
	}
	else if(btMemVal == 7)
	{
		strcpy(buf,"115200bps");
	}
	else
	{
		strcpy(buf,"reserved");
	}
	
	Write_list(posi,0,"");
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Parity");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	if(btMemVal == 0)
	{
		strcpy(buf,"No parity");
	}
	else
	{
		strcpy(buf,"reserved");
	}
	
	Write_list(posi,0,"");
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Stop bits");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	if(btMemVal == 1)
	{
		strcpy(buf,"1 Stop bit");
	}
	else
	{
		strcpy(buf,"reserved");
	}
	
	Write_list(posi,0,"");
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Flow Control");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	if((btMemVal&0x1) == 1)
	{
		strcpy(buf,"DCD required for transmit");
	}
	else if((btMemVal&0x2) == 2)
	{
		strcpy(buf,"RTS/CTS hardware flow control");
	}
	else if((btMemVal&0x4) == 4)
	{
		strcpy(buf,"XON/XOFF software control");
	}
	else
	{
		strcpy(buf,"reserved");
	}
	
	Write_list(posi,0,"");
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Terminal Type");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	if(btMemVal == 0)
	{
		strcpy(buf,"VT100");
	}
	else if(btMemVal == 1)
	{
		strcpy(buf,"VT-100+");
	}
	else if(btMemVal == 2)
	{
		strcpy(buf,"VT-UTF8");
	}
	else if(btMemVal == 3)
	{
		strcpy(buf,"ANSI");
	}
	else
	{
		strcpy(buf,"reserved");
	}
	
	Write_list(posi,0,"");
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	
	Write_list(posi,0,"PCI Device ID");
	sprintf(buf,"%04X (HEX)",(WORD)dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"PCI Vendor ID");
	sprintf(buf,"%04X (HEX)",(WORD)(dwMemVal>>16));
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"PCI Bus Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"PCI Device Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"PCI Function Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	
	Write_list(posi,0,"PCI Flags");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"PCI Segment");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
}

void CDetailView::expend_spmi(DWORD addr,BYTE *buff)
{
	DWORD start_addr,dwMemVal,d1,d2;
	BYTE btMemVal;
	char buf[200];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Interface Type");
	if(btMemVal == 0)
	{
		sprintf(buf,"%02X (HEX) - Reserved",btMemVal);
	}
	else if(btMemVal == 1)
	{
		sprintf(buf,"%02X (HEX) - Keyboard Controller Style (KCS)",btMemVal);
	}
	else if(btMemVal == 2)
	{
		sprintf(buf,"%02X (HEX) - Server Management Interface Chip (SMIC)",btMemVal);
	}
	else if(btMemVal == 3)
	{
		sprintf(buf,"%02X (HEX) - Block Transfer (BT)",btMemVal);
	}
	else if(btMemVal == 4)
	{
		sprintf(buf,"%02X (HEX) - SMBus System Interface (SSIF)",btMemVal);
	}
	else
	{
		sprintf(buf,"%02X (HEX) - reserved",btMemVal);
	}
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=2;
	
	Write_list(posi,0,"Specification Revision");
	sprintf(buf,"%04X (HEX)",(WORD)dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Interrupt Type");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"");
	Write_list(posi,1,"[7:2] - Reserved");
	posi++;
	
	Write_list(posi,0,"");
	Write_list(posi,1,"[1] - I/O APIC/SAPIC interrupt(Global System Interrupt)");
	posi++;
	
	Write_list(posi,0,"");
	sprintf(buf,"[0] - SCI triggered through GPE - %s",(btMemVal&0x1) ? "supported" : "not supported");
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"GPE");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"PCI Device Flag");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	
	Write_list(posi,0,"Global System Interrupt");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &d1);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &d2);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	
	Write_list(posi,0,"Base Address");
	sprintf(buf,"%08lX%08lX%08lX (HEX)",dwMemVal,d2,d1);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"PCI segment Group Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"PCI Bus Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"PCI Device Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"PCI Function Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
}

void CDetailView::expend_tcpa(DWORD addr,BYTE *buff)
{
	//
}

void CDetailView::expend_wdat(DWORD addr,BYTE *buff)
{
	DWORD start_addr,dwMemVal,d1,d2,i,cnt;
	BYTE btMemVal;
	char buf[200];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	Write_list(posi,0,"Watchdog Header Length");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=2;
	Write_list(posi,0,"PCI Segment");
	sprintf(buf,"%04X (HEX)",(WORD)dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	Write_list(posi,0,"PCI Bus Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	Write_list(posi,0,"PCI Device Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	Write_list(posi,0,"PCI Function Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=3;
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%06lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	Write_list(posi,0,"Timer Period");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	Write_list(posi,0,"Maximum Count");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	Write_list(posi,0,"Minimum Count");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	Write_list(posi,0,"Watchdog Flags");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=3;
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%06lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	Write_list(posi,0,"Number watch instruction entries");
	sprintf(buf,"%08lX (HEX)",dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	cnt = dwMemVal;
	for(i = 0; i < cnt; i++)
	{
		Write_list(posi,0,"");
		sprintf(buf,"************** Watchdog Instruction Entry %ld *****************",i+1);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_byte(start_addr, &btMemVal);	
		start_addr++;
		Write_list(posi,0,"Watchdog Action");
		sprintf(buf,"%02X (HEX)",btMemVal);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_byte(start_addr, &btMemVal);	
		start_addr++;
		Write_list(posi,0,"Instruction Flags");
		sprintf(buf,"%02X (HEX)",btMemVal);
		Write_list(posi,1,buf);
		posi++;
		
		if(btMemVal == 0)
		{
			strcpy(buf,"Read Value");
		}
		else if(btMemVal == 1)
		{
			strcpy(buf,"Read Countdown");
		}
		else if(btMemVal == 2)
		{
			strcpy(buf,"Write Value");
		}
		else if(btMemVal == 3)
		{
			strcpy(buf,"Write Countdown");
		}
		else if(btMemVal == 0x80)
		{
			strcpy(buf,"Preserve register");
		}
		Write_list(posi,0,"");
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &dwMemVal);	
		start_addr+=2;
		Write_list(posi,0,"Reserved");
		sprintf(buf,"%02X (HEX)",(WORD)dwMemVal);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &d1);	
		start_addr+=4;
		
		read_mem_dword(start_addr, &d2);	
		start_addr+=4;
		
		read_mem_dword(start_addr, &dwMemVal);	
		start_addr+=4;
		Write_list(posi,0,"Register region");
		sprintf(buf,"%08lX%08lX%08lX (HEX)",dwMemVal,d2,d1);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &dwMemVal);	
		start_addr+=4;
		Write_list(posi,0,"Value");
		sprintf(buf,"%08lX (HEX)",dwMemVal);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &dwMemVal);	
		start_addr+=4;
		Write_list(posi,0,"Mask");
		sprintf(buf,"%08lX (HEX)",dwMemVal);
		Write_list(posi,1,buf);
		posi++;
	}
	
}

void CDetailView::expend_wdrt(DWORD addr,BYTE *buff)
{
	DWORD start_addr,dwMemVal,d1,d2;
	BYTE btMemVal;
	char buf[200];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	
	read_mem_dword(start_addr, &d1);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &d2);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	Write_list(posi,0,"Control Register Address");
	sprintf(buf,"%08lX%08lX%08lX (HEX)",dwMemVal,d2,d1);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &d1);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &d2);	
	start_addr+=4;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	Write_list(posi,0,"Count Register Address");
	sprintf(buf,"%08lX%08lX%08lX (HEX)",dwMemVal,d2,d1);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=4;
	Write_list(posi,0,"PCI Device ID");
	sprintf(buf,"%04X (HEX)",(WORD)dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	Write_list(posi,0,"PCI Vendor ID");
	sprintf(buf,"%04X (HEX)",(WORD)(dwMemVal>>16));
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	Write_list(posi,0,"PCI Bus Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	Write_list(posi,0,"PCI Device Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	Write_list(posi,0,"PCI Function Number");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	Write_list(posi,0,"PCI Segment");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &dwMemVal);	
	start_addr+=2;
	Write_list(posi,0,"Max Count");
	sprintf(buf,"%04X (HEX)",(WORD)dwMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &btMemVal);	
	start_addr++;
	Write_list(posi,0,"Units");
	sprintf(buf,"%02X (HEX)",btMemVal);
	Write_list(posi,1,buf);
	posi++;
	
	if(btMemVal == 0)
	{
		strcpy(buf,"1 second/count");
	}
	else if(btMemVal == 1)
	{
		strcpy(buf,"100 milli-second/count");
	}
	
	else if(btMemVal == 2)
	{
		strcpy(buf,"10 milli-second/count");
	}
	
	Write_list(posi,0,"");
	Write_list(posi,1,buf);
	posi++;
}

void CDetailView::expend_wspt(DWORD addr,BYTE *buff)
{
	Write_list(posi,0,"");
	Write_list(posi,1,"Spec Not found");
	posi++;
}


void CDetailView::expend_erst(DWORD addr,BYTE *buff)
{
	DWORD start_addr,i,d1,d2,d3,d4;
	BYTE d8;
	char buf[200];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	read_mem_dword(start_addr, &d1);
	start_addr+=4;
	Write_list(posi,0,"Serialization Header Size");
	sprintf(buf,"%08lX (HEX)",d1);
	Write_list(posi,1,buf);
	posi++;
	
	
	read_mem_dword(start_addr, &d1);
	start_addr+=4;
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%08lX (HEX)",d1);
	Write_list(posi,1,buf);
	posi++;
	
	
	read_mem_dword(start_addr, &d1);
	start_addr+=4;
	Write_list(posi,0,"Instruction Entry Count");
	sprintf(buf,"%08lX (HEX)",d1);
	Write_list(posi,1,buf);
	posi++;
	
	//action table起頭
	for(i = 0; i < d1; i++)
	{
		sprintf(buf,"Serialization Action Table - %d",i+1);
		Write_list(posi,0,buf);
		posi++;
		
		read_mem_byte(start_addr, &d8);
		start_addr++;
		Write_list(posi,0,"Serialization Action");
		sprintf(buf,"%02X (HEX)",d8);
		Write_list(posi,1,buf);
		posi++;
		
		
		read_mem_byte(start_addr, &d8);
		start_addr++;
		Write_list(posi,0,"Instruction");
		sprintf(buf,"%02X (HEX)",d8);
		Write_list(posi,1,buf);
		posi++;
		

		read_mem_byte(start_addr, &d8);
		start_addr++;
		Write_list(posi,0,"Flags");
		sprintf(buf,"%02X (HEX)",d8);
		Write_list(posi,1,buf);
		posi++;
		

		read_mem_byte(start_addr, &d8);
		start_addr++;
		Write_list(posi,0,"Reserved");
		sprintf(buf,"%02X (HEX)",d8);
		Write_list(posi,1,buf);
		posi++;
		

		read_mem_dword(start_addr, &d2);
		start_addr+=4;
		read_mem_dword(start_addr, &d3);
		start_addr+=4;
		read_mem_dword(start_addr, &d4);
		start_addr+=4;
		Write_list(posi,0,"Register Region");
		sprintf(buf,"%08lX%08lX%08lX (HEX)",d4,d3,d2);
		Write_list(posi,1,buf);
		posi++;
		
		
		read_mem_dword(start_addr, &d2);
		start_addr+=4;
		read_mem_dword(start_addr, &d3);
		start_addr+=4;
		Write_list(posi,0,"Value");
		sprintf(buf,"%08lX%08lX (HEX)",d3,d2);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &d2);
		start_addr+=4;
		read_mem_dword(start_addr, &d3);
		start_addr+=4;
		Write_list(posi,0,"Mask");
		sprintf(buf,"%08lX%08lX (HEX)",d3,d2);
		Write_list(posi,1,buf);
		posi++;
		
	}
	
}

void CDetailView::expend_bert(DWORD addr,BYTE *buff)
{
	DWORD start_addr,d1,d2;
	char buf[200];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	read_mem_dword(start_addr, &d1);
	start_addr+=4;
	Write_list(posi,0,"BOOT Error Region Length");
	sprintf(buf,"%08lX (HEX)",d1);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &d1);
	start_addr+=4;
	read_mem_dword(start_addr, &d2);
	start_addr+=4;
	Write_list(posi,0,"BOOT Error Region");
	sprintf(buf,"%08lX%08lX (HEX)",d2,d1);
	Write_list(posi,1,buf);
	posi++;
	
	
	
}

void CDetailView::expend_hest(DWORD addr,BYTE *buff)
{
	DWORD start_addr,i,d1,d2;
	WORD d16;
	BYTE d8;
	char buf[200];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	read_mem_dword(start_addr, &d1);
	start_addr+=4;
	Write_list(posi,0,"Error Source Count");
	sprintf(buf,"%08lX (HEX)",d1);
	Write_list(posi,1,buf);
	posi++;
	
	for(i = 0; i < d1; i++)
	{
		sprintf(buf,"Error Source Structure - %d",i+1);
		Write_list(posi,0,buf);
		posi++;
		
		read_mem_word(start_addr, &d16);
		start_addr+=2;
		Write_list(posi,0,"Type");
		sprintf(buf,"%04X (HEX)",d16);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_word(start_addr, &d16);
		start_addr+=2;
		Write_list(posi,0,"Souce Id");
		sprintf(buf,"%04X (HEX)",d16);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_word(start_addr, &d16);
		start_addr+=2;
		Write_list(posi,0,"Configuration Write Enable");
		sprintf(buf,"%04X (HEX)",d16);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_byte(start_addr, &d8);
		start_addr++;
		Write_list(posi,0,"Flags");
		sprintf(buf,"%02X (HEX)",d8);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_byte(start_addr, &d8);
		start_addr++;
		Write_list(posi,0,"Reserved");
		sprintf(buf,"%02X (HEX)",d8);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &d2);
		start_addr+=4;
		Write_list(posi,0,"Number of Records to Pre-allocate");
		sprintf(buf,"%08lX (HEX)",d2);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &d2);
		start_addr+=4;
		Write_list(posi,0,"Max Sections Per Record");
		sprintf(buf,"%08lX (HEX)",d2);
		Write_list(posi,1,buf);
		posi++;
		
	}
}

void CDetailView::expend_einj(DWORD addr,BYTE *buff)
{
	DWORD start_addr,i,d1,d2,d3,d4;
	BYTE d8;
	char buf[200];
	
	start_addr = addr+sizeof(DESC_TABLE_HEAD);
	read_mem_dword(start_addr, &d1);
	start_addr+=4;
	Write_list(posi,0,"Injection Header Size");
	sprintf(buf,"%08lX (HEX)",d1);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_byte(start_addr, &d8);
	start_addr++;
	Write_list(posi,0,"Reserved");
	sprintf(buf,"%02X (HEX)",d8);
	Write_list(posi,1,buf);
	posi++;
	
	read_mem_dword(start_addr, &d1);
	start_addr+=4;
	Write_list(posi,0,"Injection Entry Count");
	sprintf(buf,"%08lX (HEX)",d1);
	Write_list(posi,1,buf);
	posi++;
	
	for(i = 0; i < d1; i++)
	{
		sprintf(buf,"Injection Instruction Entry - %d",i+1);
		Write_list(posi,0,buf);
		posi++;
		
		read_mem_byte(start_addr, &d8);
		start_addr++;
		Write_list(posi,0,"Injection Action");
		sprintf(buf,"%02X (HEX)",d8);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_byte(start_addr, &d8);
		start_addr++;
		Write_list(posi,0,"Instruction");
		sprintf(buf,"%02X (HEX)",d8);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_byte(start_addr, &d8);
		start_addr++;
		Write_list(posi,0,"Flags");
		sprintf(buf,"%02X (HEX)",d8);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_byte(start_addr, &d8);
		start_addr++;
		Write_list(posi,0,"Reserved");
		sprintf(buf,"%02X (HEX)",d8);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &d2);
		start_addr+=4;
		read_mem_dword(start_addr, &d3);
		start_addr+=4;
		read_mem_dword(start_addr, &d4);
		start_addr+=4;
		Write_list(posi,0,"Register Region");
		sprintf(buf,"%08lX%08lX%08lX (HEX)",d4,d3,d2);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &d2);
		start_addr+=4;
		read_mem_dword(start_addr, &d3);
		start_addr+=4;
		Write_list(posi,0,"Value");
		sprintf(buf,"%08lX%08lX (HEX)",d3,d2);
		Write_list(posi,1,buf);
		posi++;
		
		read_mem_dword(start_addr, &d2);
		start_addr+=4;
		read_mem_dword(start_addr, &d3);
		start_addr+=4;
		Write_list(posi,0,"Mask");
		sprintf(buf,"%08lX%08lX (HEX)",d3,d2);
		Write_list(posi,1,buf);
		posi++;
		
	}
	
	
}





int str_to_hex(char *p, DWORD *data)                   // convert Hex ASCII to integer
{//字串轉16進位
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




