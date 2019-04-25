// CheckDlg.cpp: implementation of the CCheckDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CheckDlg.h"
#include "StuInfor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CStuInfor* arrStu[MAXNUM];

CCheckDlg::CCheckDlg(CWnd* pParent) 
      : CDialog(CCheckDlg::IDD,pParent)
{
	this->m_pParent = (CMainWindow*)pParent; //��ȡ������ָ��
	nStu = 0; //�ѽ���������ʼ��Ϊ0

	//ͳ�Ƴ�ʼ������
	for(int n = 0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)
		{
			if(arrStu[n]->nState == 2)
				nStu++;
		}
	}
}

CCheckDlg::~CCheckDlg()
{

}

void CCheckDlg::OnOK()
{

	int nNum = 0; //��¼�Ѿ�����˼�������
	CString str;
	//ѭ������ѧ��
	for(int n = 0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)
		{
			if(arrStu[n]->nState == 2) //״̬Ϊ��������
			{
				arrStu[n]->CheckAllAnswer(); //���ÿ����������Ծ�

				///�������
				nNum++; //���������1
				str.Format("���ȣ�%d��/ %d��",nNum,nStu);
				m_pStatic->SetWindowText(str);//��ʾ�������ϵ�������
				m_pProgressCtrl->SetPos(nNum);//���½���������

			}
		}

	}
	AfxMessageBox("�ľ����");
	CDialog::OnOK();

}

BOOL CCheckDlg::OnInitDialog()
{

	CDialog::OnInitDialog();

	m_pProgressCtrl = ((CProgressCtrl*)GetDlgItem(IDC_PROGRESS));
	m_pProgressCtrl->SetRange(0,nStu);
														//����������Ϊ0-nStu(�ѽ�������)
	m_pProgressCtrl->SetPos(0);
	                                                    //��ʼλ������0

	//��ʾһ���ַ��� �ڽ������Ϸ� ���������ϸ���̬�ı����Գ�����
	CString str;
	str.Format("���ȣ�0�� / %d��",nStu);
	m_pStatic = ((CStatic*)GetDlgItem(IDC_TEXT));
	if(m_pStatic != NULL)
	m_pStatic->SetWindowText(str);

	return TRUE;

}
