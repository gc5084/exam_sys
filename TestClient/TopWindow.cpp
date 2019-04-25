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
	                                           //ע�ᴰ����
	CreateEx(WS_EX_TOPMOST,strWndClass,"ʱ�䴰��",
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
	m_fontMain.CreatePointFont(100,_T("����"));
	CFont *pOldFont = dc.SelectObject(&m_fontMain);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
														//ѡ�������� ��ȡ����������Ϣ
	m_cxChar = tm.tmAveCharWidth;
	m_cyChar = tm.tmHeight+tm.tmExternalLeading;
	dc.SelectObject(pOldFont);

	m_rectR.SetRect(0,0,48*m_cxChar,4*m_cyChar);
														//������Ҫ�ػ�������С ����������
	m_rectAll.SetRect(0,0,62*m_cxChar,4*m_cyChar);
														//����ȫ�������С
	//һ������ռ�����ַ�λ
	CalcWindowRect(&m_rectAll);
	SetWindowPos(NULL,0,0,m_rectAll.Width(),m_rectAll.Height(),
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);



	m_button.Create(_T("����"),WS_CHILD|WS_VISIBLE|BS_BITMAP|BS_OWNERDRAW,
		CRect(48*m_cxChar,m_cyChar,62*m_cxChar,4*m_cyChar),this,IDC_SEND);
    m_button.LoadBitmaps(IDB_SENDU,IDB_SENDD);
	m_button.SizeToContent();

	arrTabStop[0] = 14*m_cxChar;
	arrTabStop[1] = 24*m_cxChar;
    arrTabStop[2] = 32*m_cxChar;
									//����tabֹͣλ��

	GhWndTop = GetSafeHwnd(); //��ȫ�ֱ��������ڵľ��
 
	return 0;
}

void CTopWindow::ShowInfor()
{
	
    CClientDC dc(this);
	CFont *pOldFont = dc.SelectObject(&m_fontMain);
													//���붨������
	dc.SetBkMode(TRANSPARENT);
													//����Ϊ͸��ģʽ
	CString str;
													//������Ϣ�ַ���
	CString str2;
													//������Ϣ�ַ���
	int restTime;
													//ʣ��ʱ��
	
	if(GTimeLong == 0)
	{
		str.Format("�ȴ����������Ϳ���ʱ����Ϣ...");
		dc.TextOut(4*m_cxChar,m_cyChar,str);
	}
	else
	{
			restTime = GTimeLong - GTime;
			str.Format("��������\t����ʱ��\t����ʱ\tʣ��ʱ��");
			str2.Format("%s\t%d:����\t%d:����\t%d:����",GczName,GTimeLong,GTime,restTime);
			
			dc.TabbedTextOut(4*m_cxChar,m_cyChar,str,str.GetLength(),
				sizeof(arrTabStop),arrTabStop,0);
			
			dc.TabbedTextOut(4*m_cxChar,2*m_cyChar,str2,str2.GetLength(),
				sizeof(arrTabStop),arrTabStop,0);
		
	}

	dc.SelectObject(pOldFont);
    
	
}

void CTopWindow::OnTimeUp(WPARAM wParam, LPARAM lParam)
{
    //��ʾ��Ϣ
    Invalidate(TRUE);

	//ʱ���ѵ��������ڷ���ѶϢ							
	if((GTimeLong - GTime) == 0)
	{
		
		::PostMessage(GhWndMain,WM_TIMEOVER,NULL,NULL);	
		MessageBox("����ʱ���ѵ���ϵͳ���Զ��ύ�Ծ�\r\n�����򽫹ر�","��ʾ",MB_SYSTEMMODAL);
	}
}

void CTopWindow::OnSend()
{
	if(AfxMessageBox("ȷ�Ͻ���",MB_YESNO) == IDNO)
		return;

	ShowInfor();
    
	::SendMessage(GhWndMain,WM_TESTSEND,NULL,NULL);
}
