/////////////////////////////////////////////////////////////////////
//������CCheckDlg
//˵�����������Ի�����
//���ܣ�������п������Ĵ��
//���ߣ�����(gc5084@163.com)
//��֯��ͼ��ͼ���о���
//���ڣ�2009.03
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKDLG_H__D42936C5_F1FF_45FD_98C0_8972A7CB1A31__INCLUDED_)
#define AFX_CHECKDLG_H__D42936C5_F1FF_45FD_98C0_8972A7CB1A31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SrvMainWnd.h"

class CCheckDlg : public CDialog  
{
public:
	CCheckDlg(CWnd* pParent);
	virtual ~CCheckDlg();
	virtual void OnOK();

	enum {IDD = IDD_CHECKDLG};
protected:
	CMainWindow* m_pParent;

	int          nStu;//��¼�ж�����ѧ���ѽ��� ���ڽ�������������ʾ

	CStatic*       m_pStatic;
	CProgressCtrl* m_pProgressCtrl;

	virtual BOOL OnInitDialog();


};

#endif // !defined(AFX_CHECKDLG_H__D42936C5_F1FF_45FD_98C0_8972A7CB1A31__INCLUDED_)
