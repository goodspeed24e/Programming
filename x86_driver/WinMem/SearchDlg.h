#if !defined(AFX_SEARCHDLG_H__050FC312_55C8_4081_A373_9EEDB8F68D0E__INCLUDED_)
#define AFX_SEARCHDLG_H__050FC312_55C8_4081_A373_9EEDB8F68D0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog

class CSearchDlg : public CDialog
{
// Construction
public:
	void OnOffHex(void);
	CSearchDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchDlg)
	enum { IDD = IDD_SEARCH_DIALOG };
	CEdit	m_write_start;
	CEdit	m_write_data;
	CButton	m_string;
	CButton	m_hex;
	CEdit	m_value;
	CEdit	m_end;
	CEdit	m_start;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHexRadio();
	afx_msg void OnStringRadio();
	virtual void OnOK();
	afx_msg void OnWriteButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHDLG_H__050FC312_55C8_4081_A373_9EEDB8F68D0E__INCLUDED_)
