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
	this->m_pParent = (CMainWindow*)pParent; //获取主窗口指针
	nStu = 0; //已交卷人数初始化为0

	//统计初始化人数
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

	int nNum = 0; //记录已经检查了几个人了
	CString str;
	//循环所有学生
	for(int n = 0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)
		{
			if(arrStu[n]->nState == 2) //状态为交卷则检查
			{
				arrStu[n]->CheckAllAnswer(); //检查该考生的所有试卷

				///界面更新
				nNum++; //检查人数加1
				str.Format("进度：%d人/ %d人",nNum,nStu);
				m_pStatic->SetWindowText(str);//显示进度条上的人数比
				m_pProgressCtrl->SetPos(nNum);//更新进度条进度

			}
		}

	}
	AfxMessageBox("阅卷完成");
	CDialog::OnOK();

}

BOOL CCheckDlg::OnInitDialog()
{

	CDialog::OnInitDialog();

	m_pProgressCtrl = ((CProgressCtrl*)GetDlgItem(IDC_PROGRESS));
	m_pProgressCtrl->SetRange(0,nStu);
														//进度条长度为0-nStu(已交卷人数)
	m_pProgressCtrl->SetPos(0);
	                                                    //初始位置设置0

	//显示一个字符串 在进度条上方 坐标是先拖个静态文本框试出来的
	CString str;
	str.Format("进度：0人 / %d人",nStu);
	m_pStatic = ((CStatic*)GetDlgItem(IDC_TEXT));
	if(m_pStatic != NULL)
	m_pStatic->SetWindowText(str);

	return TRUE;

}
