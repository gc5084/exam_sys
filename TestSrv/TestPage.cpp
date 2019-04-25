// TestPage.cpp: implementation of the CTestPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPage.h"
#include "InforSheet.h"
#include "StuInfor.h"
#include "SrvMyApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CStuInfor* arrStu[MAXNUM];
extern SendTestData g_sendTestData[MAXNUM];

BEGIN_MESSAGE_MAP(CTestPage,CPropertyPage)
  ON_CBN_SELCHANGE(IDC_CBLIST,OnSelChange)
END_MESSAGE_MAP()
CTestPage::CTestPage():
         CPropertyPage(CTestPage::IDD)
{
	for(int n=0;n<9;n++)
	{
		m_Test[n] = NULL;
		m_TestPK[n] = NULL;
	}
}

CTestPage::~CTestPage()
{

}


void CTestPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_EDITTEST,m_EditTest);
	DDX_Control(pDX,IDC_CBLIST,m_CBList);
	DDX_Control(pDX,IDC_EDITPK,m_EditPK);

}

BOOL CTestPage::OnInitDialog()
{
	int nIndex = 0;//m_Test��m_TestPK����������������һ���������Ӧָ��������һ��
	CDialog::OnInitDialog();
	//�õ��������Ա���m_nStu����¼��Ӧѧ�����������
	this->m_nStu = ((CInforSheet*)GetParent())->m_nStu;
	
	if(arrStu[m_nStu]->testPackIndex == -1)  //������δ��¼ ֱ�ӷ���
	{
		return TRUE;
	}



	CString str;
	for(int n = 0;n<3;n++)
	{
		if(g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandFill[n] != -1)
		{
			//�б�����һ��Ԫ��
			str.Format("����� %d",n+1);
			m_CBList.AddString(str);
			//����Ӧ�Ŀ�������⿼�����ָ�븴�Ƶ���Ӧλ��
			m_Test[nIndex]   = arrStu[m_nStu]->StuAnswerFill[n];
			m_TestPK[nIndex] = arrStu[m_nStu]->GetTestStr(0,
				g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandFill[n],1); 
			nIndex++;//�������������1
		}

		if(g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandModify[n] != -1)
		{
			str.Format("�Ĵ��� %d",n+1);
			m_CBList.AddString(str);
			m_Test[nIndex]   = arrStu[m_nStu]->StuAnswerModify[n];
			m_TestPK[nIndex] = arrStu[m_nStu]->GetTestStr(1,
				g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandModify[n],1);
			nIndex++;
		}

		if(g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandDesign[n] != -1)
		{
			str.Format("����� %d",n+1);
			m_CBList.AddString(str);
			m_Test[nIndex]   =  arrStu[m_nStu]->StuAnswerDesign[n];
			m_TestPK[nIndex] =  arrStu[m_nStu]->GetTestStr(2,
				g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandDesign[n],1);
			nIndex++;
		}
	}


	return TRUE;
}


void CTestPage::OnSelChange()
{
	int nIndex = m_CBList.GetCurSel();
	if(nIndex != LB_ERR)
	{
		if(m_Test[nIndex] != NULL)
		{
			m_EditTest.SetWindowText(m_Test[nIndex]);
			m_EditPK.SetWindowText(m_TestPK[nIndex]);
		}
		else
		{
			m_EditTest.SetWindowText("����Ϣ��");
			m_EditPK.SetWindowText("����Ϣ��");
		}


		
	}
}
