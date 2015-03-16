; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDetaildlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WinSMB.h"

ClassCount=4
Class1=CWinSMBApp
Class2=CWinSMBDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_WINSMB_DIALOG
Class4=CDetaildlg
Resource4=IDD_DETAIL_DIALOG

[CLS:CWinSMBApp]
Type=0
HeaderFile=WinSMB.h
ImplementationFile=WinSMB.cpp
Filter=N

[CLS:CWinSMBDlg]
Type=0
HeaderFile=WinSMBDlg.h
ImplementationFile=WinSMBDlg.cpp
Filter=D
LastObject=CWinSMBDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=WinSMBDlg.h
ImplementationFile=WinSMBDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_WINSMB_DIALOG]
Type=1
Class=CWinSMBDlg
ControlCount=4
Control1=IDC_LIST,SysListView32,1350631437
Control2=IDOK,button,1342242816
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_DETAIL_DIALOG]
Type=1
Class=CDetaildlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308354
Control4=IDC_DATA_STATIC,static,1342308352
Control5=IDC_ASCII_STATIC,static,1342308352

[CLS:CDetaildlg]
Type=0
HeaderFile=Detaildlg.h
ImplementationFile=Detaildlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CDetaildlg
VirtualFilter=dWC

