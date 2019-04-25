// SelectTestDlg.cpp: implementation of the CSelectTestDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SelectTestDlg.h"
#include "SrvMyApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CList<MemoryData,MemoryData>   listTestFill;										
extern CList<MemoryData,MemoryData>   listTestModify;
extern CList<MemoryData,MemoryData>   listTestDesign;

BEGIN_MESSAGE_MAP(CSelectTestDlg, CDialog)

	ON_CBN_SELCHANGE(IDC_COMBOBOX,OnSelChange)
	ON_BN_CLICKED(IDC_DELECT, OnDelect)
	ON_BN_CLICKED(IDC_ADD, OnAdd)

END_MESSAGE_MAP()

CSelectTestDlg::CSelectTestDlg(CWnd* pParent) : CDialog(CSelectTestDlg::IDD,pParent)
{
	this->nSelect = -1;
}

CSelectTestDlg::~CSelectTestDlg()
{
	//清楚链表内容
	m_listUnSelectFill.RemoveAll();
	m_listUnSelectModify.RemoveAll();
	m_listUnSelectDesign.RemoveAll();
}

void CSelectTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_SELECT,this->m_ListSelect);

	DDX_Control(pDX,IDC_UNSELECT,this->m_ListUnSelect);

	DDX_Control(pDX,IDC_COMBOBOX,this->m_ComboBox);

	DDX_Control(pDX,IDC_DELECT,this->m_ButtonDelect);

	DDX_Control(pDX,IDC_ADD,this->m_ButtonAdd);

}

BOOL CSelectTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

//	m_ListSelect.ModifyStyle(NULL,LBS_MULTIPLESEL);

	CString str;

	m_ComboBox.AddString("填空题");
	m_ComboBox.AddString("改错题");
	m_ComboBox.AddString("设计题");

	return TRUE;
}

void CSelectTestDlg::OnSelChange()
{
	//清空列表框原来项目
	m_ListSelect.ResetContent();
	m_ListUnSelect.ResetContent();

	//获得组合框列表选项
	int Item;
	Item = this->m_ComboBox.GetCurSel();

	POSITION pos;
	MemoryData TempMD;
	CString str;
	switch(Item)
	{
	case 0:   //填空题
		{
			//选择列表框列出项目
			pos = listTestFill.GetHeadPosition(); //获取头指针
			while(pos != NULL)
			{
				TempMD = listTestFill.GetNext(pos);//获取下一个元素
				str.Format("%s  %s",TempMD.PrimaryKey,TempMD.Remark);
				this->m_ListSelect.AddString(str);
			}

			//未选择列表框列出项目
			pos = this->m_listUnSelectFill.GetHeadPosition();
			while(pos != NULL)
			{
				TempMD = m_listUnSelectFill.GetNext(pos);
				str.Format("%s  %s",TempMD.PrimaryKey,TempMD.Remark);
				this->m_ListUnSelect.AddString(str);
			}
			nSelect = 0;//当前活动页为填空题
			break;
		}

	case 1:   //改错题
		{
			//选择列表框列出项目
			pos = listTestModify.GetHeadPosition(); //获取头指针
			while(pos != NULL)
			{
				TempMD = listTestModify.GetNext(pos);//获取下一个元素
				str.Format("%s  %s",TempMD.PrimaryKey,TempMD.Remark);
				this->m_ListSelect.AddString(str);
			}
			//未选择列表框列出项目
			pos = this->m_listUnSelectModify.GetHeadPosition();
			while(pos != NULL)
			{
				TempMD = m_listUnSelectModify.GetNext(pos);
				str.Format("%s  %s",TempMD.PrimaryKey,TempMD.Remark);
				this->m_ListUnSelect.AddString(str);
			}
			nSelect = 1;//当前活动页为改错题
			break;
		}

	case 2:   //设计题
		{
			
			//选择列表框列出项目
			pos = listTestDesign.GetHeadPosition(); //获取头指针
			while(pos != NULL)
			{
				TempMD = listTestDesign.GetNext(pos);//获取下一个元素
				str.Format("%s  %s",TempMD.PrimaryKey,TempMD.Remark);
				this->m_ListSelect.AddString(str);
			}
			//未选择列表框列出项目
			pos = this->m_listUnSelectDesign.GetHeadPosition();
			while(pos != NULL)
			{
				TempMD = m_listUnSelectDesign.GetNext(pos);
				str.Format("%s  %s",TempMD.PrimaryKey,TempMD.Remark);
				this->m_ListUnSelect.AddString(str);
			}
			nSelect = 2;//当前活动页为设计题
			break;
		}
	default:
		break;
	}
}

/*剔除键相应函数 将选择列表框选择的数据 剪切到 未选择列表框*/

