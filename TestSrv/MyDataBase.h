/////////////////////////////////////////////////////////////////////
//类名：CMyDataBase
//说明：应用程序数据库类
//功能：封装所有对数据库的操作。
//      考生，考题等信息读取与导出        
//作者：郭承(gc5084@163.com)
//组织：图形图像研究所
//日期：2009.03
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
						//连接com组件
    _ConnectionPtr  m_pConnection;
						//记录集com组件	
	_RecordsetPtr m_pRecordset;
								
public:
	//记录学生总数
	int nStudent;

	//各试题题总数


};

#endif // !defined(AFX_MYDATABASE_H__B50C9E25_C42F_4248_86AC_7ECCE78C42A2__INCLUDED_)
