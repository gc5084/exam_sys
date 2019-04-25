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

	//����ʱ����� ֻ������һ������ʵ��
	if(CreateEvent(NULL,FALSE,FALSE,"ClientOnlyOneStart") != NULL)
	{
		if(GetLastError() ==  ERROR_ALREADY_EXISTS)
		{
			AfxMessageBox("һ������ʵ���������У�");
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
		str.Format(_T("�����׽��ֿ�ʧ�� �������%d"),WSAGetLastError());
		AfxMessageBox(str);
		return FALSE;
	}
	
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		AfxMessageBox(_T("�׽��ֿ�汾����"));               
		WSACleanup( );
		return FALSE; 
	}

	m_sock  = socket(AF_INET,SOCK_STREAM,0);

	//���ֵ�¼�Ի���
	CEntryDlg Edlg;

	if(Edlg.DoModal() == IDCANCEL)
	{
		return FALSE;
	}												//ȡ���˳���ȷ������

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
//ȫ��

CTestClientApp theApp;
SOCKET Gsock;
int    GTime = 0;
int    GTimeLong  = 0;        //������ʱ��
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

		czRecv = mysock.MyRecv(Gsock);//��������

		if(czRecv == NULL) //�ӵ������� ������������
		{
			char* czTemp = new char[strlen("�������жϣ�")+ADDBUFFER];
			_tcscpy(czTemp,"�������жϣ�");

			if(mysock.GetLastError() == WSAECONNRESET) //�������ж� ���˳�����
			{
				if(::IsWindow(GhWndMain))
				{
					::SendMessage(GhWndMain,WM_MESSAGE,NULL,(long)czTemp);//�������ڷ�����Ϣ
				}
				else if(::IsWindow(GhWndWait))
				{
					::SendMessage(GhWndWait,WM_MESSAGE,NULL,(long)czTemp);//�������ڷ�����Ϣ
				}
				return -1;
			}
		    continue;
		}

									
		switch(czRecv[SOCKHEAD-2])
		{
			/*
		case 5:   //�����1
		case 6:   //�����2
		case 7:   //�����3
		case 8:   //�Ĵ���1
		case 9:   //�Ĵ���2
		case 10:  //�Ĵ���3
		case 11:  //�����1
		case 12:  //�����2
		case 13:  //�����3
			{
				CTestManage testMange;  //����һ����������� ����������Ϣ
				testMange.InputText(czRecv); //���ú�������
				break;  //����
			}
			*/
		case 14:  //���ⷢ�ͽ�����Ϣ
			{
				if(::IsWindow(GhWndWait))
				{
					::SendMessage(GhWndWait,WM_TESTSENDOVER,NULL,NULL);//�������ڷ�����Ϣ
				}
				
				break;
			}
		case 15:  //ʱ����Ϣ
			{
				GTime      = (int)czRecv[SOCKHEAD]-1;
				//ʱ���1 ���Ϸ���Լ��
				GTimeLong  = (int)czRecv[SOCKHEAD+1];
				
				if(::IsWindow(GhWndTop))
				{
					::PostMessage(GhWndTop,WM_TIMEUPDATA,NULL,NULL);//�򶥲�ʱ�䴰�ڷ�����Ϣ
				}
				break;
				
			}
		case 16:  //�������ı���Ϣ
			{
				char* czTemp = new char[strlen(&czRecv[4])+ADDBUFFER];
				_tcscpy(czTemp,&czRecv[4]);
				if(::IsWindow(GhWndMain))
				{
					::PostMessage(GhWndMain,WM_MESSAGE,NULL,(long)czTemp);//�������ڷ�����Ϣ
				}
				else if(::IsWindow(GhWndWait))
				{
					::PostMessage(GhWndWait,WM_MESSAGE,NULL,(long)czTemp);//�������ڷ�����Ϣ
				}
				break;
				
			}

		case 17:  //������Ϣ
			{
				if(::IsWindow(GhWndMain))
				{
					::PostMessage(GhWndMain,WM_RESTART,NULL,NULL);//�򴰿ڷ���������Ϣ
				}
				else if(::IsWindow(GhWndWait))
				{
					::PostMessage(GhWndWait,WM_RESTART,NULL,NULL);//�򴰿ڷ���������Ϣ
				}
				break;
			}
		case 19:  //����ɹ���Ϣ
			{
				//�򴰿ڷ��ͽ���ɹ���Ϣ
				if(::IsWindow(GhWndMain))
				{
					::PostMessage(GhWndMain,WM_SENDSUCCESS,NULL,NULL);
					                //�����Ի����ͽ���ɹ���Ϣ
				}
			}
		default:
			{
				break;
			}


		}
	}

}