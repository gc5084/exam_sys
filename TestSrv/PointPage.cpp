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
	int nCorrect = 0;//记录有几个试题答对了
	this->m_nStu = ((CInforSheet*)GetParent())->m_nStu;

	for(int n=0;n<3;n++)
	{
		if(g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandFill[n] != -1)
		{
			//格式化字符串
			if(arrStu[m_nStu]->StuAnswerFill[n] ==NULL)//上交试卷为空
			{
				str.Format("填空题第%d题     考生还未交卷",n+1);
			}
			else if(arrStu[m_nStu]->StuCorrectFill[n] == 0)
			{
				str.Format("填空题第%d题     试题未批阅",n+1);
			}
			else if(arrStu[m_nStu]->StuCorrectFill[n] == 1)
			{
				str.Format("填空题第%d题     正确",n+1);
				//正确数加1
				nCorrect++;
			}
			else if(arrStu[m_nStu]->StuCorrectFill[n] == 2)
			{
				str.Format("填空题第%d题     错误",n+1);
			}
			else
			{
				str.Format("异常！");
			}

			//添加字符串于列表
			m_ListBox.AddString(str);
		}

		if(g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandModify[n] != -1)
		{
			if(arrStu[m_nStu]->StuAnswerModify[n] ==NULL)//上交试卷为空
			{
				str.Format("改错题第%d题     考生还未交卷",n+1);
			}
			else if(arrStu[m_nStu]->StuCorrectModify[n] == 0)
			{
				str.Format("改错题第%d题     试题未批阅",n+1);
			}
			else if(arrStu[m_nStu]->StuCorrectModify[n] == 1)
			{
				str.Format("改错题第%d题     正确",n+1);
				//正确数加1
				nCorrect++;
			}
			else if(arrStu[m_nStu]->StuCorrectModify[n] == 2)
			{
				str.Format("改错题第%d题     错误",n+1);
			}
			else
			{
				str.Format("异常！");
			}
			
			m_ListBox.AddString(str);
		}

		if(g_sendTestData[arrStu[m_nStu]->testPackIndex].nRandDesign[n] != -1)
		{
			if(arrStu[m_nStu]->StuAnswerDesign[n] ==NULL)//上交试卷为空
			{
				str.Format("设计题第%d题     考生还未交卷",n+1);
			}
			else if(arrStu[m_nStu]->StuCorrectDesign[n] == 0)
			{
				str.Format("设计题第%d题     试题未批阅",n+1);
			}
			else if(arrStu[m_nStu]->StuCorrectDesign[n] == 1)
			{
				str.Format("设计题第%d题     正确",n+1);
				//正确数加1
				nCorrect++;
			}
			else if(arrStu[m_nStu]->StuCorrectDesign[n] == 2)
			{
				str.Format("设计题第%d题     错误",n+1);
			}
			else
			{
				str.Format("异常！");
			}
			
			m_ListBox.AddString(str);
		}
	}


	//显示总分
	if(m_ListBox.GetCount() == 0)
	{
		m_ListBox.AddString("试题数为零，可能考试还未开始");
	}
	else
	{
		str.Format("该考生的总分为 %d",arrStu[m_nStu]->nAllPoint);
		m_ListBox.AddString("");
		m_ListBox.AddString(str);
	}

	return TRUE;
}