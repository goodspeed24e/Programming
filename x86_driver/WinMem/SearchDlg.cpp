// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Memory.h"
#include "def.h"
#include "myio.h"
#include "SearchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern SEARCH_INFO s_info;
extern int str_to_hex(char *p, DWORD *data);
/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog


CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDlg)
	DDX_Control(pDX, IDC_WRITE_START_EDIT, m_write_start);
	DDX_Control(pDX, IDC_WRITE_DATA_EDIT, m_write_data);
	DDX_Control(pDX, IDC_STRING_RADIO, m_string);
	DDX_Control(pDX, IDC_HEX_RADIO, m_hex);
	DDX_Control(pDX, IDC_VALUE_EDIT, m_value);
	DDX_Control(pDX, IDC_END_EDIT, m_end);
	DDX_Control(pDX, IDC_START_EDIT, m_start);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchDlg)
	ON_BN_CLICKED(IDC_HEX_RADIO, OnHexRadio)
	ON_BN_CLICKED(IDC_STRING_RADIO, OnStringRadio)
	ON_BN_CLICKED(IDC_WRITE_BUTTON, OnWriteButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg message handlers

BOOL CSearchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_hex.SetCheck(BST_CHECKED);
	m_value.SetWindowText("");
	m_end.SetWindowText("FFFFFFFF");
	m_start.SetWindowText("00000000");
	OnOffHex();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchDlg::OnHexRadio() 
{
	// TODO: Add your control notification handler code here
	m_string.SetCheck(BST_UNCHECKED);
	OnOffHex();
}

void CSearchDlg::OnStringRadio() 
{
	// TODO: Add your control notification handler code here
	m_hex.SetCheck(BST_UNCHECKED);
	OnOffHex();
}

void CSearchDlg::OnOK() 
{
	// TODO: Add extra validation here
	char buf[20];
	
	if(m_start.GetWindowText(buf,sizeof(buf))==0)
	{
		MessageBox("開始位址未輸入","錯誤",MB_OK | MB_ICONSTOP);
		m_start.SetFocus();
		return;
	}
	str_to_hex(buf,&(s_info.sh_start));
	
	if(m_end.GetWindowText(buf,sizeof(buf))==0)
	{
		MessageBox("結束位址未輸入","錯誤",MB_OK | MB_ICONSTOP);
		m_end.SetFocus();
		return;
	}
	str_to_hex(buf,&(s_info.sh_end));
	
	if(m_value.GetWindowText(s_info.sh_value,sizeof(s_info.sh_value))==0)
	{
		MessageBox("找尋內容未輸入","錯誤",MB_OK | MB_ICONSTOP);
		m_value.SetFocus();
		return;
	}
	
	s_info.sh_type = 0;
	if(m_hex.GetCheck()==BST_UNCHECKED)
	{
		s_info.sh_type = 1;
	}
	
	CDialog::OnOK();
}

void CSearchDlg::OnOffHex(void)
{
	if(m_hex.GetCheck()==BST_UNCHECKED)
	{
		GetDlgItem(IDC_HEX_STATIC)->ShowWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_HEX_STATIC)->ShowWindow(TRUE);
	}
}

void CSearchDlg::OnWriteButton() 
{
	// TODO: Add your control notification handler code here
	char buf[20],data[10];
	DWORD start,w_data;
	int len,flag;
	
	if(m_write_start.GetWindowText(buf,sizeof(buf))==0)
	{
		MessageBox("開始位址未輸入","錯誤",MB_OK | MB_ICONSTOP);
		m_write_start.SetFocus();
		return;
	}
	if(str_to_hex(buf,&start)==1)
	{
		MessageBox("開始位址非16進位值","錯誤",MB_OK | MB_ICONSTOP);
		m_write_start.SetFocus();
		return;
	}
	
	len = m_write_data.GetWindowText(data,sizeof(data));
	if(len==0)
	{
		MessageBox("填寫內容未輸入","錯誤",MB_OK | MB_ICONSTOP);
		m_write_data.SetFocus();
		return;
	}
	
	switch(len)
	{
		case 2:
			flag=1;
			break;
		case 4:
			flag=2;
			break;
		case 8:
			flag=3;
			break;
		default:
			MessageBox("填寫內容只能2,4,8個字母","錯誤",MB_OK | MB_ICONSTOP);
			m_write_data.SetFocus();
			break;
	}
	
	if(str_to_hex(data,&w_data)==1)
	{
		MessageBox("填寫內容非16進位值","錯誤",MB_OK | MB_ICONSTOP);
		m_write_data.SetFocus();
		return;
	}
	
	//寫入
	switch(flag)
	{
		case 1:
			write_mem_byte(start, (BYTE)w_data);
			break;
		case 2:
			write_mem_word(start, (WORD)w_data);
			break;
		case 3:
			write_mem_dword(start, w_data);
			break;
	}
	
	MessageBox("資料寫入完成","提示",MB_OK | MB_ICONINFORMATION);
}
