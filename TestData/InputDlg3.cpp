// InputDlg3.cpp : implementation file
//

#include "stdafx.h"
#include "testdata.h"
#include "InputDlg3.h"
#include "PSheet.h"
#include "FillDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputDlg3 property page

IMPLEMENT_DYNCREATE(CInputDlg3, CPropertyPage)

CInputDlg3::CInputDlg3() : CPropertyPage(CInputDlg3::IDD)
{
	//{{AFX_DATA_INIT(CInputDlg3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CInputDlg3::~CInputDlg3()
{
}

void CInputDlg3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDlg3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputDlg3, CPropertyPage)
	//{{AFX_MSG_MAP(CInputDlg3)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDlg3 message handlers

BOOL CInputDlg3::OnSetActive() 
{
	((CPSheet*)this->GetParent())->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);
	return CPropertyPage::OnSetActive();
}

BOOL CInputDlg3::OnWizardFinish() 
{
	nPos = ((CPSheet*)(this->GetParent()))->m_nPos;
	                               //获得传来的插入位置
 	CFillDlg* pMainDlg = (CFillDlg*)((CPSheet*)GetParent())->m_pMWnd;
                                   // 获得主框架窗口
	CString strC;
    ((CEdit*)this->GetDlgItem(IDC_INPUT_CHECK))->GetWindowText(strC);
	if(strC.IsEmpty()==TRUE)
	{
		AfxMessageBox("阅卷内容不允许为空！");
		return 0;
	}
	                              //检查试题内容是否为空
	(pMainDlg->GetpBase())->Input((CEdit*)GetDlgItem(IDC_INPUT_CHECK),
		nPos,"fcheck");
    
	((CEdit*)this->GetDlgItem(IDC_INPUT_OUT))->GetWindowText(strC);
	if(strC.IsEmpty() == TRUE)
    {
		AfxMessageBox("阅卷输出不允许为空！");
			return 0;
	}

		(pMainDlg->GetpBase())->Input((CEdit*)this->GetDlgItem(IDC_INPUT_OUT),
			nPos,"fout");
                                  //检查试题内容是否为空
	return CPropertyPage::OnWizardFinish();
}
