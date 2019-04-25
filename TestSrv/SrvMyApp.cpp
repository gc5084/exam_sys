#include "stdAfx.h"
#include "SrvMyApp.h"
#include "SrvMainWnd.h"
#include "MySocket.h"
#include "StuInfor.h"
#include "DealMethod.h"
//�����ڵľ�̬���ݳ�Ա ��¼��ǰ״̬�ı�־
int CMainWindow::nFlag = 0;

//����Ϊȫ�ֶ���
CMyApp myApp;							
										//Ӧ�ó�����
CStuInfor* arrStu[MAXNUM];
										//ѧ����Ϣ����
SendTestData g_sendTestData[MAXNUM];
										//�������������Ϣ
CList<SOCKET,SOCKET> listSock;
										//����socket������
CList<MemoryData,MemoryData>   listTestFill;
										//�����������ṹָ������
CList<MemoryData,MemoryData>   listTestModify;
										//����Ĵ�����ṹָ������
CList<MemoryData,MemoryData>   listTestDesign;
										//�����������ṹָ������

CCriticalSection g_list;
										//����ListSock���ٽ�������
CCriticalSection g_sock;
										//���ڱ����շ����ݵ��ٽ�������
int GStartTime;
                                        //���濪ʼʱ��

int GTestTime = 0;		
										//���濼����ʱ��
HWND GhWnd;


UINT MyRecvFunc(LPVOID pParam);
										//�������� �˺���������ܵ������¼�

/*
Ӧ�ó����ʼ�������м���1.1�汾���׽��ֿ⣬
����CMainWindow�����������ڣ���ʾ������
*/
BOOL CMyApp::InitInstance()
{
	//����ʱ����� ֻ������һ������ʵ��
	if(CreateEvent(NULL,FALSE,FALSE,"SrvOnlyOneStart") != NULL)
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

	//�����׽��ֿ�
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
 
/* The WinSock DLL is acceptable. Proceed. */


	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

/*���ܺ���*/
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
			//����ʧ��
			WSAGetLastError();
		}
			//���׽��ִ����׽������� 
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
													//�ȴ�0.1�룬�ټ�������Ƿ�������
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
													//50�����ֹͣ���� ���ܽ��ܵ��µ�sock����
		if(nSelect == 0)
			continue;								
													//Ҳ���Բ�д д�����
		if(nSelect == SOCKET_ERROR)
		{
			CString str;
			str.Format(_T("Selectʧ�� �������%d"),WSAGetLastError());
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
					//ֵ����,��ָ��������̻߳�δ����ʱ tempSock�ͱ�
					//tempSock = listSock.GetNext(pos);���ı�
					Sleep(0);
					//���߳̽�������
					
					nSelect--;
				}

			}

		}

      
	}
}

