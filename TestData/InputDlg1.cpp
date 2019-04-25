// InputDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "TestData.h"
#include "InputDlg1.h"
#include "FillDlg.h"
#include "PSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputDlg1 property page

IMPLEMENT_DYNCREATE(CInputDlg1, CPropertyPage)

CInputDlg1::CInputDlg1() : CPropertyPage(CInputDlg1::IDD)
{
	//{{AFX_DATA_INIT(CInputDlg1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CInputDlg1::~CInputDlg1()
{
}

void CInputDlg1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDlg1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputDlg1, CPropertyPage)
	//{{AFX_MSG_MAP(CInputDlg1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDlg1 message handlers

BOOL CInputDlg1::OnSetActive() 
{
    ((CPSheet*)this->GetParent())->SetWizardButtons(PSWIZB_NEXT);
	   //设置有下一步按钮
	return CPropertyPage::OnSetActive();
}

LRESULT CInputDlg1::OnWizardNext() 
{
    nPos = ((CPSheet*)(this->GetParent()))->m_nPos;

	CFillDlg* pMainDlg = (CFillDlg*)((CPSheet*)GetParent())->m_pMWnd;
                                   // 获得主框架窗口
	CString strC;
    ((CEdit*)this->GetDlgItem(IDC_INPUT_TITLE))->GetWindowText(strC);
	if(strC.IsEmpty()==TRUE)
	{
		AfxMessageBox("标题摘要不允许为空！");
			return -1;
	}
	                              //检查标题是否为空
	CString strTitle = "ftitle";
	(pMainDlg->GetpBase())->Input((CEdit*)this->GetDlgItem(IDC_INPUT_TITLE),
		nPos,strTitle);
    
	((CEdit*)this->GetDlgItem(IDC_INPUT_REMARK))->GetWindowText(strC);
	if(strC.IsEmpty() == FALSE)
    {
	    CString strRemark = "fremark";
	    (pMainDlg->GetpBase())->Input((CEdit*)this->GetDlgItem(IDC_INPUT_REMARK),
		nPos,strRemark);
	}

    return CPropertyPage::OnWizardNext();
}
