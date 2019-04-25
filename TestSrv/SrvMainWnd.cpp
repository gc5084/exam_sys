#include "StdAfx.h"
#include "SrvMainWnd.h"
#include "SrvMyApp.h"
#include "TimeDlg.h"
#include "StuInfor.h"
#include "CheckDlg.h"
#include "InforSheet.h"
#include "ListAllDlg.h"
#include "SelectTestDlg.h"
#include "MuchTestDlg.h"
#include "MySocket.h"
#include "TalkDlg.h"
#include "LOCKDLG.h"
#include "UnlockDlg.h"
#include "DealMethod.h"


UINT AcceptFunc(LPVOID pParam);
UINT SelectFunc(LPVOID pParam);
UINT TimerFunc(LPVOID pParam);
extern CStuInfor* arrStu[MAXNUM];
extern CList<SOCKET,SOCKET> listSock;
extern CCriticalSection g_list;
extern CList<MemoryData,MemoryData>   listTestFill;										
extern CList<MemoryData,MemoryData>   listTestModify;
extern CList<MemoryData,MemoryData>   listTestDesign;
extern int GStartTime;
extern int GTestTime;
extern HWND GhWnd;
extern SendTestData g_sendTestData[MAXNUM];

//һ��Ϊ��Ϣӳ���
BEGIN_MESSAGE_MAP(CMainWindow,CWnd)
   ON_WM_CREATE()
   ON_WM_PAINT()
   ON_WM_CLOSE()
   ON_WM_MOUSEMOVE()
   ON_WM_RBUTTONDOWN()
   ON_COMMAND(ID_START,OnStart)
   ON_COMMAND(ID_NPERSON,OnPerson)
   ON_COMMAND(ID_SETTIME,OnSetTime)

   ON_COMMAND(ID_CONCHECK,OnConCheck)
   ON_COMMAND(ID_CONSTUINFO,OnConStuInfo)
   ON_COMMAND(ID_CONFORBID,OnConForbid)
   ON_COMMAND(ID_CONRESTATE,OnConRestate)
   ON_COMMAND(ID_CONSEND,OnConSend)

   ON_COMMAND(ID_RESET,OnReset)
   ON_COMMAND(ID_EXITTEST,OnExitTest)
   ON_COMMAND(ID_LOADSTU,OnLoadStu)
   ON_COMMAND(ID_REPAINT,OnRePaint)
   ON_COMMAND(ID_FORBID,OnForbid)
   ON_COMMAND(ID_SENDINFOR,OnSendInfor)
   ON_COMMAND(ID_CHECKALL,OnCheckAll)
   ON_COMMAND(ID_CHECKSAVE,OnCheckSave)
   ON_COMMAND(ID_CHECKSHOW,OnCheckShow)
   ON_COMMAND(ID_HELPABOUT,OnHelpAbout)
   ON_COMMAND(ID_LOCK,OnLock)
   ON_COMMAND(ID_OUTEXCEL,OnOutExcel)
   ON_COMMAND(ID_TOOLDATA,OnToolData)


   ON_MESSAGE(WM_INFORPAINT,OnInforPaint)
END_MESSAGE_MAP()

//һ���Ǻͽ����йصĺ���

/*
CMainWindow�Ĺ��캯��
ע�ᴰ���ಢ��������
�ҽӲ˵�
��ʼ����������
*/
CMainWindow::CMainWindow()
{
	CString strWndClass = AfxRegisterWndClass(
		0,
		NULL,
		(HBRUSH)(COLOR_3DFACE + 1),
		AfxGetApp()->LoadIcon(IDI_ICONMAIN)
        );
	                                           //ע�ᴰ����
	CreateEx(0,strWndClass,_T("C++�ϻ�����ϵͳ��������"),
		WS_OVERLAPPED|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,
		0,0,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,NULL);
	

	CMenu menu;
	menu.LoadMenu(IDR_MAIN_MENU);
	SetMenu(&menu);
	menu.Detach();								//�ҽӲ˵�

	int nHlength = m_cxChar*CELLWIDTH;
												//һ������������
	int nVlength = m_cyChar*CELLHIGH;
												//һ������ߵ�����


												//����Ϊ��ʼ�����80������ֵ
	int n=0;
    for(int i=0;i<8;i++)
	{
		for(int j=0;j<10;j++)
		{
			Arect[n].SetRect(m_cxChar+nHlength*j,	//jΪ������iΪ����
				(m_cyChar*2+LINEW)+nVlength*i,
				m_cxChar+nHlength*(j+1),
				(m_cyChar*2+LINEW)+nVlength*(i+1)
				);
			
			n++;								//n++׼�������һ������
		}
	}
	
	for(int k=0;k<80;k++)
	{
		arrStu[k] = NULL;
	}
											//��ʼ��ѧ����Ϣ����
	PassedRect = -1;
	//��ʼ��ǰһ����ǰ����Ϊ-1 ����
	nFlag  = 0;
	//��־λ��ʼ��Ϊ��

	m_threadAccept = NULL;//�߳��������ʼ��Ϊ��
	m_threadSelect = NULL;

}

