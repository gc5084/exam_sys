#include "stdAfx.h"
#include "SrvMyApp.h"
#include "SrvMainWnd.h"
#include "MySocket.h"
#include "StuInfor.h"
#include "DealMethod.h"
//主窗口的静态数据成员 记录当前状态的标志
int CMainWindow::nFlag = 0;

//以下为全局对象
CMyApp myApp;							
										//应用程序本身
CStuInfor* arrStu[MAXNUM];
										//学生信息链表
SendTestData g_sendTestData[MAXNUM];
										//随机分配试题信息
CList<SOCKET,SOCKET> listSock;
										//储存socket的链表
CList<MemoryData,MemoryData>   listTestFill;
										//储存填空试题结构指针链表
CList<MemoryData,MemoryData>   listTestModify;
										//储存改错试题结构指针链表
CList<MemoryData,MemoryData>   listTestDesign;
										//储存设计试题结构指针链表

CCriticalSection g_list;
										//用于ListSock的临界区对象
CCriticalSection g_sock;
										//用于保护收发数据的临界区对象
int GStartTime;
                                        //保存开始时间

int GTestTime = 0;		
										//保存考试总时长
HWND GhWnd;


UINT MyRecvFunc(LPVOID pParam);
										//函数声明 此函数处理接受到数据事件

