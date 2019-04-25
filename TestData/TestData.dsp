# Microsoft Developer Studio Project File - Name="TestData" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TestData - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestData.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestData.mak" CFG="TestData - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestData - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TestData - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestData - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "TestData - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TestData - Win32 Release"
# Name "TestData - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Base.cpp
# End Source File
# Begin Source File

SOURCE=.\BigShowDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Design.cpp
# End Source File
# Begin Source File

SOURCE=.\Fill.cpp
# End Source File
# Begin Source File

SOURCE=.\FillDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InputDlg1.cpp
# End Source File
# Begin Source File

SOURCE=.\InputDlg2.cpp
# End Source File
# Begin Source File

SOURCE=.\InputDlg3.cpp
# End Source File
# Begin Source File

SOURCE=.\Modify.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TestData.cpp
# End Source File
# Begin Source File

SOURCE=.\TestData.rc
# End Source File
# Begin Source File

SOURCE=.\TestDataDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WaitDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Base.h
# End Source File
# Begin Source File

SOURCE=.\BigShowDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChangeDlg.h
# End Source File
# Begin Source File

SOURCE=.\Design.h
# End Source File
# Begin Source File

SOURCE=.\Fill.h
# End Source File
# Begin Source File

SOURCE=.\FillDlg.h
# End Source File
# Begin Source File

SOURCE=.\InputDlg1.h
# End Source File
# Begin Source File

SOURCE=.\InputDlg2.h
# End Source File
# Begin Source File

SOURCE=.\InputDlg3.h
# End Source File
# Begin Source File

SOURCE=.\Modify.h
# End Source File
# Begin Source File

SOURCE=.\PSheet.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShowDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TestData.h
# End Source File
# Begin Source File

SOURCE=.\TestDataDlg.h
# End Source File
# Begin Source File

SOURCE=.\WaitDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\TestData.ico
# End Source File
# Begin Source File

SOURCE=.\res\TestData.rc2
# End Source File
# Begin Source File

SOURCE=".\res\断开数据库_按下.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\断开数据库_点燃.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\断开数据库_禁止.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\断开数据库_正常.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\改错题_按下.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\改错题_点燃.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\改错题_禁止.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\改错题_正常.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\链接数据库_按下.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\链接数据库_点燃.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\链接数据库_禁止.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\链接数据库_正常.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\录入试题_正常.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设计题_按下.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设计题_点燃.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设计题_禁止.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设计题_正常.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\填空题_按下.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\填空题_点燃.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\填空题_禁止.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\填空题_正常.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\退出_按下.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\退出_点燃.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\退出_禁止.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\退出_正常.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
