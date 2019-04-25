#include "stdAfx.h"
#include "SrvMyApp.h"
#include "SrvMainWnd.h"
#include "MySocket.h"
#include "StuInfor.h"


extern CList<MemoryData,MemoryData>   listTestFill;
extern CList<MemoryData,MemoryData>   listTestModify;
extern CList<MemoryData,MemoryData>   listTestDesign;
extern CCriticalSection g_list;
extern CList<SOCKET,SOCKET> listSock;
extern SendTestData g_sendTestData[MAXNUM];
	
CStuInfor::CStuInfor()
{
	strNum = NULL;
	strName = NULL;
	nState  = 0;//初始化为未登录
	sock  = NULL;
	passTime = 0;
	testPackIndex = -1;
	for(int n=0;n<3;n++)
	{
		StuAnswerFill[n]    = NULL; 
		StuAnswerModify[n]  = NULL;
		StuAnswerDesign[n]  = NULL;
		StuCorrectFill[n]   = 0;//0为不存在 1正确 2 错误
		StuCorrectModify[n] = 0;
		StuCorrectDesign[n] = 0;
		nAllPoint           = 0;
		
	}
}

void CStuInfor::ReState()
{
	//删除对应套接字在链表中
	if(nState == 1)//状态为在线才删除 （已交卷状态 已经将套接字在链表中删除）
	{
		g_list.Lock();
	    listSock.RemoveAt(listSock.Find(sock));
	    g_list.Unlock();
	}
	sock  = NULL;

	for(int n=0;n<3;n++)
	{
		//删除学生作答试题
		delete[] StuAnswerFill[n];
		StuAnswerFill[n]    = NULL; 

		delete[] StuAnswerModify[n];
		StuAnswerModify[n]    = NULL; 

		delete[] StuAnswerDesign[n];
		StuAnswerDesign[n]    = NULL; 

		//阅卷结果全部改为未阅卷
		StuCorrectFill[n]   = 0;//0为不存在 1正确 2 错误
		StuCorrectModify[n] = 0;
		StuCorrectDesign[n] = 0;
	}


	//初始化为未登录
	nState  = 0;
	//已用时清零
	passTime = 0;
}

void CStuInfor::CheckAllAnswer()
{

	//获取当前路径用于保存考生
	m_szPath = new char[100];
	::GetCurrentDirectory(100,m_szPath);
	//创建一个SrvCheck文件夹
	CString  strDir = m_szPath;	
	strDir = strDir+"\\SrvCheck";
	::CreateDirectory(strDir,NULL); //如果已有同名文件夹就函数失败 

	//循环检测试题
	for(int i = 0;i < 3;i++)
		for(int j =0;j<3;j++)
		{
			if((i==0)&&(g_sendTestData[testPackIndex].nRandFill[j] != -1))
				CheckOne(i,j);
			else if((i==1)&&(g_sendTestData[testPackIndex].nRandModify[j] != -1))
				CheckOne(i,j);
			else if((i==2)&&(g_sendTestData[testPackIndex].nRandDesign[j] != -1))
				CheckOne(i,j);

		}

	//计算总分
	MakeAllPoint();

	delete[] m_szPath;//释放文件资源
	m_szPath = NULL;

}


