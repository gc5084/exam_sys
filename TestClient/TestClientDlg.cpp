// TestClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestClient.h"
#include "TestClientDlg.h"
#include "UIThread.h"
#include "EntryDlg.h"
#include "Mysocket.h"
#include "TopWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
extern CTestClientApp theApp;
extern HWND GhWndMain;
extern SOCKET Gsock;
extern CCriticalSection GLockSock;
extern int GTime;
extern int GTimeLong;
extern HWND GhWndTop;
UINT RecvFunc(LPVOID pParam);

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// CTestClientDlg dialog
BEGIN_MESSAGE_MAP(CTestClientDlg, CDialog)
	//{{AFX_MSG_MAP(CTestClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_LOOK_FILL_1, OnLookFill1)
	ON_BN_CLICKED(IDC_LOOK_FILL_2, OnLookFill2)
	ON_BN_CLICKED(IDC_LOOK_FILL_3, OnLookFill3)
	ON_BN_CLICKED(IDC_LOOK_MODIFY_1, OnLookModify1)
	ON_BN_CLICKED(IDC_LOOK_MODIFY_2, OnLookModify2)
	ON_BN_CLICKED(IDC_LOOK_MODIFY_3, OnLookModify3)
	ON_BN_CLICKED(IDC_LOOK_DESIGN_1, OnLookDesign1)
	ON_BN_CLICKED(IDC_LOOK_DESIGN_2, OnLookDesign2)
	ON_BN_CLICKED(IDC_LOOK_DESIGN_3, OnLookDesign3)
	ON_BN_CLICKED(IDC_ANSWER_FILL_1, OnAnswerFill1)
	ON_BN_CLICKED(IDC_ANSWER_FILL_2, OnAnswerFill2)
	ON_BN_CLICKED(IDC_ANSWER_FILL_3, OnAnswerFill3)
	ON_BN_CLICKED(IDC_ANSWER_MODIFY_1, OnAnswerModify1)
	ON_BN_CLICKED(IDC_ANSWER_MODIFY_2, OnAnswerModify2)
	ON_BN_CLICKED(IDC_ANSWER_MODIFY_3, OnAnswerModify3)
	ON_BN_CLICKED(IDC_ANSWER_DESIGN_1, OnAnswerDesign1)
	ON_BN_CLICKED(IDC_ANSWER_DESIGN_2, OnAnswerDesign2)
	ON_BN_CLICKED(IDC_ANSWER_DESIGN_3, OnAnswerDesign3)

	ON_MESSAGE(WM_TIMEOVER,OnTimeOver)
	ON_MESSAGE(WM_TESTSEND,OnTestSend)
	ON_MESSAGE(WM_MYCLOSE,OnMyClose)
	ON_MESSAGE(WM_RESTART,OnReStart)
	ON_MESSAGE(WM_MESSAGE,OnMessage)
	ON_MESSAGE(WM_SENDSUCCESS,OnSendSuccess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CTestClientDlg::CTestClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for(int n=0;n<3;n++)
	{
		fill[n]   = theApp.fill[n];
		modify[n] = theApp.modify[n];
		design[n] = theApp.design[n];
	}
	//复制应用程序类中的试题指针数组


	CWinThread* pThread = AfxBeginThread(RUNTIME_CLASS(CUIThread));
									//开启计时UI线程 顶层窗口
	//获取应用程序当前路径
	m_AppPath = new char[100];
	::GetCurrentDirectory(100,m_AppPath);

	//填充文件名数组
	initFileName();



}

void CTestClientDlg::initFileName()
{

//	CString FolderPath = m_AppPath;
//	CString FolderPath = "C:\\Test";
	CString FolderPath = "K:\\";

	//循环填充二维数组
	CString TempFileName; //用于储存每次循环中临时的文件名
	for(int i=0;i<3;i++)
	{
		TempFileName.Format("\\Fill%d.cpp",i);
		this->m_TestFileName[0][i] = FolderPath + TempFileName;

		TempFileName.Format("\\Modify%d.cpp",i);
		this->m_TestFileName[1][i] = FolderPath + TempFileName;

		TempFileName.Format("\\Design%d.cpp",i);
		this->m_TestFileName[2][i] = FolderPath + TempFileName;

	}
}

void CTestClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestClientDlg)
	DDX_Control(pDX, IDC_TESTINFO, m_TestInfo);
	///////////////////////////////////
	DDX_Control(pDX, IDC_LOOK_FILL_1, m_LookButton[0][0]);
	DDX_Control(pDX, IDC_LOOK_FILL_2, m_LookButton[0][1]);
	DDX_Control(pDX, IDC_LOOK_FILL_3, m_LookButton[0][2]);

	DDX_Control(pDX, IDC_LOOK_MODIFY_1, m_LookButton[1][0]);
	DDX_Control(pDX, IDC_LOOK_MODIFY_2, m_LookButton[1][1]);
	DDX_Control(pDX, IDC_LOOK_MODIFY_3, m_LookButton[1][2]);

	DDX_Control(pDX, IDC_LOOK_DESIGN_1, m_LookButton[2][0]);
	DDX_Control(pDX, IDC_LOOK_DESIGN_2, m_LookButton[2][1]);
	DDX_Control(pDX, IDC_LOOK_DESIGN_3, m_LookButton[2][2]);
			//////////////////////////////////////

	DDX_Control(pDX, IDC_ANSWER_FILL_1, m_AnswerButton[0][0]);
	DDX_Control(pDX, IDC_ANSWER_FILL_2, m_AnswerButton[0][1]);
	DDX_Control(pDX, IDC_ANSWER_FILL_3, m_AnswerButton[0][2]);

	DDX_Control(pDX, IDC_ANSWER_MODIFY_1, m_AnswerButton[1][0]);
	DDX_Control(pDX, IDC_ANSWER_MODIFY_2, m_AnswerButton[1][1]);
	DDX_Control(pDX, IDC_ANSWER_MODIFY_3, m_AnswerButton[1][2]);

	DDX_Control(pDX, IDC_ANSWER_DESIGN_1, m_AnswerButton[2][0]);
	DDX_Control(pDX, IDC_ANSWER_DESIGN_2, m_AnswerButton[2][1]);
	DDX_Control(pDX, IDC_ANSWER_DESIGN_3, m_AnswerButton[2][2]);


	//}}AFX_DATA_MAP
	
}



/////////////////////////////////////////////////////////////////////////////
// CTestClientDlg message handlers

BOOL CTestClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//显示试题数目
	ShowTestNumber();

	DisableButton(); //使没有题的按钮灰化

	//开启计时器
	if(!SetTimer(1,60000,NULL))
		return FALSE;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestClientDlg::DisableButton()
{
	for(int i=0;i<3;i++)
	{
		
		if(this->fill[i] == NULL)
		{
			this->m_LookButton[0][i].EnableWindow(FALSE);
			this->m_AnswerButton[0][i].EnableWindow(FALSE);
		}

		if(this->modify[i] == NULL)
		{
			this->m_LookButton[1][i].EnableWindow(FALSE);
			this->m_AnswerButton[1][i].EnableWindow(FALSE);
		}

		if(this->design[i] == NULL)
		{
			this->m_LookButton[2][i].EnableWindow(FALSE);
			this->m_AnswerButton[2][i].EnableWindow(FALSE);
		}
		
		
	}
}

void CTestClientDlg::ShowTestNumber()
{
	//统计各题数量
	int FillNumber    = 0;  //填空题个数
	int ModifyNumber  = 0;  //改错题个数
	int DesignNumber  = 0;  //设计题个数
	
	for(int i=0; i<3; i++) //循环查看各题不为 试题描述指针不为空就在相应变量上加1
	{
		if(this->fill[i] != NULL)
			FillNumber++;
		if(this->modify[i] != NULL)
			ModifyNumber++;
		if(this->design[i] != NULL)
			DesignNumber++;
	}

	//显示到静态文本控件上
	CString strTestNumber;
	strTestNumber.Format("共%d题 填空题%d道 改错题%d道 设计题%d道",
		FillNumber+ModifyNumber+DesignNumber,
		FillNumber,
		ModifyNumber,
		DesignNumber);   //格式化要显示的字符串

	this->m_TestInfo.SetWindowText(strTestNumber);

}

void CTestClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}


	GhWndMain = GetSafeHwnd(); //窗口句柄给全局变量
	
}


