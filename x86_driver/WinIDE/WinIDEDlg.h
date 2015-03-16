// WinIDEDlg.h : header file
//

#if !defined(AFX_WINIDEDLG_H__79A8E2E6_4013_4C97_BDEC_DDD1282A5B39__INCLUDED_)
#define AFX_WINIDEDLG_H__79A8E2E6_4013_4C97_BDEC_DDD1282A5B39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "def.h"

/////////////////////////////////////////////////////////////////////////////
// CWinIDEDlg dialog

class CWinIDEDlg : public CDialog
{
// Construction
public:
	int controller_cnt;

	int SearchIDEcontroller( void );
	BYTE IdentifyDevice(WORD Port,BYTE Device,BYTE *Data);
	BYTE IsPacketSignature(WORD Port);
	BYTE GetIdentifyData(WORD Port,BYTE *Data);
	void GetHDDpara(WORD Port,BYTE Device,HDDpara *Para,BYTE *DataBuff);
	void Write_list(char *value, int posi, int col);
	void Get_IDE_info(void);
	CWinIDEDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinIDEDlg)
	enum { IDD = IDD_WINIDE_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinIDEDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinIDEDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINIDEDLG_H__79A8E2E6_4013_4C97_BDEC_DDD1282A5B39__INCLUDED_)
