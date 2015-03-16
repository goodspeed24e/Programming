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
	int FindEntry(void); //��MSMBIOS table���i�J�I
	void ReadEntry(void); //Ū��entry���
	int FindTable(int sld);//��M���w��table
	void Jump_str(void); //���L�C�@��table�᭱�����[�r��
	
	void ReportOEM(void); //oem������
	void ReportEnd(void); //table 127 ��ƸѪR
	void ReportTp126(void); //table 126 ��ƸѪR
	void ReportTp39(void); //table 39 ��ƸѪR
	void ReportTp38(void); //table 38 ��ƸѪR
	void ReportTp37(void); //table 37 ��ƸѪR
	void ReportTp36(void); //table 36 ��ƸѪR
	void ReportTp35(void); //table 35 ��ƸѪR
	void ReportTp34(void); //table 34 ��ƸѪR
	void ReportTp33(void); //table 33 ��ƸѪR
	void ReportTp32(void); //table 32 ��ƸѪR
	void ReportTp30(void); //table 30 ��ƸѪR
	void ReportTp29(void); //table 29 ��ƸѪR
	void ReportTp28(void); //table 28 ��ƸѪR
	void ReportTp27(void); //table 27 ��ƸѪR
	void ReportTp26(void); //table 26 ��ƸѪR
	void ReportTp25(void); //table 25 ��ƸѪR
	void ReportTp24(void); //table 24 ��ƸѪR
	void ReportTp23(void); //table 23 ��ƸѪR
	void ReportTp22(void); //table 22 ��ƸѪR
	void ReportTp21(void); //table 21 ��ƸѪR
	void ReportTp20(void); //table 20 ��ƸѪR
	void ReportTp19(void); //table 19 ��ƸѪR
	void ReportTp18(void); //table 18 ��ƸѪR
	void ReportTp17(void); //table 17 ��ƸѪR
	void ReportTp16(void); //table 16 ��ƸѪR
	void ReportTp15(void); //table 15 ��ƸѪR
	void ReportTp14(void); //table 14 ��ƸѪR
	void ReportTp13(void); //table 13 ��ƸѪR
	void ReportTp12(void); //table 12 ��ƸѪR
	void ReportTp11(void); //table 11 ��ƸѪR
	void ReportTp10(void); //table 10 ��ƸѪR
	void ReportTp9(void); //table 9 ��ƸѪR
	void ReportTp8(void); //table 8 ��ƸѪR
	void ReportTp7(void); //table 7 ��ƸѪR
	void ReportTp6(void); //table 6 ��ƸѪR
	void ReportTp5(void); //table 5 ��ƸѪR
	void ReportTp4(void); //table 4 ��ƸѪR
	void ReportTp3(void); //table 3 ��ƸѪR
	void ReportTp2(void); //table 2 ��ƸѪR
	void ReportTp1(void); //table 1 ��ƸѪR
	void ReportTp0(void); //table 0 ��ƸѪR
	void ReportEntry(void); //entry��ƸѪR
	
	void CalSize(char *tmp,WORD dd); //�ഫtable 17���O����j�p
	void WriteReport(int posi,int col,char *value); //�N�����ܦb�e���W
	void GetAttachedString(char *str,int sw); //���o���[�btable�᭱���r��
	void ShowReport(int sld); //��M���w��table
	void ShowStatus(char *str); //��ܸ�ƨ쪬�A�C
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
