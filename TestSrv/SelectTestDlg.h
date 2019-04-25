/////////////////////////////////////////////////////////////////////
//类名：CSelectTestDlg
//说明：选择出题类
//功能：将加载如相应链表的试题全部列出，剔除不想在本次考试中出现的试题       
//作者：郭承(gc5084@163.com)
//组织：图形图像研究所
//日期：2009.03
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELECTTESTDLG_H__08A8E4AC_314D_4DE8_9130_9B8C2A6AC7F7__INCLUDED_)
#define AFX_SELECTTESTDLG_H__08A8E4AC_314D_4DE8_9130_9B8C2A6AC7F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SrvMyApp.h"
class CSelectTestDlg : public CDialog  
{
public:
	CSelectTestDlg(CWnd* pParent);
	virtual ~CSelectTestDlg();

	enum { IDD = IDD_SELECTTEST };

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange*);

	virtual void OnCancel();
	
	afx_msg void OnSelChange();
	afx_msg void OnDelect();
	afx_msg void OnAdd();

protected:
	CListBox    m_ListSelect;    //选中试题列表框
	CListBox    m_ListUnSelect;  //未被选中试题列表框
	CComboBox   m_ComboBox;      //试题类型选择列表
	CButton     m_ButtonDelect;  //删除到未被选中试题列表框
	CButton     m_ButtonAdd;     //恢复到选中试题列表框
	int         nSelect;         //保存当前在那个题型下

	//保存被删到未选择列表框的试题链表
	CList<MemoryData,MemoryData>   m_listUnSelectFill; //填空题
	CList<MemoryData,MemoryData>   m_listUnSelectModify; //改错题
	CList<MemoryData,MemoryData>   m_listUnSelectDesign; //设计题

	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_SELECTTESTDLG_H__08A8E4AC_314D_4DE8_9130_9B8C2A6AC7F7__INCLUDED_)
