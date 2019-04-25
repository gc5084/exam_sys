// TimeDlg.h: interface for the CTimeDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMEDLG_H__17C2D32C_0B56_44D2_BFE1_6950DEA9053F__INCLUDED_)
#define AFX_TIMEDLG_H__17C2D32C_0B56_44D2_BFE1_6950DEA9053F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SrvMainWnd.h"

class CTimeDlg : public CDialog  
{
public:
	CTimeDlg(CWnd* pParent);
	virtual ~CTimeDlg();

	virtual void OnOK();

	enum { IDD = IDD_TIMEDLG };
protected:
	CMainWindow* m_pParent;

};

#endif // !defined(AFX_TIMEDLG_H__17C2D32C_0B56_44D2_BFE1_6950DEA9053F__INCLUDED_)