/*
��������ʾǰִ��
��Ҫ���������������С
*/
int CMainWindow::OnCreate(LPCREATESTRUCT lpcreatestruct)
{
	if(CWnd::OnCreate(lpcreatestruct) == -1)
		return -1;
	CClientDC dc(this);

	m_fontMain.CreatePointFont(90,_T("����"));
														//�����帳ֵ���飬9����С
	CFont *pOldFont = dc.SelectObject(&m_fontMain);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
														//ѡ�������� ��ȡ����������Ϣ
	m_cxChar = tm.tmAveCharWidth;
	m_cyChar = tm.tmHeight+tm.tmExternalLeading;
	dc.SelectObject(pOldFont);

	//����������������ֵ
	m_rcPaint.SetRect(0,0,
		m_cxChar*(CELLWIDTH*COLCOUNT+2),m_cyChar*(CELLHIGH*ROWCOUNT+4)+LINEW);

	//���ͻ�������������������ֵ
	m_rcClient.SetRect(m_cxChar,m_cyChar*2+LINEW,
		m_cxChar*(CELLWIDTH*COLCOUNT+1),m_cyChar*(CELLHIGH*ROWCOUNT+2)+LINEW);

	//�����ʾ��Ϣ���������ֵ
	m_rcInfor.SetRect(0,0,
		m_cxChar*(CELLWIDTH*COLCOUNT+2),m_cyChar*2);


	CalcWindowRect(&m_rcPaint);//�������������ֵ���ʺ��������ڵĴ�С
														//������������ �� ��Ϣ���������Ϣ
	
	//����������Ĵ�С������m_rcPaint
	SetWindowPos(NULL,0,0,m_rcPaint.Width(),m_rcPaint.Height(),
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//��ȡ���ھ����ȫ�ֱ��� ���������̷߳���Ϣ��������
	GhWnd = GetSafeHwnd();

														//�������ڴ�С������λ��
	

	return 0;

}

/*
�ػ溯��
*/

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	CBrush brush(RGB(255,255,255));
	dc.FillRect(m_rcClient,&brush);
						//�ð�ɫ��ˢ�������
	CFont *pOldFont = dc.SelectObject(&m_fontMain);

	DrawInfor(&dc);
						//�ػ���ʾ��Ϣ
	DrawClient(&dc);
						//�ػ�����Ϣ
	dc.SelectObject(pOldFont);
						//��ԭ����
}

	
/*
������ʾ��Ϣ������
*/
void CMainWindow::DrawInfor(CDC* pDC)
{
	  //��ˢ������� ������ԭ����
	  CBrush brush(RGB(212,208,200));
	  pDC->FillRect(m_rcInfor,&brush);

	  pDC->SetBkMode(TRANSPARENT);
      pDC->SetTextColor(RGB(0,0,0));
	  pDC->MoveTo(0,0);
	  pDC->LineTo(m_cxChar*(17*10+1),0);
											//���صĲ˵���ͻ���֮�仮һ����

	  //������ɫ��ʾ�ַ���
	  pDC->TextOut(m_cxChar,m_cyChar,_T("��ɫ��Ϣ��"));

	  pDC->SetTextColor(RGB(0,0,0));
	  pDC->TextOut(m_cxChar*12,m_cyChar,_T("��ɫ��δ��¼"));

	  pDC->SetTextColor(RGB(255,0,0));
	  pDC->TextOut(m_cxChar*26,m_cyChar,_T("��ɫ������"));

	  pDC->SetTextColor(RGB(0,0,255));
	  pDC->TextOut(m_cxChar*38,m_cyChar,_T("��ɫ���ѽ���"));

	  pDC->SetTextColor(RGB(255,0,255));
	  pDC->TextOut(m_cxChar*52,m_cyChar,_T("��ɫ������ֹ"));

	  pDC->SetTextColor(RGB(0,255,0));
	  pDC->TextOut(m_cxChar*66,m_cyChar,_T("��ɫ���쳣"));

      pDC->SetTextColor(RGB(222,111,0));
      pDC->TextOut(m_cxChar*78,m_cyChar,_T("��ɫ������Ϣ"));

	  //��������ɫ��غ�ɫ
	  pDC->SetTextColor(RGB(0,0,0));

	  //��ʾ����ʱ����Ϣ
	  CString str;
	  if(GTestTime == 0)//��ʱ��Ϊ0 ��������ʱ��Ϊ����
	  {
		  str.Format("��������ʱ�䣺δ����");
	  }
	  else
	  {
		  str.Format("����������ʱ�䣺%d",
			  GTestTime);
	  }
	  pDC->TextOut(m_cxChar*95,m_cyChar,str);//��ʾ����ʱ����Ϣ
/*
	  //��ʾ����״̬
	  if((nFlag&FLAG_START) == FLAG_START)  //����������
	  {
		  if((nFlag&FLAG_OVER) == FLAG_OVER)  //�п��Խ�����־
		  {
			  pDC->TextOut(m_cxChar*145,m_cyChar,"�����ѽ���");
		  }
		  else //�޿��Խ�����־
		  {
			  if((nFlag&FLAG_TIMEGO) == FLAG_TIMEGO) //�п��Լ�ʱ��־
			  {
				  pDC->TextOut(m_cxChar*145,m_cyChar,"�������ڽ���");
			  }
			  else
			  {
				  pDC->TextOut(m_cxChar*145,m_cyChar,"����δ��ʼ��ʱ");
			  }

		  }

	  }
	  else    //���Ի�δ����
	  {
		  pDC->TextOut(m_cxChar*145,m_cyChar,"����δ����");
	  }
*/
}
	  

