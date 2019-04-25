// TestClient.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestClient.h"
#include "TestClientDlg.h"
#include "EntryDlg.h"
#include "MySocket.h"
#include "TestManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestClientApp

BEGIN_MESSAGE_MAP(CTestClientApp, CWinApp)
	//{{AFX_MSG_MAP(CTestClientApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestClientApp construction

CTestClientApp::CTestClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	for(int n=0;n<3;n++)
	{
		fill[n]   = NULL;
		modify[n] = NULL;
		design[n] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestClientApp object



/////////////////////////////////////////////////////////////////////////////
// CTestClientApp initialization

BOOL CTestClientApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	//创建时间对象 只能启动一个程序实例
	if(CreateEvent(NULL,FALSE,FALSE,"ClientOnlyOneStart") != NULL)
	{
		if(GetLastError() ==  ERROR_ALREADY_EXISTS)
		{
			AfxMessageBox("一个程序实例正在运行！");
			return FALSE;
		}
	}
	else
	{
		DWORD dw;
		dw = GetLastError();
		CString str;
		str.Format("%u",dw);
		AfxMessageBox(str);
	}


	WORD wVersionRequested;
	int err;
	
	wVersionRequested = MAKEWORD( 1, 1 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		CString str;
		str.Format(_T("申请套接字库失败 错误代码%d"),WSAGetLastError());
		AfxMessageBox(str);
		return FALSE;
	}
	
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		AfxMessageBox(_T("套接字库版本不符"));               
		WSACleanup( );
		return FALSE; 
	}

	m_sock  = socket(AF_INET,SOCK_STREAM,0);

	//出现登录对话框
	CEntryDlg Edlg;

	if(Edlg.DoModal() == IDCANCEL)
	{
		return FALSE;
	}												//取消退出，确定继续

	CTestClientDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}




///////////////////////////////////////////////////////////////////////////////////////////
//全局

CTestClientApp theApp;
SOCKET Gsock;
int    GTime = 0;
int    GTimeLong  = 0;        //考试总时长
char   *GczName; 
CCriticalSection GLockSock;
HWND   GhWndEntry = NULL;
HWND   GhWndMain = NULL;
HWND   GhWndTop  = NULL;
HWND   GhWndWait = NULL;



UINT RecvFunc(LPVOID pParam)
{
	CMySocket mysock;
	char *czRecv;

	while(1)
	{

		czRecv = mysock.MyRecv(Gsock);//接收数据

		if(czRecv == NULL) //接到空数据 接受数据有误
		{
			char* czTemp = new char[strlen("服务器中断！")+ADDBUFFER];
			_tcscpy(czTemp,"服务器中断！");

			if(mysock.GetLastError() == WSAECONNRESET) //服务器中断 需退出程序
			{
				if(::IsWindow(GhWndMain))
				{
					::SendMessage(GhWndMain,WM_MESSAGE,NULL,(long)czTemp);//向主窗口发送消息
				}
				else if(::IsWindow(GhWndWait))
				{
					::SendMessage(GhWndWait,WM_MESSAGE,NULL,(long)czTemp);//向主窗口发送消息
				}
				return -1;
			}
		    continue;
		}

									
		switch(czRecv[SOCKHEAD-2])
		{
			/*
		case 5:   //填空题1
		case 6:   //填空题2
		case 7:   //填空题3
		case 8:   //改错题1
		case 9:   //改错题2
		case 10:  //改错题3
		case 11:  //设计题1
		case 12:  //设计题2
		case 13:  //设计题3
			{
				CTestManage testMange;  //产生一个试题管理类 处理试题消息
				testMange.InputText(czRecv); //调用函数处理
				break;  //跳出
			}
			*/
		case 14:  //试题发送结束消息
			{
				if(::IsWindow(GhWndWait))
				{
					::SendMessage(GhWndWait,WM_TESTSENDOVER,NULL,NULL);//向主窗口发送消息
				}
				
				break;
			}
		case 15:  //时间消息
			{
				GTime      = (int)czRecv[SOCKHEAD]-1;
				//时间减1 符合发送约定
				GTimeLong  = (int)czRecv[SOCKHEAD+1];
				
				if(::IsWindow(GhWndTop))
				{
					::PostMessage(GhWndTop,WM_TIMEUPDATA,NULL,NULL);//向顶层时间窗口发送消息
				}
				break;
				
			}
		case 16:  //服务器文本消息
			{
				char* czTemp = new char[strlen(&czRecv[4])+ADDBUFFER];
				_tcscpy(czTemp,&czRecv[4]);
				if(::IsWindow(GhWndMain))
				{
					::PostMessage(GhWndMain,WM_MESSAGE,NULL,(long)czTemp);//向主窗口发送消息
				}
				else if(::IsWindow(GhWndWait))
				{
					::PostMessage(GhWndWait,WM_MESSAGE,NULL,(long)czTemp);//向主窗口发送消息
				}
				break;
				
			}

		case 17:  //重置消息
			{
				if(::IsWindow(GhWndMain))
				{
					::PostMessage(GhWndMain,WM_RESTART,NULL,NULL);//向窗口发送重置消息
				}
				else if(::IsWindow(GhWndWait))
				{
					::PostMessage(GhWndWait,WM_RESTART,NULL,NULL);//向窗口发送重置消息
				}
				break;
			}
		case 19:  //交卷成功消息
			{
				//向窗口发送交卷成功消息
				if(::IsWindow(GhWndMain))
				{
					::PostMessage(GhWndMain,WM_SENDSUCCESS,NULL,NULL);
					                //向主对话框发送交卷成功消息
				}
			}
		default:
			{
				break;
			}


		}
	}

}