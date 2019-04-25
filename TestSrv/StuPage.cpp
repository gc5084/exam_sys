// StuPage.cpp: implementation of the CStuPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StuPage.h"
#include "InforSheet.h"
#include "StuInfor.h"
#include "MySocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CStuInfor* arrStu[MAXNUM];

CStuPage::CStuPage() : 
       CPropertyPage(CStuPage::IDD)
{
}

CStuPage::~CStuPage()
{

}

void CStuPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_EDITNUM,m_EditNum);
	DDX_Control(pDX,IDC_EDITNAME,m_EditName);
	DDX_Control(pDX,IDC_EDITSTATE,m_EditState);
	DDX_Control(pDX,IDC_EDITSOCKET,m_EditSocket);
	DDX_Control(pDX,IDC_EDITIP,m_EditIP);

}

BOOL CStuPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->m_nStu = ((CInforSheet*)GetParent())->m_nStu;

	//显示学号
	m_EditNum.SetWindowText(arrStu[m_nStu]->strNum);
	//显示姓名
	m_EditName.SetWindowText(arrStu[m_nStu]->strName);

	//根据状态变量显示状态信息
	if(arrStu[m_nStu]->nState == 0)
		m_EditState.SetWindowText("该考生还未登录");
	else if(arrStu[m_nStu]->nState == 1)
		m_EditState.SetWindowText("该考生正在考试");
	else if(arrStu[m_nStu]->nState == 2)
		m_EditState.SetWindowText("该考生已交卷");
	else if(arrStu[m_nStu]->nState == 4)
		m_EditState.SetWindowText("该考生被禁止考试");
	else
		m_EditState.SetWindowText("该考生状态为异常 可能是强请关闭了客户端造成的");

	//显示考生IP
	if(arrStu[m_nStu]->nState == 1)
	{
		CMySocket mysock;
		sockaddr_in   sa; //定义sock地址由于存放IP，端口等信息
		if(mysock.GetIP(arrStu[m_nStu]->sock,(sockaddr*)&sa) == TRUE)
		{
			//this->m_IPCtrl.SetAddress(htonl(sa.sin_addr.S_un.S_addr));
			this->m_EditIP.SetWindowText(inet_ntoa(sa.sin_addr));
		}
		CString str;
		str.Format("%d",arrStu[m_nStu]->sock);
		m_EditSocket.SetWindowText(str);
	}
	else
	{
		CString str;
		str.Format("无对应IP地址");
		m_EditIP.SetWindowText(str);

		str.Format("无对应套接字");
		m_EditSocket.SetWindowText(str);
	}
	

	return TRUE;
}