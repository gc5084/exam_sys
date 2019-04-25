// LOCKDLG.cpp: implementation of the CLOCKDLG class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LOCKDLG.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLOCKDLG::CLOCKDLG(CMainWindow* pParent) : CDialog(CLOCKDLG::IDD,pParent)
{
	this->m_pParent = pParent;
}

CLOCKDLG::~CLOCKDLG()
{

}

void CLOCKDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_PASSWORD,m_Password);
	DDX_Control(pDX,IDC_REPASS,m_RePass);
}

void CLOCKDLG::OnOK()
{
	CString strPass,strRePass;
	this->m_Password.GetWindowText(strPass);
	this->m_RePass.GetWindowText(strRePass);

	if(strPass.GetLength() == 0)
	{
		AfxMessageBox("���벻��Ϊ��");
		return;
	}
	if(strPass.Compare(strRePass) != 0)
	{
		AfxMessageBox("�����������벻һ��,����������");
		return;
	}
	this->m_pParent->Password = strPass;
	CDialog::OnOK();
}
