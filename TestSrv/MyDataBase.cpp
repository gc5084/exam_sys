// MyDataBase.cpp: implementation of the CMyDataBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SrvMyApp.h"
#include "MyDataBase.h"
#include "StuInfor.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CList<MemoryData,MemoryData>   listTestFill;
extern CList<MemoryData,MemoryData>   listTestModify;
extern CList<MemoryData,MemoryData>   listTestDesign;
extern CStuInfor* arrStu[80];
										

CMyDataBase::CMyDataBase()
{
	//初始化com环境
	::CoInitialize(NULL);
	//初始化链接对象
	m_pConnection.CreateInstance(__uuidof(Connection));
	//初始化记录集
	m_pRecordset.CreateInstance(__uuidof(Recordset));
		
}

CMyDataBase::~CMyDataBase()
{

}

//连接SQL数据库
BOOL CMyDataBase::ConnectSQL()
{
	CString str;
	str.Format("Provider=SQLOLEDB.1;Persist Security Info=False;\
		Integrated Security=SSPI;Data Source=.;database=TestData");
	try
	{
		if(m_pConnection->State)
		{
			m_pConnection->Close();
		}
		
		m_pConnection->Open((_bstr_t)str,"","",adModeUnknown);
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}
	

	return TRUE;
}

//关闭SQL数据库
BOOL CMyDataBase::CloseSQL()
{
	try
	{
		if(m_pConnection->State)
		{
			m_pConnection->Close();
			return TRUE;
		}
		return FALSE;
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}
	

}

BOOL CMyDataBase::ConnectExcel(CString strPathName)
{
	try
	{

		if(m_pConnection->State)
		{
			m_pConnection->Close();
		}
		CString str,strSQL;
	    str.Format("Provider=Microsoft.Jet.OLEDB.4.0;Persist Security Info=False;Data Source=%s;Extended Properties=Excel 8.0;",strPathName);
		//执行连接
		m_pConnection->Open((_bstr_t)str,"","",adModeUnknown);

	}

	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;
}

BOOL CMyDataBase::CloseExcel()
{
	return TRUE;
}

int CMyDataBase::LoadTest()
{
	CString strSQL;
	char* czTemp;
	int   nTemp;
	MemoryData TempData;			//储存试题信息的结构

	try
	{
		//连接数据库
		ConnectSQL();

//存入填空题
		strSQL.Format("select * from fill;");
		if(m_pRecordset->State)
			m_pRecordset->Close();

		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);
		nTemp = 0;
		while(m_pRecordset->adoEOF == 0)
		{
			if(m_pRecordset->GetCollect("fnum").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"));
				TempData.PrimaryKey = czTemp;
			}
				
			else
				TempData.PrimaryKey = NULL;

			if(m_pRecordset->GetCollect("ftitle").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle"));
				TempData.TestTitle = czTemp;
			}
				
			else
				TempData.TestTitle = NULL;
			                     

			if(m_pRecordset->GetCollect("fcontent").vt != VT_NULL)
			{

				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcontent"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcontent"));
				TempData.TestContent = czTemp;

			}
			else 
				TempData.TestContent = NULL;

			
			if(m_pRecordset->GetCollect("fcheck").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck"));
				TempData.Check = czTemp;
			}
				
			else
				TempData.Check = NULL;

			//填充阅卷输出
			if(m_pRecordset->GetCollect("fout").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout"));
				TempData.CheckOut = czTemp;
			}
				
			else
				TempData.CheckOut = NULL;

			//填充备注
			if(m_pRecordset->GetCollect("fremark").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark"));
				TempData.Remark = czTemp;
			}
				
			else
				TempData.Remark = NULL;

			if(TempData.PrimaryKey!= NULL)
				listTestFill.AddTail(TempData);
								//无为空则存入链表
			m_pRecordset->MoveNext();
			nTemp++;
		}

//存入改错题
		strSQL.Format("select * from modify;");
		if(m_pRecordset->State)
			m_pRecordset->Close();
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);

		nTemp = 0;
		while(m_pRecordset->adoEOF == 0)
		{
			if(m_pRecordset->GetCollect("fnum").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"));
				TempData.PrimaryKey = czTemp;
			}
				
			else
				TempData.PrimaryKey = NULL;

			if(m_pRecordset->GetCollect("ftitle").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle"));
				TempData.TestTitle = czTemp;
			}
				
			else
				TempData.TestTitle = NULL;
			                     

			if(m_pRecordset->GetCollect("fcontent").vt != VT_NULL)
			{

				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcontent"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcontent"));
				TempData.TestContent = czTemp;

			}
			else 
				TempData.TestContent = NULL;

			
			if(m_pRecordset->GetCollect("fcheck").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck"));
				TempData.Check = czTemp;
			}
				
			else
				TempData.Check = NULL;


			if(m_pRecordset->GetCollect("fout").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout"));
				TempData.CheckOut = czTemp;
			}
				
			else
				TempData.CheckOut = NULL;

			if(m_pRecordset->GetCollect("fremark").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark"));
				TempData.Remark = czTemp;
			}
				
			else
				TempData.Remark = NULL;

			if(TempData.PrimaryKey!= NULL)
				listTestModify.AddTail(TempData);
								//无为空则存入链表
			m_pRecordset->MoveNext();
			nTemp++;
		}

