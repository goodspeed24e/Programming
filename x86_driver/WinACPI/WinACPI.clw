; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDetailView
LastTemplate=CFormView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WinACPI.h"
LastPage=0

ClassCount=6
Class1=CWinACPIApp
Class2=CWinACPIDoc
Class3=CWinACPIView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_WINACPI_FORM
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Resource3=IDR_MAINFRAME
Class6=CDetailView
Resource4=IDD_DETAIL_FORMVIEW

[CLS:CWinACPIApp]
Type=0
HeaderFile=WinACPI.h
ImplementationFile=WinACPI.cpp
Filter=N

[CLS:CWinACPIDoc]
Type=0
HeaderFile=WinACPIDoc.h
ImplementationFile=WinACPIDoc.cpp
Filter=N

[CLS:CWinACPIView]
Type=0
HeaderFile=WinACPIView.h
ImplementationFile=WinACPIView.cpp
Filter=D
LastObject=CWinACPIView
BaseClass=CFormView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=WinACPI.cpp
ImplementationFile=WinACPI.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_VIEW_STATUS_BAR
Command3=ID_APP_ABOUT
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_WINACPI_FORM]
Type=1
Class=CWinACPIView
ControlCount=2
Control1=IDC_SHOW_STATIC,static,1342308865
Control2=IDC_TREE,SysTreeView32,1350631463

[CLS:CDetailView]
Type=0
HeaderFile=DetailView.h
ImplementationFile=DetailView.cpp
BaseClass=CFormView
Filter=D
LastObject=CDetailView
VirtualFilter=VWC

[DLG:IDD_DETAIL_FORMVIEW]
Type=1
Class=CDetailView
ControlCount=2
Control1=IDC_SHOW_STATIC,static,1342308353
Control2=IDC_LIST,SysListView32,1350664461

