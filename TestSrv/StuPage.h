// StuPage.h: interface for the CStuPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STUPAGE_H__8B40B934_AAD6_4BB4_AF01_04E784FFCC7D__INCLUDED_)
#define AFX_STUPAGE_H__8B40B934_AAD6_4BB4_AF01_04E784FFCC7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStuPage : public CPropertyPage  
{
public:
	CStuPage();
	virtual ~CStuPage();

	enum {IDD = IDD_STUINFOR};
protected:
	virtual void DoDataExchange(CDataExchange*);

	virtual BOOL OnInitDialog();

protected:
	CEdit    m_EditNum;      //ѧ�ű༭��
	CEdit    m_EditName;     //�����༭��
	CEdit    m_EditState;    //״̬�༭��
	CEdit    m_EditSocket;   //�׽��ֱ༭��

	CEdit    m_EditIP;       //��ʾIP
	int      m_nStu;         //ѧ����������
};

#endif // !defined(AFX_STUPAGE_H__8B40B934_AAD6_4BB4_AF01_04E784FFCC7D__INCLUDED_)