//存入设计题
		strSQL.Format("select * from design;");
		if(m_pRecordset->State)
			m_pRecordset->Close();

		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);

		nTemp = 0;
		while(m_pRecordset->adoEOF == 0)
		{
			if(m_pRecordset->GetCollect("fnum").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fnum"));
				TempData.PrimaryKey = czTemp;
			}
				
			else
				TempData.PrimaryKey = NULL;

			if(m_pRecordset->GetCollect("ftitle").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ftitle"));
				TempData.TestTitle = czTemp;
			}
				
			else
				TempData.TestTitle = NULL;
			                     

			if(m_pRecordset->GetCollect("fcontent").vt != VT_NULL)
			{

				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcontent"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcontent"));
				TempData.TestContent = czTemp;

			}
			else 
				TempData.TestContent = NULL;

			
			if(m_pRecordset->GetCollect("fcheck").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fcheck"));
				TempData.Check = czTemp;
			}
				
			else
				TempData.Check = NULL;


			if(m_pRecordset->GetCollect("fout").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fout"));
				TempData.CheckOut = czTemp;
			}
				
			else
				TempData.CheckOut = NULL;

			if(m_pRecordset->GetCollect("fremark").vt != VT_NULL)//检查是否空 否则会引起异常
			{
			
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("fremark"));
				TempData.Remark = czTemp;
			}
				
			else
				TempData.Remark = NULL;

			if(TempData.PrimaryKey!= NULL)
				listTestDesign.AddTail(TempData);
								//无为空则存入链表
			m_pRecordset->MoveNext();
			nTemp++;
		}


		if(m_pRecordset->State)
			m_pRecordset->Close();
	}

	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	//关闭数据库
	CloseSQL();
	return TRUE;
}
/*
载入学生库的学生信息函数
*/
BOOL CMyDataBase::LoadStudent()
{
	CString strSQL;
	strSQL.Format("select * from student;");
	int n = 0;					//用于arrStu的数组索引
    char* czTemp;
	
	try
	{
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		
		
		if(m_pRecordset->State)
			m_pRecordset->Close();
		
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);
		while(m_pRecordset->adoEOF == 0)
		{
			arrStu[n] = new CStuInfor;
			if(m_pRecordset->GetCollect("snum").vt != VT_NULL)//检查是否空 否则会引起异常
			{
				
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("snum"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("snum"));
				arrStu[n]->strNum = czTemp;
			}				
			else
				arrStu[n]->strNum = NULL;
			
			
			if(m_pRecordset->GetCollect("sname").vt != VT_NULL)
			{
				
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("sname"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("sname"));
				arrStu[n]->strName = czTemp;
				
			}
			else 
				arrStu[n]->strName = NULL;
			
		 		n++;
														//索引加一
			if(n >= MAXNUM)
				break;
									//计数到MAXNUM时退出本循环（填充学生数组） 
			m_pRecordset->MoveNext();
		}

		nStudent = n;//保存有多少个学生

		while(n < MAXNUM)           //如果没有到MAXNUM继续填充剩余的学生数组
		{
			arrStu[n] = NULL;
			n++;
		}
		if(m_pRecordset->State)
			m_pRecordset->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return nStudent;
		
}