/*
���Ʊ��������
�Ȼ��Ʊ��
�ٻ�����Ϣ��״̬
*/
void CMainWindow::DrawClient(CDC *pDC)
{
	for(int nH=0;nH<COLCOUNT-1;nH++)
	{
		pDC->MoveTo(m_cxChar*(CELLWIDTH+1)+m_cxChar*CELLWIDTH*nH,
			m_cyChar*2+LINEW);
												//���ߵ����

		pDC->LineTo(m_cxChar*(CELLWIDTH+1)+m_cxChar*CELLWIDTH*nH,
			m_cyChar*(CELLHIGH*ROWCOUNT+2)+LINEW);
												//���ߵĽ�β
	}
	for(int nV=0;nV<ROWCOUNT-1;nV++)
	{
		pDC->MoveTo(m_cxChar,
			m_cyChar*(CELLHIGH+2)+LINEW+m_cyChar*CELLHIGH*nV);
												//���ߵ����
		pDC->LineTo(m_cxChar*(CELLWIDTH*COLCOUNT+1),
			m_cyChar*(CELLHIGH+2)+LINEW+m_cyChar*CELLHIGH*nV);
												//���ߵĽ�β
	}
	
	CString strTemp;
	CString strState;
	for(int n=0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)					//���ѧ����Ϣ���Ƿ�Ϊ��
		{
			if(arrStu[n]->nState == 0)
			{
				strState = "δ��¼";
			    pDC->SetTextColor(RGB(0,0,0));
			}
			else if(arrStu[n]->nState == 1)
			{
				strState = "����";
				pDC->SetTextColor(RGB(255,0,0));
			}
			else if(arrStu[n]->nState == 2)
			{
				strState = "�ѽ���";
				pDC->SetTextColor(RGB(0,0,255));
			}
			else if(arrStu[n]->nState == 4)
			{
				strState = "����ֹ";
				pDC->SetTextColor(RGB(255,0,255));
			}
			else
			{
				strState ="�쳣";
				pDC->SetTextColor(RGB(0,255,0));
			}
												//����ѧ�������� ��Ϣ״̬����ɫ
			
			strTemp.Format("\r\nѧ��:%s\r\n����:%s\r\n״̬:%s",
				arrStu[n]->strNum,arrStu[n]->strName,strState);

			pDC->DrawText(strTemp,-1,Arect[n],
				DT_CENTER|DT_VCENTER);
		}
		else
		{
			pDC->SetTextColor(RGB(222,111,0));
			pDC->DrawText(_T("\r\n����Ϣ\r\n���ݿ�������"),-1,Arect[n],
				DT_CENTER|DT_VCENTER);
		}
	}


}

void CMainWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	CBrush brush(RGB(200,200,200));
	CClientDC dc(this);
	CString strState,strTemp;
	dc.SetBkMode(TRANSPARENT);
	CFont* pOldFont = dc.SelectObject(&m_fontMain);
	
	for(int n=0;n<MAXNUM;n++)
	{
		if(Arect[n].PtInRect(point)==TRUE)
		{
			if(n != PassedRect)
			{
				
				if(PassedRect != -1)
				{
					InvalidateRect(Arect[PassedRect],TRUE);
				}


				dc.FillRect(Arect[n],&brush);
				if(arrStu[n] != NULL)					//���ѧ����Ϣ���Ƿ�Ϊ��
				{
					if(arrStu[n]->nState == 0)
					{
						strState = "δ��¼";
						dc.SetTextColor(RGB(0,0,0));
					}
					else if(arrStu[n]->nState == 1)
					{
						strState = "����";
						dc.SetTextColor(RGB(255,0,0));
					}
					else if(arrStu[n]->nState == 2)
					{
						strState = "�ѽ���";
						dc.SetTextColor(RGB(0,0,255));
					}
					else if(arrStu[n]->nState == 4)
					{
						strState = "����ֹ";
						dc.SetTextColor(RGB(255,0,255));
					}
					else
					{
						strState ="�쳣";
						dc.SetTextColor(RGB(0,255,0));
					}
					//����ѧ�������� ��Ϣ״̬����ɫ
					
					strTemp.Format("\r\nѧ��:%s\r\n����:%s\r\n״̬:%s",
						arrStu[n]->strNum,arrStu[n]->strName,strState);
					
					dc.DrawText(strTemp,-1,Arect[n],
						DT_CENTER|DT_VCENTER);
				}
				else
				{
					dc.SetTextColor(RGB(222,111,0));
					dc.DrawText(_T("\r\n����Ϣ\r\n���ݿ�������"),-1,Arect[n],
						DT_CENTER|DT_VCENTER);
				}
			}
			
			PassedRect = n;
			return;
		}
	}

}


