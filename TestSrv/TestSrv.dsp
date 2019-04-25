# Microsoft Developer Studio Project File - Name="TestSrv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TestSrv - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestSrv.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestSrv.mak" CFG="TestSrv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestSrv - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TestSrv - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestSrv - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "TestSrv - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TestSrv - Win32 Release"
# Name "TestSrv - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CheckDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DealMethod.cpp
# End Source File
# Begin Source File

SOURCE=.\InforSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\ListAllDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LOCKDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\MuchTestDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyDataBase.cpp
# End Source File
# Begin Source File

SOURCE=.\MySocket.cpp
# End Source File
# Begin Source File

SOURCE=.\PointPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectTestDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SrvMainWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\SrvMyApp.cpp
# End Source File
# Begin Source File

SOURCE=.\StuInfor.cpp
# End Source File
# Begin Source File

SOURCE=.\StuPage.cpp
# End Source File
# Begin Source File

SOURCE=.\TalkDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TestPage.cpp
# End Source File
# Begin Source File

SOURCE=.\TestSrv.rc
# End Source File
# Begin Source File

SOURCE=.\TimeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UnlockDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CheckDlg.h
# End Source File
# Begin Source File

SOURCE=.\DealMethod.h
# End Source File
# Begin Source File

SOURCE=.\InforSheet.h
# End Source File
# Begin Source File

SOURCE=.\ListAllDlg.h
# End Source File
# Begin Source File

SOURCE=.\LOCKDLG.h
# End Source File
# Begin Source File

SOURCE=.\MuchTestDlg.h
# End Source File
# Begin Source File

SOURCE=.\MyDataBase.h
# End Source File
# Begin Source File

SOURCE=.\MySocket.h
# End Source File
# Begin Source File

SOURCE=.\PointPage.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SelectTestDlg.h
# End Source File
# Begin Source File

SOURCE=.\SrvMainWnd.h
# End Source File
# Begin Source File

SOURCE=.\SrvMyApp.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StuInfor.h
# End Source File
# Begin Source File

SOURCE=.\StuPage.h
# End Source File
# Begin Source File

SOURCE=.\TalkDlg.h
# End Source File
# Begin Source File

SOURCE=.\TestPage.h
# End Source File
# Begin Source File

SOURCE=.\TimeDlg.h
# End Source File
# Begin Source File

SOURCE=.\UnlockDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\精美电脑图标下载34.ico"
# End Source File
# End Group
# End Target
# End Project
