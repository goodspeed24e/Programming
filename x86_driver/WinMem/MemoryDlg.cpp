// MemoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Memory.h"
#include "myio.h"
#include "def.h"
#include "searchdlg.h"
#include "MemoryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

	void delay1us(DWORD delay);
	
SEARCH_INFO s_info;

char version[10]="1.0";
int str_to_hex(char *p, DWORD *data);
int go_flag;//,bk_flag;

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
	virtual BOOL OnInitDialog();
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

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char buf[200];

	sprintf(buf,"Memory Viewer 版本: %s",version);
	GetDlgItem(IDC_VER_STATIC)->SetWindowText(buf);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoryDlg dialog

CMemoryDlg::CMemoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMemoryDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMemoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMemoryDlg)
	DDX_Control(pDX, IDC_ADV_BUTTON, m_adv);
	DDX_Control(pDX, IDC_SCROLLBAR, m_scroll);
	DDX_Control(pDX, IDC_INPUT_EDIT, m_input);
	DDX_Control(pDX, IDC_EDIT, m_content);
	DDX_Control(pDX, IDC_BUTTON, m_run);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMemoryDlg, CDialog)
	//{{AFX_MSG_MAP(CMemoryDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_INPUT_EDIT, OnChangeInputEdit)
	ON_BN_CLICKED(IDC_BUTTON, OnButton)
	ON_WM_CLOSE()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_ADV_BUTTON, OnAdvButton)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MSG_STATUS, OnStatus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoryDlg message handlers

BOOL CMemoryDlg::OnInitDialog()
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
	char buf[200];

	m_search = new CSearchDlg;
	
	sprintf(buf,"Memory Viewer 版本: %s",version);
	SetWindowText(buf);
	
	m_input.SetWindowText("00000000");
	
	if(OnMyIo()==0)
	{
		MessageBox("開啟IO驅動程式失敗","錯誤",MB_OK | MB_ICONSTOP);
		OnCancel();
	}
	
	//開始顯示記憶體位址
	reg_start = 0;
	
	mode = 0;
	//bk_flag = 0;
	
	OnButton();
	Set_Scroll();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMemoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMemoryDlg::OnPaint() 
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
HCURSOR CMemoryDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CMemoryDlg::OnChangeInputEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int len;
	
	len = m_input.GetWindowTextLength(); //Edit裡的字數
	if(len==0)
	{//如果字數為0，關閉執行按鈕
		m_run.EnableWindow(FALSE);
	}
	else
	{
		m_run.EnableWindow(TRUE);
	}
}

void CMemoryDlg::OnButton() 
{//Run
	// TODO: Add your control notification handler code here
	
	if(mode==0)
	{//一般模式
		DWORD start;
		char in_buf[20];
	
		m_input.GetWindowText(in_buf,sizeof(in_buf));	
		if(str_to_hex(in_buf,&start) != 0)
		{
			MessageBox("輸入的顯示位址有錯","錯誤",MB_OK | MB_ICONSTOP);
			return;
		}
			//sprintf(in_buf,"addr=%08lX",start);
			//AfxMessageBox(in_buf);
	
		//讀資料並顯示
		Display(start);
	
		//同時更新scroll bar位址
		reg_start = start;
		Set_Scroll();
	}
	else
	{//找尋模式
		m_run.EnableWindow(FALSE);
		go_flag = 1;
	}
}

void CMemoryDlg::Display(DWORD start_addr)
{
	int i,j,qty;
	char in_buf[20],out_buf[1024],content[100],tmp[50],asc_buf[500];
	DWORD start;
	BYTE data8;
	//	char bbb[100];
	
	//開始抓記憶體位置
	start = start_addr;
	
	//清除顯示區文字
	qty = m_content.GetWindowTextLength();
	m_content.SetReadOnly(FALSE);
	m_content.SetSel(0,-1,TRUE);
	m_content.Clear();
	m_content.SetReadOnly(TRUE);
	
	ZeroMemory(out_buf,sizeof(out_buf));
	ZeroMemory(asc_buf,sizeof(asc_buf));
	
	//抓16x16筆資料
	for(i = 0; i < 16; i++)
	{
		//顯示區左邊位址文字
		sprintf(in_buf,"%08lX",start);
		//in_buf[7] = 'x';
		strcat(out_buf,in_buf);
		if(i < 15)
		{
			strcat(out_buf,"\n");
		}
		
		ZeroMemory(content,sizeof(content));
		
			/*sprintf(bbb,"i=%d",i);
			AfxMessageBox(bbb);*/
		for(j = 0; j < 16; j++)
		{//也許是driver問題，只能用byte去讀，用dword有時會失敗
			read_mem_byte(start,&data8);
			start++;
			sprintf(tmp,"%02X",data8);
			strcat(content,tmp);
			if(j != 15)
			{
				strcat(content," ");
			}
			
			//show ASCII
			if(data8 >= ' ' && data8 <= '~')
			{//如果是一般的字元
				sprintf(tmp,"%c",(char)data8);
			}
			else
			{//特殊字元，用.表示
				strcpy(tmp,".");
			}
			strcat(asc_buf,tmp);
		}
		
		if(i!= 15)
		{
			strcat(content,"\r\n");
			strcat(asc_buf,"\n");
		}
		qty = m_content.GetWindowTextLength();
		m_content.SetSel(qty,qty,FALSE);
		m_content.ReplaceSel(content,FALSE);	
	}
	
	//更新顯示文字
	GetDlgItem(IDC_VIR_STATIC)->SetWindowText(out_buf);
	GetDlgItem(IDC_ASCII_STATIC)->SetWindowText(asc_buf);
	//RedrawWindow(NULL, NULL,RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);//畫面重畫
}

void CMemoryDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	OffMyIo(); //關閉IO driver
	CDialog::OnClose();
}

void CMemoryDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{//scroll bar被按下
	// TODO: Add your message handler code here and/or call default
	
	if(pScrollBar->GetDlgCtrlID() == IDC_SCROLLBAR )
	{
		switch(nSBCode)
		{
			case SB_LINEDOWN: //下箭頭被按下
				if(reg_start < 0xffffffef)
				{
					reg_start+=16;
					Display(reg_start);
					Set_Scroll();
				}
				break;
				
			case SB_LINEUP: //上箭頭被按下
				if(reg_start >= 16)
				{
					reg_start-=16;
					Display(reg_start);
					Set_Scroll();
				}
				break;
			case SB_PAGEDOWN: //姆指盒下方被按下
				if(reg_start <= 0xffffff00)
				{
					reg_start += 256;
				}
				else
				{
					reg_start = 0xfffffff0;
				}
				Display(reg_start);
				Set_Scroll();
				break;
			case SB_PAGEUP: //姆指盒上方被按下
				if(reg_start > 256)
				{
					reg_start -= 256;
				}
				else
				{
					reg_start = 0;
				}
				Display(reg_start);
				Set_Scroll();
				break;
			case SB_THUMBPOSITION: //姆指盒被按下
				SCROLLINFO info;
				
				info.cbSize = sizeof(SCROLLINFO); 
				m_scroll.GetScrollInfo(&info);
				
				reg_start = info.nTrackPos * 0x100100;
				
				Display(reg_start);
				Set_Scroll();
				break; 
		}
		
		
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMemoryDlg::Set_Scroll(void)
{//設定捲軸位置
	SCROLLINFO info;

	info.cbSize = sizeof(SCROLLINFO);     
	info.fMask = SIF_ALL;     
	info.nMin = 0;     
	info.nMax = 4095; 
	info.nPage = 16;     
	info.nPos = (int)(reg_start/0x100100);
	m_scroll.SetScrollInfo(&info);
}

LONG CMemoryDlg::OnStatus(WPARAM wParam, LPARAM lParam)
{
	char* pMsg = (char*) lParam;
	
	GetDlgItem(IDC_STATUS_STATIC)->SetWindowText(pMsg);
	delete pMsg;
	return 0;
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

void CMemoryDlg::OnAdvButton() 
{
	// TODO: Add your control notification handler code here
	if(mode==0)
	{
		if(m_search->DoModal()==IDOK)
		{
			mode = 1;
			//bk_flag = 0;
			m_run.SetWindowText("找下一個");
			m_run.EnableWindow(FALSE);
			m_adv.SetWindowText("停止");
			//m_scroll.EnableWindow(FALSE);
			go_flag = 1;
			
			//開一個執行緒去找
			m_hThread = CreateThread(NULL, 30000, MLTProc, (void*) this, CREATE_SUSPENDED, &m_thisThreadID);
			// check for successful thread creation
			if (m_hThread == NULL)
			{
				MessageBox("Error trying to create SEARCH thread","warning",MB_OK);
				return ;
			}
			ResumeThread(m_hThread);
		}
		
	}
	else
	{
		mode = 0;
		go_flag = 0;
		//bk_flag = 1;
		PostMessage(WM_MSG_STATUS, 0, (LPARAM) AllocBuffer(""));
		m_run.SetWindowText("執行");
		m_run.EnableWindow(TRUE);
		m_adv.SetWindowText("進階功能");
		//m_scroll.EnableWindow(TRUE);
		SuspendThread(m_hThread);
	}
}

DWORD __stdcall MLTProc(void *p)
{
	CMemoryDlg *hd=(CMemoryDlg *)p;
	DWORD i;
	BYTE data;
	int j,cnt;
	char buf[100],tmp[100];
	
	strcpy(buf,s_info.sh_value);
	cnt = strlen(s_info.sh_value);
	if(s_info.sh_type==0)
	{
		str_to_hex(buf,&i);
		cnt /= 2;
		buf[0] = (char)(i&0xff);
		buf[1] = (char)((i>>8)&0xff);
		buf[2] = (char)((i>>16)&0xff);
		buf[3] = (char)((i>>24)&0xff);
	}
	
	for(i = s_info.sh_start; i < s_info.sh_end; i++)
	{
		if(go_flag != 0)
		{
			if((i % 0x100)==0)
			{
				sprintf(tmp,"Searching %lXh",i);
				hd->PostMessage(WM_MSG_STATUS, 0, (LPARAM) AllocBuffer(tmp));
			}
			read_mem_byte(i,&data); //從記憶體讀資料
			if(data == buf[0])
			{
				for(j = 1; j < cnt; j++)
				{
					read_mem_byte((i+j),&data);
					if(data != buf[j])
					{
						break;
					}
				}
				if(j == cnt)
				{
					sprintf(tmp,"Searching %lXh",i);
					hd->PostMessage(WM_MSG_STATUS, 0, (LPARAM) AllocBuffer(tmp));
					hd->m_run.EnableWindow(TRUE);
					hd->Display(i);
					hd->reg_start = (i / 10)*10; //不要個位數
					hd->Set_Scroll();
					go_flag = 0;
				}
			}
		}
		else
		{
			while(1)
			{
				if(go_flag != 0)
				{
					break;
				}
				Sleep(100);
			}
		}
	}
	
	hd->OnAdvButton();
	return 0;
}

void CMemoryDlg::OnOK() 
{
	// TODO: Add extra validation here
	OnButton();
	//CDialog::OnOK();
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