void CMainWindow::OnRButtonDown(UINT nFlags, CPoint point)
{
	CString str;
	CPoint pos = point;

	//���������Ĳ˵�
	CMenu ContextMenu;
	ContextMenu.CreatePopupMenu();
							//�����Ӳ˵����� ��Ϊ�������Ĳ˵�

	//�������λ�� ����ѧ����Ϣ�����Ӧ�˵�
	for(int n =0;n<MAXNUM;n++)//ѭ����������
	{
		if(Arect[n].PtInRect(point)==TRUE)//�Ƿ�����һ����
		{
			nRightDown = n;
							//����ǰ�����������ֵ��nRightDown
			                //��Ϊ����Ӧ�˵�����ʱҪ֪�������ĸ������Ĳ˵�
			if(arrStu[n]!=NULL)
			{
				if(arrStu[n]->nState == 0)//δ��¼ʱ�˵�
				{
					str.Format("�鿴%s��Ϣ",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONSTUINFO,str);
											//��Ӳ˵�ѡ�� MF_STRING,ָ���ڶ���������ID �����Ӳ˵�
											//str �Ӳ˵�Ҫ��ʾ������

					str.Format("��ֹ%s����",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONFORBID,str);

				}
				else if(arrStu[n]->nState == 1)//����ʱ�˵�
				{
					str.Format("�鿴%s��Ϣ",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONSTUINFO,str);

					str.Format("��%s����Ϣ",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONSEND,str);

				//	str.Format("ǿ����ȡ%s�Ծ�",arrStu[n]->strName);
				//	ContextMenu.AppendMenu(MF_STRING,ID_CONFORCEGET,str);

					str.Format("����%s״̬",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONRESTATE,str);
				}
				else if(arrStu[n]->nState == 2)//����ʱ�˵�
				{
					str.Format("�鿴%s��Ϣ",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONSTUINFO,str);

					str.Format("����%s�Ծ�",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONCHECK,str);

					str.Format("����%s״̬",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONRESTATE,str);

				}
				else 
				{
					str.Format("�鿴%s��Ϣ",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONSTUINFO,str);

					str.Format("����%s״̬",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONRESTATE,str);
				}

				//��ʾ�����Ĳ˵�
				ClientToScreen(&pos);//�������Ŀͻ�������ת������Ļ����
				ContextMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,
					pos.x,pos.y,this);//�����λ����ʾ�����Ĳ˵�

				return;//ֱ�ӷ��ز�����ѭ��
			}
		}
	}

}
/*������غ�������*/

/*���˵���Ӧ����*/
//ϵͳ���˵�

/*��������*/
void CMainWindow::OnStart()
{
	if((nFlag&FLAG_START) != FLAG_START)
	{
		//���μ���������Ϣ
		if(LoadTestFirst() == FALSE)
		{
			this->ReStart();
			return;
		}

		//����ɸѡ����
		CSelectTestDlg dlgSelect(this);
	    if(dlgSelect.DoModal() != IDOK)
		{
			this->ReStart();
			return;
		}

		//������������Ի���
		CMuchTestDlg dlgMuch(this);
		if(dlgMuch.DoModal() != IDOK)
		{
			this->ReStart();
			return;
		}

		//����ѧ����Ϣ
		if((nFlag&FLAG_STU) != FLAG_STU)//���û�м��ؿ��������ͼ��� �����Թ�
		{
			AfxMessageBox("δ���ؿ�����������ȷ�����ؿ�������");
			if(OnLoadStu() == FALSE)
			{
				this->ReStart();
				return;
			}
			 
		}

		//���ÿ���ʱ��
		CTimeDlg dlg(this);
		if(dlg.DoModal()==IDOK)
		{
			InvalidateRect(m_rcInfor,TRUE);
		}
		else
		{
			this->ReStart();
			return;
		}

		//�����������
		RandStu();

		//�������п����������ļ�
		CDealMethod dealMethod;
		dealMethod.SendAllStuTest();

        //�����׽���		
		if(InitMySocket()!= TRUE)
		{
			this->ReStart();
			return;
		}
				
		m_threadAccept = AfxBeginThread(AcceptFunc,&m_LisSock);
		//���������߳�
		m_threadSelect = AfxBeginThread(SelectFunc,&m_LisSock);
		//����select�߳�
		
		
		//���´���ʵ����Ϣ���ػ� ��OnPaint��������
		InvalidateRect(m_rcClient,TRUE);

		nFlag = nFlag|FLAG_START;

		//��־Ϊ�Ѿ���ʼ������
	}
	else
	{
		AfxMessageBox("�����Ѿ���ʼ�� ���������һ������ �����ó���");
	}
	

}


