// DealMethod.cpp: implementation of the CDealMethod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DealMethod.h"
#include "SrvMainWnd.h"
#include "SrvMyApp.h"
#include "StuInfor.h"
#include "MySocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CList<MemoryData,MemoryData>   listTestFill;
extern CList<MemoryData,MemoryData>   listTestModify;
extern CList<MemoryData,MemoryData>   listTestDesign;
extern CStuInfor* arrStu[MAXNUM];
extern int GStartTime;
extern int GTestTime;	
extern SendTestData g_sendTestData[MAXNUM];

CDealMethod::CDealMethod()
{

}

CDealMethod::~CDealMethod()
{

}

/*向所有在线考生发送试题*/
BOOL CDealMethod::SendAllStuTest()
{
	
	//创建总文件夹
	CString  strNewFolderPath = "C:\\AllTest";
	if(::CreateDirectory(strNewFolderPath,NULL) == 0)//参数NULL 指明如果有此文件夹就不创建文件夹
	{
		//删除文件夹
		::system("rd/s/q C:\\AllTest");

	}
	::CreateDirectory(strNewFolderPath,NULL);//如果删除过就创建文件夹 没删除创建两编也无妨

	int NowStudentIndex;
	for(NowStudentIndex = 0;NowStudentIndex<MAXNUM;NowStudentIndex++)
	{
		
		m_CurrentFolder.Format("C:\\AllTest\\K%d\\",NowStudentIndex);
		::CreateDirectory(m_CurrentFolder,NULL); //参数NULL 指明如果有此文件夹就不创建文件夹
		if(SendTest(NowStudentIndex) == FALSE)
			return FALSE;
		
	}
	return TRUE;
}

/*处理2号消息 考号确认消息*/
BOOL CDealMethod::DealNumberSure(char* czRecvPage,SOCKET sock)
{

	//根据学号找到该生
	int NowStudentIndex;
	NowStudentIndex = SearchStuIndex(&czRecvPage[SOCKHEAD]);

/*
	//发送试题
	int nFlag = CMainWindow::nFlag;
	if(nFlag&FLAG_TIMEGO == 1)   //考试已经计时开始 发送试题 如果没开始就仅发送时间
	{
		if(SendTest(NowStudentIndex,sock) == FALSE)
		{
			return FALSE;
		}
	}
*/

	arrStu[NowStudentIndex]->nState = 1; //将考生状态改为在线
			
    arrStu[NowStudentIndex]->sock = sock;//保存该套接字于考生信息类中
	//发送时间
	if(SendTime(sock) == FALSE)
		return FALSE;

	//更改考生状态
		

		
	return TRUE;

}

/*处理3号消息 考生交卷消息*/
BOOL CDealMethod::TestOver(SOCKET sock)
{
	//找到该考生
	int NowStudentIndex;
	NowStudentIndex = this->SearchStuIndex(sock);

	//将考生状态改写为交卷
	if((NowStudentIndex>=0)&&(NowStudentIndex<MAXNUM)) //保证参数正确
	{
		arrStu[NowStudentIndex]->nState = 2; //状态改写为交卷
	}

	//将考生答卷后的文件读入 内存
	arrStu[NowStudentIndex]->ReadTestFile();

	//给考生发送交卷成功消息
	CMySocket mysock;
	if(mysock.MySend(sock,NULL,19,1) == FALSE)
	{
		arrStu[NowStudentIndex]->nState = 3; //状态改写为异常
		return FALSE;
	}

	return TRUE;

}

/*处理20号消息 请求试题消息*/
BOOL CDealMethod::DealRequestTest(SOCKET sock)
{
	/*
	//根据套接字找到学生索引
	int NowStudentIndex;
	NowStudentIndex = SearchStuIndex(sock);

	//发送试题
	if(SendTest(NowStudentIndex) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
	*/
	return TRUE;
}








BOOL CDealMethod::SendTime(SOCKET sock)
{
	char SendBuf[4];
	int NowStudentIndex = SearchStuIndex(sock);
	int passTime = arrStu[NowStudentIndex]->passTime;

	SendBuf[0] = passTime+1;
	//时间加1 以防止时间为0时，截断字符串
	SendBuf[1] = GTestTime;  //考试总时长
	
	int nFlag = CMainWindow::nFlag;
	if((nFlag&FLAG_TIMEGO) == FLAG_TIMEGO)
		SendBuf[2] = 1;
	else
		SendBuf[2] = 2;
	//发送时间消息中包含 考试是否计时开始信息
	SendBuf[3] = 0;//结束符
	
	CMySocket mysock;
	if(mysock.MySend(sock,SendBuf,15,1) == FALSE) //发送时间信息
	{
		return FALSE;
	}
		
	return TRUE;
	
}

BOOL CDealMethod::SendTime(int NowStudentIndex)
{
	return TRUE;
}

BOOL CDealMethod::TestPackIndex(int pack,SOCKET sock)
{
	int stuIndex =  SearchStuIndex(sock);
	int packIndex = pack - 1; //在服务器写入文件时加1了
	if(packIndex>=0 && packIndex<MAXNUM)
	{
		arrStu[stuIndex]->testPackIndex = packIndex;
	}
	else
	{
		AfxMessageBox("接受的试题包编号不再范围！");
		return FALSE;
	}
	return TRUE;
	
}

