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

//���Ҫ��ʾ�ڶԻ����ϵ�����
void CWaitStartDlg::GetInitMessage(CString Number)
{

	this->m_Num = Number;    //ѧ��      ���Դ����Ĳ���

	this->m_Name = GczName;  //����      ����ȫ�ֱ���

	CString strAllTimes;     //����ʱ��  ����ȫ�ֱ��� ��intת����CString
	strAllTimes.Format("%d",GTimeLong);
	this->m_Time = strAllTimes;
}



BOOL CWaitStartDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	this->UpdateData(TRUE); //�������ݵ��ؼ���

	GhWndWait = GetSafeHwnd(); //�����ھ������ȫ�ֱ���

	if(this->m_SendRequest == TRUE) //������������
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

/*��Ӧ�Զ���Message��Ϣ����ʾ��������������Ϣ*/
void CWaitStartDlg::OnMessage(WPARAM wParam, LPARAM lParam)
{
	char* czTemp = (char*)lParam;

	MessageBox(czTemp,"��������Ϣ",MB_ICONASTERISK | MB_ICONINFORMATION | MB_OK | MB_SYSTEMMODAL );

	delete[] czTemp;
	
}

void CWaitStartDlg::OnReStart(WPARAM wParam, LPARAM lParam)
{
	MessageBox("�����������״̬���ã����򼴽��رգ��������������Ա����","��Ϣ",MB_SYSTEMMODAL);
	GhWndWait = NULL;   //ȫ�ֱ����ڱ����ÿ�
	CDialog::OnCancel();  //ȡ��ʽ�رս�����IDCANCEL
}

void CWaitStartDlg::OnTestSendOver(WPARAM wParam, LPARAM lParam)
{
	//�رձ��Ի���
	GhWndWait = NULL;  //ȫ�ֱ����ڱ����ÿ�
	CDialog::OnOK();
}

void CWaitStartDlg::SendRequestTest(BOOL result)
{
	this->m_SendRequest = result;
}


void CWaitStartDlg::OnOK()   //ȡ���س���Ӧ
{}

void CWaitStartDlg::OnCancel() //ȡ��esc����Ӧ
{}