void CSelectTestDlg::OnDelect()
{
	//获取别选择的项目索引 保存于aryListBoxSel中
	int nCount = this->m_ListSelect.GetSelCount();
	                                   //得到选择项目的数量
	CArray<int,int> aryListBoxSel;
	                       //定义一个整型数组用于存放选择项目的索引
	aryListBoxSel.SetSize(nCount);
                          //设置其大小为选择项目的数量
	m_ListSelect.GetSelItems(nCount, aryListBoxSel.GetData());
	                  //将项目索引存于aryListBoxSel ，GetData()提供数组的指针
	
	//按照数组中的索引删除试题链表中的项目并存于被删除列表
	int n,j; //循环变量
	POSITION pos;
	switch(nSelect)      //根据当前活动页确定操作哪那个链表
	{
	case 0:  //当前活动页为填空题
		for(n=0;n<nCount;n++)
		{
			pos = listTestFill.GetHeadPosition();

			//利用循环 吧pos循环到合适位置
			for(j=0;j<aryListBoxSel[n];j++)
			{
				listTestFill.GetNext(pos);	
			}

			//添加到未选择列表
			m_listUnSelectFill.AddTail(listTestFill.GetAt(pos));

			//在原列表中删除 
			listTestFill.RemoveAt(pos);//删除

			//链表中的当前元素将被删除 修改下一个位置中储存的索引
			if(n < nCount-1)//n已经是最后一个元素了
				aryListBoxSel[n+1] = aryListBoxSel[n+1] - (n+1);
				                            //(n+1) 已经有几个元素被删除
		}
		break;
	case 1:  //当前活动页为改错题
		for(n=0;n<nCount;n++)
		{
			pos = listTestModify.GetHeadPosition();

			//利用循环 吧pos循环到合适位置
			for(j=0;j<aryListBoxSel[n];j++)
			{
				listTestModify.GetNext(pos);
			}
			//添加到未选择列表
			m_listUnSelectModify.AddTail(listTestModify.GetAt(pos));

			//在原列表中删除 
			listTestModify.RemoveAt(pos);//删除

			//链表中的当前元素将被删除 修改下一个位置中储存的索引
			if(n < nCount-1)//n已经是最后一个元素了
				aryListBoxSel[n+1] = aryListBoxSel[n+1] - (n+1);
				                            //(n+1) 已经有几个元素被删除
		}
		break;
	case 2:
		for(n=0;n<nCount;n++)
		{
			pos = listTestDesign.GetHeadPosition();

			//利用循环 吧pos循环到合适位置
			for(j=0;j<aryListBoxSel[n];j++)
			{
				listTestDesign.GetNext(pos);
			}

			//添加到未选择列表
			m_listUnSelectDesign.AddTail(listTestDesign.GetAt(pos));

			//在原列表中删除 
			listTestDesign.RemoveAt(pos);//删除

			//链表中的当前元素将被删除 修改下一个位置中储存的索引
			if(n < nCount-1)//n已经是最后一个元素了
				aryListBoxSel[n+1] = aryListBoxSel[n+1] - (n+1);
				                            //(n+1) 已经有几个元素被删除
		}
		break;
	default:
		break;
	}

	//调用组合框选择函数刷新列表框
	OnSelChange();

	
}

/*恢复键相应函数 将未选择列表框选择的数据 剪切到 选择列表框*/
void CSelectTestDlg::OnAdd()
{
	//获取别选择的项目索引 保存于aryListBoxSel中
	int nCount = this->m_ListUnSelect.GetSelCount();
	                                   //得到未选择列表框选择项目的数量
	CArray<int,int> aryListBoxSel;
	                       //定义一个整型数组用于存放选择项目的索引
	aryListBoxSel.SetSize(nCount);
                          //设置其大小为选择项目的数量
	m_ListUnSelect.GetSelItems(nCount, aryListBoxSel.GetData());
	                  //将项目索引存于aryListBoxSel ，GetData()提供数组的指针
	
	//按照数组中的索引删除试题链表中的项目并存于被删除列表
	int n,j; //循环变量
	POSITION pos;
	switch(nSelect)      //根据当前活动页确定操作哪那个链表
	{
	case 0:  //当前活动页为填空题
		for(n=0;n<nCount;n++)
		{
			pos = m_listUnSelectFill.GetHeadPosition();

			//利用循环 吧pos循环到合适位置
			for(j=0;j<aryListBoxSel[n];j++)
			{
				m_listUnSelectFill.GetNext(pos);	
			}

			//添加到选择列表
			listTestFill.AddTail(m_listUnSelectFill.GetAt(pos));

			//在原列表中删除 
			m_listUnSelectFill.RemoveAt(pos);//删除

			//链表中的当前元素将被删除 修改下一个位置中储存的索引
			if(n < nCount-1)//n已经是最后一个元素了
				aryListBoxSel[n+1] = aryListBoxSel[n+1] - (n+1);
				                            //(n+1) 已经有几个元素被删除
		}
		break;
	case 1:  //当前活动页为改错题
		for(n=0;n<nCount;n++)
		{
			pos = m_listUnSelectModify.GetHeadPosition();

			//利用循环 吧pos循环到合适位置
			for(j=0;j<aryListBoxSel[n];j++)
			{
				m_listUnSelectModify.GetNext(pos);
			}
			//添加到未选择列表
			listTestModify.AddTail(m_listUnSelectModify.GetAt(pos));

			//在原列表中删除 
			m_listUnSelectModify.RemoveAt(pos);//删除

			//链表中的当前元素将被删除 修改下一个位置中储存的索引
			if(n < nCount-1)//n已经是最后一个元素了
				aryListBoxSel[n+1] = aryListBoxSel[n+1] - (n+1);
				                            //(n+1) 已经有几个元素被删除
		}
		break;
	case 2:
		for(n=0;n<nCount;n++)
		{
			pos = m_listUnSelectDesign.GetHeadPosition();

			//利用循环 吧pos循环到合适位置
			for(j=0;j<aryListBoxSel[n];j++)
			{
				m_listUnSelectDesign.GetNext(pos);
			}

			//添加到未选择列表
			listTestDesign.AddTail(m_listUnSelectDesign.GetAt(pos));

			//在原列表中删除 
			m_listUnSelectDesign.RemoveAt(pos);//删除

			//链表中的当前元素将被删除 修改下一个位置中储存的索引
			if(n < nCount-1)//n已经是最后一个元素了
				aryListBoxSel[n+1] = aryListBoxSel[n+1] - (n+1);
				                            //(n+1) 已经有几个元素被删除
		}
		break;
	default:
		break;
	}

	//调用组合框选择函数刷新列表框
	OnSelChange();
}

//覆盖OnCancel 使esc键不能取消对话框
void CSelectTestDlg::OnCancel()
{}

