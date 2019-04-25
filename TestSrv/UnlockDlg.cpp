// UnlockDlg.cpp: implementation of the CUnlockDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UnlockDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUnlockDlg::CUnlockDlg(CMainWindow* pParent) : CDialog(CUnlockDlg::IDD,pParent)
{
	this->strCorrectPass = pParent->Password;
}

CUnlockDlg::~CUnlockDlg()
{

}

void CUnlockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_EDITPASS,m_EditPass);
}

void CUnlockDlg::OnOK()
{
	CString str;

	m_EditPass.GetWindowText(str);

	if(str.Compare(strCorrectPass) != 0)
	{
		AfxMessageBox("√‹¬Î¥ÌŒÛ£°");
		return;
	}

	CDialog::OnOK();
}

void CUnlockDlg::OnCancel()
{
}