/*���Կ�ʼ��ʱ   ���¼ܹ�����Ҫ��
void CMainWindow::OnTimeStart()
{
	if((nFlag&FLAG_START) == FLAG_START)  //���Կ�ʼ���ܽ���
	{
		if((nFlag&FLAG_TIMEGO) != FLAG_TIMEGO)  //����û�п�ʼ��ʱ���ܼ�ʱ
		{
			SetStartTime();//���ÿ�ʼ��ʱ����

			nFlag = nFlag|FLAG_TIMEGO; //�����ӿ��Լ�ʱ�ѿ�ʼ
		}
		else
		{
			MessageBox("�����Ѿ���ʼ��ʱ");
			return;
		}
	}
	else
	{
		MessageBox("���Ի�δ����");
		return;
	}

	//���������߿��Է�������
	CDealMethod SendMethod;
	SendMethod.SendAllStuTest();

	Invalidate(TRUE);  //ˢ�½���
	

}
*/


/*���ÿ���*/
void CMainWindow::OnReset()
{
	if(AfxMessageBox("�⽫��ʧ����δ��������ݣ�ȷ��Ҫ���ÿ�����",MB_YESNO) == IDYES)
	{
		//�������¿�ʼ����
		ReStart();
	}
	else
		return;
}

/*�˳�����ϵͳ*/
void CMainWindow::OnExitTest()
{
	if(AfxMessageBox("�⽫��ʧ����δ��������ݣ�ȷ��Ҫ�˳�������",MB_YESNO) == IDYES)
	{
		SendMessage(WM_CLOSE);
	}
}

/*���ؿ�����Ϣ*/
BOOL CMainWindow::OnLoadStu()
{
	if((nFlag&FLAG_START) != FLAG_START)
	{
		char *czFilter = "Excle�ļ�(*.xls)|*.xls||";
		CString strPathName;
		
		CFileDialog dlg(TRUE,"xls",NULL,
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,czFilter);
		
		if(dlg.DoModal() == IDOK)
		{
			strPathName = dlg.GetPathName();
			//AfxMessageBox(strPathName);
			//����Excleѧ���ɼ�
			
			if(m_DataBase.ConnectExcel(strPathName) ==FALSE)
				return FALSE;
			if(m_DataBase.LoadStudentExcel() == FALSE)
				return FALSE;
			if(m_DataBase.CloseDataBase() ==FALSE)
				return FALSE;
			
		
			
			Invalidate(TRUE);
			
			nFlag |= FLAG_STU;
			
		}
		else
		{
			return FALSE;
		}
		
	}
	else
	{
		AfxMessageBox("�����Ѿ���ʼ�����ڸ�������������");
		return FALSE;
	}
	return TRUE;
	
}

//�������˵�
/*�޸Ŀ�����ʱ��*/
BOOL CMainWindow::OnSetTime()
{
	if((nFlag&FLAG_START) == FLAG_START)//ֻ�п��Կ�ʼ�����޸Ŀ���ʱ��
	{
		CTimeDlg dlg(this);
		if(dlg.DoModal()==IDOK)
		{
			InvalidateRect(m_rcInfor,TRUE);
			return TRUE;
		}
		return FALSE;
	}
	else
	{
		AfxMessageBox("����δ��ʼ��");
		return FALSE;
	}
	
	
}

/*
��ѯ�μӱ��ο��Ե�����
*/
void CMainWindow::OnPerson()
{
	int n; //ѭ������
    int nOnLine = 0; //��¼��������
	int nUnOnLine = 0; //��¼δ��¼����
	int nSended = 0; //��¼�ѽ�������
	int nForbid = 0; //����ֹ��������
	int nUnNormal = 0; //��¼�쳣����

	for(n=0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)
		{
			switch(arrStu[n]->nState)
			{
			case 0:
				nUnOnLine++;
				break;
			case 1:
				nOnLine++;
				break;
			case 2:
				nSended++;
				break;
			case 4:
				nForbid++;
				break;
			default:
				nUnNormal++;
			}
		}
	}
 
	CString str,str1,str2,str3,str4,str5;
	str1.Format(_T("�μӱ��ο��Ե�������Ϊ %d �� \r\n\r\n"),nOnLine+nUnOnLine+nSended+nForbid+nUnNormal);
	str2.Format(_T("�μӱ��ο�����������Ϊ %d �� \r\n\r\n"),nOnLine);
	str3.Format(_T("�μӱ��ο����ѽ�������Ϊ %d �� \r\n\r\n"),nSended);
	str4.Format(_T("�μӱ��ο���״̬�쳣����Ϊ %d �� \r\n\r\n"),nUnNormal);
	str5.Format(_T("�μӱ��ο���δ��¼����Ϊ %d ��"),nUnOnLine);
	str = str1+str2+str3+str4+str5;

	AfxMessageBox(str);
}


/*ˢ��*/
void CMainWindow::OnRePaint()
{
	Invalidate(TRUE);
  
}

