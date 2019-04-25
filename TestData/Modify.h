// Modify.h: interface for the CModify class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODIFY_H__623871DC_083C_4507_AA6D_FF8FE80BE18F__INCLUDED_)
#define AFX_MODIFY_H__623871DC_083C_4507_AA6D_FF8FE80BE18F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Base.h"

class CModify : public CBase  
{
public:
	CModify(_ConnectionPtr  m_pConnection);
	virtual ~CModify();

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

#endif // !defined(AFX_MODIFY_H__623871DC_083C_4507_AA6D_FF8FE80BE18F__INCLUDED_)
