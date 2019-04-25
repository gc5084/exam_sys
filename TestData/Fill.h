// Fill.h: interface for the CFill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILL_H__2C515EB9_E57B_49B8_AAEA_97686CEACE23__INCLUDED_)
#define AFX_FILL_H__2C515EB9_E57B_49B8_AAEA_97686CEACE23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
  CFill类继承于CBase类
  CFill类提供填空题的各项功能，如：显示，更改，删除
  本类于特定界面无关，只留控件指针为函数接口，用于和界面交流
  本类的函数直接操作数据库，所有与填空题数据库有关的操作都在本类中
*/

#include "Base.h"

class CFill : public CBase  
{
public:
	CFill(_ConnectionPtr  m_pConnection);
	virtual ~CFill();

	virtual BOOL Show(CEdit* pEdit,int nIndex,CString);
	virtual BOOL List(CListBox* pList);
	virtual BOOL Delete(int nIndex);
	virtual BOOL SetPcon(_ConnectionPtr  m_pCon);
	virtual BOOL Input(CEdit* pEdit,int nIndex,CString str);
	virtual int  account();
	virtual int  WhereIn();
	virtual int  NtoP(int n);
	virtual BOOL CreateNew(int p);
	virtual void Check(int p);
	virtual BOOL CheckOver(int n);

};

#endif // !defined(AFX_FILL_H__2C515EB9_E57B_49B8_AAEA_97686CEACE23__INCLUDED_)
