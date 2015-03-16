#if !defined(AFX_LISTDLG_H__AD98EC2F_28A7_40F8_8AD1_69BDFA1D1E41__INCLUDED_)
#define AFX_LISTDLG_H__AD98EC2F_28A7_40F8_8AD1_69BDFA1D1E41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListDlg.h : header file
//

class CRegDlg;

/////////////////////////////////////////////////////////////////////////////
// CListDlg dialog

class CListDlg : public CDialog
{
// Construction
public:
	CDialog *m_dlg;
	
	int func;
	DWORD SMB_addr;
	
	void GetAttachedString(char *str);
	int ReadEntry(void);
	void Get_Slot_info(void);
	void Get_PCI_info(void);
	void Write_list(int posi,int col,char *value);
	CRegDlg *m_regDlg;
	CListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CListDlg)
	enum { IDD = IDD_LIST_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListDlg)
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTDLG_H__AD98EC2F_28A7_40F8_8AD1_69BDFA1D1E41__INCLUDED_)