/*
应用程序初始化，其中加载1.1版本的套接字库，
构造CMainWindow，产生主窗口，显示并更新
*/
BOOL CMyApp::InitInstance()
{
	//创建时间对象 只能启动一个程序实例
	if(CreateEvent(NULL,FALSE,FALSE,"SrvOnlyOneStart") != NULL)
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

	//申请套接字库
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
 
/* The WinSock DLL is acceptable. Proceed. */


	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

/*接受函数*/
UINT AcceptFunc(LPVOID pParam)
{
	SOCKET sockTemp;
	int nCount = 0;
    sockaddr_in tempAddr;
	int size =sizeof(tempAddr);
	while(1)
	{
		sockTemp = accept(*((SOCKET*)pParam),(sockaddr*)&tempAddr,&size);
		if(sockTemp == INVALID_SOCKET)
		{
			//链接失败
			WSAGetLastError();
		}
			//将套接字存入套接字数组 
		g_list.Lock();
		listSock.AddHead(sockTemp);
		g_list.Unlock();
	}

	return 0;

}

UINT SelectFunc(LPVOID pParam)
{
	fd_set fdRead;

	g_list.Lock();
	POSITION pos = listSock.GetHeadPosition();
	g_list.Unlock();

	SOCKET tempSock;
	int nSelect;
	timeval time;
	time.tv_sec=0;time.tv_usec=50;
	while(1)
	{
		while(pos == NULL)
		{
			Sleep(100);

			g_list.Lock();
            pos = listSock.GetHeadPosition();
			g_list.Unlock();
													//等待0.1秒，再检查链表是否有数据
		}
		FD_ZERO(&fdRead);
		while(pos != NULL)
		{
			g_list.Lock();
			tempSock = listSock.GetNext(pos);
			g_list.Unlock();

			FD_SET(tempSock,&fdRead);
       
		}

		nSelect = select(0,&fdRead,NULL,NULL,&time);
													//50毫秒后停止阻塞 可能接受到新的sock加入
		if(nSelect == 0)
			continue;								
													//也可以不写 写上清楚
		if(nSelect == SOCKET_ERROR)
		{
			CString str;
			str.Format(_T("Select失败 错误代码%d"),WSAGetLastError());
			AfxMessageBox(str);
			return -1;
			
		}
        while(nSelect>0)
		{
			g_list.Lock();
			pos = listSock.GetHeadPosition();
			g_list.Unlock();

			while(pos != NULL)
			{

                g_list.Lock();
				tempSock = listSock.GetNext(pos);
				g_list.Unlock();

		   		if(FD_ISSET(tempSock,&fdRead))
				{
					g_list.Lock();
					listSock.RemoveAt(listSock.Find(tempSock));
					g_list.Unlock();

					AfxBeginThread(MyRecvFunc,(LPVOID)tempSock);
					//值传递,传指针可能在线程还未开启时 tempSock就被
					//tempSock = listSock.GetNext(pos);语句改变
					Sleep(0);
					//开线程接受数据
					
					nSelect--;
				}

			}

		}

      
	}
}

/*
处理一条客户消息的线程函数
*/
UINT MyRecvFunc(LPVOID pParam)				                                           
{
	SOCKET sock;
	sock = ((SOCKET)pParam);
	int nFlag;
										//对应退出循环类别 0为未找到
	int n;
										//n学生类指针数组索引

	CMySocket mysock;
	char *czRecvPage;
	
	czRecvPage = mysock.MyRecv(sock);
	if(czRecvPage == NULL)
		return -1;

	switch(czRecvPage[SOCKHEAD-2])
	{

//发送来学号信息
//发送数据库中对应学生姓名 发送副版本1
//若没有找到相应信息 发送副版本2
//若该学号学生已经登陆过 发送副版本3
//若该学号状态为禁止 发送副版本4
	case 1:
		{
			n     = 0;
			//索引赋值为0
			nFlag = 0;
			//标志赋值为0
			while(n < MAXNUM)
			{
				//if保证数组项的指针不为空 为空则对应位置无学生信息
				if(arrStu[n] != NULL)
				{
					if(strcmp(&czRecvPage[SOCKHEAD],arrStu[n]->strNum) == 0) //找到对应项
					{
						nFlag = 1;			
						//将标志设为找到
						if(arrStu[n]->nState == 0)   //用户状态为未登录 允许登录
						{
							if(mysock.MySend(sock,arrStu[n]->strName,1,1)==FALSE)//发送学生姓名
								return -1;
							break;
						}
						else if(arrStu[n]->nState == 4) //状态为被禁止考试
						{
							if(mysock.MySend(sock,arrStu[n]->strName,1,4)==FALSE)
								return -1;
							break;
						}
						else
						{
							if(mysock.MySend(sock,arrStu[n]->strName,1,3)==FALSE)
								return -1;
							break;
							//用户状态不允许重复登陆
						}
					}
				}
				
				n++;
				//累加索引
			}
			if(nFlag == 0)
				if(mysock.MySend(sock,NULL,1,2)==FALSE)
					return -1;
				//发送信息说明未找到学生信息
				break;
				
		}
	

//发送来学号确认信息
//根据学号找到该生 匹配时再根据考试是否已经计时发送试题后考试时间信息
	case Mess_ConfirmNumber:
		{
			CDealMethod dealMethod;
			if(dealMethod.DealNumberSure(czRecvPage,sock) == FALSE)
				return -1;
			//刷新显示区域
			::SendMessage(GhWnd,WM_INFORPAINT,sock,NULL);
			break;
		}
		
		

//正常退出消息 及考生交卷完毕消息
	case Mess_TestOver:	//正常退出消息
		{
			CDealMethod dealMethod;
			if(dealMethod.TestOver(sock) == FALSE)
			{
				return -1;
			}
			//刷新显示区域
			::SendMessage(GhWnd,WM_INFORPAINT,sock,NULL);

			break;
		}

//试题包序号消息
	case Mess_TestPackIndex:
		{
			CDealMethod dealMethod;
			if(dealMethod.TestPackIndex((int)czRecvPage[SOCKHEAD-1],sock) == FALSE)
			{
				return -1;
			}
			break;
		}
//更新考生剩余时间消息
	case Mess_Time:
		{
			CDealMethod dealMethod;
			if(dealMethod.TiemUpdata((int)czRecvPage[SOCKHEAD-1],sock) == FALSE)
			{
				return -1;
			}
			break;
		}

/*
	case 5://填空题消息
		{
			for(n=0;n<MAXNUM;n++)
			{
				if(arrStu[n] != NULL)
				{
					if(arrStu[n]->sock == sock)
					{
						arrStu[n]->StuAnswerFill[czRecvPage[SOCKHEAD-1]-1] =
							new char[strlen(czRecvPage)+ADDBUFFER];  //堆上分配空间 赋给StuAnswerFill指针
						
						::lstrcpy(arrStu[n]->StuAnswerFill[czRecvPage[SOCKHEAD-1]-1],
							&czRecvPage[SOCKHEAD]);  //将接受缓冲区的数据复制给StuAnswerFill
						
						break;
						
					}
				}
				
			}
			break;
			
		}
		
	case 6://改错题消息
		{
			for(n=0;n<MAXNUM;n++)
			{
				if(arrStu[n] != NULL)
				{
					if(arrStu[n]->sock == sock)
					{
						arrStu[n]->StuAnswerModify[czRecvPage[SOCKHEAD-1]-1] =
							new char[strlen(czRecvPage)+ADDBUFFER];
						
						::lstrcpy(arrStu[n]->StuAnswerModify[czRecvPage[SOCKHEAD-1]-1],
							&czRecvPage[SOCKHEAD]);
						break;
						
					}
				}
				
			}
			break;
		}
		
	case 7://设计题信息
		{
			for(n=0;n<MAXNUM;n++)
			{
				if(arrStu[n] != NULL)
				{
					if(arrStu[n]->sock == sock)
					{
						arrStu[n]->StuAnswerDesign[czRecvPage[SOCKHEAD-1]-1] =
							new char[strlen(czRecvPage)+ADDBUFFER];
						
						::lstrcpy(arrStu[n]->StuAnswerDesign[czRecvPage[SOCKHEAD-1]-1],
							&czRecvPage[SOCKHEAD]);
						
						break;
						
					}
				}
				
			}
			break;
		}


	case 20:  //请求发送试题消息
		{
			CDealMethod RequestMethod;
			if(RequestMethod.DealRequestTest(sock) == FALSE)
			{
				return -1;
			}
			break;
				
		}
*/


	default:
		break;
		
		
	}
	g_list.Lock();
	listSock.AddTail(sock);					//套接字重新添加进链表
	g_list.Unlock();

	return 0;


}

/*
向所有在线学生发送服务器时间的线程函数

UINT TimerFunc(LPVOID pParam)
{

	CTime NowTime = CTime::GetCurrentTime();
	int nHour     = NowTime.GetHour();
	int nMinute   = NowTime.GetMinute();
	//获取到当前时间 小时和分钟
    int nNowTime = nHour*60 + nMinute;
	int nPassTime = nNowTime - GStartTime;
	GPassTime = nPassTime;
	char SendBuf[3];
	SendBuf[0] = nPassTime+1;
									//时间加1 以防止时间为0时，截断字符串
	SendBuf[1] = GTestTime;  //总时长

	int nFlag = CMainWindow::nFlag; //获取主窗口的标志
	if((nFlag&FLAG_TIMEGO) == FLAG_TIMEGO)
		SendBuf[2] = 1;
	else
		SendBuf[2] = 2;
	
	SendBuf[3] = 0;
	//设置要发送的字符串


	
	int n = 0;
	CMySocket mysock;
	while(n<80)
	{
		if((arrStu[n]!=NULL) && (arrStu[n]->nState==1))
		{
			if(mysock.MySend(arrStu[n]->sock,SendBuf,15,1) == FALSE)//时间信息ID为15
			{
				arrStu[n]->nState = 3; //考生状态更改为异常
			}
			
		}
		//给每位在线的学生发送服务器时间 和 考试总时长
		n++;

	}
	return 0;

}
*/