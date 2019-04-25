// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__4991CA92_6B40_4ADD_B91A_4F9BE7273EE0__INCLUDED_)
#define AFX_STDAFX_H__4991CA92_6B40_4ADD_B91A_4F9BE7273EE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
const int SOCKHEAD  = 4;
const int ADDBUFFER = 4;
const int ERROR_TEXTTOOLONG = -2;


///////////////////////////////////服务器客户端消息对于const
const int Mess_TestPackIndex = 20;
const int Mess_Time = 15;
const int Mess_ConfirmNumber = 2;


#define ID_TIMER 1
#define WM_TIMEUPDATA (WM_USER + 101)
#define WM_TIMEOVER   (WM_USER + 102)
#define WM_TESTSEND   (WM_USER + 103)   //按下顶层窗口的发送按钮 产生的消息
#define WM_MYCLOSE    (WM_USER + 104)   //接收函数向主窗口发送的关闭程序消息 用于服务器中断
#define WM_RESTART    (WM_USER + 105)   //RecvFunc函数接收到服务器重置消息 发向主窗口
#define WM_MESSAGE    (WM_USER + 106)   //RecvFunc函数接收到服务器发来的文字消息 发向主窗口
#define WM_TESTSENDOVER (WM_USER + 107)   //试题发送完毕消息  用于等待对话框或登录对话框
#define WM_SENDSUCCESS  (WM_USER + 108)   //交卷成功消息 主对话框接收消息



#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <afxmt.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <Afxsock.h>


#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__4991CA92_6B40_4ADD_B91A_4F9BE7273EE0__INCLUDED_)
