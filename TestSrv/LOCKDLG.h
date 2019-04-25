// LOCKDLG.h: interface for the CLOCKDLG class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCKDLG_H__396FB6EE_5F12_4B39_BF00_E5DBF5E2811C__INCLUDED_)
#define AFX_LOCKDLG_H__396FB6EE_5F12_4B39_BF00_E5DBF5E2811C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SrvMainWnd.h"

class CLOCKDLG : public CDialog  
{
public:
	CLOCKDLG(CMainWindow* pParent);
	virtual ~CLOCKDLG();

	virtual void OnOK();

	enum { IDD = IDD_LOCK };
protected:

	virtual void DoDataExchange(CDataExchange*);

	CEdit        m_Password; //√‹¬Î
	CEdit        m_RePass;   //√‹¬Î»∑»œ

	CMainWindow* m_pParent;
};

#endif // !defined(AFX_LOCKDLG_H__396FB6EE_5F12_4B39_BF00_E5DBF5E2811C__INCLUDED_)
