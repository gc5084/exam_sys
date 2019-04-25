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
	//3������ÿ�����͵������� ����0 Ϊѡ���� 1 Ϊ�Ĵ� 2Ϊ���

	CStatic       m_TextFill;   //��������ʾ�ı���������Χ��

	CStatic       m_TextModify; //�Ĵ������ʾ�ı���������Χ��

	CStatic       m_TextDesign; //��������ʾ�ı���������Χ��

};

#endif // !defined(AFX_MUCHTESTDLG_H__13504FFA_4427_4FA7_BE66_1FB52C90E32A__INCLUDED_)
