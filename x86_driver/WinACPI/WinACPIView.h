// WinACPIView.h : interface of the CWinACPIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINACPIVIEW_H__C8E93047_1E38_4F55_A0E5_CB5798A65BD9__INCLUDED_)
#define AFX_WINACPIVIEW_H__C8E93047_1E38_4F55_A0E5_CB5798A65BD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWinACPIView : public CFormView
{
protected: // create from serialization only
	CWinACPIView();
	DECLARE_DYNCREATE(CWinACPIView)

public:
	//{{AFX_DATA(CWinACPIView)
	enum { IDD = IDD_WINACPI_FORM };
	CTreeCtrl	m_tree;
	//}}AFX_DATA

// Attributes
public:
	CWinACPIDoc* GetDocument();

// Operations
public:
	HTREEITEM hti;
	
	
	int FindRSDP(void);
	int FindSubTable(DWORD addr_start);
	
	LONG OnStart(WPARAM wParam, LPARAM lParam);
	void DetectACPI(void);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinACPIView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWinACPIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWinACPIView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WinACPIView.cpp
inline CWinACPIDoc* CWinACPIView::GetDocument()
   { return (CWinACPIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINACPIVIEW_H__C8E93047_1E38_4F55_A0E5_CB5798A65BD9__INCLUDED_)
