// NicUSBDlg.h : header file
//

#if !defined(AFX_NICUSBDLG_H__177BB008_396F_40CC_9E31_837C3ECF2A72__INCLUDED_)
#define AFX_NICUSBDLG_H__177BB008_396F_40CC_9E31_837C3ECF2A72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNicUSBDlg dialog

class CNicUSBDlg : public CDialog
{
// Construction
public:

	CNicUSBDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNicUSBDlg)
	enum { IDD = IDD_NICUSB_DIALOG };
	CButton	m_ok;
	CIPAddressCtrl	m_ip;
	CEdit	m_string;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNicUSBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNicUSBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NICUSBDLG_H__177BB008_396F_40CC_9E31_837C3ECF2A72__INCLUDED_)