HCURSOR CTestClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CTestClientDlg::DealLookButton(int type,int order)
{
	//检查输入参数
	if((type>2)||(type<0))
		return FALSE;
	if((order>2)||(order<0))
		return FALSE;
	//组织成二维表
	char* TestTable[3][3];
	for(int i=0;i<3;i++)      //一趟将各题型的第i道题复制
	{
		TestTable[0][i] = this->fill[i];
		TestTable[1][i] = this->modify[i];
		TestTable[2][i] = this->design[i];
	}
	//处理&显示
	if(TestTable[type][order] == NULL)
		this->SetDlgItemText(IDC_TITLEINFO,"没有相应试题");
	else
		this->SetDlgItemText(IDC_TITLEINFO,TestTable[type][order]);

	return TRUE;

}

BOOL CTestClientDlg::DealAnswerButton(int type,int order)
{
	//检查输入参数
	if((type>2)||(type<0))
		return FALSE;
	if((order>2)||(order<0))
		return FALSE;
	//组织成二维表
	char* TestTable[3][3];
	for(int i=0;i<3;i++)      //一趟将各题型的第i道题复制
	{
		TestTable[0][i] = this->fill[i];
		TestTable[1][i] = this->modify[i];
		TestTable[2][i] = this->design[i];
	}

	//打开相应文件
	if(TestTable[type][order] == NULL)
	{
		MessageBox("没有相应试题");
		return FALSE;
	}
	else
	{
		CString OpenString; //打开进程字符串
		OpenString.Format("call VCVARS32.BAT  \r\n MSDEV %s",this->m_TestFileName[type][order]);
		
		CString strBatPath = "open.bat";

		try
		{
			
			CFile fillBat(strBatPath,CFile::modeReadWrite|CFile::modeCreate);//SrvCheck
			fillBat.Write(OpenString,sizeof(char)*OpenString.GetLength());
			fillBat.Close();
		}
		catch(CFileException* e)
		{
			e->ReportError();
			e->Delete();
			return FALSE;
		}

		
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		
		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );
		
		GetStartupInfo(&si);
		si.dwFlags    =STARTF_USESHOWWINDOW; //不加此句 在桌面快捷方式执行时不能隐藏进程
		si.wShowWindow=SW_HIDE;

		
		char *szBatPath = new char[strBatPath.GetLength() + 11 +ADDBUFFER];
		szBatPath = strBatPath.GetBuffer(0);

		CreateProcess( NULL, // No module name (use command line). 
        szBatPath, // Command line. SrvCheck
        NULL,             // Process handle not inheritable. 
        NULL,             // Thread handle not inheritable. 
        FALSE,            // Set handle inheritance to FALSE. 
        0, // No creation flags.CREATE_NO_WINDOW 
        NULL,             // Use parent's environment block. 
        NULL,             // Use parent's starting directory. 
        &si,              // Pointer to STARTUPINFO structure.
        &pi );              // Pointer to PROCESS_INFORMATION structure.

		WaitForSingleObject(pi.hProcess,INFINITE);
		
		WinExec(OpenString,SW_SHOW); //执行启动VC进程
		return TRUE;
	}

}


void CTestClientDlg::OnLookFill1() 
{
	DealLookButton(0,0);
}
void CTestClientDlg::OnLookFill2() 
{
	DealLookButton(0,1);
}
void CTestClientDlg::OnLookFill3() 
{
	DealLookButton(0,2);
}

void CTestClientDlg::OnLookModify1() 
{
	DealLookButton(1,0);
}

void CTestClientDlg::OnLookModify2() 
{
	DealLookButton(1,1);
}

void CTestClientDlg::OnLookModify3() 
{
	DealLookButton(1,2);
}


void CTestClientDlg::OnLookDesign1() 
{
	DealLookButton(2,0);
}

void CTestClientDlg::OnLookDesign2() 
{
	DealLookButton(2,1);
}

void CTestClientDlg::OnLookDesign3() 
{
	DealLookButton(2,2);
}


void CTestClientDlg::OnAnswerFill1() 
{
	DealAnswerButton(0,0);
}

void CTestClientDlg::OnAnswerFill2() 
{
	DealAnswerButton(0,1);
}
void CTestClientDlg::OnAnswerFill3() 
{
	DealAnswerButton(0,2);
}

void CTestClientDlg::OnAnswerModify1() 
{
	DealAnswerButton(1,0);
}

