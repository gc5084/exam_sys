// MySocket.cpp: implementation of the CMySocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestClient.h"
#include "MySocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HWND  GhWndMain;

CMySocket::CMySocket()
{
	RecvBuffer = NULL;
	nLastError = 0;
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
	czHead[SOCKHEAD] = 0;
    ret = recv(sock,czHead,SOCKHEAD,0);
	if(ret == SOCKET_ERROR)
	{
		int nError = WSAGetLastError();
		if(nError == WSAECONNRESET)
		{
			this->nLastError = WSAECONNRESET; //�������жϴ���
			return NULL;
		}
		this->nLastError = nError;
		return NULL;
	}
	nLeft = (int)((czHead[0]-1)*100) + (int)czHead[1]; 
													//��ȡ������Ϣ�ĳ���
	int nLenth = nLeft;                             //����
    char* TempBuffer = new char[nLeft+ADDBUFFER];		        	
	nIndex = 0;										//�������賤�ȵ��ַ���
	while(nLeft > 0)
	{
		ret = recv(sock,&TempBuffer[nIndex],nLeft,0);
		if(ret == SOCKET_ERROR)
		{
			this->nLastError = WSAGetLastError();
			return NULL;
		}
		nLeft -= ret;
		nIndex += ret;
	}
	if(RecvBuffer != NULL)
		delete[] RecvBuffer;
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
		this->nLastError = ERROR_TEXTTOOLONG;  //�ı���������־
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
		ret = send(sock,&czPage[nIndex],nLeft,0);
		if(ret == SOCKET_ERROR )
		{
			nLastError = WSAGetLastError();
			return FALSE;
		}
		
		nLeft = nLeft - ret;
		nIndex += ret; 
		
	}
	delete[] czPage;
	czPage = NULL;
	return TRUE;

}

int CMySocket::GetLastError()
{
	return this->nLastError;
}