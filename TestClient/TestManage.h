// TestManage.h: interface for the CTestManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTMANAGE_H__283EA69E_FED7_4885_9682_0E95DC3988A7__INCLUDED_)
#define AFX_TESTMANAGE_H__283EA69E_FED7_4885_9682_0E95DC3988A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestManage  
{
public:
	CTestManage();
	virtual ~CTestManage();

    BOOL InputText(char* Buffer);
	BOOL InputFile(char* Buffer,int MajorFlag);
	void ReadDescribeFile();
protected:
	char* m_szAppPath;            //应用程序路径
	char* Describe[3][3];

};

#endif // !defined(AFX_TESTMANAGE_H__283EA69E_FED7_4885_9682_0E95DC3988A7__INCLUDED_)