BOOL CMyDataBase::LoadStudentExcel()
{
	CString strSQL;
	strSQL.Format("select * from [Sheet1$];");//[Sheet1$],
	int n = 0;					//用于number与name的数组索引
	int i,j;//临时循环计数
    char* czTemp;

	//定义两个指针数组 为了暂存学号和姓名 
	//先把学号和姓名读出来 若是学号有重复就提示然后删除new出的缓冲区并返回错误
	//这样当有学号重复错误时就可以不存在arrStu数组中了
	char* number[MAXNUM];
	char* name[MAXNUM];
	//初始化为零
	//memset(number,NULL,MAXNUM);
	//memset(name,NULL,MAXNUM);
	for(i=0;i<MAXNUM;i++)
	{
		number[i] = NULL;
		name[i]   = NULL;
	}

	
	try
	{
		
		if(m_pRecordset->State)
			m_pRecordset->Close();
		//执行记录集的打开操作
		m_pRecordset->Open((_bstr_t)strSQL,m_pConnection.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);

		while(m_pRecordset->adoEOF == 0)
		{
			//载入考生学号 
			if(m_pRecordset->GetCollect("number").vt != VT_NULL)//检查是否空 否则会引起异常
			{
				
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("number"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("number"));
				number[n] = czTemp;
				//检查学号是否有重复 
				for(j=0;j<MAXNUM;j++)
				{
					if(n != j)
					{
						//与当前学号相等并且不是同一个索引位置 则学号有重复
						if(strcmp(number[n],number[j])==0)
						{
							CString strShow;
							strShow.Format("%s 考号有重复 请修改后再加载！",number[n]);
							AfxMessageBox(strShow);
							//释放缓冲区
							for(i =0;i<MAXNUM;i++)
							{
								delete[] number[i];
								delete[] name[i];
							}
							return FALSE;
						}
					}
					else
						break;
					//如果学号指针数组当前索引等于循环索引 后面的都为空 检查完毕 跳出循环
				}
			}				
			else
			{
				//释放缓冲区
				for(i =0;i<MAXNUM;i++)
				{
					delete[] number[i];
					delete[] name[i];
				}
				AfxMessageBox("考生学号不能为空！请修改后重新载入");
				return FALSE;
			}
			
			//载入考生姓名
			if(m_pRecordset->GetCollect("name").vt != VT_NULL)
			{
				
				czTemp = new char[strlen((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("name"))+ADDBUFFER];
				::lstrcpy(czTemp,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("name"));
				name[n] = czTemp;
				
			}
			else
			{
				for(i =0;i<MAXNUM;i++)
				{
					delete[] number[i];
					delete[] name[i];
				}
				AfxMessageBox("考生姓名不能为空！请修改后重新载入");
				return FALSE;
			}
			//索引加一
			n++;
			if(n >= MAXNUM)
				break;
				//计数到MAXNUM时退出本循环 
			m_pRecordset->MoveNext();
		}

		nStudent = n;//保存有多少个学生

		//将堆栈中的学号 姓名 指针数组 导入到arrStu数组中
		for(i = 0; i<MAXNUM; i++)
		{
			if(number[i] != NULL)
			{
				//创建类 并给填充学号和姓名
				arrStu[i] = new CStuInfor();
				arrStu[i]->strNum  = number[i];
				arrStu[i]->strName = name[i];
			}
			else
				break;
			    //当number循环到空时说明考生信息完了 跳出循环停止产生CStuInfor类
		}
		//临时代码
        //strSQL.Format("insert into [Sheet1$] values('0610014188','奥光')");
		
		//关闭记录集连接
		if(m_pRecordset->State)
			m_pRecordset->Close();

	//	strSQL.Format("alter table student add  remark int;");//[Sheet1$]
	//	strSQL.Format("create table ttt(aa char(3),bb char(3));");
	//	m_pConnection->Execute((_bstr_t)strSQL,NULL,adCmdText);
	}

	catch(_com_error e)
	{
		AfxMessageBox("Excel内容不符合标准");
		return FALSE;
	}

	return nStudent;
		
}

/*
关闭与数据库的连接
*/
BOOL CMyDataBase::CloseDataBase()
{
	try
	{
		if(m_pConnection->State)
			m_pConnection->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}
	return TRUE;

}


/*数据输出到excel*/
BOOL CMyDataBase::OutExcel(CString strPathName)
{
	//连接Excel
	if(ConnectExcel(strPathName) ==FALSE)
	{
		return FALSE;
	}

	//填充数据
	CString strSQL;
	for(int n = 0;n<MAXNUM;n++)
	{
		if(arrStu[n] != NULL)
		{
			//格式化要执行的SQL语句
			strSQL.Format(
				"insert into [Sheet1$] values('%s','%s','%d','%d','%d','%d','%d','%d','%d','%d','%d' ,'%d')",
				arrStu[n]->strNum,arrStu[n]->strName,
				arrStu[n]->StuCorrectFill[0],arrStu[n]->StuCorrectFill[1],arrStu[n]->StuCorrectFill[2],
				arrStu[n]->StuCorrectModify[0],arrStu[n]->StuCorrectModify[1],arrStu[n]->StuCorrectModify[2],
				arrStu[n]->StuCorrectDesign[0],arrStu[n]->StuCorrectDesign[1],arrStu[n]->StuCorrectDesign[2],
				arrStu[n]->nAllPoint);
			try
			{
				m_pConnection->Execute((_bstr_t)strSQL,NULL,adCmdText); //执行添加元组语句
			}
			catch(_com_error e)
			{
				return FALSE;
			}
		}
		
		
	}

	CloseSQL(); //关闭数据库
	return TRUE;
}