// WinACPIDoc.cpp : implementation of the CWinACPIDoc class
//

#include "stdafx.h"
#include "WinACPI.h"

#include "WinACPIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinACPIDoc

IMPLEMENT_DYNCREATE(CWinACPIDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinACPIDoc, CDocument)
	//{{AFX_MSG_MAP(CWinACPIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinACPIDoc construction/destruction

CWinACPIDoc::CWinACPIDoc()
{
	// TODO: add one-time construction code here

}

CWinACPIDoc::~CWinACPIDoc()
{
}

BOOL CWinACPIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWinACPIDoc serialization

void CWinACPIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWinACPIDoc diagnostics

#ifdef _DEBUG
void CWinACPIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinACPIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinACPIDoc commands
