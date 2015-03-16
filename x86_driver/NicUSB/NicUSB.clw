; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNicUSBDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NicUSB.h"

ClassCount=3
Class1=CNicUSBApp
Class2=CNicUSBDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_NICUSB_DIALOG

[CLS:CNicUSBApp]
Type=0
HeaderFile=NicUSB.h
ImplementationFile=NicUSB.cpp
Filter=N

[CLS:CNicUSBDlg]
Type=0
HeaderFile=NicUSBDlg.h
ImplementationFile=NicUSBDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CNicUSBDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=NicUSBDlg.h
ImplementationFile=NicUSBDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_NICUSB_DIALOG]
Type=1
Class=CNicUSBDlg
ControlCount=6
Control1=IDC_IPADDRESS,SysIPAddress32,1342242816
Control2=IDC_EDIT,edit,1350631552
Control3=IDOK,button,1342242816
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