BOOL CStuInfor::CheckOne(int nTestClass,int nTestNum)
{
	char* czAnswer;
	char* czCheck;
	char* czCheckOut;

	switch(nTestClass)
	{
	case 0://填空题
		switch(nTestNum)
		{
		case 0://第一个
			czAnswer    = StuAnswerFill[0];
			if(g_sendTestData[testPackIndex].nRandFill[0] == -1)
				return FALSE;
			czCheck     = GetTestStr(0,g_sendTestData[testPackIndex].nRandFill[0],2);
			czCheckOut  = GetTestStr(0,g_sendTestData[testPackIndex].nRandFill[0],3);
			break;
		case 1://第二个
			czAnswer = StuAnswerFill[1];
			if(g_sendTestData[testPackIndex].nRandFill[1] == -1)
				return FALSE;
			czCheck     = GetTestStr(0,g_sendTestData[testPackIndex].nRandFill[1],2);
			czCheckOut  = GetTestStr(0,g_sendTestData[testPackIndex].nRandFill[1],3);
			break;
		case 2://第三个
			czAnswer = StuAnswerFill[2];
			if(g_sendTestData[testPackIndex].nRandFill[2] == -1)
				return FALSE;
			czCheck     = GetTestStr(0,g_sendTestData[testPackIndex].nRandFill[2],2);
			czCheckOut  = GetTestStr(0,g_sendTestData[testPackIndex].nRandFill[2],3);
			break;
		}
        //检查错对并赋值 放在主switch中 试题类型靠主switch来定 第几试题用nTestNum
		if(CheckOne(czAnswer,czCheck,czCheckOut) == TRUE)
		{
			StuCorrectFill[nTestNum] = 1;
			return TRUE;
		}
		else
		{
			StuCorrectFill[nTestNum] = 2;
			return FALSE;
		}
		
		break;


	case 1://改错题
		switch(nTestNum)
		{
		case 0://第一个
			czAnswer = StuAnswerModify[0];
			if(g_sendTestData[testPackIndex].nRandModify[0] == -1)
				return FALSE;
			czCheck     = GetTestStr(1,g_sendTestData[testPackIndex].nRandModify[0],2);
			czCheckOut  = GetTestStr(1,g_sendTestData[testPackIndex].nRandModify[0],3);
			break;
		case 1://第二个
			czAnswer = StuAnswerModify[1];
			if(g_sendTestData[testPackIndex].nRandModify[1] == -1)
				return FALSE;
			czCheck     = GetTestStr(1,g_sendTestData[testPackIndex].nRandModify[1],2);
			czCheckOut  = GetTestStr(1,g_sendTestData[testPackIndex].nRandModify[1],3);
			break;
		case 2://第三个
			czAnswer = StuAnswerModify[2];
			if(g_sendTestData[testPackIndex].nRandModify[2] == -1)
				return FALSE;
			czCheck     = GetTestStr(1,g_sendTestData[testPackIndex].nRandModify[2],2);
			czCheckOut  = GetTestStr(1,g_sendTestData[testPackIndex].nRandModify[2],3);
			break;
		}

		if(CheckOne(czAnswer,czCheck,czCheckOut) == TRUE)
		{
			StuCorrectModify[nTestNum] = 1;
			return TRUE;
		}
		else
		{
			StuCorrectModify[nTestNum] = 2;
			return FALSE;
		}
		break;


	case 2://设计题
		switch(nTestNum)
		{
		case 0://第一个
			czAnswer = StuAnswerDesign[0];
			if(g_sendTestData[testPackIndex].nRandDesign[0] == -1)
				return FALSE;
			czCheck     = GetTestStr(2,g_sendTestData[testPackIndex].nRandDesign[0],2);
			czCheckOut  = GetTestStr(2,g_sendTestData[testPackIndex].nRandDesign[0],3);
			break;
		case 1://第二个
			czAnswer = StuAnswerDesign[1];
			if(g_sendTestData[testPackIndex].nRandDesign[1] == -1)
				return FALSE;
			czCheck     = GetTestStr(2,g_sendTestData[testPackIndex].nRandDesign[1],2);
			czCheckOut  = GetTestStr(2,g_sendTestData[testPackIndex].nRandDesign[1],3);
			break;
		case 2://第三个
			czAnswer = StuAnswerDesign[2];
			if(g_sendTestData[testPackIndex].nRandDesign[2] == -1)
				return FALSE;
			czCheck     = GetTestStr(2,g_sendTestData[testPackIndex].nRandDesign[2],2);
			czCheckOut  = GetTestStr(2,g_sendTestData[testPackIndex].nRandDesign[2],3);
			break;
		}

//		AfxMessageBox(czAnswer);
//		AfxMessageBox(czCheck);
//		AfxMessageBox(czCheckOut);
		if(CheckOne(czAnswer,czCheck,czCheckOut) == TRUE)
		{
			StuCorrectDesign[nTestNum] = 1;
			return TRUE;
		}
		else
		{
			StuCorrectDesign[nTestNum] = 2;
			return FALSE;
		}
		break;

	default:
			return FALSE;
	}
	
}

