// Design.h: interface for the CDesign class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESIGN_H__37AE2C9D_667C_43EC_A6F0_BD4666B0D618__INCLUDED_)
#define AFX_DESIGN_H__37AE2C9D_667C_43EC_A6F0_BD4666B0D618__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Base.h"

class CDesign : public CBase  
{
public:
	CDesign(_ConnectionPtr  m_pConnection);
	virtual ~CDesign();

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

#endif // !defined(AFX_DESIGN_H__37AE2C9D_667C_43EC_A6F0_BD4666B0D618__INCLUDED_)