/*��ֹ����δ��¼������¼*/
void CMainWindow::OnForbid()
{
	int StuIndex;
	for(StuIndex = 0;StuIndex<MAXNUM;StuIndex++)
	{
		if(arrStu[StuIndex] != NULL)
		{
			if(arrStu[StuIndex]->nState == 0)  //�������δ��¼
			{
				arrStu[StuIndex]->nState = 4;  //״̬��Ϊ����ֹ
			}
		}
	}
	Invalidate(TRUE);
}

/*�����п���������Ϣ*/
void CMainWindow::OnSendInfor()
{
	CTalkDlg talkDlg(this);
	if(talkDlg.DoModal() == IDOK)
	{
		//׼�����͵���Ϣ
		CString strContent = talkDlg.GetContent(); //��ȡ�Ի�������
		char* szContentSend = new char[strContent.GetLength()+ADDBUFFER]; //���Ƶ�char���ַ�����
		strcpy(szContentSend,strContent);

		//���͸��������߿���(ѭ����� )
		CMySocket mysock;
		int stuIndex;
		for(stuIndex=0;stuIndex<MAXNUM;stuIndex++)
		{
			if(arrStu[stuIndex] != NULL)
			{
				if(arrStu[stuIndex]->nState == 1)  //����
				{
					mysock.MySend(arrStu[stuIndex]->sock,szContentSend,16,1); //����
				}
			}
		}

		delete[] szContentSend;
	}
}

//�������˵�
/*��ǰ��������*/
void CMainWindow::OnCheckAll()
{
	CCheckDlg dlg(this);
	dlg.DoModal();
}

/*�������ֽ��*/
void CMainWindow::OnCheckSave()
{
	AfxMessageBox("�������ֽ��");
}

void CMainWindow::OnHelpAbout()
{
 	AfxMessageBox("����");
}

/*����Ӧ�ó������*/
void CMainWindow::OnLock()
{
	CLOCKDLG dlg(this);
	if(dlg.DoModal() == IDOK)
	{
		CUnlockDlg Undlg(this);
		Undlg.DoModal();
	}
}

/*�ɼ�������Excel*/
void CMainWindow::OnOutExcel()
{
	char *czFilter = "Excle�ļ�(*.xls)|*.xls||"; //�ļ��������� ��5������
	CString strPathName;
		
	CFileDialog dlg(FALSE,"xls","Achieve.xls",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,czFilter);

	if(dlg.DoModal()  == IDOK)
	{
		strPathName = dlg.GetPathName(); //��ȡҪ�����ļ�·��

		//copyģ�嵽��ǰĿ¼��
	    char* m_szPath = new char[100];
	    ::GetCurrentDirectory(100,m_szPath); //��ȡ��ǰ�����ļ���·��

		CString strTepPath = m_szPath;
		strTepPath = strTepPath + "\\template.xls"; //ģ��Excel����·��

		::CopyFile(strTepPath,strPathName,FALSE); //����ʽ���� ����FALSE


        //�������ݿ��ཫ������䵽Excel��
		if(m_DataBase.OutExcel(strPathName) == TRUE)
		{
			AfxMessageBox("����ɹ�!");
		}
		else
		{
			AfxMessageBox("����ʧ��!");
		}
	}
}

/*���������ϵͳ*/
void CMainWindow::OnToolData()
{
	CString OpenString;
	OpenString.Format("TestData.exe");

	WinExec(OpenString,SW_SHOW);  //�򿪳��� ������һ������
}

/*��ʾ���ֽ��*/
void CMainWindow::OnCheckShow()
{
	CListAllDlg dlg(this);
	dlg.DoModal();
}









////////////////////////////////////////////////////////////
/////////����Ϊ�����Ĳ˵���Ӧ����
/*
�����ľ���Ӧ����
*/
void CMainWindow::OnConCheck()
{
	arrStu[nRightDown]->CheckAllAnswer();
	MessageBox("�ľ����!");
}

/*��ʾ������Ϣ����ҳ*/
void CMainWindow::OnConStuInfo()
{
	CInforSheet sheet("��ʾ��Ϣ",this);

	sheet.DoModal();
}

/*������״̬����Ϊ��ֹ*/
void CMainWindow::OnConForbid()
{
	if(arrStu[nRightDown]->nState == 0)//��Ȼֻ�п�����δ��¼����²��ܱ���ֹ
	{
		arrStu[nRightDown]->nState = 4;
		Invalidate(TRUE);
	}
	else
	{
		AfxMessageBox("��״̬�������ܱ���ֹ����");
	}
}