BOOL CStuInfor::CheckOne(char* czAnswer,char* czCheck,char* czCheckOut)
{
	//组合出完整字符串
	CString strCombo;
	if(ComboAnswer(czAnswer,czCheck) == FALSE)
		return FALSE;
	strCombo = m_strTemp;
//	AfxMessageBox(strCombo);

	
	//将完整字符串写入到指定文件
	CString strFileName = m_szPath;
	strFileName = strFileName + "\\SrvCheck";

	CString strCppPath = strFileName + "\\Test.cpp";//文件名含路径字符串											
	try
	{
		CFile outFile(strCppPath,CFile::modeReadWrite|CFile::modeCreate);
		outFile.Write((LPCTSTR)strCombo,sizeof(char)*strCombo.GetLength());
		outFile.Close();
												//将插入完成的检测字符串写入文件,以待被检测
	}
	catch(CFileException* e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}

	//创建批处理
	CString strBat;
     strBat.Format("cd SrvCheck \r\n call VCVARS32.BAT \r\n  cl Test.cpp \r\n link Test.obj \r\n Test.exe");

	 CString strBatPath = strFileName + "\\Check.bat"; //批处理完整路径
    try
	{

		CFile fillBat(strBatPath,CFile::modeReadWrite|CFile::modeCreate);//SrvCheck
		fillBat.Write(strBat,sizeof(char)*strBat.GetLength());
		fillBat.Close();
	}
	catch(CFileException* e)
	{
		e->ReportError();
		e->Delete();
        return FALSE;
	}
	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	GetStartupInfo(&si);
	si.dwFlags    =STARTF_USESHOWWINDOW; //不加此句 在桌面快捷方式执行时不能隐藏进程
	si.wShowWindow=SW_HIDE;

	
	char *szBatPath = new char[strFileName.GetLength() + 11 +ADDBUFFER];
	szBatPath = strBatPath.GetBuffer(0);
	//AfxMessageBox(szBatPath);

	CreateProcess( NULL, // No module name (use command line). 
        szBatPath, // Command line. SrvCheck
        NULL,             // Process handle not inheritable. 
        NULL,             // Thread handle not inheritable. 
        FALSE,            // Set handle inheritance to FALSE. 
        0, // No creation flags.CREATE_NO_WINDOW 
        NULL,             // Use parent's environment block. 
        NULL,             // Use parent's starting directory. 
        &si,              // Pointer to STARTUPINFO structure.
        &pi );              // Pointer to PROCESS_INFORMATION structure.
	WaitForSingleObject(pi.hProcess,INFINITE);



	//检查正确与否并返回信息
	if(AnswerCorrect(czCheckOut) == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}




	return TRUE;
}

