// MuchTestDlg.cpp: implementation of the CMuchTestDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MuchTestDlg.h"
#include "SrvMyApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CList<MemoryData,MemoryData>   listTestFill;
extern CList<MemoryData,MemoryData>   listTestModify;
extern CList<MemoryData,MemoryData>   listTestDesign;

CMuchTestDlg::CMuchTestDlg(CWnd* pParent) : CDialog(CMuchTestDlg::IDD,pParent)
{
    this->m_pParent = (CMainWindow*)pParent;

	//����ο�����ÿ�������ܹ�����������m_nTestMax����
	m_nTestMax[0] = listTestFill.GetCount();   //�����
	m_nTestMax[1] = listTestModify.GetCount(); //�Ĵ���
	m_nTestMax[2] = listTestDesign.GetCount(); //����� 


}

CMuchTestDlg::~CMuchTestDlg()
{

}

void CMuchTestDlg::OnOK()
{
	int nTest[3];

	CString str;
	nTest[0] = (int)GetDlgItemInt(IDC_EDITFILL);
	if((nTest[0]<0)||(nTest[0]>m_nTestMax[0]))
	{
		str.Format("��������Ӧ����0 �� %d ֮��",m_nTestMax[0]);
		AfxMessageBox(str);
		return;
	}

	nTest[1] = (int)GetDlgItemInt(IDC_EDITMODIFY);
	if((nTest[1]<0)||(nTest[1]>m_nTestMax[1]))
	{
		str.Format("�Ĵ������Ӧ����0 �� %d ֮��",m_nTestMax[1]);
		AfxMessageBox(str);
		return;
	}

	nTest[2] = (int)GetDlgItemInt(IDC_EDITDESIGN);
	if((nTest[2]<0)||(nTest[2]>m_nTestMax[2]))
	{
		str.Format("��������Ӧ����0 �� %d ֮��",m_nTestMax[2]);
		AfxMessageBox(str);
		return;
	}
	//�ܺ��Ƿ�Ϊ��
	if((nTest[0]+nTest[1]+nTest[2]) == 0)
	{
		AfxMessageBox("����������Ӧ�ô���0");
		return;
	}

	//���Ƹ���������
	this->m_pParent->nMuchTest[0] = nTest[0];
	this->m_pParent->nMuchTest[1] = nTest[1];
	this->m_pParent->nMuchTest[2] = nTest[2];

	CDialog::OnOK();
}

void CMuchTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_TEXTFILL,this->m_TextFill);
	DDX_Control(pDX,IDC_TEXTMODIFY,this->m_TextModify);
	DDX_Control(pDX,IDC_TEXTDESIGN,this->m_TextDesign);

}
BOOL CMuchTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//����ÿ�����͵����뷶Χ��ʾ�ı�
	CString str;
	//�����
	if(m_nTestMax[0] > 3)
	{
		m_nTestMax[0] = 3;
	}
	str.Format("��0��%d��",this->m_nTestMax[0]);
	this->m_TextFill.SetWindowText(str);

	//�Ĵ���
	if(m_nTestMax[1] > 3)
	{
		m_nTestMax[1] = 3;
	}
	str.Format("��0��%d��",this->m_nTestMax[1]);
	this->m_TextModify.SetWindowText(str);

	//�����
	if(m_nTestMax[2] > 3)
	{
		m_nTestMax[2] = 3;
	}
	str.Format("��0��%d��",this->m_nTestMax[2]);
	this->m_TextDesign.SetWindowText(str);

	return TRUE; 
}