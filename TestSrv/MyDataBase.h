/////////////////////////////////////////////////////////////////////
//������CMyDataBase
//˵����Ӧ�ó������ݿ���
//���ܣ���װ���ж����ݿ�Ĳ�����
//      �������������Ϣ��ȡ�뵼��        
//���ߣ�����(gc5084@163.com)
//��֯��ͼ��ͼ���о���
//���ڣ�2009.03
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDATABASE_H__B50C9E25_C42F_4248_86AC_7ECCE78C42A2__INCLUDED_)
#define AFX_MYDATABASE_H__B50C9E25_C42F_4248_86AC_7ECCE78C42A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyDataBase  
{
public:
	CMyDataBase();
	virtual ~CMyDataBase();
	BOOL virtual ConnectSQL();
	BOOL virtual CloseSQL();
	BOOL virtual ConnectExcel(CString strPathName);
	BOOL virtual CloseExcel();
	BOOL virtual LoadTest();
	BOOL virtual LoadStudent();
	BOOL virtual LoadStudentExcel();
	BOOL virtual CloseDataBase();
	BOOL virtual OutExcel(CString strPathName);
protected:
						//����com���
    _ConnectionPtr  m_pConnection;
						//��¼��com���	
	_RecordsetPtr m_pRecordset;
								
public:
	//��¼ѧ������
	int nStudent;

	//������������


};

#endif // !defined(AFX_MYDATABASE_H__B50C9E25_C42F_4248_86AC_7ECCE78C42A2__INCLUDED_)