char* CStuInfor::GetTestStr(int nTest,int nIndex,int nItem)
{
	//参数含义 nTest那类试题  nIndex试题随机数 nItem获得什么内容1试题序号2阅卷内容...
	POSITION pos;
	int n;

	switch(nTest)
	{
	case 0:
		pos = listTestFill.GetHeadPosition();
		for(n=0;n<nIndex;n++)
		{
			listTestFill.GetNext(pos);
		}

		if(nItem == 1)//返回试题序号
		{
			return listTestFill.GetNext(pos).PrimaryKey;
		}
		else if(nItem == 2)//返回阅卷内容
		{
			return listTestFill.GetNext(pos).Check;
		}
		else if(nItem == 3)//返回阅卷输出
		{
			return listTestFill.GetNext(pos).CheckOut;
		}
		else
		{
			return NULL;
		}
		

	case 1:
		pos = listTestModify.GetHeadPosition();
		for(n=0;n<nIndex;n++)
		{
			listTestModify.GetNext(pos);
		}
		
		if(nItem == 1)//返回试题序号
		{
			return listTestModify.GetNext(pos).PrimaryKey;
		}
		else if(nItem == 2)//返回阅卷内容
		{
			return listTestModify.GetNext(pos).Check;
		}
		else if(nItem == 3)//返回阅卷输出
		{
			return listTestModify.GetNext(pos).CheckOut;
		}
		else
		{
			return NULL;
		}
	case 2:
		pos = listTestDesign.GetHeadPosition();
		for(n=0;n<nIndex;n++)
		{
			listTestDesign.GetNext(pos);
		}

		if(nItem == 1)//返回试题序号
		{
			return listTestDesign.GetNext(pos).PrimaryKey;
		}
		else if(nItem == 2)//返回阅卷内容
		{
			return listTestDesign.GetNext(pos).Check;
		}
		else if(nItem == 3)//返回阅卷输出
		{
			return listTestDesign.GetNext(pos).CheckOut;
		}
		else
		{
			return NULL;
		}
		break;
	default:
		return NULL;

	}
}


BOOL CStuInfor::ComboAnswer(char* czAnswer,char* czCheck)
{
	int nAsBegin,nAsEnd,nCKBegin,nCKEnd;
	CString strAnswer = czAnswer;
	CString strCheck  = czCheck;
	CString temp;

	while(strAnswer.Find("/***found***/")!=-1)
	{
        nAsBegin = strAnswer.Find("/***found***/");
		if((nAsEnd = strAnswer.Find("/***end***/")) == -1)
			return FALSE;
		//答案字符串中有一个/***found***/ 就有一个/***end***/ 否则就出错要返回
		if( (nCKBegin = strCheck.Find("/***found***/")) == -1)
			return FALSE;
		if((nCKEnd = strCheck.Find("/***end***/")) == -1)
			return FALSE;
		//检查字符串中有一个/***found***/ 就有一个/***end***/ 否则就出错要返回

												//获取答案和检测中的起始结束

        temp = strAnswer.Left(nAsEnd);
												//截取第一个/***end***/的左半部分
		temp = temp.Right(nAsEnd - nAsBegin - 13);
												//截取temp中右半部 提取内容 13为/***found***/的长度

		strCheck.Insert(nCKEnd,temp);
												//插入阅卷对应位置
		strAnswer.Delete(nAsBegin,13);
												//删除答案字符串中已截取过的/***found***/标记
		if((nAsEnd = strAnswer.Find("/***end***/")) == -1)
			return FALSE;
												//字符串被删改 位置需从新寻找
		strAnswer.Delete(nAsEnd,11);
												//删除答案字符串中已截取过的/***end***/标记

		strCheck.Delete(nCKBegin,13);
		if((nCKEnd = strCheck.Find("/***end***/")) == -1)
			return FALSE;
		strCheck.Delete(nCKEnd,11);
		                                        //如上删除的检测题中的标记标记	
	}
	m_strTemp = strCheck;
	return TRUE;
}

///检查考生作答产生的文件内容是否正确
BOOL CStuInfor::AnswerCorrect(char* czCheckOut)
{
	CString strCorrect = czCheckOut;

    CString str;
	CFile value;
	CFileException e;
	if(value.Open("SrvCheck\\answer.txt",CFile::modeRead,&e))	//把文件中的数据读入字符串。
	{
		char* buffur = new char[value.GetLength()+1];
		value.Read(buffur,value.GetLength()*sizeof(char));
		buffur[value.GetLength()] = 0;							
		str = buffur;
		delete []buffur;
		
	}
	else
		return FALSE;


	if(str.Compare(strCorrect)==0)
		return TRUE;
	else
		return FALSE;


}