/*���ÿ���״̬��Ӧ����*/
void CMainWindow::OnConRestate()
{
	if(arrStu[nRightDown]->nState == 1)
	{
		if(AfxMessageBox("״̬Ϊ���ߣ����ý���ǿ�йرտ����ͻ���",MB_YESNO) == IDYES)
		{
			CMySocket mysock;
			mysock.MySend(arrStu[nRightDown]->sock,NULL,17,1); //17Ϊ������Ϣ
			arrStu[nRightDown]->ReState();
		}
	}
	else if(arrStu[nRightDown]->nState == 2)
	{
		if(AfxMessageBox("״̬Ϊ�ѽ������ý���ʧ�ÿ���δ���������",MB_YESNO) == IDYES)
		{
			arrStu[nRightDown]->ReState();
		}
	}
	else
	{
		arrStu[nRightDown]->ReState();
	}

	Invalidate(TRUE);
}

/*����������Ϣ*/
void CMainWindow::OnConSend()
{
	CTalkDlg dlg(this);
	if(dlg.DoModal() == IDOK) //ȷ��
	{
		CString strContent = dlg.GetContent(); //��ȡ�Ի�������

		char* szContentSend = new char[strContent.GetLength()+ADDBUFFER]; //���Ƶ�char���ַ�����
		strcpy(szContentSend,strContent);

		//������Ϣ
		CMySocket mysock;
		mysock.MySend(arrStu[nRightDown]->sock,szContentSend,16,1);

		delete[] szContentSend;  //�ͷ��ַ���

	}
}




/*
����ѧ����Ϣ����
������Ϻ�ر����ݿ�

BOOL CMainWindow::LoadStuInfor()
{
	if(m_DataBase.LoadStudent() == FALSE)
		return FALSE;
	for(int n =0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)
		{//��ʱ����
			arrStu[n]->nState = 0;
			arrStu[n]->nRandFill[0]  = 0;
			arrStu[n]->nRandFill[1]  = -1;
			arrStu[n]->nRandFill[2]  = -1;

			arrStu[n]->nRandModify[0] = 0;
			arrStu[n]->nRandModify[1] = -1;
			arrStu[n]->nRandModify[2] = -1;

			arrStu[n]->nRandDesign[0] = 0;
			arrStu[n]->nRandDesign[1] = -1;
			arrStu[n]->nRandDesign[2] = -1;
		}
	}
	if(m_DataBase.CloseDataBase() == FALSE)
		return FALSE;
	return TRUE;
}
*/

/*
�������⺯��
*/
BOOL CMainWindow::LoadTestFirst()
{
	if(m_DataBase.LoadTest() == FALSE)
		return FALSE;

	return TRUE;
}

/*
��ʼ���׽��ֺ���
*/
BOOL CMainWindow::InitMySocket()
{
	m_LisSock = socket(AF_INET,SOCK_STREAM,0);
	if(m_LisSock == INVALID_SOCKET)
	{
		CString str;
		str.Format(_T("�����׽���ʧ�ܣ��������Ϊ%d"),WSAGetLastError());
		AfxMessageBox(str);
		return FALSE;
	}

	SOCKADDR_IN addrSock;
	addrSock.sin_port = htons(7500);
	addrSock.sin_family = AF_INET;
	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	int nBind;
	nBind = bind(m_LisSock,(sockaddr*)&addrSock,sizeof(addrSock));
	if(nBind == SOCKET_ERROR)
	{
		CString str;
		str.Format(_T("��ʧ�ܣ��������Ϊ%d"),WSAGetLastError());
		AfxMessageBox(str);
		return FALSE;
	}

	int nListen;
	nListen = listen(m_LisSock,5);
	if(nListen == SOCKET_ERROR )
	{
		CString str;
		str.Format(_T("����ʧ�ܣ��������Ϊ%d"),WSAGetLastError());
		AfxMessageBox(str);
		return FALSE;
	}

	return TRUE;
}

void CMainWindow::RandStu()
{
	
	int nStu,nTest;
	int n;
	//��ʼ��
	for(nStu =0;nStu<MAXNUM;nStu++)
		for(n=0;n<3;n++)
		{
			g_sendTestData[nStu].nRandFill[n] = -1;
			g_sendTestData[nStu].nRandModify[n] = -1;
			g_sendTestData[nStu].nRandDesign[n] = -1;
		}


	//���һ�������
	srand( (unsigned)time( NULL ) ); //ʱ������
	int nRand = rand();
	
	
	for(nStu =0;nStu<MAXNUM;nStu++)
	{
		
		//�����
		if(listTestFill.GetCount() == nMuchTest[0])
			//����������һ��ѡ�����һ���� ���Ǿ���Ϊ����Ա����Ҫ��������ÿ��������
			//���Ǿ���ÿ��������ÿ�������ź����ݶ���Ӧ��� �����������
		{
			for(nTest = 0;nTest<nMuchTest[0];nTest++)
			{
				g_sendTestData[nStu].nRandFill[nTest] = nTest;
				//nRandFill��˳���������
			}
		}
		else //������С��һ��ѡ��������� ��Ҫ�������
		{
			for(nTest = 0;nTest<nMuchTest[0];nTest++)
			{
				g_sendTestData[nStu].nRandFill[nTest] = (nRand+nStu*2+nTest)%listTestFill.GetCount();
				//�õ�����Ϊ �����+��Ӧѧ����������*2+nTest ģ 
			}
		}
		
		//�Ĵ���
		if(listTestModify.GetCount() == nMuchTest[1])
		{
			for(nTest = 0;nTest<nMuchTest[1];nTest++)
			{
				g_sendTestData[nStu].nRandModify[nTest] = nTest;
				//nRandModify��˳���������
			}
		}
		else //������С��һ��ѡ��������� ��Ҫ�������
		{
			for(nTest = 0;nTest<nMuchTest[1];nTest++)
			{
				g_sendTestData[nStu].nRandModify[nTest] = (nRand+nStu*2+nTest)%listTestModify.GetCount();
				//�õ�����Ϊ �����+��Ӧѧ���������� ģ 
			}
		}
		
		//�����
		if(listTestDesign.GetCount() == nMuchTest[2])
		{
			for(nTest = 0;nTest<nMuchTest[2];nTest++)
			{
				g_sendTestData[nStu].nRandDesign[nTest] = nTest;
				//nRandModify��˳���������
			}
		}
		else //������С��һ��ѡ��������� ��Ҫ�������
		{
			for(nTest = 0;nTest<nMuchTest[2];nTest++)
			{
				g_sendTestData[nStu].nRandDesign[nTest] = (nRand+nStu*2+nTest)%listTestDesign.GetCount();
				//�õ�����Ϊ �����+��Ӧѧ���������� ģ 
			}
		}
		
	}
}

