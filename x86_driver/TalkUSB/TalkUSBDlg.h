// TalkUSBDlg.h : header file
//

#if !defined(AFX_TALKUSBDLG_H__811E246B_6418_49D5_B155_D9F3749C02FF__INCLUDED_)
#define AFX_TALKUSBDLG_H__811E246B_6418_49D5_B155_D9F3749C02FF__INCLUDED_

#if _MSC_VER > 1000
#include "HIDDevice.h"
#include "afxwin.h"

#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTalkUSBDlg dialog

class CTalkUSBDlg : public CDialog
{
// Construction
public:
	HANDLE m_hNotifyDevNode;
	DWORD  m_thisThreadID;//新建立執行緒的 ID
	HANDLE m_hThread;//新建立的執行緒
		
	void RegisterNotification();
	void UnregisterNotification();
	BOOL OnDeviceChange(UINT nEventType, DWORD dwData);
	void USBConnect();
	void USBDisconnect();
	void SendOneChar(unsigned char ch);
	void Check_Stats (unsigned char* Stat1);
	
	
	
	friend DWORD __stdcall MLTProc(void *p);//主程式
	CHIDDevice HID_Talker;
	CTalkUSBDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTalkUSBDlg)
	enum { IDD = IDD_TALKUSB_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTalkUSBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTalkUSBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TALKUSBDLG_H__811E246B_6418_49D5_B155_D9F3749C02FF__INCLUDED_)