/*
����һ���ͻ���Ϣ���̺߳���
*/
UINT MyRecvFunc(LPVOID pParam)				                                           
{
	SOCKET sock;
	sock = ((SOCKET)pParam);
	int nFlag;
										//��Ӧ�˳�ѭ����� 0Ϊδ�ҵ�
	int n;
										//nѧ����ָ����������

	CMySocket mysock;
	char *czRecvPage;
	
	czRecvPage = mysock.MyRecv(sock);
	if(czRecvPage == NULL)
		return -1;

	switch(czRecvPage[SOCKHEAD-2])
	{

//������ѧ����Ϣ
//�������ݿ��ж�Ӧѧ������ ���͸��汾1
//��û���ҵ���Ӧ��Ϣ ���͸��汾2
//����ѧ��ѧ���Ѿ���½�� ���͸��汾3
//����ѧ��״̬Ϊ��ֹ ���͸��汾4
	case 1:
		{
			n     = 0;
			//������ֵΪ0
			nFlag = 0;
			//��־��ֵΪ0
			while(n < MAXNUM)
			{
				//if��֤�������ָ�벻Ϊ�� Ϊ�����Ӧλ����ѧ����Ϣ
				if(arrStu[n] != NULL)
				{
					if(strcmp(&czRecvPage[SOCKHEAD],arrStu[n]->strNum) == 0) //�ҵ���Ӧ��
					{
						nFlag = 1;			
						//����־��Ϊ�ҵ�
						if(arrStu[n]->nState == 0)   //�û�״̬Ϊδ��¼ �����¼
						{
							if(mysock.MySend(sock,arrStu[n]->strName,1,1)==FALSE)//����ѧ������
								return -1;
							break;
						}
						else if(arrStu[n]->nState == 4) //״̬Ϊ����ֹ����
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
							//�û�״̬�������ظ���½
						}
					}
				}
				
				n++;
				//�ۼ�����
			}
			if(nFlag == 0)
				if(mysock.MySend(sock,NULL,1,2)==FALSE)
					return -1;
				//������Ϣ˵��δ�ҵ�ѧ����Ϣ
				break;
				
		}
	

//������ѧ��ȷ����Ϣ
//����ѧ���ҵ����� ƥ��ʱ�ٸ��ݿ����Ƿ��Ѿ���ʱ�����������ʱ����Ϣ
	case Mess_ConfirmNumber:
		{
			CDealMethod dealMethod;
			if(dealMethod.DealNumberSure(czRecvPage,sock) == FALSE)
				return -1;
			//ˢ����ʾ����
			::SendMessage(GhWnd,WM_INFORPAINT,sock,NULL);
			break;
		}
		
		

//�����˳���Ϣ ���������������Ϣ
	case Mess_TestOver:	//�����˳���Ϣ
		{
			CDealMethod dealMethod;
			if(dealMethod.TestOver(sock) == FALSE)
			{
				return -1;
			}
			//ˢ����ʾ����
			::SendMessage(GhWnd,WM_INFORPAINT,sock,NULL);

			break;
		}

//����������Ϣ
	case Mess_TestPackIndex:
		{
			CDealMethod dealMethod;
			if(dealMethod.TestPackIndex((int)czRecvPage[SOCKHEAD-1],sock) == FALSE)
			{
				return -1;
			}
			break;
		}
//���¿���ʣ��ʱ����Ϣ
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
	case 5://�������Ϣ
		{
			for(n=0;n<MAXNUM;n++)
			{
				if(arrStu[n] != NULL)
				{
					if(arrStu[n]->sock == sock)
					{
						arrStu[n]->StuAnswerFill[czRecvPage[SOCKHEAD-1]-1] =
							new char[strlen(czRecvPage)+ADDBUFFER];  //���Ϸ���ռ� ����StuAnswerFillָ��
						
						::lstrcpy(arrStu[n]->StuAnswerFill[czRecvPage[SOCKHEAD-1]-1],
							&czRecvPage[SOCKHEAD]);  //�����ܻ����������ݸ��Ƹ�StuAnswerFill
						
						break;
						
					}
				}
				
			}
			break;
			
		}
		
	case 6://�Ĵ�����Ϣ
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
		
	case 7://�������Ϣ
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


	case 20:  //������������Ϣ
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
	listSock.AddTail(sock);					//�׽���������ӽ�����
	g_list.Unlock();

	return 0;


}

/*
����������ѧ�����ͷ�����ʱ����̺߳���

UINT TimerFunc(LPVOID pParam)
{

	CTime NowTime = CTime::GetCurrentTime();
	int nHour     = NowTime.GetHour();
	int nMinute   = NowTime.GetMinute();
	//��ȡ����ǰʱ�� Сʱ�ͷ���
    int nNowTime = nHour*60 + nMinute;
	int nPassTime = nNowTime - GStartTime;
	GPassTime = nPassTime;
	char SendBuf[3];
	SendBuf[0] = nPassTime+1;
									//ʱ���1 �Է�ֹʱ��Ϊ0ʱ���ض��ַ���
	SendBuf[1] = GTestTime;  //��ʱ��

	int nFlag = CMainWindow::nFlag; //��ȡ�����ڵı�־
	if((nFlag&FLAG_TIMEGO) == FLAG_TIMEGO)
		SendBuf[2] = 1;
	else
		SendBuf[2] = 2;
	
	SendBuf[3] = 0;
	//����Ҫ���͵��ַ���


	
	int n = 0;
	CMySocket mysock;
	while(n<80)
	{
		if((arrStu[n]!=NULL) && (arrStu[n]->nState==1))
		{
			if(mysock.MySend(arrStu[n]->sock,SendBuf,15,1) == FALSE)//ʱ����ϢIDΪ15
			{
				arrStu[n]->nState = 3; //����״̬����Ϊ�쳣
			}
			
		}
		//��ÿλ���ߵ�ѧ�����ͷ�����ʱ�� �� ������ʱ��
		n++;

	}
	return 0;

}
*/