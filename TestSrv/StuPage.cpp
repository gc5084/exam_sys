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

	//��ʾѧ��
	m_EditNum.SetWindowText(arrStu[m_nStu]->strNum);
	//��ʾ����
	m_EditName.SetWindowText(arrStu[m_nStu]->strName);

	//����״̬������ʾ״̬��Ϣ
	if(arrStu[m_nStu]->nState == 0)
		m_EditState.SetWindowText("�ÿ�����δ��¼");
	else if(arrStu[m_nStu]->nState == 1)
		m_EditState.SetWindowText("�ÿ������ڿ���");
	else if(arrStu[m_nStu]->nState == 2)
		m_EditState.SetWindowText("�ÿ����ѽ���");
	else if(arrStu[m_nStu]->nState == 4)
		m_EditState.SetWindowText("�ÿ�������ֹ����");
	else
		m_EditState.SetWindowText("�ÿ���״̬Ϊ�쳣 ������ǿ��ر��˿ͻ�����ɵ�");

	//��ʾ����IP
	if(arrStu[m_nStu]->nState == 1)
	{
		CMySocket mysock;
		sockaddr_in   sa; //����sock��ַ���ڴ��IP���˿ڵ���Ϣ
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
		str.Format("�޶�ӦIP��ַ");
		m_EditIP.SetWindowText(str);

		str.Format("�޶�Ӧ�׽���");
		m_EditSocket.SetWindowText(str);
	}
	

	return TRUE;
}