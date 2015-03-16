// WinACPIDoc.h : interface of the CWinACPIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINACPIDOC_H__9B1B0A9F_B1D5_42DD_95F2_E9D6E1A6DB42__INCLUDED_)
#define AFX_WINACPIDOC_H__9B1B0A9F_B1D5_42DD_95F2_E9D6E1A6DB42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWinACPIDoc : public CDocument
{
protected: // create from serialization only
	CWinACPIDoc();
	DECLARE_DYNCREATE(CWinACPIDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinACPIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWinACPIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWinACPIDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINACPIDOC_H__9B1B0A9F_B1D5_42DD_95F2_E9D6E1A6DB42__INCLUDED_)
