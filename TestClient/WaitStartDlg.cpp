// WaitStartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestClient.h"
#include "WaitStartDlg.h"
#include "MySocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaitStartDlg dialog

extern char* GczName;
extern int    GTimeLong;
extern HWND   GhWndWait;
extern SOCKET Gsock;

CWaitStartDlg::CWaitStartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitStartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaitStartDlg)
	m_Name = _T("");
	m_Num = _T("");
	m_Time = _T("");
	//}}AFX_DATA_INIT
	this->m_SendRequest = FALSE;
}


void CWaitStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaitStartDlg)
	DDX_Text(pDX, IDC_WAITNAME, m_Name);
	DDX_Text(pDX, IDC_WAITNUM, m_Num);
	DDX_Text(pDX, IDC_WAITTIME, m_Time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaitStartDlg, CDialog)
	//{{AFX_MSG_MAP(CWaitStartDlg)
	ON_MESSAGE(WM_TESTSENDOVER,OnTestSendOver)
	ON_MESSAGE(WM_MESSAGE,OnMessage)
	ON_MESSAGE(WM_RESTART,OnReStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitStartDlg message handlers

//获得要显示在对话框上的数据
void CWaitStartDlg::GetInitMessage(CString Number)
{

	this->m_Num = Number;    //学号      来自传来的参数

	this->m_Name = GczName;  //姓名      来自全局变量

	CString strAllTimes;     //考试时间  来自全局变量 从int转化成CString
	strAllTimes.Format("%d",GTimeLong);
	this->m_Time = strAllTimes;
}



BOOL CWaitStartDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	this->UpdateData(TRUE); //更新数据到控件上

	GhWndWait = GetSafeHwnd(); //将窗口句柄传到全局变量

	if(this->m_SendRequest == TRUE) //发送试题请求
	{
		CMySocket sendGetTestInfor;
		if(sendGetTestInfor.MySend(Gsock,NULL,20,1) == FALSE)
		{
			return FALSE;
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*响应自定义Message消息，显示服务器发来的消息*/
void CWaitStartDlg::OnMessage(WPARAM wParam, LPARAM lParam)
{
	char* czTemp = (char*)lParam;

	MessageBox(czTemp,"服务器消息",MB_ICONASTERISK | MB_ICONINFORMATION | MB_OK | MB_SYSTEMMODAL );

	delete[] czTemp;
	
}

void CWaitStartDlg::OnReStart(WPARAM wParam, LPARAM lParam)
{
	MessageBox("服务器将你的状态重置，程序即将关闭，如有问题向管理员联络","消息",MB_SYSTEMMODAL);
	GhWndWait = NULL;   //全局本窗口变量置空
	CDialog::OnCancel();  //取消式关闭将返回IDCANCEL
}

void CWaitStartDlg::OnTestSendOver(WPARAM wParam, LPARAM lParam)
{
	//关闭本对话框
	GhWndWait = NULL;  //全局本窗口变量置空
	CDialog::OnOK();
}

void CWaitStartDlg::SendRequestTest(BOOL result)
{
	this->m_SendRequest = result;
}


void CWaitStartDlg::OnOK()   //取消回车响应
{}

void CWaitStartDlg::OnCancel() //取消esc的响应
{}