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
	//��ȡѧ��������ѧ��
	char czNum[11];
    this->GetDlgItemText(IDC_NUMBER,czNum,11); //ѧ��ֻ��ȡ10+1Ϊ ������ֹ��
	czNum[10] = 0;
	Gsock = ((CTestClientApp*)AfxGetApp())->m_sock ;

	//���ӷ�����
	if(ConnectSrv() == FALSE)
		return;

	//���͸�������ѧ��
	CMySocket mysock;
	if(mysock.MySend(Gsock,czNum,1,1) == FALSE)
		return;

	//���շ��������ص����ݰ�
	char *czRecvPage;
	czRecvPage = mysock.MyRecv(Gsock);
	if(czRecvPage == NULL)
		return;

	CString str;
	if(czRecvPage[SOCKHEAD-2] == 1) //���汾��
	{
		//�ҵ���Ӧѧ�� ����������ѧ�� �ȴ��ͻ���ȷ��
		if(czRecvPage[SOCKHEAD-1] == 1)	//��Ϣ�к��б�־1�����ݿ�������Ϣ
		{
			if(DealFoundNumber(czRecvPage,czNum) == FALSE)
				return;
		}
		else if(czRecvPage[SOCKHEAD-1] == 2)
		{
			AfxMessageBox("���ݿ���û�и�ѧ����Ϣ��");
			return;
		}

		else if(czRecvPage[SOCKHEAD-1] == 3)
		{
			str.Format("ѧ�� %s �Ѿ���¼�� ���������������Ա��ϵ",&czRecvPage[SOCKHEAD]);
			AfxMessageBox(str);
			return;
		}
		
		else if(czRecvPage[SOCKHEAD-1] == 4)//����־Ϊ4 ��Ӧ���ű���ֹ����
		{
			str.Format("����%s ����ֹ���� ���������������Ա��ϵ",&czRecvPage[SOCKHEAD]);
			AfxMessageBox(str);
			return;
		}	
	}
	else
		AfxMessageBox("�쳣��");
	
}
	
BOOL CEntryDlg::ConnectSrv()
{
	//��ȡ�ļ��е�IP
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
		MessageBox("�Ҳ���SrvIP.dat�ļ� �������÷�����IP","����");
		return FALSE;
	}
	
	//����������ַ�ṹ
	sockaddr_in addrSrv;
	addrSrv.sin_family = AF_INET;  //ָ��ΪTCPЭ��
	addrSrv.sin_addr.S_un.S_addr = inet_addr(szIP); 
									//�ļ���ȡ�ķ�����IP��inet_addrת��Ϊ�����ֽ���
	addrSrv.sin_port = htons(7500);
									//��7500�˿�

	//���ӷ�����
	if(!m_bConnect)
	{
		int nConnect;
		nConnect = connect(Gsock,(sockaddr*)&addrSrv,sizeof(sockaddr));
		if(nConnect == SOCKET_ERROR)
		{
			CString str;
			str.Format(_T("������δ����"));
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
	::lstrcpy(GczName,&czRecvPage[SOCKHEAD]); //�������а��������ָ��Ƹ�ȫ�ֱ���
	
	CMySocket mysock;
	CString strName;
	strName.Format("��������ǣ�%s",&czRecvPage[SOCKHEAD]);
	if(AfxMessageBox(strName,MB_YESNO) == IDYES) 
	{
		mysock.MySend(Gsock,czNum,2,1);
		//������Ϣ ȷ����Ϣ��ȷ ����־2
		
		//����һ������ʱ����Ϣ
		char* Buffer;
		Buffer = mysock.MyRecv(Gsock);
		if(Buffer[2] ==15)      //ʱ����Ϣ
		{
			GTime      = (int)Buffer[SOCKHEAD]-1;
			//ʱ���1 ���Ϸ���Լ��
			GTimeLong  = (int)Buffer[SOCKHEAD+1];
			
			int IsTestStart = (int)Buffer[SOCKHEAD+2]; 
			//��ÿ����Ƿ�ʼ��Ϣ ������ʱ����Ϣ��
			
			if(GTime == GTimeLong)
			{
				AfxMessageBox("��Ŀ���ʱ���Ѿ�ʹ�����ˣ�");
				return FALSE;
			}

			///��ȡ����ӳ���ļ�����
			CTestManage testManage;
			testManage.ReadDescribeFile();

			//���������߳�
			AfxBeginThread(RecvFunc,NULL);

			GhWndEntry = NULL;
			CDialog::OnOK(); //�رձ���¼�Ի���
		}
		else
		{
			MessageBox("�쳣 �����ԣ�","����",MB_SYSTEMMODAL);  //���㴰��
			return FALSE;
		}
		
	}
	else //ȡ������ѯ�ʶԻ���
		return FALSE;
	
	//���� ����TRUE
	return TRUE;
}




BOOL CEntryDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_bmExit.LoadBitmaps(IDB_EXIT,IDB_EXITONFOCUS,IDB_EXITONFOCUS,IDB_EXITONFOCUS); //�Ƴ���ť
    m_bmExit.SizeToContent();

	m_bmStart.LoadBitmaps(IDB_START,IDB_STARTONFOCUS,IDB_STARTONFOCUS,IDB_STARTONFOCUS); //��ʼ��ť
    m_bmStart.SizeToContent();

	// TODO: Add extra initialization here
	GhWndEntry = GetSafeHwnd(); //�����ھ������ȫ�ֱ���
	m_bitmap.LoadBitmap(IDB_WELCOME);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/////�����ػ���Ϣ
BOOL CEntryDlg::OnEraseBkgnd(CDC*   pDC)
{
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);  //������Ӧ���ڴ��豸

	CBitmap* pOldBitmap = dcMem.SelectObject(&m_bitmap);
	pDC->BitBlt(0,0,618,448,&dcMem,0,0,SRCCOPY);
	dcMem.SelectObject(&pOldBitmap);
	return TRUE;
}
