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

//一下为消息映射表
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

//一下是和界面有关的函数

/*
CMainWindow的构造函数
注册窗口类并创建窗口
挂接菜单
初始化方格区域
*/
CMainWindow::CMainWindow()
{
	CString strWndClass = AfxRegisterWndClass(
		0,
		NULL,
		(HBRUSH)(COLOR_3DFACE + 1),
		AfxGetApp()->LoadIcon(IDI_ICONMAIN)
        );
	                                           //注册窗口类
	CreateEx(0,strWndClass,_T("C++上机考试系统—服务器"),
		WS_OVERLAPPED|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,
		0,0,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,NULL);
	

	CMenu menu;
	menu.LoadMenu(IDR_MAIN_MENU);
	SetMenu(&menu);
	menu.Detach();								//挂接菜单

	int nHlength = m_cxChar*CELLWIDTH;
												//一个方格宽的像素
	int nVlength = m_cyChar*CELLHIGH;
												//一个方格高的像素


												//以下为初始化填充80个矩形值
	int n=0;
    for(int i=0;i<8;i++)
	{
		for(int j=0;j<10;j++)
		{
			Arect[n].SetRect(m_cxChar+nHlength*j,	//j为列数，i为行数
				(m_cyChar*2+LINEW)+nVlength*i,
				m_cxChar+nHlength*(j+1),
				(m_cyChar*2+LINEW)+nVlength*(i+1)
				);
			
			n++;								//n++准备填充下一个区域
		}
	}
	
	for(int k=0;k<80;k++)
	{
		arrStu[k] = NULL;
	}
											//初始化学生信息数组
	PassedRect = -1;
	//初始化前一个当前区域为-1 即无
	nFlag  = 0;
	//标志位初始化为零

	m_threadAccept = NULL;//线程类变量初始化为零
	m_threadSelect = NULL;

}

