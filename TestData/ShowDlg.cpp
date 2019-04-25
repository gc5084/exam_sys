// ShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestData.h"
#include "ShowDlg.h"
#include "Fill.h"
#include "FillDlg.h"
#include "BigShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowDlg dialog


CShowDlg::CShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pParentDlg = (CFillDlg*)pParent;
}


void CShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowDlg, CDialog)
	//{{AFX_MSG_MAP(CShowDlg)
	ON_BN_CLICKED(IDC_FILL_BIGT, OnFillBigt)
	ON_BN_CLICKED(IDC_FILL_BIGCO, OnFillBigco)
	ON_BN_CLICKED(IDC_FILL_BIGA, OnFillBiga)
	ON_BN_CLICKED(IDC_FILL_BIGCH, OnFillBigch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowDlg message handlers


BOOL CShowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CListBox* pList;

    pList = ((CListBox*)pParentDlg->GetDlgItem(IDC_LIST_FILL));
	nIndex = pList->GetCurSel();
    //获取所选列表索引
	int p;
	p = (pParentDlg->GetpBase())->NtoP(nIndex);
	CString strTitle = "ftitle";
	pParentDlg->GetpBase()->Show((CEdit*)GetDlgItem(IDC_EDIT_TITLE),p,strTitle);

	pParentDlg->GetpBase()->Show((CEdit*)GetDlgItem(IDC_EDIT_CONNENT),p,"fcontent");

	pParentDlg->GetpBase()->Show((CEdit*)GetDlgItem(IDC_EDIT_ANSWER),p,"fanswer");

	pParentDlg->GetpBase()->Show((CEdit*)GetDlgItem(IDC_EDIT_REMARK),p,"fremark");

	pParentDlg->GetpBase()->Show((CEdit*)GetDlgItem(IDC_EDIT_CHECK),p,"fcheck");

	pParentDlg->GetpBase()->Show((CEdit*)GetDlgItem(IDC_EDIT_OUT),p,"fout");






	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CShowDlg::OnFillBigt() 
{
	strItem = "ftitle";
	CBigShowDlg dlg(this);
	dlg.DoModal();
}

void CShowDlg::OnFillBigco() 
{
	strItem = "fcontent";
	CBigShowDlg dlg(this);
	dlg.DoModal();
	
}

void CShowDlg::OnFillBiga() 
{
	strItem = "fanswer";
	CBigShowDlg dlg(this);
	dlg.DoModal();
	
}

void CShowDlg::OnFillBigch() 
{
	strItem = "fcheck";
	CBigShowDlg dlg(this);
	dlg.DoModal();
	
}


