// MuchTestDlg.h: interface for the CMuchTestDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUCHTESTDLG_H__13504FFA_4427_4FA7_BE66_1FB52C90E32A__INCLUDED_)
#define AFX_MUCHTESTDLG_H__13504FFA_4427_4FA7_BE66_1FB52C90E32A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SrvMainWnd.h"

class CMuchTestDlg : public CDialog  
{
public:
    CMuchTestDlg(CWnd* pParent);
	virtual ~CMuchTestDlg();

	virtual void OnOK();

	enum { IDD = IDD_MUCHTEST };

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange*);

	CMainWindow* m_pParent;

	      
	int          m_nTestMax[3];    
	//3中题型每个题型的总题数 索引0 为选择题 1 为改错 2为设计

	CStatic       m_TextFill;   //填空题的提示文本（个数范围）

	CStatic       m_TextModify; //改错题的提示文本（个数范围）

	CStatic       m_TextDesign; //设计题的提示文本（个数范围）

};

#endif // !defined(AFX_MUCHTESTDLG_H__13504FFA_4427_4FA7_BE66_1FB52C90E32A__INCLUDED_)
