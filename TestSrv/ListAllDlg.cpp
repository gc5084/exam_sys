// ListAllDlg.cpp: implementation of the CListAllDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ListAllDlg.h"
#include "SrvMyApp.h"
#include "StuInfor.h"
#include "SrvMainWnd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CStuInfor* arrStu[MAXNUM];
CListAllDlg::CListAllDlg(CWnd* pParent)
      : CDialog(CListAllDlg::IDD,pParent)
{
	this->nFill = ((CMainWindow*)pParent)->nMuchTest[0];
	this->nModify = ((CMainWindow*)pParent)->nMuchTest[1];
	this->nDesign = ((CMainWindow*)pParent)->nMuchTest[2];
}

CListAllDlg::~CListAllDlg()
{

}

void CListAllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_LIST,m_ListCtrl);
}

BOOL CListAllDlg::OnInitDialog()
{
	
	CDialog::OnInitDialog();
	int i;
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle()|
		LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);


	//设置属性列 共12列 列名如szColumn
	char *szColumn[]={"学号","姓名","填空题1","填空题2","填空题3",
		"改错题1","改错题2","改错题3","设计题1","设计题2","设计题3","总分"};
    LV_COLUMN lvc;
	//LVCF_FMT:The fmt member is valid. 
    lvc.mask=LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
    lvc.fmt=LVCFMT_LEFT;
	for(i = 0;i<12;i++)
	{
		if(i == 0)
			lvc.cx = 100;//列宽
		else
			lvc.cx =60;
		lvc.pszText=szColumn[i];
		lvc.iSubItem = i;
		m_ListCtrl.InsertColumn(i,&lvc);
	}


	CString str;
	for(i=0;i<MAXNUM;i++)
	{
		if(arrStu[i] != NULL)
		{
			m_ListCtrl.InsertItem(i,arrStu[i]->strNum);
			//添加每行各项
		    //m_ListCtrl.SetItemText(i,5,"sss");
			//考生姓名
			m_ListCtrl.SetItemText(i,1,arrStu[i]->strName);
			//填空题
			str.Format("%d",arrStu[i]->StuCorrectFill[0]);
			m_ListCtrl.SetItemText(i,2,str);
			str.Format("%d",arrStu[i]->StuCorrectFill[1]);
			m_ListCtrl.SetItemText(i,3,str);
			str.Format("%d",arrStu[i]->StuCorrectFill[2]);
			m_ListCtrl.SetItemText(i,4,str);
			//改错题
			str.Format("%d",arrStu[i]->StuCorrectModify[0]);
			m_ListCtrl.SetItemText(i,5,str);
			str.Format("%d",arrStu[i]->StuCorrectModify[1]);
			m_ListCtrl.SetItemText(i,6,str);
			str.Format("%d",arrStu[i]->StuCorrectModify[2]);
			m_ListCtrl.SetItemText(i,7,str);
			//设计题
			str.Format("%d",arrStu[i]->StuCorrectDesign[0]);
			m_ListCtrl.SetItemText(i,8,str);
			str.Format("%d",arrStu[i]->StuCorrectDesign[1]);
			m_ListCtrl.SetItemText(i,9,str);
			str.Format("%d",arrStu[i]->StuCorrectDesign[2]);
			m_ListCtrl.SetItemText(i,10,str);
			//显示总分
			str.Format("%d 分",arrStu[i]->nAllPoint);
			m_ListCtrl.SetItemText(i,11,str);

		}
		else
			break;//数组到结尾了 跳出
		
	}
    

	return TRUE;
}