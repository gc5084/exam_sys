/////////////////////////////////////////////////////////////////////
//类名：CInforSheet
//说明：学生信息属性表单类
//功能：承载考生信息的属性页
//作者：郭承(gc5084@163.com)
//组织：图形图像研究所
//日期：2009.03
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFORSHEET_H__EA9C6CEF_C990_4B36_9FAB_866CD5687E6F__INCLUDED_)
#define AFX_INFORSHEET_H__EA9C6CEF_C990_4B36_9FAB_866CD5687E6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StuPage.h"
#include "TestPage.h"
#include "PointPage.h"

class CInforSheet : public CPropertySheet  
{
public:
	CInforSheet(LPCTSTR pszCaption,CWnd* pParent);
	CInforSheet(LPCTSTR pszCaption,char* czNumber);
	virtual ~CInforSheet();

	CStuPage     m_StuPage;
	             //学生基本信息页
	CTestPage    m_TestPage;
	             //学生试题信息页
	CPointPage   m_PointPage;
	             //学生成绩信息页
	int          m_nStu;
	             //学生数组索引 标志对应的学生



};

#endif // !defined(AFX_INFORSHEET_H__EA9C6CEF_C990_4B36_9FAB_866CD5687E6F__INCLUDED_)
