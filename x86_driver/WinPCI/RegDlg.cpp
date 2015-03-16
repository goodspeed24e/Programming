// RegDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCI.h"
#include "myio.h"
#include "RegDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog


CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegDlg)
	DDX_Control(pDX, IDC_ROW_STATIC, m_row);
	DDX_Control(pDX, IDC_DESC_STATIC, m_title);
	DDX_Control(pDX, IDC_SCROLLBAR, m_scroll);
	DDX_Control(pDX, IDC_EDIT, m_reg);
	DDX_Control(pDX, IDC_ASC_STATIC, m_ascii);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegDlg, CDialog)
	//{{AFX_MSG_MAP(CRegDlg)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegDlg message handlers

BOOL CRegDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	int i;
	char title[1024];
	
	reg_start = 0;
	
	if(pci_express)
	{
		if(Cal_PciE_addr(bus,dev,func))
		{//�줣��memory�A���IO�覡
//				AfxMessageBox("No");
			pci_express = 0;
		}
			//sprintf(title,"addr=%lx",Pci_E_addr);
			//AfxMessageBox(title);
	}
	
	sprintf(title,"Vendor:%s  Device-ID:%s\n  Class:%s  Bus:%02Xh  Device:%02Xh  Fucntion:%02Xh",para[0],para[1],para[2],bus,dev,func);
	m_title.SetWindowText(title);
	
	if(!pci_express)
	{
		m_scroll.ShowWindow(FALSE);
	}
	
	Show_Data();
	Set_Scroll();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRegDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(pScrollBar->GetDlgCtrlID() == IDC_SCROLLBAR )
	{
		switch(nSBCode)
		{
			case SB_LINEDOWN: //�U�b�Y�Q���U
				if(reg_start < 0xffef)
				{
					reg_start+=16;
					Show_Data();
					Set_Scroll();
				}
				break;
				
			case SB_LINEUP: //�W�b�Y�Q���U
				if(reg_start >= 16)
				{
					reg_start-=16;
					Show_Data();
					Set_Scroll();
				}
				break;
			case SB_PAGEDOWN: //�i�����U��Q���U
				if(reg_start <= 0xff00)
				{
					reg_start += 256;
				}
				else
				{
					reg_start = 0xfff0;
				}
				Show_Data();
				Set_Scroll();
				break;
			case SB_PAGEUP: //�i�����W��Q���U
				if(reg_start > 256)
				{
					reg_start -= 256;
				}
				else
				{
					reg_start = 0;
				}
				Show_Data();
				Set_Scroll();
				break;
			case SB_THUMBPOSITION: //�i�����Q���U
				SCROLLINFO info;
				
				info.cbSize = sizeof(SCROLLINFO); 
				m_scroll.GetScrollInfo(&info);
				
				reg_start = info.nTrackPos * 0x10;
				
				Show_Data();
				Set_Scroll();
				break; 
		}
		
		
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CRegDlg::Show_Data(void)
{
	char in_buf[20],out_buf[1024],content[1024],tmp[100],asc_buf[500];
	int i,j,k,qty,start;
	DWORD data;
	
	//sprintf(title,"Vendor:%s  Device-ID:%s\n  Class:%s  Bus:%02Xh  Device:%02Xh  Fucntion:%02Xh",para[0],para[1],para[2],bus,dev,func);
	//m_title.SetWindowText(title);
	start = reg_start;
	//Pci_E_addr = 0;
	qty = m_reg.GetWindowTextLength();
	m_reg.SetReadOnly(FALSE);
	m_reg.SetSel(0,-1,TRUE);
	m_reg.Clear();
	m_reg.SetReadOnly(TRUE);
	
	ZeroMemory(out_buf,sizeof(out_buf));
	ZeroMemory(asc_buf,sizeof(asc_buf));
	
	for(i = 0; i < 16; i++)
	{
		//��ܰϥ����}��r
		sprintf(in_buf,"%04X",start);
		in_buf[3] = 'x';
		strcat(out_buf,in_buf);
		if(i != 15)
		{
			strcat(out_buf,"\n");
		}
		
		//Ū4��DWORD
		ZeroMemory(content,sizeof(content));
		for(j = 0; j < 4; j++)
		{
			if(!pci_express)
			{
				read_pci_dword(bus,dev,func,(BYTE)start,&data);
			}
			else
			{
				read_mem_dword((Pci_E_addr+start),&data); //�q�O����Ū���
			}
			start+= 4;
			
			sprintf(tmp,"%02X %02X %02X %02X",(BYTE)data,(BYTE)(data>>8),(BYTE)(data>>16),(BYTE)(data>>24));
			
			strcat(content,tmp);
			if(j != 3)
			{
				strcat(content," ");
			}
			
			//show ASCII
			for(k = 0; k < 4; k++)
			{
				if((BYTE)data >= 0x20)
				{//�p�G�O�@�몺�r��
					sprintf(tmp,"%c",(BYTE)data);
				}
				else
				{//�S��r���A��.���
					strcpy(tmp,".");
				}
				strcat(asc_buf,tmp);
				data >>= 8;
			}
		}
		if(i != 15)
		{
			strcat(content,"\r\n");
			strcat(asc_buf,"\n");
		}
		
		qty = m_reg.GetWindowTextLength();
		m_reg.SetSel(qty,qty,FALSE);
		m_reg.ReplaceSel(content,FALSE);
	}
	
	m_row.SetWindowText(out_buf);
	m_ascii.SetWindowText(asc_buf);
}

void CRegDlg::Set_Scroll(void)
{
	SCROLLINFO info;

	info.cbSize = sizeof(SCROLLINFO);     
	info.fMask = SIF_ALL;     
	info.nMin = 0;     
	info.nMax = 4095; 
	info.nPage = 16;     
	info.nPos = reg_start/0x10;
	m_scroll.SetScrollInfo(&info);
}

int CRegDlg::Cal_PciE_addr(BYTE bus,BYTE dev,BYTE func)
{
	//DWORD tmp;
	
	/*
	PCI bus address to Memory address format:
	+-----------------------------------------+
	| 1110 bbbb bbbb dddd dfff 0000 0000 0000 |
	+-----------------------------------------+
	*/
	/*Pci_E_addr = 0xe0000000;
	tmp = (DWORD)bus;
	Pci_E_addr |= tmp << 20;
	tmp = (DWORD)dev;
	Pci_E_addr |= tmp << 15;
	tmp = (DWORD)func;
	Pci_E_addr |= tmp << 12;*/
	
	int cct=0;
	DWORD tmp,data1,data2;
	
	/*
	PCI bus address to Memory address format:
	+-----------------------------------------+
	| 1110 bbbb bbbb dddd dfff 0000 0000 0000 |
	+-----------------------------------------+
	   ^
	   + OEM define
	*/
	
	read_pci_dword(bus,dev,func,0,&data1);
	
	Pci_E_addr = 0x10000000;
	
	while(1)
	{
		if((Pci_E_addr&0xF0000000)!=0xF0000000)
		{
			Pci_E_addr += cct * 0x10000000;
			if(!cct)
			{
				tmp = (DWORD)bus;
				Pci_E_addr |= tmp << 20;
				tmp = (DWORD)dev;
				Pci_E_addr |= tmp << 15;
				tmp = (DWORD)func;
				Pci_E_addr |= tmp << 12;
			}
			cct++;
		}
		else
		{
			return 1;
		}

		read_mem_dword(Pci_E_addr,&data2);
		if(data1 == data2)
		{//�z�LIOŪ�쪺�n��memoryŪ�쪺�@��
			break;
		}
	}
	return 0;
}
