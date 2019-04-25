// MySocket.h: interface for the CMySocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSOCKET_H__C9DF80E7_9600_4493_ACDB_30320119FD29__INCLUDED_)
#define AFX_MYSOCKET_H__C9DF80E7_9600_4493_ACDB_30320119FD29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMySocket  
{
public:
	CMySocket();
	virtual ~CMySocket();
	char* MyRecv(SOCKET sock);
	BOOL  MySend(SOCKET sock,char* czInfor,int nMajorFlag,int nSubFlag);
	int GetLastError();
protected:
	char* RecvBuffer;

	int nLastError;  //最后一个错误标志


};

#endif // !defined(AFX_MYSOCKET_H__C9DF80E7_9600_4493_ACDB_30320119FD29__INCLUDED_)
