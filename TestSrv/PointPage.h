/////////////////////////////////////////////////////////////////////
//������CPointPage
//˵����������Ϣ�ɼ�����ҳ
//���ܣ���ʾ��������ĶԴ� �ͼ��㲢��ʾ�������ܷ�       
//���ߣ�����(gc5084@163.com)
//��֯��ͼ��ͼ���о���
//���ڣ�2009.03
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTPAGE_H__637982F4_301A_47F3_9CAF_372872294D99__INCLUDED_)
#define AFX_POINTPAGE_H__637982F4_301A_47F3_9CAF_372872294D99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPointPage : public CPropertyPage  
{
public:
	CPointPage();
	virtual ~CPointPage();

	enum {IDD = IDD_POINTINFOR};
protected:

	virtual void DoDataExchange(CDataExchange*);

	virtual BOOL OnInitDialog();
protected:
	int        m_nStu;         //ѧ����������
	CListBox   m_ListBox;      //�б�����


};

#endif // !defined(AFX_POINTPAGE_H__637982F4_301A_47F3_9CAF_372872294D99__INCLUDED_)
