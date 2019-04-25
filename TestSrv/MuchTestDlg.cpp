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

	//将这次考试中每种题型总共的数量赋给m_nTestMax数组
	m_nTestMax[0] = listTestFill.GetCount();   //填空题
	m_nTestMax[1] = listTestModify.GetCount(); //改错题
	m_nTestMax[2] = listTestDesign.GetCount(); //设计题 


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
		str.Format("填空题个数应该在0 ～ %d 之间",m_nTestMax[0]);
		AfxMessageBox(str);
		return;
	}

	nTest[1] = (int)GetDlgItemInt(IDC_EDITMODIFY);
	if((nTest[1]<0)||(nTest[1]>m_nTestMax[1]))
	{
		str.Format("改错题个数应该在0 ～ %d 之间",m_nTestMax[1]);
		AfxMessageBox(str);
		return;
	}

	nTest[2] = (int)GetDlgItemInt(IDC_EDITDESIGN);
	if((nTest[2]<0)||(nTest[2]>m_nTestMax[2]))
	{
		str.Format("填空题个数应该在0 ～ %d 之间",m_nTestMax[2]);
		AfxMessageBox(str);
		return;
	}
	//总和是否为零
	if((nTest[0]+nTest[1]+nTest[2]) == 0)
	{
		AfxMessageBox("试题个数相加应该大于0");
		return;
	}

	//复制给主窗口类
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

	//设置每个题型的输入范围提示文本
	CString str;
	//填空题
	if(m_nTestMax[0] > 3)
	{
		m_nTestMax[0] = 3;
	}
	str.Format("（0～%d）",this->m_nTestMax[0]);
	this->m_TextFill.SetWindowText(str);

	//改错题
	if(m_nTestMax[1] > 3)
	{
		m_nTestMax[1] = 3;
	}
	str.Format("（0～%d）",this->m_nTestMax[1]);
	this->m_TextModify.SetWindowText(str);

	//设计题
	if(m_nTestMax[2] > 3)
	{
		m_nTestMax[2] = 3;
	}
	str.Format("（0～%d）",this->m_nTestMax[2]);
	this->m_TextDesign.SetWindowText(str);

	return TRUE; 
}