/*更新考试时间函数*/
BOOL CDealMethod::TiemUpdata(int time,SOCKET sock)
{
	int stuIndex =  SearchStuIndex(sock);

	arrStu[stuIndex]->passTime = time;

	return TRUE;

}



////////////////////////////////////////////////////////////////////////////////]
//保护函数 

/*根据学号找到学生数组索引*/
int CDealMethod::SearchStuIndex(char* czStuNumber)
{
	int NowStudentIndex = 0; //索引置0 
	while(NowStudentIndex<MAXNUM)
	{
		if(arrStu[NowStudentIndex] != NULL)
		{
			if(strcmp(czStuNumber,arrStu[NowStudentIndex]->strNum)== 0)
				break; //找到该生跳出循环
		}
		NowStudentIndex++;
	}
	if(NowStudentIndex > MAXNUM)  //出循环是因为累加变量大于总人数 即未找到该生
	{
		return -1; //直接return 就不会把这个套接字恢复到链表 这属于异常 
	}

	return NowStudentIndex;
}



/*根据套接字找到学生数组索引*/
int CDealMethod::SearchStuIndex(SOCKET sock)
{
	int NowStudentIndex = 0; //索引置0 
	while(NowStudentIndex<MAXNUM)
	{
		if(arrStu[NowStudentIndex] != NULL)
		{
			if(arrStu[NowStudentIndex]->sock == sock)
				break; //找到该生跳出循环
		}
		NowStudentIndex++;
	}
	if(NowStudentIndex > MAXNUM)  //出循环是因为累加变量大于总人数 即未找到该生
	{
		return -1; //直接return 就不会把这个套接字恢复到链表 这属于异常 
	}

	return NowStudentIndex;
}




/*给索引对应学生发送试题*/
BOOL CDealMethod::SendTest(int NowStudentIndex)
{
	//检查输入参数
	if((NowStudentIndex>MAXNUM)||(NowStudentIndex<0))
	{
		return FALSE;
	}
	//填充储存该生考题随机数的二维数组
	int TestRand[3][3];  //申请一个二维数组
	
	for(int i=0;i<3;i++)
	{
		TestRand[0][i] = g_sendTestData[NowStudentIndex].nRandFill[i];
		TestRand[1][i] = g_sendTestData[NowStudentIndex].nRandModify[i];
		TestRand[2][i] = g_sendTestData[NowStudentIndex].nRandDesign[i];
	}
	
	//生成试题物理文件（试题）
	int type,order;
	MemoryData TempData;
	CString Desfilename;
	CString filename;

	for(type=0; type<3; type++)
		for(order=0; order<3; order++)
		{
			if(TestRand[type][order] != -1) //该考生有该试题 发送
			{

				//从相应链表中取出试题存入 TempData 并写入文件
				switch(type)
				{
				case 0:
					TempData = listTestFill.GetAt(
						listTestFill.FindIndex(TestRand[type][order]));

					Desfilename.Format("DesFill%d",order);
					Desfilename = m_CurrentFolder + Desfilename;
					this->CreateTestFile(Desfilename,TempData.TestTitle);

					filename.Format("Fill%d.cpp",order);
					filename = m_CurrentFolder + filename;
					this->CreateTestFile(filename,TempData.TestContent);
					break;
				case 1:
					TempData = listTestModify.GetAt(
						listTestModify.FindIndex(TestRand[type][order]));

					Desfilename.Format("DesModify%d",order);
					Desfilename = m_CurrentFolder + Desfilename;
					this->CreateTestFile(Desfilename,TempData.TestTitle);

					filename.Format("Modify%d.cpp",order);
					filename = m_CurrentFolder + filename;
					this->CreateTestFile(filename,TempData.TestContent);
					break;
				case 2:
					TempData = listTestDesign.GetAt(
						listTestDesign.FindIndex(TestRand[type][order]));

					Desfilename.Format("DesDesign%d",order);
					Desfilename = m_CurrentFolder + Desfilename;
					this->CreateTestFile(Desfilename,TempData.TestTitle);

					filename.Format("Design%d.cpp",order);
					filename = m_CurrentFolder + filename;
					this->CreateTestFile(filename,TempData.TestContent);
					break;
				}
				
			}
			
		}
		//写入Index文件
		char content[2];
		content[0] = NowStudentIndex+1 ;content[1] = 0;

		filename = "Index";
		filename = m_CurrentFolder + filename;
		this->CreateTestFile(filename,content);

		return TRUE;
		
}

/*将指定文件名，内容写入文件夹*/
BOOL CDealMethod::CreateTestFile(CString fileName,char* fileContent)
{

	try
	{
		CFile outFile(fileName,CFile::modeReadWrite|CFile::modeCreate);
		outFile.Write(fileContent,strlen(fileContent));
		outFile.Close();
												//将插入完成的检测字符串写入文件,以待被检测
	}
	catch(CFileException* e)
	{
		AfxMessageBox("写入文件异常！");
		e->ReportError();
		e->Delete();
		return FALSE;
	}
	return TRUE;
}

