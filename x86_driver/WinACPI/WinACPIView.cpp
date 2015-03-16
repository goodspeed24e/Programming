// WinACPIView.cpp : implementation of the CWinACPIView class
//
#define AFX_MAINFRM_H__3C6A463A_C852_462E_BB03_585BC5B08A9D__INCLUDED_

#include "stdafx.h"
#include "WinACPI.h"
#include "myio.h"
#include "def.h"
#include "acpi_def.h"

#include "WinACPIDoc.h"
#include "WinACPIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HTREEITEM old_sld;

//DWORD RSDP_addr;

struct RSDP rsdp;
//struct RSDT rsdt;
//struct SSDT ssdt;

/////////////////////////////////////////////////////////////////////////////
// CWinACPIView

IMPLEMENT_DYNCREATE(CWinACPIView, CFormView)

BEGIN_MESSAGE_MAP(CWinACPIView, CFormView)
	//{{AFX_MSG_MAP(CWinACPIView)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_TREE, OnClickTree)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MSG_DETECT, OnStart)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinACPIView construction/destruction

CWinACPIView::CWinACPIView()
	: CFormView(CWinACPIView::IDD)
{
	//{{AFX_DATA_INIT(CWinACPIView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	//this->SetWindowPos(NULL,0,0,300,600,SWP_NOMOVE);
	
	if(OnMyIo() == 0)
	{
		MessageBox("Fail to open MyIO","Error",MB_OK | MB_ICONSTOP);
	}
	//RSDP_addr = 0;
	old_sld = NULL;
}

CWinACPIView::~CWinACPIView()
{
	OffMyIo();
}

void CWinACPIView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinACPIView)
	DDX_Control(pDX, IDC_TREE, m_tree);
	//}}AFX_DATA_MAP
}

BOOL CWinACPIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CWinACPIView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CWinACPIView diagnostics

#ifdef _DEBUG
void CWinACPIView::AssertValid() const
{
	CFormView::AssertValid();
}

void CWinACPIView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CWinACPIDoc* CWinACPIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinACPIDoc)));
	return (CWinACPIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinACPIView message handlers

void CWinACPIView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if( m_tree.GetSafeHwnd())// && IsWindow(m_name) )
	{
		//                       起點x,起點y,寬,高, 1:1.75左右(圖與實際顯示)
		m_tree.SetWindowPos(NULL,0,0,cx,cy-22,SWP_NOMOVE | SWP_NOZORDER);
			//AfxMessageBox("In1");
	}
	if( GetDlgItem(IDC_SHOW_STATIC)->GetSafeHwnd())// && IsWindow(m_name) )
	{
		//                       起點x,起點y,寬,高, 1:1.75左右(圖與實際顯示)
		GetDlgItem(IDC_SHOW_STATIC)->SetWindowPos(NULL,0,0,cx,22,SWP_NOMOVE | SWP_NOZORDER);
			//AfxMessageBox("In2");
		RedrawWindow(NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);//畫面重畫
	}
}

void CWinACPIView::OnClickTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	SetTimer(1,100,0);

	*pResult = 0;
}

void CWinACPIView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFormView::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	//SetTimer(1,100,0);
	//this->SetWindowPos(NULL,0,0,300,600,SWP_NOMOVE);
	this->PostMessage(WM_MSG_DETECT, 0,0);
}

void CWinACPIView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//DWORD dd;
	HTREEITEM sld;
	
	KillTimer(1);
	
	sld = m_tree.GetSelectedItem();
	
	if(sld != NULL && sld != old_sld)
	{
		old_sld = sld;
	
		AfxGetMainWnd()->PostMessage(WM_MSG_STATUS, 0,(LPARAM)AllocBuffer("Loading, please wait"));
		//dd = m_tree.GetItemData(old_sld);
		AfxGetMainWnd()->PostMessage(WM_MSG_SHOW, 0,(LPARAM)sld);
		//AfxGetMainWnd()->PostMessage(WM_MSG_SHOW, 0,dd);
		AfxGetMainWnd()->PostMessage(WM_MSG_STATUS, 0,(LPARAM)AllocBuffer("Done"));
	}
	
	CFormView::OnTimer(nIDEvent);
}

