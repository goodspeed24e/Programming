; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSearchDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Memory.h"

ClassCount=4
Class1=CMemoryApp
Class2=CMemoryDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_MEMORY_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CSearchDlg
Resource4=IDD_SEARCH_DIALOG

[CLS:CMemoryApp]
Type=0
HeaderFile=Memory.h
ImplementationFile=Memory.cpp
Filter=N

[CLS:CMemoryDlg]
Type=0
HeaderFile=MemoryDlg.h
ImplementationFile=MemoryDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDOK

[CLS:CAboutDlg]
Type=0
HeaderFile=MemoryDlg.h
ImplementationFile=MemoryDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_VER_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_MEMORY_DIALOG]
Type=1
Class=CMemoryDlg
ControlCount=14
Control1=IDC_INPUT_EDIT,edit,1350631552
Control2=IDC_BUTTON,button,1342242816
Control3=IDC_ADV_BUTTON,button,1342242816
Control4=IDCANCEL,button,1342242816
Control5=IDOK,button,1073741824
Control6=IDC_EDIT,edit,1350637572
Control7=IDC_STATIC,static,1342308352
Control8=IDC_VIR_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_SCROLLBAR,scrollbar,1342177281
Control11=IDC_STATIC,static,1342308352
Control12=IDC_ASCII_STATIC,static,1342308352
Control13=IDC_STATUS_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308353

[DLG:IDD_SEARCH_DIALOG]
Type=1
Class=CSearchDlg
ControlCount=23
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308354
Control4=IDC_STATIC,static,1342308354
Control5=IDC_STATIC,static,1342308354
Control6=IDC_VALUE_EDIT,edit,1350631552
Control7=IDC_HEX_RADIO,button,1342308361
Control8=IDC_STRING_RADIO,button,1342308361
Control9=IDC_START_EDIT,edit,1350631552
Control10=IDC_END_EDIT,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_HEX_STATIC,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342308352
Control18=IDC_WRITE_START_EDIT,edit,1350631552
Control19=IDC_WRITE_BUTTON,button,1342242816
Control20=IDC_WRITE_DATA_EDIT,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352

[CLS:CSearchDlg]
Type=0
HeaderFile=SearchDlg.h
ImplementationFile=SearchDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSearchDlg

