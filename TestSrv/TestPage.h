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
	int          m_nStu;         //学生数组索引
	CEdit        m_EditTest;     //编辑框显示考生答卷
	CEdit        m_EditPK;       //编辑框显示答卷对应的试卷序号（主键）
	CComboBox    m_CBList;       //组合列表框
	char*        m_Test[9];      //记录对应于列表的考生上交试卷的指针 用于显示在只读编辑框
	char*        m_TestPK[9];    //记录上交试卷对应的试题主键的指针

DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_TESTPAGE_H__1AD61325_1C1F_4180_97A3_454AF77BE703__INCLUDED_)