/*
主窗口显示前执行
主要是设置了主窗体大小
*/
int CMainWindow::OnCreate(LPCREATESTRUCT lpcreatestruct)
{
	if(CWnd::OnCreate(lpcreatestruct) == -1)
		return -1;
	CClientDC dc(this);

	m_fontMain.CreatePointFont(90,_T("楷书"));
														//主字体赋值楷书，9磅大小
	CFont *pOldFont = dc.SelectObject(&m_fontMain);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
														//选入主字体 获取主字体宽高信息
	m_cxChar = tm.tmAveCharWidth;
	m_cyChar = tm.tmHeight+tm.tmExternalLeading;
	dc.SelectObject(pOldFont);

	//填充整个区域变量的值
	m_rcPaint.SetRect(0,0,
		m_cxChar*(CELLWIDTH*COLCOUNT+2),m_cyChar*(CELLHIGH*ROWCOUNT+4)+LINEW);

	//填充客户（表格区域）区域变量的值
	m_rcClient.SetRect(m_cxChar,m_cyChar*2+LINEW,
		m_cxChar*(CELLWIDTH*COLCOUNT+1),m_cyChar*(CELLHIGH*ROWCOUNT+2)+LINEW);

	//填充提示消息区域变量的值
	m_rcInfor.SetRect(0,0,
		m_cxChar*(CELLWIDTH*COLCOUNT+2),m_cyChar*2);


	CalcWindowRect(&m_rcPaint);//调整整个区域的值以适合整个窗口的大小
														//设置整个区域 和 信息区域矩形信息
	
	//设置主窗体的大小，根据m_rcPaint
	SetWindowPos(NULL,0,0,m_rcPaint.Width(),m_rcPaint.Height(),
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//获取窗口句柄给全局变量 用于其他线程发消息给主窗口
	GhWnd = GetSafeHwnd();

														//调整窗口大小到合适位置
	

	return 0;

}

/*
重绘函数
*/

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);
	CBrush brush(RGB(255,255,255));
	dc.FillRect(m_rcClient,&brush);
						//用白色画刷填充表格区
	CFont *pOldFont = dc.SelectObject(&m_fontMain);

	DrawInfor(&dc);
						//重绘提示信息
	DrawClient(&dc);
						//重绘表格信息
	dc.SelectObject(pOldFont);
						//还原字体
}

	
/*
绘制提示信息区域函数
*/
void CMainWindow::DrawInfor(CDC* pDC)
{
	  //画刷填充区域 即擦除原内容
	  CBrush brush(RGB(212,208,200));
	  pDC->FillRect(m_rcInfor,&brush);

	  pDC->SetBkMode(TRANSPARENT);
      pDC->SetTextColor(RGB(0,0,0));
	  pDC->MoveTo(0,0);
	  pDC->LineTo(m_cxChar*(17*10+1),0);
											//加载的菜单与客户区之间划一条线

	  //画出颜色提示字符串
	  pDC->TextOut(m_cxChar,m_cyChar,_T("颜色信息—"));

	  pDC->SetTextColor(RGB(0,0,0));
	  pDC->TextOut(m_cxChar*12,m_cyChar,_T("黑色：未登录"));

	  pDC->SetTextColor(RGB(255,0,0));
	  pDC->TextOut(m_cxChar*26,m_cyChar,_T("红色：在线"));

	  pDC->SetTextColor(RGB(0,0,255));
	  pDC->TextOut(m_cxChar*38,m_cyChar,_T("蓝色：已交卷"));

	  pDC->SetTextColor(RGB(255,0,255));
	  pDC->TextOut(m_cxChar*52,m_cyChar,_T("紫色：被禁止"));

	  pDC->SetTextColor(RGB(0,255,0));
	  pDC->TextOut(m_cxChar*66,m_cyChar,_T("绿色：异常"));

      pDC->SetTextColor(RGB(222,111,0));
      pDC->TextOut(m_cxChar*78,m_cyChar,_T("黄色：无信息"));

	  //将字体颜色设回黑色
	  pDC->SetTextColor(RGB(0,0,0));

	  //显示考试时间信息
	  CString str;
	  if(GTestTime == 0)//总时长为0 表明考试时间为设置
	  {
		  str.Format("本场考试时间：未设置");
	  }
	  else
	  {
		  str.Format("本场考试总时间：%d",
			  GTestTime);
	  }
	  pDC->TextOut(m_cxChar*95,m_cyChar,str);//显示考试时间信息
/*
	  //显示考试状态
	  if((nFlag&FLAG_START) == FLAG_START)  //考试已启动
	  {
		  if((nFlag&FLAG_OVER) == FLAG_OVER)  //有考试结束标志
		  {
			  pDC->TextOut(m_cxChar*145,m_cyChar,"考试已结束");
		  }
		  else //无考试结束标志
		  {
			  if((nFlag&FLAG_TIMEGO) == FLAG_TIMEGO) //有考试计时标志
			  {
				  pDC->TextOut(m_cxChar*145,m_cyChar,"考试正在进行");
			  }
			  else
			  {
				  pDC->TextOut(m_cxChar*145,m_cyChar,"考试未开始计时");
			  }

		  }

	  }
	  else    //考试还未启动
	  {
		  pDC->TextOut(m_cxChar*145,m_cyChar,"考试未启动");
	  }
*/
}
	  

