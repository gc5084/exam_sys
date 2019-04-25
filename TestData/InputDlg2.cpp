// InputDlg2.cpp : implementation file
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
// CInputDlg2 property page

IMPLEMENT_DYNCREATE(CInputDlg2, CPropertyPage)

CInputDlg2::CInputDlg2() : CPropertyPage(CInputDlg2::IDD)
{
	//{{AFX_DATA_INIT(CInputDlg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CInputDlg2::~CInputDlg2()
{
}

void CInputDlg2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDlg2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputDlg2, CPropertyPage)
	//{{AFX_MSG_MAP(CInputDlg2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDlg2 message handlers

BOOL CInputDlg2::OnSetActive() 
{
     ((CPSheet*)this->GetParent())->SetWizardButtons(PSWIZB_BACK|PSWIZB_NEXT);
	   //��������һ����ť	
	return CPropertyPage::OnSetActive();
}


LRESULT CInputDlg2::OnWizardNext() 
{
    nPos = ((CPSheet*)(this->GetParent()))->m_nPos;
	                               //��ô����Ĳ���λ��
 	CFillDlg* pMainDlg = (CFillDlg*)((CPSheet*)GetParent())->m_pMWnd;
                                   // �������ܴ���
	CString strC;
    ((CEdit*)this->GetDlgItem(IDC_INPUT_CONTENT))->GetWindowText(strC);
	if(strC.IsEmpty()==TRUE)
	{
		AfxMessageBox("�������ݲ�����Ϊ�գ�");
			return -1;
	}
	                              //������������Ƿ�Ϊ��
	(pMainDlg->GetpBase())->Input((CEdit*)this->GetDlgItem(IDC_INPUT_CONTENT),
		nPos,"fcontent");
    
	((CEdit*)this->GetDlgItem(IDC_INPUT_ANSWER))->GetWindowText(strC);
	if(strC.IsEmpty() == TRUE)
    {
		AfxMessageBox("�ľ����ݲ�����Ϊ�գ�");
			return -1;
	}

	CString strAnswer = "fanswer";
		(pMainDlg->GetpBase())->Input((CEdit*)this->GetDlgItem(IDC_INPUT_ANSWER),
			nPos,strAnswer);
                                  //������������Ƿ�Ϊ��	
	return CPropertyPage::OnWizardNext();
}
