#if !defined(AFX_REGDLG_H__9AB8ABED_C22C_45E3_806F_B5BBBF7842CB__INCLUDED_)
#define AFX_REGDLG_H__9AB8ABED_C22C_45E3_806F_B5BBBF7842CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog

class CRegDlg : public CDialog
{
// Construction
public:
	BYTE bus;
	BYTE dev;
	BYTE func;
	DWORD Pci_E_addr;
	BYTE data_source[5000];
	char para[3][100];
	int pci_express;
	int reg_start;
	
	int Cal_PciE_addr(BYTE bus,BYTE dev,BYTE func);
	void Show_Data(void);
	void Set_Scroll(void);
	CRegDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegDlg)
	enum { IDD = IDD_REG_DIALOG };
	CStatic	m_row;
	CStatic	m_title;
	CScrollBar	m_scroll;
	CEdit	m_reg;
	CStatic	m_ascii;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGDLG_H__9AB8ABED_C22C_45E3_806F_B5BBBF7842CB__INCLUDED_)
