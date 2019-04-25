// EntryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestClient.h"
#include "EntryDlg.h"
#include "MySocket.h"
#include "WaitStartDlg.h"
#include "TestManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEntryDlg dialog
UINT RecvFunc(LPVOID pParam);

extern SOCKET Gsock;
extern CTestClientApp theApp;
extern char* GczName;
extern int    GTime;
extern int    GTimeLong;
extern BOOL   GTestSendOver;
extern HWND   GhWndEntry;

CEntryDlg::CEntryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEntryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEntryDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bConnect = FALSE;
}


void CEntryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntryDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDCANCEL, m_bmExit);
	DDX_Control(pDX, IDOK, m_bmStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEntryDlg, CDialog)
	//{{AFX_MSG_MAP(CEntryDlg)
	  ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntryDlg message handlers



void CEntryDlg::OnOK() 
{
	//获取学号输入框的学号
	char czNum[11];
    this->GetDlgItemText(IDC_NUMBER,czNum,11); //学号只截取10+1为 带空终止符
	czNum[10] = 0;
	Gsock = ((CTestClientApp*)AfxGetApp())->m_sock ;

	//连接服务器
	if(ConnectSrv() == FALSE)
		return;

	//发送给服务器学号
	CMySocket mysock;
	if(mysock.MySend(Gsock,czNum,1,1) == FALSE)
		return;

	//接收服务器返回的数据包
	char *czRecvPage;
	czRecvPage = mysock.MyRecv(Gsock);
	if(czRecvPage == NULL)
		return;

	CString str;
	if(czRecvPage[SOCKHEAD-2] == 1) //主版本号
	{
		//找到对应学生 服务器发送学号 等待客户端确认
		if(czRecvPage[SOCKHEAD-1] == 1)	//信息中含有标志1是数据库中有信息
		{
			if(DealFoundNumber(czRecvPage,czNum) == FALSE)
				return;
		}
		else if(czRecvPage[SOCKHEAD-1] == 2)
		{
			AfxMessageBox("数据库中没有该学生信息！");
			return;
		}

		else if(czRecvPage[SOCKHEAD-1] == 3)
		{
			str.Format("学生 %s 已经登录过 如有异议请与管理员联系",&czRecvPage[SOCKHEAD]);
			AfxMessageBox(str);
			return;
		}
		
		else if(czRecvPage[SOCKHEAD-1] == 4)//副标志为4 对应考号被禁止考试
		{
			str.Format("考生%s 被禁止考试 如有异议请与管理员联系",&czRecvPage[SOCKHEAD]);
			AfxMessageBox(str);
			return;
		}	
	}
	else
		AfxMessageBox("异常！");
	
}
	
BOOL CEntryDlg::ConnectSrv()
{
	//获取文件中的IP
	CFile file;
	CFileException e;

	char* szIP;
	if(file.Open("SrvIP.dat",CFile::modeReadWrite,&e))
	{
		int n = file.GetLength();
		szIP = new char[file.GetLength()+1];
		file.Read( szIP,file.GetLength());
		szIP[file.GetLength()] =0;
	}
	else
	{
		MessageBox("找不到SrvIP.dat文件 请先设置服务器IP","错误！");
		return FALSE;
	}
	
	//填充服务器地址结构
	sockaddr_in addrSrv;
	addrSrv.sin_family = AF_INET;  //指定为TCP协议
	addrSrv.sin_addr.S_un.S_addr = inet_addr(szIP); 
									//文件获取的服务器IP，inet_addr转化为网络字节序
	addrSrv.sin_port = htons(7500);
									//绑定7500端口

	//连接服务器
	if(!m_bConnect)
	{
		int nConnect;
		nConnect = connect(Gsock,(sockaddr*)&addrSrv,sizeof(sockaddr));
		if(nConnect == SOCKET_ERROR)
		{
			CString str;
			str.Format(_T("服务器未开启"));
			AfxMessageBox(str);
			return FALSE;
		}
		m_bConnect = TRUE;
	}

	return TRUE;
}
	

BOOL CEntryDlg::DealFoundNumber(char* czRecvPage, char* czNum)
{
	GczName = new char[20];
	::lstrcpy(GczName,&czRecvPage[SOCKHEAD]); //将数据中包含的名字复制给全局变量
	
	CMySocket mysock;
	CString strName;
	strName.Format("你的姓名是：%s",&czRecvPage[SOCKHEAD]);
	if(AfxMessageBox(strName,MB_YESNO) == IDYES) 
	{
		mysock.MySend(Gsock,czNum,2,1);
		//发送消息 确认信息正确 主标志2
		
		//接受一个考试时间消息
		char* Buffer;
		Buffer = mysock.MyRecv(Gsock);
		if(Buffer[2] ==15)      //时间消息
		{
			GTime      = (int)Buffer[SOCKHEAD]-1;
			//时间减1 符合发送约定
			GTimeLong  = (int)Buffer[SOCKHEAD+1];
			
			int IsTestStart = (int)Buffer[SOCKHEAD+2]; 
			//获得考试是否开始信息 包含在时间消息里
			
			if(GTime == GTimeLong)
			{
				AfxMessageBox("你的考试时间已经使用完了！");
				return FALSE;
			}

			///读取网络映射文件内容
			CTestManage testManage;
			testManage.ReadDescribeFile();

			//开启监听线程
			AfxBeginThread(RecvFunc,NULL);

			GhWndEntry = NULL;
			CDialog::OnOK(); //关闭本登录对话框
		}
		else
		{
			MessageBox("异常 请重试！","错误",MB_SYSTEMMODAL);  //顶层窗口
			return FALSE;
		}
		
	}
	else //取消姓名询问对话框
		return FALSE;
	
	//正常 返回TRUE
	return TRUE;
}




BOOL CEntryDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_bmExit.LoadBitmaps(IDB_EXIT,IDB_EXITONFOCUS,IDB_EXITONFOCUS,IDB_EXITONFOCUS); //推出按钮
    m_bmExit.SizeToContent();

	m_bmStart.LoadBitmaps(IDB_START,IDB_STARTONFOCUS,IDB_STARTONFOCUS,IDB_STARTONFOCUS); //开始按钮
    m_bmStart.SizeToContent();

	// TODO: Add extra initialization here
	GhWndEntry = GetSafeHwnd(); //将窗口句柄传到全局变量
	m_bitmap.LoadBitmap(IDB_WELCOME);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/////背景重绘消息
BOOL CEntryDlg::OnEraseBkgnd(CDC*   pDC)
{
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);  //创建对应的内存设备

	CBitmap* pOldBitmap = dcMem.SelectObject(&m_bitmap);
	pDC->BitBlt(0,0,618,448,&dcMem,0,0,SRCCOPY);
	dcMem.SelectObject(&pOldBitmap);
	return TRUE;
}
