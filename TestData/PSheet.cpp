// PSheet.cpp : implementation file
//

#include "stdafx.h"
#include "TestData.h"
#include "PSheet.h"
#include "FillDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheet

IMPLEMENT_DYNAMIC(CPSheet, CPropertySheet)

CPSheet::CPSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pMWnd = pParentWnd;
	m_nPos = ((CFillDlg*)m_pMWnd)->m_nNewPos;
	this->AddPage(&m_Dlg1);
	this->AddPage(&m_Dlg2);
	this->AddPage(&m_Dlg3);
	m_psh.dwFlags&=~PSH_HASHELP;
}

CPSheet::CPSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pMWnd = pParentWnd;
	m_nPos = ((CFillDlg*)m_pMWnd)->m_nNewPos;
	this->AddPage(&m_Dlg1);
	this->AddPage(&m_Dlg2);
	this->AddPage(&m_Dlg3);
    m_psh.dwFlags&=~PSH_HASHELP;
}

CPSheet::~CPSheet()
{
}


BEGIN_MESSAGE_MAP(CPSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CPSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheet message handlers

BOOL CPSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	 GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);   
	
	return bResult;
}


