// Base.cpp: implementation of the CBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestData.h"
#include "Base.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBase::CBase(_ConnectionPtr pConnection)
{
    m_pConnection = pConnection;
}

CBase::~CBase()
{

}

BOOL CBase::Show(CEdit* Edit,int nIndex,CString str)
{
	return TRUE;
}


BOOL CBase::List(CListBox* pList)
{
	return TRUE;
}

BOOL CBase::Delete(int nIndex)
{
	return TRUE;
}

BOOL CBase::SetPcon(_ConnectionPtr  m_pCon)
{
	return TRUE;
}

BOOL CBase::Input(CEdit* pEdit,int nIndex,CString str)
{
    return TRUE;
}

int  CBase::account()
{
	return 0;
}
BOOL CBase::CreateNew(int p)
{
	return FALSE;
}

int CBase::NtoP(int n)
{
	return 0;
}

int CBase::WhereIn()
{
	return 0;
}

void CBase::Check(int n)
{
}

BOOL CBase::CheckOver(int n)
{
	return FALSE;
}