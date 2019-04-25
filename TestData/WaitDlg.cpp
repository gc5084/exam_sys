// WaitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testdata.h"
#include "WaitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaitDlg dialog


CWaitDlg::CWaitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaitDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaitDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaitDlg, CDialog)
	//{{AFX_MSG_MAP(CWaitDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitDlg message handlers
/*
  依靠框架发送的WM_PAINT消息
  实现自动执行 增长进度条
 */
void CWaitDlg::OnPaint() 
{
	
	CPaintDC dc(this); // device context for painting
	//(CButton*)GetDlgItem(IDC_TIT)->ShowWindow(SW_SHOW);
    //::Sleep(100);
	AfxMessageBox("检测开始");//不在这里加这个 不出现静态文本 暂时先这样
	for(int i=0;i<100;i++)
	{
		((CProgressCtrl*)GetDlgItem(IDC_PROGRESS))->SetPos(i);
        ::Sleep(50);
	}

	PostMessage(WM_CLOSE);
}

BOOL CWaitDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS))->SetRange(0,100);
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS))->SetPos(0);
	


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
