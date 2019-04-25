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
	czHead[SOCKHEAD] = 0;					//添加结束标志 必须

//接收数据的数据头
	g_sock.Lock();
    ret = recv(sock,czHead,SOCKHEAD,0);
	g_sock.Unlock();

	if(ret == SOCKET_ERROR||ret == 0)
	{
		int nError = WSAGetLastError();
		if(nError == WSAECONNRESET)			//客户端断开连接 删除链表中的socket
		{
			for(int n=0;n<MAXNUM;n++)
			{
				if(arrStu[n] != NULL)
				{
					if(arrStu[n]->sock == sock && arrStu[n]->nState == 1)
					{
						arrStu[n]->nState = 3; //将对应学生的状态置为异常
					}
				}
			}
											
			int nc = closesocket(sock);
			if(nc == SOCKET_ERROR)
			{
				CString str;
				str.Format(_T("关闭套接字失败 错误代码%d"),WSAGetLastError());
//				AfxMessageBox(str);
				return NULL;
				
			}
			
			::SendMessage(GhWnd,WM_INFORPAINT,sock,NULL);
            return NULL;
			
		}

		return NULL;
	}
//接受数据的数据区
	nLeft = (int)((czHead[0]-1)*100) + (int)czHead[1]; 
													//获取整个信息的长度
	int nLenth = nLeft;				
													//保留整个信息长度 留为后用
    char* TempBuffer = new char[nLeft + ADDBUFFER];		        	
	nIndex = 0;										//分配所需长度的字符串
	while(nLeft > 0)
	{
		g_sock.Lock();
		ret = recv(sock,&TempBuffer[nIndex],nLeft,0);
		g_sock.Unlock();

		if(ret == SOCKET_ERROR)
		{
			int nError = WSAGetLastError();
			if(nError == WSAECONNRESET)			//客户端断开连接 删除链表中的socket
			{
				int nc = closesocket(sock);
				if(nc == SOCKET_ERROR)
				{
					CString str;
					str.Format(_T("关闭套接字失败 错误代码%d"),WSAGetLastError());
//					AfxMessageBox(str);
					return NULL;
					
				}
				AfxMessageBox("断开连接！");
				return NULL;
				
			}
			CString str;
			str.Format(_T("接收数据失败 错误代码%d"),nError);
//			AfxMessageBox(str);
			return NULL;
		}
		nLeft -= ret;
		nIndex += ret;
	}
//	RecvBuffer = new char[SOCKHEAD+nLeft];    //我日我日我日
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
		g_sock.Lock();
		ret = send(sock,&czPage[nIndex],nLeft,0);
		g_sock.Unlock();
		if(ret == SOCKET_ERROR )
		{
			CString str;
			str.Format(_T("发送数据失败 错误代码%d"),WSAGetLastError());
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
	//获取sockaddr变量的长度
	int len = sizeof(*name);
	//执行获取IP的API函数
	if(getpeername(s,name,&len) == SOCKET_ERROR)
	{
		CString str;
		str.Format(_T("获取IP失败 错误代码%d"),WSAGetLastError());
		AfxMessageBox(str);
		return FALSE;
	}

	return TRUE;
}
