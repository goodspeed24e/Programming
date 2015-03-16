// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "WinACPI.h"
#include "detailview.h"
#include "winacpidoc.h"
#include "winacpiview.h"
#include "def.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MSG_STATUS, OnStatus)
	ON_MESSAGE(WM_MSG_SHOW, OnShowDetail)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	//this->SetWindowPos(NULL,0,0,700,600,SWP_NOMOVE | SWP_NOZORDER);
	
	Write_Status("Detecting ACPI tables, please wait");
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//CRect rect(0,0,640,480);
	//::AdjustWindowRectEx(&rect,GetStyle(),true,GetExStyle());
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(s_wndSplitter.CreateStatic(this,1,2,WS_CHILD | WS_VISIBLE) == 0) // 一行兩列
		return false;//不成功就返回
	else 
	{
		s_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CWinACPIView),CSize(200,480),pContext); // left
		s_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CDetailView),CSize(600,480),pContext); // right
		m_acpi = (CWinACPIView *)s_wndSplitter.GetPane(0,0);
		m_detail = (CDetailView *)s_wndSplitter.GetPane(0,1);
		m_detail->OnInitialUpdate();
	}
	
	return true;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::Write_Status(char *str)
{//寫資料到status bar
	m_wndStatusBar.SetPaneText(0,str);
	m_wndStatusBar.RedrawWindow(NULL, NULL,RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);//畫面重畫
}

LONG CMainFrame::OnStatus(WPARAM wParam, LPARAM lParam)
{
	char* pMsg = (char*) lParam;

	Write_Status(pMsg);
	delete pMsg;
	return 0;
}

LONG CMainFrame::OnShowDetail(WPARAM wParam, LPARAM lParam)
{
	char name[10];
	CString na;
	DWORD addr;
	HTREEITEM sld;
//		char buf[100];
	
	sld = (HTREEITEM)lParam;
	na = m_acpi->m_tree.GetItemText(sld);
	addr = m_acpi->m_tree.GetItemData(sld);
	sprintf(name,"%s",na);
		//sprintf(buf,"name:%s, addr:%08lX",na,addr);
		//AfxMessageBox(buf);
	//呼叫detail的顯示函式
	m_detail->GetTable(name,addr);
	return 0;
}