void CTestClientDlg::OnAnswerModify2() 
{
	DealAnswerButton(1,1);
}

void CTestClientDlg::OnAnswerModify3() 
{
	DealAnswerButton(1,2);
}

void CTestClientDlg::OnAnswerDesign1() 
{
	DealAnswerButton(2,0);
}

void CTestClientDlg::OnAnswerDesign2() 
{
	DealAnswerButton(2,1);
}

void CTestClientDlg::OnAnswerDesign3() 
{
	DealAnswerButton(2,2);
}


/*将文件数据 读入内存 用于上交给服务器
char* CTestClientDlg::ReadMyFile(const char* czFileName)  
{
	
	CFile value;
	CFileException e;
	char* buffer;
	if(value.Open(czFileName,CFile::modeRead,&e))	//把文件中的数据读入字符串。
	{
		buffer = new char[value.GetLength()+ADDBUFFER];
		value.Read(buffer,value.GetLength());
		buffer[value.GetLength()] = 0;							
		
	}
	else
	{
		e.ReportError();
	}

	value.Close();

	return buffer;
}
*/

void CTestClientDlg::OnTimeOver(WPARAM wParam, LPARAM lParam)
{	
	OnTestSend(NULL,NULL);  //调用响应顶层发送按钮的发送消息	
}


void CTestClientDlg::OnTestSend(WPARAM wParam, LPARAM lParam)
{
	//////////////////////////////////////////////////////程序架构改变不用交卷
	/*
	//组织成二维表
	char* TestTable[3][3];
	for(int i=0;i<3;i++)      //一趟将各题型的第i道题标题指针复制
	{
		TestTable[0][i] = this->fill[i];
		TestTable[1][i] = this->modify[i];
		TestTable[2][i] = this->design[i];
	}

	CString strFileName;
	CMySocket mysock;
	char* TempBuffer;


	//循环发送每个试题
	for(int type=0;type<3;type++)
		for(int order=0;order<3;order++)
		{
			if(TestTable[type][order]!=NULL)  //试题描述不为空 有试题 发送文件
			{
				TempBuffer = ReadMyFile(m_TestFileName[type][order]);
				
				mysock.MySend(Gsock,TempBuffer,5+type,order+1);//副版本号不能为零 防止截断字符串
				//主号5，6，7分别代表三个题 副号1，2，3 为第几个题
			}
		}

	//调用交卷完毕函数
	*/
	SendOver();
}

/*向服务器发送 交卷完毕消息*/
void CTestClientDlg::SendOver()
{
	CMySocket mysock;

	mysock.MySend(Gsock,NULL,3,1);  //号3 为客户端对出消息

	
}

void CTestClientDlg::OnSendSuccess(WPARAM wParam, LPARAM lParam)
{
	MessageBox("试卷上交成功，点击确定退出！","提示",MB_SYSTEMMODAL);

	//关闭对话框 即程序
	SendMessage(WM_CLOSE);
}

void CTestClientDlg::OnMyClose(WPARAM wParam, LPARAM lParam)
{
	SendMessage(WM_CLOSE);
}

/*相应自定义ReStart消息，关闭主对话框，因为服务器对该生进行了重置*/
void CTestClientDlg::OnReStart(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox("服务器将你的状态重置，程序即将关闭，如有问题向管理员联络");
	SendMessage(WM_CLOSE);
}


/*响应自定义Message消息，显示服务器发来的消息*/
void CTestClientDlg::OnMessage(WPARAM wParam, LPARAM lParam)
{
	char* czTemp = (char*)lParam;

	MessageBox(czTemp,"服务器消息",MB_ICONASTERISK | MB_ICONINFORMATION | MB_OK | MB_SYSTEMMODAL );

	delete[] czTemp;
	
}
/*计时器响应函数*/
void CTestClientDlg::OnTimer(UINT nTimerID)
{
	GTime += 1; //时间累加

	//更新顶层窗口时间
	if(::IsWindow(GhWndTop))
	{
		::PostMessage(GhWndTop,WM_TIMEUPDATA,NULL,NULL);//向顶层时间窗口发送消息
	}

	//将时间发送到服务器
	CMySocket mysocket;
	mysocket.MySend(Gsock,NULL,Mess_Time,GTime);

}