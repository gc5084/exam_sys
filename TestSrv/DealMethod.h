// DealMethod.h: interface for the CDealMethod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEALMETHOD_H__B54F61CC_9A82_48B3_BE3F_F164A0191344__INCLUDED_)
#define AFX_DEALMETHOD_H__B54F61CC_9A82_48B3_BE3F_F164A0191344__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDealMethod  
{
public:
	CDealMethod();
	virtual ~CDealMethod();

	BOOL DealNumberSure(char* czRecvPage,SOCKET sock);
	BOOL SendTime(int NowStudentIndex);
	BOOL SendTime(SOCKET sock);
	BOOL DealRequestTest(SOCKET sock);
	BOOL SendAllStuTest();
	BOOL TestOver(SOCKET sock);
	BOOL TestPackIndex(int pack,SOCKET sock);
	BOOL TiemUpdata(int time,SOCKET sock);
	

protected:
	int SearchStuIndex(char* czStuNumber);
	int SearchStuIndex(SOCKET sock);
	BOOL SendTest(int NowStudentIndex);
	BOOL CreateTestFile(CString fileName,char* fileContent);

	CString m_CurrentFolder;

};

#endif // !defined(AFX_DEALMETHOD_H__B54F61CC_9A82_48B3_BE3F_F164A0191344__INCLUDED_)
