// BigShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testdata.h"
#include "BigShowDlg.h"
#include "ShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBigShowDlg dialog


CBigShowDlg::CBigShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBigShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBigShowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_pParent = (CShowDlg*)pParent;
}


void CBigShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBigShowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBigShowDlg, CDialog)
	//{{AFX_MSG_MAP(CBigShowDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBigShowDlg message handlers

BOOL CBigShowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int p;
	p = (m_pParent->pParentDlg->GetpBase())->NtoP(m_pParent->nIndex);
	CString str = m_pParent->strItem;
	m_pParent->pParentDlg->GetpBase()->Show((CEdit*)GetDlgItem(IDC_EDIT_BIGED),p,str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