/*
绘制表格区函数
先绘制表格
再绘制信息和状态
*/
void CMainWindow::DrawClient(CDC *pDC)
{
	for(int nH=0;nH<COLCOUNT-1;nH++)
	{
		pDC->MoveTo(m_cxChar*(CELLWIDTH+1)+m_cxChar*CELLWIDTH*nH,
			m_cyChar*2+LINEW);
												//竖线的起点

		pDC->LineTo(m_cxChar*(CELLWIDTH+1)+m_cxChar*CELLWIDTH*nH,
			m_cyChar*(CELLHIGH*ROWCOUNT+2)+LINEW);
												//竖线的结尾
	}
	for(int nV=0;nV<ROWCOUNT-1;nV++)
	{
		pDC->MoveTo(m_cxChar,
			m_cyChar*(CELLHIGH+2)+LINEW+m_cyChar*CELLHIGH*nV);
												//横线的起点
		pDC->LineTo(m_cxChar*(CELLWIDTH*COLCOUNT+1),
			m_cyChar*(CELLHIGH+2)+LINEW+m_cyChar*CELLHIGH*nV);
												//横线的结尾
	}
	
	CString strTemp;
	CString strState;
	for(int n=0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)					//检测学生信息类是否为空
		{
			if(arrStu[n]->nState == 0)
			{
				strState = "未登录";
			    pDC->SetTextColor(RGB(0,0,0));
			}
			else if(arrStu[n]->nState == 1)
			{
				strState = "在线";
				pDC->SetTextColor(RGB(255,0,0));
			}
			else if(arrStu[n]->nState == 2)
			{
				strState = "已交卷";
				pDC->SetTextColor(RGB(0,0,255));
			}
			else if(arrStu[n]->nState == 4)
			{
				strState = "被禁止";
				pDC->SetTextColor(RGB(255,0,255));
			}
			else
			{
				strState ="异常";
				pDC->SetTextColor(RGB(0,255,0));
			}
												//根据学生类设置 信息状态及颜色
			
			strTemp.Format("\r\n学号:%s\r\n姓名:%s\r\n状态:%s",
				arrStu[n]->strNum,arrStu[n]->strName,strState);

			pDC->DrawText(strTemp,-1,Arect[n],
				DT_CENTER|DT_VCENTER);
		}
		else
		{
			pDC->SetTextColor(RGB(222,111,0));
			pDC->DrawText(_T("\r\n无信息\r\n数据库无资料"),-1,Arect[n],
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
				if(arrStu[n] != NULL)					//检测学生信息类是否为空
				{
					if(arrStu[n]->nState == 0)
					{
						strState = "未登录";
						dc.SetTextColor(RGB(0,0,0));
					}
					else if(arrStu[n]->nState == 1)
					{
						strState = "在线";
						dc.SetTextColor(RGB(255,0,0));
					}
					else if(arrStu[n]->nState == 2)
					{
						strState = "已交卷";
						dc.SetTextColor(RGB(0,0,255));
					}
					else if(arrStu[n]->nState == 4)
					{
						strState = "被禁止";
						dc.SetTextColor(RGB(255,0,255));
					}
					else
					{
						strState ="异常";
						dc.SetTextColor(RGB(0,255,0));
					}
					//根据学生类设置 信息状态及颜色
					
					strTemp.Format("\r\n学号:%s\r\n姓名:%s\r\n状态:%s",
						arrStu[n]->strNum,arrStu[n]->strName,strState);
					
					dc.DrawText(strTemp,-1,Arect[n],
						DT_CENTER|DT_VCENTER);
				}
				else
				{
					dc.SetTextColor(RGB(222,111,0));
					dc.DrawText(_T("\r\n无信息\r\n数据库无资料"),-1,Arect[n],
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

	//创建上下文菜单
	CMenu ContextMenu;
	ContextMenu.CreatePopupMenu();
							//创建子菜单类型 因为是上下文菜单

	//检索点击位置 根据学生信息添加相应菜单
	for(int n =0;n<MAXNUM;n++)//循环所有区域
	{
		if(Arect[n].PtInRect(point)==TRUE)//是否在这一区域
		{
			nRightDown = n;
							//将当前区域的索引赋值给nRightDown
			                //因为在相应菜单函数时要知道是在哪个弹出的菜单
			if(arrStu[n]!=NULL)
			{
				if(arrStu[n]->nState == 0)//未登录时菜单
				{
					str.Format("查看%s信息",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONSTUINFO,str);
											//添加菜单选项 MF_STRING,指明第二个参数是ID 不是子菜单
											//str 子菜单要显示的内容

					str.Format("禁止%s考试",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONFORBID,str);

				}
				else if(arrStu[n]->nState == 1)//在线时菜单
				{
					str.Format("查看%s信息",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONSTUINFO,str);

					str.Format("向%s送消息",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONSEND,str);

				//	str.Format("强行收取%s试卷",arrStu[n]->strName);
				//	ContextMenu.AppendMenu(MF_STRING,ID_CONFORCEGET,str);

					str.Format("重置%s状态",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONRESTATE,str);
				}
				else if(arrStu[n]->nState == 2)//交卷时菜单
				{
					str.Format("查看%s信息",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONSTUINFO,str);

					str.Format("批阅%s试卷",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONCHECK,str);

					str.Format("重置%s状态",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONRESTATE,str);

				}
				else 
				{
					str.Format("查看%s信息",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONSTUINFO,str);

					str.Format("重置%s状态",arrStu[n]->strName);
					ContextMenu.AppendMenu(MF_STRING,ID_CONRESTATE,str);
				}

				//显示上下文菜单
				ClientToScreen(&pos);//将传来的客户区坐标转换成屏幕坐标
				ContextMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,
					pos.x,pos.y,this);//在鼠标位置显示上下文菜单

				return;//直接返回不用再循环
			}
		}
	}

}
/*界面相关函数结束*/

/*主菜单相应函数*/
//系统主菜单

/*启动考试*/
void CMainWindow::OnStart()
{
	if((nFlag&FLAG_START) != FLAG_START)
	{
		//初次加载试题信息
		if(LoadTestFirst() == FALSE)
		{
			this->ReStart();
			return;
		}

		//进入筛选试题
		CSelectTestDlg dlgSelect(this);
	    if(dlgSelect.DoModal() != IDOK)
		{
			this->ReStart();
			return;
		}

		//输入试题个数对话框
		CMuchTestDlg dlgMuch(this);
		if(dlgMuch.DoModal() != IDOK)
		{
			this->ReStart();
			return;
		}

		//载入学生信息
		if((nFlag&FLAG_STU) != FLAG_STU)//如果没有加载考生名单就加载 否则略过
		{
			AfxMessageBox("未加载考生名单，按确定加载考生名单");
			if(OnLoadStu() == FALSE)
			{
				this->ReStart();
				return;
			}
			 
		}

		//设置考试时间
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

		//考生随机试题
		RandStu();

		//产生所有考生的试题文件
		CDealMethod dealMethod;
		dealMethod.SendAllStuTest();

        //创建套接字		
		if(InitMySocket()!= TRUE)
		{
			this->ReStart();
			return;
		}
				
		m_threadAccept = AfxBeginThread(AcceptFunc,&m_LisSock);
		//开启监听线程
		m_threadSelect = AfxBeginThread(SelectFunc,&m_LisSock);
		//开启select线程
		
		
		//以下代码实现信息区重绘 与OnPaint函数类似
		InvalidateRect(m_rcClient,TRUE);

		nFlag = nFlag|FLAG_START;

		//标志为已经开始考试了
	}
	else
	{
		AfxMessageBox("考试已经开始过 若想进行下一场考试 请重置程序");
	}
	

}


/*考试开始计时   更新架构后不需要了
void CMainWindow::OnTimeStart()
{
	if((nFlag&FLAG_START) == FLAG_START)  //考试开始才能进入
	{
		if((nFlag&FLAG_TIMEGO) != FLAG_TIMEGO)  //考试没有开始计时才能计时
		{
			SetStartTime();//调用开始计时函数

			nFlag = nFlag|FLAG_TIMEGO; //标记添加考试计时已开始
		}
		else
		{
			MessageBox("考试已经开始计时");
			return;
		}
	}
	else
	{
		MessageBox("考试还未启动");
		return;
	}

	//给所有在线考试发送试题
	CDealMethod SendMethod;
	SendMethod.SendAllStuTest();

	Invalidate(TRUE);  //刷新界面
	

}
*/


/*重置考试*/
void CMainWindow::OnReset()
{
	if(AfxMessageBox("这将丢失所有未保存的数据，确定要重置考试吗？",MB_YESNO) == IDYES)
	{
		//调用重新开始函数
		ReStart();
	}
	else
		return;
}

/*退出考试系统*/
void CMainWindow::OnExitTest()
{
	if(AfxMessageBox("这将丢失所有未保存的数据，确定要退出考试吗？",MB_YESNO) == IDYES)
	{
		SendMessage(WM_CLOSE);
	}
}

/*加载考生信息*/
BOOL CMainWindow::OnLoadStu()
{
	if((nFlag&FLAG_START) != FLAG_START)
	{
		char *czFilter = "Excle文件(*.xls)|*.xls||";
		CString strPathName;
		
		CFileDialog dlg(TRUE,"xls",NULL,
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,czFilter);
		
		if(dlg.DoModal() == IDOK)
		{
			strPathName = dlg.GetPathName();
			//AfxMessageBox(strPathName);
			//载入Excle学生成绩
			
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
		AfxMessageBox("考试已经开始不能在更换考生名单！");
		return FALSE;
	}
	return TRUE;
	
}

//操作主菜单
/*修改考试总时长*/
BOOL CMainWindow::OnSetTime()
{
	if((nFlag&FLAG_START) == FLAG_START)//只有考试开始才能修改考试时间
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
		AfxMessageBox("考试未开始！");
		return FALSE;
	}
	
	
}

/*
查询参加本次考试的人数
*/
void CMainWindow::OnPerson()
{
	int n; //循环变量
    int nOnLine = 0; //记录在线人数
	int nUnOnLine = 0; //记录未登录人数
	int nSended = 0; //记录已交卷人数
	int nForbid = 0; //被禁止考试人数
	int nUnNormal = 0; //记录异常人数

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
	str1.Format(_T("参加本次考试的总人数为 %d 人 \r\n\r\n"),nOnLine+nUnOnLine+nSended+nForbid+nUnNormal);
	str2.Format(_T("参加本次考试在线人数为 %d 人 \r\n\r\n"),nOnLine);
	str3.Format(_T("参加本次考试已交卷人数为 %d 人 \r\n\r\n"),nSended);
	str4.Format(_T("参加本次考试状态异常人数为 %d 人 \r\n\r\n"),nUnNormal);
	str5.Format(_T("参加本次考试未登录人数为 %d 人"),nUnOnLine);
	str = str1+str2+str3+str4+str5;

	AfxMessageBox(str);
}


/*刷新*/
void CMainWindow::OnRePaint()
{
	Invalidate(TRUE);
  
}

/*禁止所有未登录考生登录*/
void CMainWindow::OnForbid()
{
	int StuIndex;
	for(StuIndex = 0;StuIndex<MAXNUM;StuIndex++)
	{
		if(arrStu[StuIndex] != NULL)
		{
			if(arrStu[StuIndex]->nState == 0)  //如果考生未登录
			{
				arrStu[StuIndex]->nState = 4;  //状态设为被禁止
			}
		}
	}
	Invalidate(TRUE);
}

/*向所有考生发送信息*/
void CMainWindow::OnSendInfor()
{
	CTalkDlg talkDlg(this);
	if(talkDlg.DoModal() == IDOK)
	{
		//准备发送的信息
		CString strContent = talkDlg.GetContent(); //获取对话框内容
		char* szContentSend = new char[strContent.GetLength()+ADDBUFFER]; //复制到char型字符串中
		strcpy(szContentSend,strContent);

		//发送给所有在线考生(循环完成 )
		CMySocket mysock;
		int stuIndex;
		for(stuIndex=0;stuIndex<MAXNUM;stuIndex++)
		{
			if(arrStu[stuIndex] != NULL)
			{
				if(arrStu[stuIndex]->nState == 1)  //在线
				{
					mysock.MySend(arrStu[stuIndex]->sock,szContentSend,16,1); //发送
				}
			}
		}

		delete[] szContentSend;
	}
}

//评分主菜单
/*当前批次评分*/
void CMainWindow::OnCheckAll()
{
	CCheckDlg dlg(this);
	dlg.DoModal();
}

/*保存评分结果*/
void CMainWindow::OnCheckSave()
{
	AfxMessageBox("保存评分结果");
}

void CMainWindow::OnHelpAbout()
{
 	AfxMessageBox("关于");
}

/*锁定应用程序界面*/
void CMainWindow::OnLock()
{
	CLOCKDLG dlg(this);
	if(dlg.DoModal() == IDOK)
	{
		CUnlockDlg Undlg(this);
		Undlg.DoModal();
	}
}

/*成绩导出到Excel*/
void CMainWindow::OnOutExcel()
{
	char *czFilter = "Excle文件(*.xls)|*.xls||"; //文件保存类型 第5个参数
	CString strPathName;
		
	CFileDialog dlg(FALSE,"xls","Achieve.xls",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,czFilter);

	if(dlg.DoModal()  == IDOK)
	{
		strPathName = dlg.GetPathName(); //获取要保存文件路径

		//copy模板到当前目录下
	    char* m_szPath = new char[100];
	    ::GetCurrentDirectory(100,m_szPath); //获取当前程序文件夹路径

		CString strTepPath = m_szPath;
		strTepPath = strTepPath + "\\template.xls"; //模板Excel绝对路径

		::CopyFile(strTepPath,strPathName,FALSE); //覆盖式复制 参数FALSE


        //调用数据库类将数据填充到Excel里
		if(m_DataBase.OutExcel(strPathName) == TRUE)
		{
			AfxMessageBox("保存成功!");
		}
		else
		{
			AfxMessageBox("保存失败!");
		}
	}
}

/*打开试题管理系统*/
void CMainWindow::OnToolData()
{
	CString OpenString;
	OpenString.Format("TestData.exe");

	WinExec(OpenString,SW_SHOW);  //打开程序 启动另一个进程
}

/*显示评分结果*/
void CMainWindow::OnCheckShow()
{
	CListAllDlg dlg(this);
	dlg.DoModal();
}









////////////////////////////////////////////////////////////
/////////以下为上下文菜单相应函数
/*
个体阅卷相应函数
*/
void CMainWindow::OnConCheck()
{
	arrStu[nRightDown]->CheckAllAnswer();
	MessageBox("阅卷完成!");
}

/*显示考生信息属性页*/
void CMainWindow::OnConStuInfo()
{
	CInforSheet sheet("显示信息",this);

	sheet.DoModal();
}

/*将考生状态设置为禁止*/
void CMainWindow::OnConForbid()
{
	if(arrStu[nRightDown]->nState == 0)//显然只有考生在未登录情况下才能被禁止
	{
		arrStu[nRightDown]->nState = 4;
		Invalidate(TRUE);
	}
	else
	{
		AfxMessageBox("该状态考生不能被禁止考试");
	}
}

/*重置考生状态相应函数*/
void CMainWindow::OnConRestate()
{
	if(arrStu[nRightDown]->nState == 1)
	{
		if(AfxMessageBox("状态为在线，重置将会强行关闭考生客户端",MB_YESNO) == IDYES)
		{
			CMySocket mysock;
			mysock.MySend(arrStu[nRightDown]->sock,NULL,17,1); //17为重置消息
			arrStu[nRightDown]->ReState();
		}
	}
	else if(arrStu[nRightDown]->nState == 2)
	{
		if(AfxMessageBox("状态为已交卷，重置将丢失该考生未保存的数据",MB_YESNO) == IDYES)
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

/*向考生发送消息*/
void CMainWindow::OnConSend()
{
	CTalkDlg dlg(this);
	if(dlg.DoModal() == IDOK) //确定
	{
		CString strContent = dlg.GetContent(); //获取对话框内容

		char* szContentSend = new char[strContent.GetLength()+ADDBUFFER]; //复制到char型字符串中
		strcpy(szContentSend,strContent);

		//发送信息
		CMySocket mysock;
		mysock.MySend(arrStu[nRightDown]->sock,szContentSend,16,1);

		delete[] szContentSend;  //释放字符串

	}
}




/*
加载学生信息函数
加载完毕后关闭数据库

BOOL CMainWindow::LoadStuInfor()
{
	if(m_DataBase.LoadStudent() == FALSE)
		return FALSE;
	for(int n =0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)
		{//临时代码
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
加载试题函数
*/
BOOL CMainWindow::LoadTestFirst()
{
	if(m_DataBase.LoadTest() == FALSE)
		return FALSE;

	return TRUE;
}

/*
初始化套接字函数
*/
BOOL CMainWindow::InitMySocket()
{
	m_LisSock = socket(AF_INET,SOCK_STREAM,0);
	if(m_LisSock == INVALID_SOCKET)
	{
		CString str;
		str.Format(_T("创建套接字失败！错误代码为%d"),WSAGetLastError());
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
		str.Format(_T("绑定失败，错误代码为%d"),WSAGetLastError());
		AfxMessageBox(str);
		return FALSE;
	}

	int nListen;
	nListen = listen(m_LisSock,5);
	if(nListen == SOCKET_ERROR )
	{
		CString str;
		str.Format(_T("监听失败，错误代码为%d"),WSAGetLastError());
		AfxMessageBox(str);
		return FALSE;
	}

	return TRUE;
}

void CMainWindow::RandStu()
{
	
	int nStu,nTest;
	int n;
	//初始化
	for(nStu =0;nStu<MAXNUM;nStu++)
		for(n=0;n<3;n++)
		{
			g_sendTestData[nStu].nRandFill[n] = -1;
			g_sendTestData[nStu].nRandModify[n] = -1;
			g_sendTestData[nStu].nRandDesign[n] = -1;
		}


	//获得一个随机数
	srand( (unsigned)time( NULL ) ); //时间撒种
	int nRand = rand();
	
	
	for(nStu =0;nStu<MAXNUM;nStu++)
	{
		
		//填空题
		if(listTestFill.GetCount() == nMuchTest[0])
			//如果出的题和一共选入的题一样多 我们就认为管理员不需要随机出题给每个考生，
			//我们就让每个考生的每个试题编号和内容都对应相等 即不用随机数
		{
			for(nTest = 0;nTest<nMuchTest[0];nTest++)
			{
				g_sendTestData[nStu].nRandFill[nTest] = nTest;
				//nRandFill按顺序等于索引
			}
		}
		else //出题数小于一共选入的试题数 则要随机出题
		{
			for(nTest = 0;nTest<nMuchTest[0];nTest++)
			{
				g_sendTestData[nStu].nRandFill[nTest] = (nRand+nStu*2+nTest)%listTestFill.GetCount();
				//得到数据为 随机数+对应学生数组索引*2+nTest 模 
			}
		}
		
		//改错题
		if(listTestModify.GetCount() == nMuchTest[1])
		{
			for(nTest = 0;nTest<nMuchTest[1];nTest++)
			{
				g_sendTestData[nStu].nRandModify[nTest] = nTest;
				//nRandModify按顺序等于索引
			}
		}
		else //出题数小于一共选入的试题数 则要随机出题
		{
			for(nTest = 0;nTest<nMuchTest[1];nTest++)
			{
				g_sendTestData[nStu].nRandModify[nTest] = (nRand+nStu*2+nTest)%listTestModify.GetCount();
				//得到数据为 随机数+对应学生数组索引 模 
			}
		}
		
		//设计题
		if(listTestDesign.GetCount() == nMuchTest[2])
		{
			for(nTest = 0;nTest<nMuchTest[2];nTest++)
			{
				g_sendTestData[nStu].nRandDesign[nTest] = nTest;
				//nRandModify按顺序等于索引
			}
		}
		else //出题数小于一共选入的试题数 则要随机出题
		{
			for(nTest = 0;nTest<nMuchTest[2];nTest++)
			{
				g_sendTestData[nStu].nRandDesign[nTest] = (nRand+nStu*2+nTest)%listTestDesign.GetCount();
				//得到数据为 随机数+对应学生数组索引 模 
			}
		}
		
	}
}

//重新开始函数
void CMainWindow::ReStart()
{
	int n;//循环变量
	
	//标志位置零 
	nFlag = 0;
	
	//关闭计时器
	KillTimer(ID_TIME);
	
	//时间变量清零 （全局）
	GStartTime = 0; GTestTime = 0;
	
	//终止个线程
	if(m_threadAccept != NULL)
	{
		if(::TerminateThread(m_threadAccept->m_hThread,NULL) == 0)//终止accept线程
		{
			GetLastError();
		}
	}
	
	if(m_threadSelect != NULL)
	{
		if(::TerminateThread(m_threadSelect->m_hThread,NULL) == 0)//终止Select线程
		{
			GetLastError();
		}
	}
	
	
	//关闭主套接字
	closesocket(m_LisSock);
	         //关闭可能失败 考试结束时监听套接字会关闭 再重置就会失败 但无所谓
	
	//释放arrStu数据 即学生信息
	for(n=0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)
		{
			delete arrStu[n];
			arrStu[n] = NULL;
		}
	}
	
	//删除试题链表的数据
	listSock.RemoveAll();
	//删除套接字链表的所有数据
	listTestFill.RemoveAll();
	//删除填空题链表的所有数据
	listTestModify.RemoveAll();
	//删除改错题链表的所有数据
	listTestDesign.RemoveAll();
	//删除设计题链表的所有数据
	Invalidate();
}

/* 架构更新后 不需要了
void CMainWindow::OnTimer(UINT nTimerID)
{
					
	if(GTestTime == GPassTime)  //考试总时长等于已过时间 
	{
		//关闭计时器
		KillTimer(ID_TIME);
		
		//标志为考试结束
		nFlag =  nFlag|FLAG_OVER;

		//关闭主套接字
		if(closesocket(m_LisSock) != 0)
		{
			CString str;
			str.Format(_T("关闭套接字失败 错误代码%d"),WSAGetLastError());
			AfxMessageBox(str);
			return;
		}

		//结束accept线程
		if(::TerminateThread(m_threadAccept->m_hThread,NULL) == 0)
		{
			CString str;
			str.Format("%u",GetLastError());
			AfxMessageBox(str);
		}
	}


	InvalidateRect(m_rcInfor,TRUE);//定时重绘提示信息区 一旦发送时间消息 就更新提示信息区

	//发送时间
	AfxBeginThread(TimerFunc,NULL); //开启发送时间消息线程
}
*/

/*开始计时开始*/
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



//相应socket线程发回的更新相应学生视图消息
void CMainWindow::OnInforPaint(WPARAM wParam, LPARAM lParam)
{
	//循环找到与线程传来的wParam的套接字相同的考生 查出其索引
	//更新其视图
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



