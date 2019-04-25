; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChangeIPDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ChangeIP.h"

ClassCount=3
Class1=CChangeIPApp
Class2=CChangeIPDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_CHANGEIP_DIALOG

[CLS:CChangeIPApp]
Type=0
HeaderFile=ChangeIP.h
ImplementationFile=ChangeIP.cpp
Filter=N

[CLS:CChangeIPDlg]
Type=0
HeaderFile=ChangeIPDlg.h
ImplementationFile=ChangeIPDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_IPADDRESS

[CLS:CAboutDlg]
Type=0
HeaderFile=ChangeIPDlg.h
ImplementationFile=ChangeIPDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CHANGEIP_DIALOG]
Type=1
Class=CChangeIPDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_IPADDRESS,SysIPAddress32,1342242816
Control4=IDC_STATIC,static,1342308352

