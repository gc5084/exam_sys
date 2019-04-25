// UnlockDlg.h: interface for the CUnlockDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNLOCKDLG_H__FAA88307_FB43_4061_A0EF_A462ED240129__INCLUDED_)
#define AFX_UNLOCKDLG_H__FAA88307_FB43_4061_A0EF_A462ED240129__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SrvMainWnd.h"

class CUnlockDlg : public CDialog  
{
public:
	CUnlockDlg(CMainWindow* pParent);
	virtual ~CUnlockDlg();

	
	virtual void OnOK();
	virtual void OnCancel();

	enum { IDD = IDD_UNLOCK };
protected:
	virtual void DoDataExchange(CDataExchange*);

	CString strCorrectPass;     //���������ڴ�������ȷ����

	CEdit m_EditPass;           //��������ؼ�
};

#endif // !defined(AFX_UNLOCKDLG_H__FAA88307_FB43_4061_A0EF_A462ED240129__INCLUDED_)
