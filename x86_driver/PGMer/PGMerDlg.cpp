// PGMerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PGMer.h"
#include "myio.h"
#include "def.h"
#include "PGMerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BYTE *eeprom_buf; //存放寫入 EEPROM的資料
BYTE *read_buf; //存放讀取的EEPROM資料
BYTE IC_Addr;

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
// CPGMerDlg dialog

CPGMerDlg::CPGMerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPGMerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPGMerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPGMerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGMerDlg)
	DDX_Control(pDX, IDC_BW_BUTTON, m_bw);
	DDX_Control(pDX, IDC_93_RADIO, m_93);
	DDX_Control(pDX, IDC_24_RADIO, m_24);
	DDX_Control(pDX, IDC_WRITE_RADIO, m_write_r);
	DDX_Control(pDX, IDC_READ_RADIO, m_read_r);
	DDX_Control(pDX, IDC_REPORT_EDIT, m_report);
	DDX_Control(pDX, IDC_FILE_EDIT, m_file);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPGMerDlg, CDialog)
	//{{AFX_MSG_MAP(CPGMerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_24_RADIO, On24Radio)
	ON_BN_CLICKED(IDC_93_RADIO, On93Radio)
	ON_BN_CLICKED(IDC_READ_RADIO, OnReadRadio)
	ON_BN_CLICKED(IDC_WRITE_RADIO, OnWriteRadio)
	ON_BN_CLICKED(IDC_BW_BUTTON, OnBwButton)
	ON_BN_CLICKED(IDC_RUN_BUTTON, OnRunButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGMerDlg message handlers

BOOL CPGMerDlg::OnInitDialog()
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
	
	m_24.SetCheck(BST_CHECKED);
	m_24.SetFocus();
	
	m_read_r.SetCheck(BST_CHECKED);
	OnReadRadio();
	
	if(OnMyIo()==0)
	{
		MessageBox("Fail to open MyIO","Error",MB_OK | MB_ICONSTOP);
		CDialog::OnOK();
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPGMerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPGMerDlg::OnPaint() 
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
HCURSOR CPGMerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CPGMerDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	OffMyIo();
	return CDialog::DestroyWindow();
}

void CPGMerDlg::On24Radio() 
{
	// TODO: Add your control notification handler code here
	m_93.SetCheck(BST_UNCHECKED);
}

void CPGMerDlg::On93Radio() 
{
	// TODO: Add your control notification handler code here
	m_24.SetCheck(BST_UNCHECKED);
}

void CPGMerDlg::OnReadRadio() 
{
	// TODO: Add your control notification handler code here
	m_write_r.SetCheck(BST_UNCHECKED);
	m_file.EnableWindow(FALSE);
	m_bw.EnableWindow(FALSE);
}

void CPGMerDlg::OnWriteRadio() 
{
	// TODO: Add your control notification handler code here
	m_read_r.SetCheck(BST_UNCHECKED);
	m_file.EnableWindow(TRUE);
	m_bw.EnableWindow(TRUE);
}

void CPGMerDlg::OnBwButton() 
{
	// TODO: Add your control notification handler code here
	OPENFILENAME ofn;
	char buf[500];
	//	char buf2[100];

	ZeroMemory(buf,sizeof(buf));//[0]  = '\0';
	//ZeroMemory(buf2,sizeof(buf2));

	ofn.lStructSize       = sizeof(OPENFILENAME);
	ofn.hwndOwner         = GetSafeHwnd();
	ofn.hInstance         = GetModuleHandle(NULL);
	ofn.lpstrFilter       = "TXT files\0*.txt\0";
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter    = 0;
	ofn.nFilterIndex      = 1;
	ofn.lpstrFile         = buf; //full path
	ofn.nMaxFile          = 500;
	ofn.lpstrFileTitle    = NULL; //file name only
	ofn.nMaxFileTitle     = 100;
	ofn.lpstrInitialDir   = NULL;
	ofn.lpstrTitle        = "Select file";
	ofn.Flags             = OFN_NOCHANGEDIR | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_EXPLORER;
	ofn.nFileOffset       = 0;
	ofn.nFileExtension    = 0;
	ofn.lpstrDefExt       = NULL;
	ofn.lCustData         = 0;
	ofn.lpfnHook          = NULL;
	ofn.lpTemplateName    = NULL;

	if(GetOpenFileName(&ofn) != 0)
	{
		m_file.SetWindowText(buf);
	}
}

void CPGMerDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CPGMerDlg::OnRunButton() 
{
	// TODO: Add your control notification handler code here
	FILE *fptr;
	char filename[1024];
	int i,j,file_cnt=1024,start=0,ign_flag;
	BYTE tmp;
	
	eeprom_buf = NULL;
	eeprom_buf = (unsigned char *)calloc(1024, sizeof(unsigned char)); //申請一塊記憶體空間
	if(eeprom_buf == NULL)
	{
		MessageBox("申請寫入記憶體失敗","錯誤",MB_OK | MB_ICONSTOP);
		return;
	}
	
	read_buf = NULL;
	read_buf = (unsigned char *)calloc(1024, sizeof(unsigned char)); //申請一塊記憶體空間
	if(read_buf == NULL)
	{
		MessageBox("申請讀取記憶體失敗","錯誤",MB_OK | MB_ICONSTOP);
		return;
	}
	
	memset(eeprom_buf,0xff,1024); //預設空的EEPROM是FFh
	memset(read_buf,0xff,1024); //預設空的EEPROM是FFh
	
	if(m_write_r.GetCheck()==BST_CHECKED)
	{
		if(m_file.GetWindowText(filename,sizeof(filename)) < 5)
		{
			MessageBox("資料檔名必須大於5個字","錯誤",MB_OK | MB_ICONSTOP);
			return;
		}
	
		fptr = fopen(filename,"rt");
		if(fptr == NULL)
		{
			MessageBox("開啟檔案失敗","錯誤",MB_OK | MB_ICONSTOP);
			return;
		}
		//計算大小
		fseek(fptr,0,SEEK_END);
		file_cnt = ftell(fptr);
		fseek(fptr,0,SEEK_SET);	
		fread(eeprom_buf,file_cnt,1,fptr); //全部讀回
		fclose(fptr);
			
		//ASCII轉HEX
		for(i = 0; i < (int)(file_cnt-2); i++)
		{
			tmp = 0;
			ign_flag = 0;
			for(j = 0; j < 2; j++)
			{
				tmp <<= 4;
				if(eeprom_buf[i+j] >= '0' && eeprom_buf[i+j] <= '9')
				{
					tmp |= (BYTE)(eeprom_buf[i+j] - 0x30);
				}
				else if(eeprom_buf[i+j] >= 'A' && eeprom_buf[i+j] <= 'F')
				{
					tmp |= (BYTE)(eeprom_buf[i+j] - 0x37);
				}
				else if(eeprom_buf[i+j] >= 'a' && eeprom_buf[i+j] <= 'f')
				{
					tmp |= (BYTE)(eeprom_buf[i+j] - 0x57);
				}
				else
				{//\n or other...
					ign_flag = 1;
					break;
				}
			}
			
			if(ign_flag==0)
			{
				eeprom_buf[start] = (BYTE)tmp;
				start++;
				i++;
			}
			//i++;
		}
	}
	
	//clear other area
	for(i = start; i < (int)file_cnt; i++)
	{
		eeprom_buf[i] = 0;
	}
	
	m_report.SetWindowText("");
	Show_Data("      00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F      ASCII code");
	
	//燒錄用執行緒
	m_hThread = CreateThread(NULL, 30000, Prog_Proc, (void*) this, CREATE_SUSPENDED, &m_thisThreadID);

	// check for successful thread creation
	if (m_hThread == NULL)
	{
		MessageBox("Error trying to create Programming thread","warning",MB_OK);
		return;
	}
	ResumeThread(m_hThread);
}

void CPGMerDlg::AsmData(BYTE *data)
{
	char buf[1024],asc[1024],tmp[10];
	int i,cnt,len;
	
	ZeroMemory(buf,sizeof(buf));
	ZeroMemory(asc,sizeof(asc));
	
	len = 256; //共有256byte
	cnt = 0;

	for(i = 0; i < len; i++)
	{//依據資料大小解析資料
		if((i%16)==0)
		{
			sprintf(buf,"%03Xx: ",cnt);
		}
			
		sprintf(tmp,"%02X ",data[i]);
		strcat(buf,tmp);
			
		//轉成ASCII code
		if(data[i] < ' ' || data[i] > '~')
		{//不可視字元，改用 點 表示
			strcpy(tmp,".");
		}
		else
		{
			sprintf(tmp,"%c",data[i]);
		}
		strcat(asc,tmp);
				
		if(((i+1)%16)==0)
		{//每16個就顯示資料與ASCII code
			strcat(buf,"  ");
			strcat(buf,asc);
			Show_Data(buf);
			ZeroMemory(buf,sizeof(buf));
			ZeroMemory(asc,sizeof(asc));
			cnt++;
		}
	}

	if(buf[0] != 0)
	{//未滿16個離開，中間要多補空白
		cnt = 16-(len % 16);
		for(i = 0; i < cnt; i++)
		{
			strcat(buf,"   ");
		}
		strcat(buf,"  ");
		strcat(buf,asc);
		Show_Data(buf);
		ZeroMemory(asc,sizeof(asc));
	}
		
	m_report.SetSel(0,0,FALSE); //回到最上面
}

void CPGMerDlg::Show_Data(char *str)
{//顯示資料到DATA EDIT中
	int qty;
	
	qty = m_report.GetWindowTextLength();
	m_report.SetSel(qty,qty,TRUE);
	m_report.ReplaceSel(str);
	m_report.ReplaceSel("\r\n");
		
	qty = m_report.GetLineCount();
		
	if(qty > 1000)
	{
		m_report.SetReadOnly(FALSE);
		qty = m_report.LineIndex(qty-1000);
		m_report.SetSel(0,qty,TRUE);
		m_report.Clear();
		qty = m_report.GetWindowTextLength();
		m_report.SetReadOnly(TRUE);
		m_report.SetSel(qty,qty,TRUE);
	}
}

DWORD __stdcall Prog_Proc(void *p)
{
	CPGMerDlg *pDlg=(CPGMerDlg *)p;
	WORD i;
	int st;
		//char dbg[100];
		
		/*for(i = 0; i < 256; i++)
		{
			read_buf[i] = i;
		}*/
		//read_buf[0] = read_Byte((BYTE)0);
		//return 0;
	
	//寫入後，會再讀回資料，顯示在畫面上
	
	if(pDlg->m_24.GetCheck()==BST_CHECKED)
	{//24系列
		
		IC_Addr = 0xA0; //位址A0h
		reset_iic();
		if(pDlg->m_write_r.GetCheck()==BST_CHECKED)
		{//寫入
			for(i = 0; i < 256; i++) //共256byte
			{
				if(write_byte(i,eeprom_buf[i]) != 0)
				{
					MessageBox(NULL,"寫入I2C EEPROM失敗","錯誤",MB_OK | MB_ICONSTOP);
					goto err_exit;
				}
			}
		}
			
		//讀回
		for(i = 0; i < 256; i++) //共256byte
		{
			st = read_byte(i,&(read_buf[i]));
			if(st != 0)
			{//失敗
				//sprintf(dbg,"st=%d",st);
				//AfxMessageBox(dbg);
			 	MessageBox(NULL,"讀取I2C EEPROM失敗","錯誤",MB_OK | MB_ICONSTOP);
				goto err_exit;
			}
		}
	}
	else
	{//93系列
		if(pDlg->m_write_r.GetCheck()==BST_CHECKED)
		{//寫入
			for(i = 0; i < 256; i++)
			{
				write_Byte((BYTE)i,eeprom_buf[i]);
			}
		}
		//讀回
		for(i = 0; i < 256; i++) //共256byte
		{
			read_buf[i] = read_Byte((BYTE)i);
		}
	}
	pDlg->AsmData(read_buf); //顯示讀到的資料
	free(read_buf);
	free(eeprom_buf);
	return 0;
	
err_exit:
	free(read_buf);
	free(eeprom_buf);
	return 1;
	
}

void Delay_1us(DWORD delay)
{
	LARGE_INTEGER start,end,Freq;
 
	QueryPerformanceFrequency(&Freq);                      
	//end.QuadPart = (delay*Freq.QuadPart)/10000;        //0.1ms
	end.QuadPart = (delay*Freq.QuadPart)/1000000;        //0.001ms
	QueryPerformanceCounter(&start);
	end.QuadPart = end.QuadPart+start.QuadPart;/*-System_test()*2;*/
	do
	{
		QueryPerformanceCounter(&Freq);
	}while (Freq.QuadPart<=end.QuadPart);
}

