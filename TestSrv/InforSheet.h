/////////////////////////////////////////////////////////////////////
//������CInforSheet
//˵����ѧ����Ϣ���Ա���
//���ܣ����ؿ�����Ϣ������ҳ
//���ߣ�����(gc5084@163.com)
//��֯��ͼ��ͼ���о���
//���ڣ�2009.03
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFORSHEET_H__EA9C6CEF_C990_4B36_9FAB_866CD5687E6F__INCLUDED_)
#define AFX_INFORSHEET_H__EA9C6CEF_C990_4B36_9FAB_866CD5687E6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StuPage.h"
#include "TestPage.h"
#include "PointPage.h"

class CInforSheet : public CPropertySheet  
{
public:
	CInforSheet(LPCTSTR pszCaption,CWnd* pParent);
	CInforSheet(LPCTSTR pszCaption,char* czNumber);
	virtual ~CInforSheet();

	CStuPage     m_StuPage;
	             //ѧ��������Ϣҳ
	CTestPage    m_TestPage;
	             //ѧ��������Ϣҳ
	CPointPage   m_PointPage;
	             //ѧ���ɼ���Ϣҳ
	int          m_nStu;
	             //ѧ���������� ��־��Ӧ��ѧ��



};

#endif // !defined(AFX_INFORSHEET_H__EA9C6CEF_C990_4B36_9FAB_866CD5687E6F__INCLUDED_)
