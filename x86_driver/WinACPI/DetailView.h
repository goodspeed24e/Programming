#if !defined(AFX_DETAILVIEW_H__EC15D19B_BC5C_461B_BCD1_E87DB74A422D__INCLUDED_)
#define AFX_DETAILVIEW_H__EC15D19B_BC5C_461B_BCD1_E87DB74A422D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DetailView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDetailView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDetailView : public CFormView
{
protected:
	CDetailView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDetailView)

// Form Data
public:
	//{{AFX_DATA(CDetailView)
	enum { IDD = IDD_DETAIL_FORMVIEW };
	CStatic	m_show;
	CListCtrl	m_list;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	int posi;
	
	void expend_rsdp(void);
	void expend_header(BYTE *buff);
	void expend_rsdt(DWORD addr,BYTE *buff);
	void expend_xsdt(DWORD addr,BYTE *buff);
	void expend_fadt(DWORD addr,BYTE *buff);
	void expend_facs(BYTE *buff);
	void expend_dsdt(DWORD addr,BYTE *buff);
	void expend_ssdt(DWORD addr,BYTE *buff);
	void expend_madt(DWORD addr,BYTE *buff);
	void expend_sbst(DWORD addr,BYTE *buff);
	void expend_ecdt(DWORD addr,BYTE *buff);
	void expend_srat(DWORD addr,BYTE *buff);
	void expend_slit(DWORD addr,BYTE *buff);
	void expend_mcfg(DWORD addr,BYTE *buff);
	void expend_boot(DWORD addr,BYTE *buff);
	void expend_hpet(DWORD addr,BYTE *buff);
	void expend_cpep(DWORD addr,BYTE *buff);
	void expend_dbgp(DWORD addr,BYTE *buff);
	void expend_spcr(DWORD addr,BYTE *buff);
	void expend_spmi(DWORD addr,BYTE *buff);
	void expend_tcpa(DWORD addr,BYTE *buff);
	void expend_wdat(DWORD addr,BYTE *buff);
	void expend_wdrt(DWORD addr,BYTE *buff);
	void expend_wspt(DWORD addr,BYTE *buff);
	void expend_erst(DWORD addr,BYTE *buff);
	void expend_bert(DWORD addr,BYTE *buff);
	void expend_hest(DWORD addr,BYTE *buff);
	void expend_einj(DWORD addr,BYTE *buff);
	
	void Write_list(int posi, int col,char *value);
	void ReadData(DWORD addr,int size,BYTE *buff);
	void GetTable(char *name,DWORD addr);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDetailView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDetailView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDetailView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DETAILVIEW_H__EC15D19B_BC5C_461B_BCD1_E87DB74A422D__INCLUDED_)
