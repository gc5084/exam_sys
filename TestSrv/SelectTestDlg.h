/////////////////////////////////////////////////////////////////////
//������CSelectTestDlg
//˵����ѡ�������
//���ܣ�����������Ӧ���������ȫ���г����޳������ڱ��ο����г��ֵ�����       
//���ߣ�����(gc5084@163.com)
//��֯��ͼ��ͼ���о���
//���ڣ�2009.03
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELECTTESTDLG_H__08A8E4AC_314D_4DE8_9130_9B8C2A6AC7F7__INCLUDED_)
#define AFX_SELECTTESTDLG_H__08A8E4AC_314D_4DE8_9130_9B8C2A6AC7F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SrvMyApp.h"
class CSelectTestDlg : public CDialog  
{
public:
	CSelectTestDlg(CWnd* pParent);
	virtual ~CSelectTestDlg();

	enum { IDD = IDD_SELECTTEST };

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange*);

	virtual void OnCancel();
	
	afx_msg void OnSelChange();
	afx_msg void OnDelect();
	afx_msg void OnAdd();

protected:
	CListBox    m_ListSelect;    //ѡ�������б��
	CListBox    m_ListUnSelect;  //δ��ѡ�������б��
	CComboBox   m_ComboBox;      //��������ѡ���б�
	CButton     m_ButtonDelect;  //ɾ����δ��ѡ�������б��
	CButton     m_ButtonAdd;     //�ָ���ѡ�������б��
	int         nSelect;         //���浱ǰ���Ǹ�������

	//���汻ɾ��δѡ���б�����������
	CList<MemoryData,MemoryData>   m_listUnSelectFill; //�����
	CList<MemoryData,MemoryData>   m_listUnSelectModify; //�Ĵ���
	CList<MemoryData,MemoryData>   m_listUnSelectDesign; //�����

	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_SELECTTESTDLG_H__08A8E4AC_314D_4DE8_9130_9B8C2A6AC7F7__INCLUDED_)
