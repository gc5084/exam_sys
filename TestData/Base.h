// Base.h: interface for the CBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE_H__E0D667EC_A89F_43DA_8375_537FD26FCF1F__INCLUDED_)
#define AFX_BASE_H__E0D667EC_A89F_43DA_8375_537FD26FCF1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBase : public CObject  
{
protected:
	_ConnectionPtr  m_pConnection;
	_RecordsetPtr m_pRecordset;

public:
	CBase(_ConnectionPtr pConnection);
	virtual ~CBase();

    virtual BOOL Show(CEdit* pEdit,int nIndex,CString);
	virtual BOOL List(CListBox* pList);
	virtual BOOL Delete(int nIndex);
	virtual BOOL SetPcon(_ConnectionPtr  m_pCon);
	virtual BOOL Input(CEdit* pEdit,int nIndex,CString str);
	virtual int  account();
	virtual int  WhereIn();
	virtual int  NtoP(int n);
	virtual BOOL CreateNew(int p);
	virtual void Check(int n);
	virtual BOOL CheckOver(int n);


};

#endif // !defined(AFX_BASE_H__E0D667EC_A89F_43DA_8375_537FD26FCF1F__INCLUDED_)
