// TopWindow.cpp : implementation file
//

#include "stdafx.h"
#include "TestClient.h"
#include "TopWindow.h"
#include "TestClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTopWindow
extern int GTimeLong;
extern int GTime;
extern char* GczName;
extern HWND GhWndMain;
extern HWND GhWndTop;
IMPLEMENT_DYNCREATE(CTopWindow, CWnd)

CTopWindow::CTopWindow()
{

	
	CString strWndClass = AfxRegisterWndClass(
		0,
		NULL,
		NULL,
		AfxGetApp()->LoadStandardIcon(IDI_WINLOGO)
        );
	                                           //注册窗口类
	CreateEx(WS_EX_TOPMOST,strWndClass,"时间窗口",
		 WS_POPUP ,
		300,0,0,0,
		NULL,NULL);


	
}

CTopWindow::~CTopWindow()
{
}


BEGIN_MESSAGE_MAP(CTopWindow, CWnd)
	//{{AFX_MSG_MAP(CTopWindow)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_MESSAGE(WM_TIMEUPDATA,OnTimeUp)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTopWindow message handlers

void CTopWindow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBrush brush(RGB(243,192,83));
	CRect rect;
	this->GetClientRect(&rect);
	dc.FillRect(rect,&brush);
	ShowInfor();
	
}

int CTopWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	m_fontMain.CreatePointFont(100,_T("楷书"));
	CFont *pOldFont = dc.SelectObject(&m_fontMain);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
														//选入主字体 获取主字体宽高信息
	m_cxChar = tm.tmAveCharWidth;
	m_cyChar = tm.tmHeight+tm.tmExternalLeading;
	dc.SelectObject(pOldFont);

	m_rectR.SetRect(0,0,48*m_cxChar,4*m_cyChar);
														//设置需要重绘的区域大小 及数据区域
	m_rectAll.SetRect(0,0,62*m_cxChar,4*m_cyChar);
														//设置全部区域大小
	//一个汉字占两个字符位
	CalcWindowRect(&m_rectAll);
	SetWindowPos(NULL,0,0,m_rectAll.Width(),m_rectAll.Height(),
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);



	m_button.Create(_T("交卷"),WS_CHILD|WS_VISIBLE|BS_BITMAP|BS_OWNERDRAW,
		CRect(48*m_cxChar,m_cyChar,62*m_cxChar,4*m_cyChar),this,IDC_SEND);
    m_button.LoadBitmaps(IDB_SENDU,IDB_SENDD);
	m_button.SizeToContent();

	arrTabStop[0] = 14*m_cxChar;
	arrTabStop[1] = 24*m_cxChar;
    arrTabStop[2] = 32*m_cxChar;
									//设置tab停止位置

	GhWndTop = GetSafeHwnd(); //给全局变量本窗口的句柄
 
	return 0;
}

void CTopWindow::ShowInfor()
{
	
    CClientDC dc(this);
	CFont *pOldFont = dc.SelectObject(&m_fontMain);
													//载入定义字体
	dc.SetBkMode(TRANSPARENT);
													//设置为透明模式
	CString str;
													//标题信息字符串
	CString str2;
													//数字信息字符串
	int restTime;
													//剩余时间
	
	if(GTimeLong == 0)
	{
		str.Format("等待服务器传送考试时间信息...");
		dc.TextOut(4*m_cxChar,m_cyChar,str);
	}
	else
	{
			restTime = GTimeLong - GTime;
			str.Format("考生姓名\t考试时长\t已用时\t剩余时间");
			str2.Format("%s\t%d:分钟\t%d:分钟\t%d:分钟",GczName,GTimeLong,GTime,restTime);
			
			dc.TabbedTextOut(4*m_cxChar,m_cyChar,str,str.GetLength(),
				sizeof(arrTabStop),arrTabStop,0);
			
			dc.TabbedTextOut(4*m_cxChar,2*m_cyChar,str2,str2.GetLength(),
				sizeof(arrTabStop),arrTabStop,0);
		
	}

	dc.SelectObject(pOldFont);
    
	
}

void CTopWindow::OnTimeUp(WPARAM wParam, LPARAM lParam)
{
    //显示信息
    Invalidate(TRUE);

	//时间已到向主窗口发送讯息							
	if((GTimeLong - GTime) == 0)
	{
		
		::PostMessage(GhWndMain,WM_TIMEOVER,NULL,NULL);	
		MessageBox("考试时间已到！系统将自动提交试卷\r\n本程序将关闭","提示",MB_SYSTEMMODAL);
	}
}

void CTopWindow::OnSend()
{
	if(AfxMessageBox("确认交卷？",MB_YESNO) == IDNO)
		return;

	ShowInfor();
    
	::SendMessage(GhWndMain,WM_TESTSEND,NULL,NULL);
}
