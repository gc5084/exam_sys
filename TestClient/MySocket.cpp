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
			this->nLastError = WSAECONNRESET; //服务器中断错误
			return NULL;
		}
		this->nLastError = nError;
		return NULL;
	}
	nLeft = (int)((czHead[0]-1)*100) + (int)czHead[1]; 
													//获取整个信息的长度
	int nLenth = nLeft;                             //保留
    char* TempBuffer = new char[nLeft+ADDBUFFER];		        	
	nIndex = 0;										//分配所需长度的字符串
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
		AfxMessageBox("文本过大");
		this->nLastError = ERROR_TEXTTOOLONG;  //文本过大错误标志
        return FALSE;
	}
	char* czPage = new char[nMessLenth+SOCKHEAD+1+ADDBUFFER]; //整个发送包的长度

	czPage[0] = nMessLenth/100 + 1;
											 //高位基数从一开始 避免0结束标志 接收时也应减去
	czPage[1] = nMessLenth%100 + 1;
											 //低位也从1开始 因为至少发送0结束标志1位
	czPage[2] = nMajorFlag;
											 //主标志
	czPage[3] = nSubFlag;	           
											 //副标志
	czPage[nMessLenth+SOCKHEAD] = 0;			     //结束标志'/0'
											 
	::lstrcpy(&czPage[SOCKHEAD],czInfor);
											 //API函数 功能将第二个参数的字符串，复制到第一个参数的地址
	
	
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