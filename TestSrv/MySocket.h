/////////////////////////////////////////////////////////////////////
//类名：CMySocket
//说明：应用程序套接字类
//功能：封装所有对套接字即对通信的操作。
//      数据的发送和接受       
//作者：郭承(gc5084@163.com)
//组织：图形图像研究所
//日期：2009.03
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_MYSOCKET_H__0A06C325_715E_4C2C_87B2_5A2C56F17705__INCLUDED_)
#define AFX_MYSOCKET_H__0A06C325_715E_4C2C_87B2_5A2C56F17705__INCLUDED_

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
	BOOL  GetIP(SOCKET s,sockaddr* name);
protected:
	char* RecvBuffer;
};

#endif // !defined(AFX_MYSOCKET_H__0A06C325_715E_4C2C_87B2_5A2C56F17705__INCLUDED_)
