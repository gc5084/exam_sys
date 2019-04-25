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
	int nIndex = 0;//m_Test，m_TestPK的索引。检索到有一个题填充相应指针再自增一下
	CDialog::OnInitDialog();
	//得到父类属性表单的m_nStu，记录相应学生数组的索引
	this->m_nStu = ((CInforSheet*)GetParent())->m_nStu;
	
	if(arrStu[m_nStu]->testPackIndex == -1)  //考生还未登录 直接返回
	{
		return TRUE;
	}



	CString str;
	for(int n = 0;n<3;n++)
	{
		if(g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandFill[n] != -1)
		{
			//列表框添加一行元素
			str.Format("填空题 %d",n+1);
			m_CBList.AddString(str);
			//将对应的考生填空题考生答卷指针复制到相应位置
			m_Test[nIndex]   = arrStu[m_nStu]->StuAnswerFill[n];
			m_TestPK[nIndex] = arrStu[m_nStu]->GetTestStr(0,
				g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandFill[n],1); 
			nIndex++;//考生答卷索引增1
		}

		if(g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandModify[n] != -1)
		{
			str.Format("改错题 %d",n+1);
			m_CBList.AddString(str);
			m_Test[nIndex]   = arrStu[m_nStu]->StuAnswerModify[n];
			m_TestPK[nIndex] = arrStu[m_nStu]->GetTestStr(1,
				g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandModify[n],1);
			nIndex++;
		}

		if(g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandDesign[n] != -1)
		{
			str.Format("设计题 %d",n+1);
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
			m_EditTest.SetWindowText("无信息！");
			m_EditPK.SetWindowText("无信息！");
		}


		
	}
}
