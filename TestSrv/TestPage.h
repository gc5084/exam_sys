// TestPage.h: interface for the CTestPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPAGE_H__1AD61325_1C1F_4180_97A3_454AF77BE703__INCLUDED_)
#define AFX_TESTPAGE_H__1AD61325_1C1F_4180_97A3_454AF77BE703__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestPage : public CPropertyPage 
{
public:
	CTestPage();
	virtual ~CTestPage();

	enum {IDD = IDD_TESTINFOR};
protected:
	virtual void DoDataExchange(CDataExchange*);

	virtual BOOL OnInitDialog();
	virtual void OnSelChange();
protected:
	int          m_nStu;         //ѧ����������
	CEdit        m_EditTest;     //�༭����ʾ�������
	CEdit        m_EditPK;       //�༭����ʾ����Ӧ���Ծ���ţ�������
	CComboBox    m_CBList;       //����б��
	char*        m_Test[9];      //��¼��Ӧ���б�Ŀ����Ͻ��Ծ��ָ�� ������ʾ��ֻ���༭��
	char*        m_TestPK[9];    //��¼�Ͻ��Ծ��Ӧ������������ָ��

DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_TESTPAGE_H__1AD61325_1C1F_4180_97A3_454AF77BE703__INCLUDED_)
