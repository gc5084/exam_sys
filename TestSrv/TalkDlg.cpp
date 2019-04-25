// TalkDlg.cpp: implementation of the CTalkDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TalkDlg.h"
#include "SrvMainWnd.h"
#include "MySocket.h"
#include "StuInfor.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CStuInfor* arrStu[MAXNUM];

CTalkDlg::CTalkDlg(CWnd* pParent = NULL) : CDialog(CTalkDlg::IDD,pParent)
{
}

CTalkDlg::~CTalkDlg()
{

}

void CTalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_CONTENT,m_Edit);
}


void CTalkDlg::OnOK()
{
	//���տؼ������ݻ�ȡ���������
	m_Edit.GetWindowText(m_strContent);
	if(m_strContent.GetLength() == 0)
	{
		AfxMessageBox("�������Ϳ����ݣ�");
		return;
	}

	CDialog::OnOK();
}

/*��ȡ�����ַ���*/
CString CTalkDlg::GetContent()
{
	return this->m_strContent;
}