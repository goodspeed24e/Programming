; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRegDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PCI.h"

ClassCount=5
Class1=CPCIApp
Class2=CPCIDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PCI_DIALOG
Class4=CRegDlg
Resource4=IDD_REG_DIALOG
Class5=CListDlg
Resource5=IDD_LIST_DIALOG

[CLS:CPCIApp]
Type=0
HeaderFile=PCI.h
ImplementationFile=PCI.cpp
Filter=N

[CLS:CPCIDlg]
Type=0
HeaderFile=PCIDlg.h
ImplementationFile=PCIDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_TAB

[CLS:CAboutDlg]
Type=0
HeaderFile=PCIDlg.h
ImplementationFile=PCIDlg.cpp
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

[DLG:IDD_PCI_DIALOG]
Type=1
Class=CPCIDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_TAB,SysTabControl32,1342177280
Control3=IDC_STATUS_STATIC,static,1342308352

[DLG:IDD_REG_DIALOG]
Type=1
Class=CRegDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDC_DESC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_ROW_STATIC,static,1342308354
Control5=IDC_EDIT,edit,1350633476
Control6=IDC_SCROLLBAR,scrollbar,1342177281
Control7=IDC_ASC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:CRegDlg]
Type=0
HeaderFile=RegDlg.h
ImplementationFile=RegDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_DESC_STATIC
VirtualFilter=dWC

[DLG:IDD_LIST_DIALOG]
Type=1
Class=CListDlg
ControlCount=2
Control1=IDOK,button,1073741824
Control2=IDC_LIST,SysListView32,1350664205

[CLS:CListDlg]
Type=0
HeaderFile=ListDlg.h
ImplementationFile=ListDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CListDlg