//���¿�ʼ����
void CMainWindow::ReStart()
{
	int n;//ѭ������
	
	//��־λ���� 
	nFlag = 0;
	
	//�رռ�ʱ��
	KillTimer(ID_TIME);
	
	//ʱ��������� ��ȫ�֣�
	GStartTime = 0; GTestTime = 0;
	
	//��ֹ���߳�
	if(m_threadAccept != NULL)
	{
		if(::TerminateThread(m_threadAccept->m_hThread,NULL) == 0)//��ֹaccept�߳�
		{
			GetLastError();
		}
	}
	
	if(m_threadSelect != NULL)
	{
		if(::TerminateThread(m_threadSelect->m_hThread,NULL) == 0)//��ֹSelect�߳�
		{
			GetLastError();
		}
	}
	
	
	//�ر����׽���
	closesocket(m_LisSock);
	         //�رտ���ʧ�� ���Խ���ʱ�����׽��ֻ�ر� �����þͻ�ʧ�� ������ν
	
	//�ͷ�arrStu���� ��ѧ����Ϣ
	for(n=0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)
		{
			delete arrStu[n];
			arrStu[n] = NULL;
		}
	}
	
	//ɾ���������������
	listSock.RemoveAll();
	//ɾ���׽����������������
	listTestFill.RemoveAll();
	//ɾ��������������������
	listTestModify.RemoveAll();
	//ɾ���Ĵ����������������
	listTestDesign.RemoveAll();
	//ɾ��������������������
	Invalidate();
}

/* �ܹ����º� ����Ҫ��
void CMainWindow::OnTimer(UINT nTimerID)
{
					
	if(GTestTime == GPassTime)  //������ʱ�������ѹ�ʱ�� 
	{
		//�رռ�ʱ��
		KillTimer(ID_TIME);
		
		//��־Ϊ���Խ���
		nFlag =  nFlag|FLAG_OVER;

		//�ر����׽���
		if(closesocket(m_LisSock) != 0)
		{
			CString str;
			str.Format(_T("�ر��׽���ʧ�� �������%d"),WSAGetLastError());
			AfxMessageBox(str);
			return;
		}

		//����accept�߳�
		if(::TerminateThread(m_threadAccept->m_hThread,NULL) == 0)
		{
			CString str;
			str.Format("%u",GetLastError());
			AfxMessageBox(str);
		}
	}


	InvalidateRect(m_rcInfor,TRUE);//��ʱ�ػ���ʾ��Ϣ�� һ������ʱ����Ϣ �͸�����ʾ��Ϣ��

	//����ʱ��
	AfxBeginThread(TimerFunc,NULL); //��������ʱ����Ϣ�߳�
}
*/

/*��ʼ��ʱ��ʼ*/
void CMainWindow::SetStartTime()
{
	CTime NowTime = CTime::GetCurrentTime();
	int nHour     = NowTime.GetHour();
	int nMinute   = NowTime.GetMinute();

	GStartTime    = nHour*60 + nMinute;
	if(SetTimer(ID_TIME,5000,NULL)==0)
		return;
}



void CMainWindow::OnClose()
{

	CWnd::OnClose();
	
}



//��Ӧsocket�̷߳��صĸ�����Ӧѧ����ͼ��Ϣ
void CMainWindow::OnInforPaint(WPARAM wParam, LPARAM lParam)
{
	//ѭ���ҵ����̴߳�����wParam���׽�����ͬ�Ŀ��� ���������
	//��������ͼ
	for(int n=0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)
		{
			if(arrStu[n]->sock == (SOCKET)wParam)
			{
				InvalidateRect(Arect[n],TRUE);
			}
		}
	}

}



