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


	//���������� ��12�� ������szColumn
	char *szColumn[]={"ѧ��","����","�����1","�����2","�����3",
		"�Ĵ���1","�Ĵ���2","�Ĵ���3","�����1","�����2","�����3","�ܷ�"};
    LV_COLUMN lvc;
	//LVCF_FMT:The fmt member is valid. 
    lvc.mask=LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
    lvc.fmt=LVCFMT_LEFT;
	for(i = 0;i<12;i++)
	{
		if(i == 0)
			lvc.cx = 100;//�п�
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
			//���ÿ�и���
		    //m_ListCtrl.SetItemText(i,5,"sss");
			//��������
			m_ListCtrl.SetItemText(i,1,arrStu[i]->strName);
			//�����
			str.Format("%d",arrStu[i]->StuCorrectFill[0]);
			m_ListCtrl.SetItemText(i,2,str);
			str.Format("%d",arrStu[i]->StuCorrectFill[1]);
			m_ListCtrl.SetItemText(i,3,str);
			str.Format("%d",arrStu[i]->StuCorrectFill[2]);
			m_ListCtrl.SetItemText(i,4,str);
			//�Ĵ���
			str.Format("%d",arrStu[i]->StuCorrectModify[0]);
			m_ListCtrl.SetItemText(i,5,str);
			str.Format("%d",arrStu[i]->StuCorrectModify[1]);
			m_ListCtrl.SetItemText(i,6,str);
			str.Format("%d",arrStu[i]->StuCorrectModify[2]);
			m_ListCtrl.SetItemText(i,7,str);
			//�����
			str.Format("%d",arrStu[i]->StuCorrectDesign[0]);
			m_ListCtrl.SetItemText(i,8,str);
			str.Format("%d",arrStu[i]->StuCorrectDesign[1]);
			m_ListCtrl.SetItemText(i,9,str);
			str.Format("%d",arrStu[i]->StuCorrectDesign[2]);
			m_ListCtrl.SetItemText(i,10,str);
			//��ʾ�ܷ�
			str.Format("%d ��",arrStu[i]->nAllPoint);
			m_ListCtrl.SetItemText(i,11,str);

		}
		else
			break;//���鵽��β�� ����
		
	}
    

	return TRUE;
}