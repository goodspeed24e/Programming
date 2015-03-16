// SMBIOSDlg.h : header file
//

#if !defined(AFX_SMBIOSDLG_H__89E9BEDC_6F7B_4287_80C4_D7E0B59A6D8F__INCLUDED_)
#define AFX_SMBIOSDLG_H__89E9BEDC_6F7B_4287_80C4_D7E0B59A6D8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSMBIOSDlg dialog

class CSMBIOSDlg : public CDialog
{
// Construction
public:
	int FindEntry(void); //找尋SMBIOS table的進入點
	void ReadEntry(void); //讀取entry資料
	int FindTable(int sld);//找尋指定的table
	void Jump_str(void); //跳過每一個table後面的附加字串
	
	void ReportOEM(void); //oem資料顯示
	void ReportEnd(void); //table 127 資料解析
	void ReportTp126(void); //table 126 資料解析
	void ReportTp39(void); //table 39 資料解析
	void ReportTp38(void); //table 38 資料解析
	void ReportTp37(void); //table 37 資料解析
	void ReportTp36(void); //table 36 資料解析
	void ReportTp35(void); //table 35 資料解析
	void ReportTp34(void); //table 34 資料解析
	void ReportTp33(void); //table 33 資料解析
	void ReportTp32(void); //table 32 資料解析
	void ReportTp30(void); //table 30 資料解析
	void ReportTp29(void); //table 29 資料解析
	void ReportTp28(void); //table 28 資料解析
	void ReportTp27(void); //table 27 資料解析
	void ReportTp26(void); //table 26 資料解析
	void ReportTp25(void); //table 25 資料解析
	void ReportTp24(void); //table 24 資料解析
	void ReportTp23(void); //table 23 資料解析
	void ReportTp22(void); //table 22 資料解析
	void ReportTp21(void); //table 21 資料解析
	void ReportTp20(void); //table 20 資料解析
	void ReportTp19(void); //table 19 資料解析
	void ReportTp18(void); //table 18 資料解析
	void ReportTp17(void); //table 17 資料解析
	void ReportTp16(void); //table 16 資料解析
	void ReportTp15(void); //table 15 資料解析
	void ReportTp14(void); //table 14 資料解析
	void ReportTp13(void); //table 13 資料解析
	void ReportTp12(void); //table 12 資料解析
	void ReportTp11(void); //table 11 資料解析
	void ReportTp10(void); //table 10 資料解析
	void ReportTp9(void); //table 9 資料解析
	void ReportTp8(void); //table 8 資料解析
	void ReportTp7(void); //table 7 資料解析
	void ReportTp6(void); //table 6 資料解析
	void ReportTp5(void); //table 5 資料解析
	void ReportTp4(void); //table 4 資料解析
	void ReportTp3(void); //table 3 資料解析
	void ReportTp2(void); //table 2 資料解析
	void ReportTp1(void); //table 1 資料解析
	void ReportTp0(void); //table 0 資料解析
	void ReportEntry(void); //entry資料解析
	
	void CalSize(char *tmp,WORD dd); //轉換table 17的記憶體大小
	void WriteReport(int posi,int col,char *value); //將資料顯示在畫面上
	void GetAttachedString(char *str,int sw); //取得附加在table後面的字串
	void ShowReport(int sld); //找尋指定的table
	void ShowStatus(char *str); //顯示資料到狀態列
	CSMBIOSDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSMBIOSDlg)
	enum { IDD = IDD_SMBIOS_DIALOG };
	CListBox	m_list;
	CStatic	m_status;
	CListCtrl	m_report;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMBIOSDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSMBIOSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeList();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMBIOSDLG_H__89E9BEDC_6F7B_4287_80C4_D7E0B59A6D8F__INCLUDED_)
