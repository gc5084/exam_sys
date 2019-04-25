/////////////////////////////////////////////////////////////////////
//类名：CPointPage
//说明：考生信息成绩属性页
//功能：显示考生各题的对错 和计算并显示考生的总分       
//作者：郭承(gc5084@163.com)
//组织：图形图像研究所
//日期：2009.03
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTPAGE_H__637982F4_301A_47F3_9CAF_372872294D99__INCLUDED_)
#define AFX_POINTPAGE_H__637982F4_301A_47F3_9CAF_372872294D99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPointPage : public CPropertyPage  
{
public:
	CPointPage();
	virtual ~CPointPage();

	enum {IDD = IDD_POINTINFOR};
protected:

	virtual void DoDataExchange(CDataExchange*);

	virtual BOOL OnInitDialog();
protected:
	int        m_nStu;         //学生数组索引
	CListBox   m_ListBox;      //列表框变量


};

#endif // !defined(AFX_POINTPAGE_H__637982F4_301A_47F3_9CAF_372872294D99__INCLUDED_)
