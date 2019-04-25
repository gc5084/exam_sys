; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestClientDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TestClient.h"

ClassCount=9
Class1=CTestClientApp
Class2=CTestClientDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ENTRY
Resource2=IDR_MAINFRAME
Class5=CMainWindow
Class6=CUIThread
Class7=CTopWindow
Class4=CTopWnd
Resource3=IDD_ABOUTBOX
Class8=CEntryDlg
Resource4=IDD_TESTCLIENT_DIALOG
Class9=CWaitStartDlg
Resource5=IDD_WAITSTART

[CLS:CTestClientApp]
Type=0
HeaderFile=TestClient.h
ImplementationFile=TestClient.cpp
Filter=N

[CLS:CTestClientDlg]
Type=0
HeaderFile=TestClientDlg.h
ImplementationFile=TestClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=TestClientDlg.h
ImplementationFile=TestClientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TESTCLIENT_DIALOG]
Type=1
Class=CTestClientDlg
ControlCount=33
Control1=IDC_LOOK_FILL_1,button,1342242816
Control2=IDC_TITLEINFO,edit,1352730756
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,button,1342177287
Control8=IDC_ANSWER_FILL_1,button,1342242816
Control9=IDC_LOOK_FILL_2,button,1342242816
Control10=IDC_ANSWER_FILL_2,button,1342242816
Control11=IDC_ANSWER_FILL_3,button,1342242816
Control12=IDC_LOOK_FILL_3,button,1342242816
Control13=IDC_LOOK_MODIFY_1,button,1342242816
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287
Control18=IDC_ANSWER_MODIFY_1,button,1342242816
Control19=IDC_LOOK_MODIFY_2,button,1342242816
Control20=IDC_ANSWER_MODIFY_2,button,1342242816
Control21=IDC_ANSWER_MODIFY_3,button,1342242816
Control22=IDC_LOOK_MODIFY_3,button,1342242816
Control23=IDC_LOOK_DESIGN_1,button,1342242816
Control24=IDC_STATIC,button,1342177287
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,button,1342177287
Control27=IDC_STATIC,button,1342177287
Control28=IDC_ANSWER_DESIGN_1,button,1342242816
Control29=IDC_LOOK_DESIGN_2,button,1342242816
Control30=IDC_ANSWER_DESIGN_2,button,1342242816
Control31=IDC_ANSWER_DESIGN_3,button,1342242816
Control32=IDC_LOOK_DESIGN_3,button,1342242816
Control33=IDC_TESTINFO,static,1342308352

[CLS:CTopWnd]
Type=0
HeaderFile=TopWnd.h
ImplementationFile=TopWnd.cpp
BaseClass=CWinThread
Filter=N

[CLS:CMainWindow]
Type=0
HeaderFile=MainWindow.h
ImplementationFile=MainWindow.cpp
BaseClass=CFrameWnd
Filter=T

[CLS:CUIThread]
Type=0
HeaderFile=UIThread.h
ImplementationFile=UIThread.cpp
BaseClass=CWinThread
Filter=N

[CLS:CTopWindow]
Type=0
HeaderFile=TopWindow.h
ImplementationFile=TopWindow.cpp
BaseClass=CWnd
Filter=T
VirtualFilter=WC
LastObject=CTopWindow

[DLG:IDD_ENTRY]
Type=1
Class=CEntryDlg
ControlCount=4
Control1=IDOK,button,1342242955
Control2=IDCANCEL,button,1342242955
Control3=IDC_NUMBER,edit,1350631552
Control4=IDC_STATIC,static,1342177294

[CLS:CEntryDlg]
Type=0
HeaderFile=EntryDlg.h
ImplementationFile=EntryDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CEntryDlg
VirtualFilter=dWC

[DLG:IDD_WAITSTART]
Type=1
Class=CWaitStartDlg
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_WAITNUM,edit,1350633600
Control5=IDC_WAITNAME,edit,1350633600
Control6=IDC_WAITTIME,edit,1350633600
Control7=IDC_STATIC,static,1342308352

[CLS:CWaitStartDlg]
Type=0
HeaderFile=WaitStartDlg.h
ImplementationFile=WaitStartDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CWaitStartDlg

