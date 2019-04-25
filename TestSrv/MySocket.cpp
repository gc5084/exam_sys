// MySocket.cpp: implementation of the CMySocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySocket.h"
#include "SrvMyApp.h"
#include "srvMainWnd.h"
#include "StuInfor.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CList<SOCKET,SOCKET> listSock;
extern CCriticalSection g_sock;
extern CStuInfor* arrStu[MAXNUM];
extern HWND GhWnd;

CMySocket::CMySocket()
{
	RecvBuffer = NULL;

}

CMySocket::~CMySocket()
{
	delete[] RecvBuffer;
    RecvBuffer = NULL;

}

char* CMySocket::MyRecv(SOCKET sock)
{
	int ret;
	int nLeft;
	int nIndex = 0;
    char czHead[SOCKHEAD+1];
	czHead[SOCKHEAD] = 0;					//��ӽ�����־ ����

//�������ݵ�����ͷ
	g_sock.Lock();
    ret = recv(sock,czHead,SOCKHEAD,0);
	g_sock.Unlock();

	if(ret == SOCKET_ERROR||ret == 0)
	{
		int nError = WSAGetLastError();
		if(nError == WSAECONNRESET)			//�ͻ��˶Ͽ����� ɾ�������е�socket
		{
			for(int n=0;n<MAXNUM;n++)
			{
				if(arrStu[n] != NULL)
				{
					if(arrStu[n]->sock == sock && arrStu[n]->nState == 1)
					{
						arrStu[n]->nState = 3; //����Ӧѧ����״̬��Ϊ�쳣
					}
				}
			}
											
			int nc = closesocket(sock);
			if(nc == SOCKET_ERROR)
			{
				CString str;
				str.Format(_T("�ر��׽���ʧ�� �������%d"),WSAGetLastError());
//				AfxMessageBox(str);
				return NULL;
				
			}
			
			::SendMessage(GhWnd,WM_INFORPAINT,sock,NULL);
            return NULL;
			
		}

		return NULL;
	}
//�������ݵ�������
	nLeft = (int)((czHead[0]-1)*100) + (int)czHead[1]; 
													//��ȡ������Ϣ�ĳ���
	int nLenth = nLeft;				
													//����������Ϣ���� ��Ϊ����
    char* TempBuffer = new char[nLeft + ADDBUFFER];		        	
	nIndex = 0;										//�������賤�ȵ��ַ���
	while(nLeft > 0)
	{
		g_sock.Lock();
		ret = recv(sock,&TempBuffer[nIndex],nLeft,0);
		g_sock.Unlock();

		if(ret == SOCKET_ERROR)
		{
			int nError = WSAGetLastError();
			if(nError == WSAECONNRESET)			//�ͻ��˶Ͽ����� ɾ�������е�socket
			{
				int nc = closesocket(sock);
				if(nc == SOCKET_ERROR)
				{
					CString str;
					str.Format(_T("�ر��׽���ʧ�� �������%d"),WSAGetLastError());
//					AfxMessageBox(str);
					return NULL;
					
				}
				AfxMessageBox("�Ͽ����ӣ�");
				return NULL;
				
			}
			CString str;
			str.Format(_T("��������ʧ�� �������%d"),nError);
//			AfxMessageBox(str);
			return NULL;
		}
		nLeft -= ret;
		nIndex += ret;
	}
//	RecvBuffer = new char[SOCKHEAD+nLeft];    //������������
	RecvBuffer = new char[SOCKHEAD+nLenth+ADDBUFFER];
	::lstrcpy(RecvBuffer,czHead);
    ::lstrcpy(&RecvBuffer[SOCKHEAD],TempBuffer);			
	delete[] TempBuffer;
    TempBuffer = NULL;
	return RecvBuffer;

}

BOOL CMySocket::MySend(SOCKET sock,char* czInfor,int nMajorFlag,int nSubFlag)
{
	char temp[] = "";
	int nMessLenth;
	if(czInfor == NULL)
		czInfor = temp;
	nMessLenth = strlen(czInfor);
	if(nMessLenth > 20000)
	{
		AfxMessageBox("�ı�����");
        return FALSE;
	}
	char* czPage = new char[nMessLenth+SOCKHEAD+1+ADDBUFFER]; //�������Ͱ��ĳ���

	czPage[0] = nMessLenth/100 + 1;
											 //��λ������һ��ʼ ����0������־ ����ʱҲӦ��ȥ
	czPage[1] = nMessLenth%100 + 1;
											 //��λҲ��1��ʼ ��Ϊ���ٷ���0������־1λ
	czPage[2] = nMajorFlag;
											 //����־
	czPage[3] = nSubFlag;	           
											 //����־
	czPage[nMessLenth+SOCKHEAD] = 0;			     //������־'/0'
											 
	::lstrcpy(&czPage[SOCKHEAD],czInfor);
											 //API���� ���ܽ��ڶ����������ַ��������Ƶ���һ�������ĵ�ַ
	
	
	int nLeft = nMessLenth+SOCKHEAD+1;
	int nIndex = 0,ret;
	while(nLeft>0)
	{
		g_sock.Lock();
		ret = send(sock,&czPage[nIndex],nLeft,0);
		g_sock.Unlock();
		if(ret == SOCKET_ERROR )
		{
			CString str;
			str.Format(_T("��������ʧ�� �������%d"),WSAGetLastError());
//			AfxMessageBox(str);
			return FALSE;
		}
		
		nLeft = nLeft - ret;
		nIndex += ret; 
		
	}
	delete[] czPage;
	czPage = NULL;

	return TRUE;

}

BOOL CMySocket::GetIP(SOCKET s,sockaddr* name)
{
	if(s == NULL)
		return FALSE;
	//��ȡsockaddr�����ĳ���
	int len = sizeof(*name);
	//ִ�л�ȡIP��API����
	if(getpeername(s,name,&len) == SOCKET_ERROR)
	{
		CString str;
		str.Format(_T("��ȡIPʧ�� �������%d"),WSAGetLastError());
		AfxMessageBox(str);
		return FALSE;
	}

	return TRUE;
}
