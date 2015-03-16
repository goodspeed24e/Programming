// Detaildlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinSMB.h"
#include "Detaildlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int smb_type;

extern BYTE read_nv_slave_data(BYTE slave_address, BYTE offset);
extern BYTE read_it_slave_data(BYTE slave_address, BYTE offset);

//void read_spd(void);

/////////////////////////////////////////////////////////////////////////////
// CDetaildlg dialog


CDetaildlg::CDetaildlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDetaildlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDetaildlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDetaildlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDetaildlg)
	DDX_Control(pDX, IDC_DATA_STATIC, m_data);
	DDX_Control(pDX, IDC_ASCII_STATIC, m_ascii);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDetaildlg, CDialog)
	//{{AFX_MSG_MAP(CDetaildlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDetaildlg message handlers

BOOL CDetaildlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	read_spd();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDetaildlg::read_spd(void)
{
	int i;
	BYTE data,x;
	char data_buf[1024],asc[1024],tmp_buf[10];
	

	x = 0;
	
	//addr = devs[current_sld].addr;
	ZeroMemory(data_buf,sizeof(data_buf));
	ZeroMemory(asc,sizeof(asc));
	for(i = 0; i < 128; i++)
	{
		if(smb_type == 0)
		{//NVidia
			data = read_nv_slave_data(addr,(BYTE)i);
		}
		else
		{
			data = read_it_slave_data(addr,(BYTE)i);
		}
		sprintf(tmp_buf,"%02X",data);
		strcat(data_buf,tmp_buf);
		
		//ASCII code
		if(data >= 0x20 && data <= 0x7e)
		{//如果是一般的字元
			sprintf(tmp_buf,"%c",data);
		}
		else
		{//特殊字元，用.表示
			strcpy(tmp_buf,".");
		}
		strcat(asc,tmp_buf);
		/*tmp = x * 3+7;
		gotoxy(tmp,(BYTE)(4+y));
		color_printf(B_WHITE | F_BLACK,"%02X",data);
		
		//ASCII code
		gotoxy((BYTE)(63+x),(BYTE)(y+4));
		if(data >= 0x20 && data <= 0x7e)
		{//如果是一般的字元
			color_printf(B_WHITE | F_BLACK,"%c",data);
		}
		else
		{//特殊字元，用.表示
			color_printf(B_WHITE | F_BLACK,".");
		}*/
		
		x++;
		if(x == 16)
		{
			x=0;
			strcat(data_buf,"\r\n");
			strcat(asc,"\r\n");
		}
		else
		{
			strcat(data_buf," ");
		}
	}
	m_data.SetWindowText(data_buf);
	m_ascii.SetWindowText(asc);
}