LONG CWinACPIView::OnStart(WPARAM wParam, LPARAM lParam)
{
	//AfxGetMainWnd()->PostMessage(WM_MSG_STATUS, 0,(LPARAM)AllocBuffer("Detecting ACPI tables, please wait"));
	Sleep(100);
	DetectACPI();
	return 0;
}

void CWinACPIView::DetectACPI(void)
{
	if(FindRSDP() != 0)
	{
		AfxGetMainWnd()->PostMessage(WM_MSG_STATUS, 0,(LPARAM)AllocBuffer("Fail to find RSDP table"));
		return;
	}
	
	if(FindSubTable(rsdp.rsdt_addr)!= 0)
	{
		AfxGetMainWnd()->PostMessage(WM_MSG_STATUS, 0,(LPARAM)AllocBuffer("Fail to find RSDT table"));
		return;
	}
	
	AfxGetMainWnd()->PostMessage(WM_MSG_STATUS, 0,(LPARAM)AllocBuffer("Done"));
}

int CWinACPIView::FindRSDP(void)
{
	DWORD addr,dwMemVal;
	char buf[100];
	
	ZeroMemory(&rsdp,sizeof(rsdp));
	
	//RSDP entry point
	for(addr = 0xe0000; addr < 0xfffff; addr+=4)
	{
		read_mem_dword(addr, &dwMemVal); //從記憶體中讀出4byte
		if(dwMemVal==0x20445352) //顛倒的"RSD "
		{
			read_mem_dword((addr+4), &dwMemVal);
			if(dwMemVal==0x20525450) //顛倒的"PTR "
			{
				int i;
				
				ZeroMemory(buf,sizeof(buf));
				for(i = 0; i <= 35; i+=4)
				{//讀出所有RSDP的資料
					read_mem_dword((addr+i), &dwMemVal);
					buf[i] = (BYTE)dwMemVal;
					buf[i+1] = (BYTE)(dwMemVal >> 8);
					buf[i+2] = (BYTE)(dwMemVal >> 16);
					buf[i+3] = (BYTE)(dwMemVal >> 24);
				}
				memcpy(&rsdp,buf,sizeof(rsdp));
				
				hti= m_tree.InsertItem("RSDP");
				m_tree.SetItemData(hti,addr);
				return 0;
			}
		}
	}
	return 1;
}

int CWinACPIView::FindSubTable(DWORD addr_start)
{
	DWORD addr,off_addr,dwMemVal;
	char buf[100];
	char sig[10];
	int i,size;
	
	size = sizeof(DESC_TABLE_HEAD);
	addr = addr_start;
	
	ZeroMemory(buf,sizeof(buf));
	read_mem_dword(addr, &dwMemVal);
	buf[0] = (BYTE)dwMemVal;
	buf[1] = (BYTE)(dwMemVal >> 8);
	buf[2] = (BYTE)(dwMemVal >> 16);
	buf[3] = (BYTE)(dwMemVal >> 24);

	read_mem_dword((addr+4), &dwMemVal); //取structure size

	if(memcmp(buf,"RSDT",4)==0)
	{//RSDT表
		HTREEITEM hti2,hti3,hti4;
		
		hti2 = m_tree.InsertItem("RSDT",hti);
		m_tree.SetItemData(hti2,addr_start);
		
		//抓取entry位址與signature
		size = (dwMemVal - sizeof(DESC_TABLE_HEAD))/4;
		
		addr+=sizeof(DESC_TABLE_HEAD);
		for(i = 0; i < size; i++)
		{
			read_mem_dword(addr, &off_addr);
			
			//signature
			ZeroMemory(sig,sizeof(sig));
			read_mem_dword(off_addr,(DWORD *)sig);
			
			hti3 = m_tree.InsertItem(sig,hti2);
			m_tree.SetItemData(hti3,off_addr);
			if(stricmp(sig,"FADT") == 0 || stricmp(sig,"FACP")==0)
			{
				hti4 = m_tree.InsertItem("FACS",hti3);
				//取得FACS的address(在FADT中)
				read_mem_dword((off_addr+36), &dwMemVal);
				m_tree.SetItemData(hti4,dwMemVal);
				
				hti4 = m_tree.InsertItem("DSDT",hti3);
				//取得DSDT的address(在FADT中)
				read_mem_dword((off_addr+40), &dwMemVal);
				m_tree.SetItemData(hti4,dwMemVal);
			}
			addr += 4;
		}
		
		return 0;
	}
	
	return 1;
}
