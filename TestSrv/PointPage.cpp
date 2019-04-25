// PointPage.cpp: implementation of the CPointPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PointPage.h"
#include "InforSheet.h"
#include "StuInfor.h"
#include "SrvMyApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CStuInfor* arrStu[MAXNUM];
extern SendTestData g_sendTestData[MAXNUM];

CPointPage::CPointPage():
          CPropertyPage(CPointPage::IDD)
{
	
}

CPointPage::~CPointPage()
{

}

void CPointPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_LISTBOX,m_ListBox);

}

BOOL CPointPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString str;
	int nCorrect = 0;//��¼�м�����������
	this->m_nStu = ((CInforSheet*)GetParent())->m_nStu;

	for(int n=0;n<3;n++)
	{
		if(g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandFill[n] != -1)
		{
			//��ʽ���ַ���
			if(arrStu[m_nStu]->StuAnswerFill[n] ==NULL)//�Ͻ��Ծ�Ϊ��
			{
				str.Format("������%d��     ������δ����",n+1);
			}
			else if(arrStu[m_nStu]->StuCorrectFill[n] == 0)
			{
				str.Format("������%d��     ����δ����",n+1);
			}
			else if(arrStu[m_nStu]->StuCorrectFill[n] == 1)
			{
				str.Format("������%d��     ��ȷ",n+1);
				//��ȷ����1
				nCorrect++;
			}
			else if(arrStu[m_nStu]->StuCorrectFill[n] == 2)
			{
				str.Format("������%d��     ����",n+1);
			}
			else
			{
				str.Format("�쳣��");
			}

			//����ַ������б�
			m_ListBox.AddString(str);
		}

		if(g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandModify[n] != -1)
		{
			if(arrStu[m_nStu]->StuAnswerModify[n] ==NULL)//�Ͻ��Ծ�Ϊ��
			{
				str.Format("�Ĵ����%d��     ������δ����",n+1);
			}
			else if(arrStu[m_nStu]->StuCorrectModify[n] == 0)
			{
				str.Format("�Ĵ����%d��     ����δ����",n+1);
			}
			else if(arrStu[m_nStu]->StuCorrectModify[n] == 1)
			{
				str.Format("�Ĵ����%d��     ��ȷ",n+1);
				//��ȷ����1
				nCorrect++;
			}
			else if(arrStu[m_nStu]->StuCorrectModify[n] == 2)
			{
				str.Format("�Ĵ����%d��     ����",n+1);
			}
			else
			{
				str.Format("�쳣��");
			}
			
			m_ListBox.AddString(str);
		}

		if(g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandDesign[n] != -1)
		{
			if(arrStu[m_nStu]->StuAnswerDesign[n] ==NULL)//�Ͻ��Ծ�Ϊ��
			{
				str.Format("������%d��     ������δ����",n+1);
			}
			else if(arrStu[m_nStu]->StuCorrectDesign[n] == 0)
			{
				str.Format("������%d��     ����δ����",n+1);
			}
			else if(arrStu[m_nStu]->StuCorrectDesign[n] == 1)
			{
				str.Format("������%d��     ��ȷ",n+1);
				//��ȷ����1
				nCorrect++;
			}
			else if(arrStu[m_nStu]->StuCorrectDesign[n] == 2)
			{
				str.Format("������%d��     ����",n+1);
			}
			else
			{
				str.Format("�쳣��");
			}
			
			m_ListBox.AddString(str);
		}
	}


	//��ʾ�ܷ�
	if(m_ListBox.GetCount() == 0)
	{
		m_ListBox.AddString("������Ϊ�㣬���ܿ��Ի�δ��ʼ");
	}
	else
	{
		str.Format("�ÿ������ܷ�Ϊ %d",arrStu[m_nStu]->nAllPoint);
		m_ListBox.AddString("");
		m_ListBox.AddString(str);
	}

	return TRUE;
}