///计算总分
void CStuInfor::MakeAllPoint()
{
	int nQuestion = 0;      //记录考试一共有几个题
	int nCorrectQue = 0;    //记录答对了几个题

	//统计一共出了几个题和答对的个数
	for(int n=0;n<3;n++)
	{
		//填空题
		if(g_sendTestData[testPackIndex].nRandFill[n] != -1) //随机题号不为-1说明有这个题
		{
			nQuestion++; 
			if(StuCorrectFill[n] == 1)//对应题是正确的正确数加1
			{
				nCorrectQue++;
			}
		}
		//改错题
		if(g_sendTestData[testPackIndex].nRandModify[n] != -1) //随机题号不为-1说明有这个题
		{
			nQuestion++; 
			if(StuCorrectModify[n] == 1)//对应题是正确的正确数加1
			{
				nCorrectQue++;
			}
		}
		//改错题 
		if(g_sendTestData[testPackIndex].nRandDesign[n] != -1) //随机题号不为-1说明有这个题
		{
			nQuestion++; 
			if(StuCorrectDesign[n] == 1)//对应题是正确的正确数加1
			{
				nCorrectQue++;
			}
		}
	}

	//算分
	if(nCorrectQue == 0)   //没有一个对的为0分
	{
		this->nAllPoint = 0;
	}
	else
	{
		int nPoint;
		nPoint = (int)( ((100.00/(float)nQuestion)*nCorrectQue)+1 ); //总分一百 加1为了刨除强转成int的不精确
		                                 
		if(nPoint >= 100) //因为加1了可能大于100
			this->nAllPoint = 100;
		else
			this->nAllPoint = nPoint;
	}
}


/*读取本考生文件夹中的试题*/
BOOL CStuInfor::ReadTestFile()
{
	CString folderPath;
	folderPath.Format("C:\\AllTest\\k%d\\",testPackIndex);


	char* Describe[3][3];
	//初始化文件名
	Describe[0][0] = "Fill0.cpp";
	Describe[0][1] = "Fill1.cpp";
	Describe[0][2] = "Fill2.cpp";

	Describe[1][0] = "Modify0.cpp";
	Describe[1][1] = "Modify1.cpp";
	Describe[1][2] = "Modify2.cpp";

	Describe[2][0] = "Design0.cpp";
	Describe[2][1] = "Design1.cpp";
	Describe[2][2] = "Design2.cpp";

	int i;
	//填空
	for(i=0;i<3;i++)
	{
		CString strFileName = Describe[0][i];
		strFileName = folderPath + strFileName;

		CFile file;
		if(file.Open(strFileName,CFile::modeReadWrite))  //打开各描述文件
		{
			StuAnswerFill[i] = new char[file.GetLength()+1];
			file.Read(StuAnswerFill[i],file.GetLength()*sizeof(char));
			StuAnswerFill[i][file.GetLength()] = 0;							
		}
		else
		{
			StuAnswerFill[i] = NULL;
		}
	}

	//改错
	for(i=0;i<3;i++)
	{
		CString strFileName = Describe[1][i];
		strFileName = folderPath + strFileName;

		CFile file;
		if(file.Open(strFileName,CFile::modeReadWrite))  //打开各描述文件
		{
			StuAnswerModify[i] = new char[file.GetLength()+1];
			file.Read(StuAnswerModify[i],file.GetLength()*sizeof(char));
			StuAnswerModify[i][file.GetLength()] = 0;							
		}
		else
		{
			StuAnswerModify[i] = NULL;
		}
	}

	//设计
	for(i=0;i<3;i++)
	{
		CString strFileName = Describe[1][i];
		strFileName = folderPath + strFileName;

		CFile file;
		if(file.Open(strFileName,CFile::modeReadWrite))  //打开各描述文件
		{
			StuAnswerDesign[i] = new char[file.GetLength()+1];
			file.Read(StuAnswerDesign[i],file.GetLength()*sizeof(char));
			StuAnswerDesign[i][file.GetLength()] = 0;							
		}
		else
		{
			StuAnswerDesign[i] = NULL;
		}
	}

	return TRUE;
}