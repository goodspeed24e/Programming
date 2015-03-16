; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSMBIOSDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SMBIOS.h"

ClassCount=3
Class1=CSMBIOSApp
Class2=CSMBIOSDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SMBIOS_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDD_SMBIOS_DIALOG (English (U.S.))

[CLS:CSMBIOSApp]
Type=0
HeaderFile=SMBIOS.h
ImplementationFile=SMBIOS.cpp
Filter=N

[CLS:CSMBIOSDlg]
Type=0
HeaderFile=SMBIOSDlg.h
ImplementationFile=SMBIOSDlg.cpp
Filter=D
LastObject=CSMBIOSDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=SMBIOSDlg.h
ImplementationFile=SMBIOSDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_SMBIOS_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CSMBIOSDlg

[DLG:IDD_SMBIOS_DIALOG (English (U.S.))]
Type=1
Class=CSMBIOSDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308354
Control2=IDC_REPORT_LIST,SysListView32,1350664193
Control3=IDC_STATUS_STATIC,static,1342308352
Control4=IDC_LIST,listbox,1352728833

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

