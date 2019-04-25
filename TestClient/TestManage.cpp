// TestManage.cpp: implementation of the CTestManage class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "TestClient.h"
#include "TestManage.h"
#include "MySocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CTestClientApp theApp;
extern SOCKET Gsock;

CTestManage::CTestManage()
{
	//获取当前路径
	this->m_szAppPath = new char[100];
	::GetCurrentDirectory(100,m_szAppPath);

	//填充试题描述名称
	Describe[0][0] = "DesFill0";
	Describe[0][1] = "DesFill1";
	Describe[0][2] = "DesFill2";

	Describe[1][0] = "DesModify0";
	Describe[1][1] = "DesModify1";
	Describe[1][2] = "DesModify2";

	Describe[2][0] = "DesDesign0";
	Describe[2][1] = "DesDesign1";
	Describe[2][2] = "DesDesign2";
/*
	//当前路径创建一个文件夹
	CString  strNewFolderPath = m_szAppPath;	
	strNewFolderPath = strNewFolderPath+"\\Test";
	::CreateDirectory(strNewFolderPath,NULL); //参数NULL 指明如果有此文件夹就不创建文件夹
	*/
}

CTestManage::~CTestManage()
{
}

/*读取描述试题文件*/
void CTestManage::ReadDescribeFile()
{
	int i;
	//填空
	for(i=0;i<3;i++)
	{
		CString strFileName = Describe[0][i];
		strFileName = _T("K:\\") + strFileName;

		CFile file;
		if(file.Open(strFileName,CFile::modeReadWrite))  //打开各描述文件
		{
			theApp.fill[i] = new char[file.GetLength()+1];
			file.Read(theApp.fill[i],file.GetLength()*sizeof(char));
			theApp.fill[i][file.GetLength()] = 0;							
		}
		else
		{
			theApp.fill[i] = NULL;
		}
	}

	//改错
	for(i=0;i<3;i++)
	{
		CString strFileName = Describe[1][i];
		strFileName = _T("K:\\") + strFileName;

		CFile file;
		if(file.Open(strFileName,CFile::modeReadWrite))  //打开各描述文件
		{
			theApp.modify[i] = new char[file.GetLength()+1];
			file.Read(theApp.modify[i],file.GetLength()*sizeof(char));
			theApp.modify[i][file.GetLength()] = 0;							
		}
		else
		{
			theApp.modify[i] = NULL;
		}
	}

	//设计
	for(i=0;i<3;i++)
	{
		CString strFileName = Describe[2][i];
		strFileName = _T("K:\\") + strFileName;

		CFile file;
		if(file.Open(strFileName,CFile::modeReadWrite))  //打开各描述文件
		{
			theApp.design[i] = new char[file.GetLength()+1];
			file.Read(theApp.design[i],file.GetLength()*sizeof(char));
			theApp.design[i][file.GetLength()] = 0;							
		}
		else
		{
			theApp.design[i] = NULL;
		}
	}
	//试题包编号
	CString strFileName;
	strFileName = _T("K:\\Index");
	
	CFile file;
	if(file.Open(strFileName,CFile::modeReadWrite))  //打开各描述文件
	{
		char* buffer = new char[file.GetLength()+1];
		file.Read(buffer,file.GetLength()*sizeof(char));
		buffer[file.GetLength()] = 0;
		
		int PackIndex;
		PackIndex = buffer[0]; //
		//发送试题包编号
		CMySocket mysock;
		mysock.MySend(Gsock,NULL,Mess_TestPackIndex,PackIndex);

	}
	else
	{
		AfxMessageBox("读取试题序号出错！程序将推出");
		exit(0);
	}




}



BOOL CTestManage::InputText(char* Buffer)
{
	if(Buffer==NULL)
		return FALSE;
	switch(Buffer[SOCKHEAD-2])
	{
	case 5:	
	case 6:
	case 7:									//5-7代表填空题
        if(Buffer[SOCKHEAD-1] == 1)			//1代表标题 复制到堆上 给theApp对象的相应指针
		{
			theApp.fill[Buffer[SOCKHEAD-2]-5] = new char[strlen(Buffer)+ADDBUFFER];
			::lstrcpy(theApp.fill[Buffer[SOCKHEAD-2]-5],&Buffer[SOCKHEAD]);
		//	AfxMessageBox(theApp.fill[Buffer[SOCKHEAD-2]-5]);
		}
		else if(Buffer[SOCKHEAD-1] == 2)   //2代表试题内容 需存入文件
		{
             if(InputFile(&Buffer[SOCKHEAD],Buffer[SOCKHEAD-2]) == FALSE)
				 return FALSE;
		}
		return TRUE;

	case 8:	
	case 9:
	case 10:								//8-10代表改错题
		if(Buffer[SOCKHEAD-1] == 1)			//1代表标题 复制到堆上 给theApp对象的相应指针
		{
			theApp.modify[Buffer[SOCKHEAD-2]-8] = new char[strlen(Buffer)+ADDBUFFER];
			::lstrcpy(theApp.modify[Buffer[SOCKHEAD-2]-8],&Buffer[SOCKHEAD]);
		//	AfxMessageBox(theApp.modify[Buffer[SOCKHEAD-2]-8]);
		}
		else if(Buffer[SOCKHEAD-1] == 2)   //2代表试题内容 需存入文件
		{
             if(InputFile(&Buffer[SOCKHEAD],Buffer[SOCKHEAD-2]) == FALSE)
				 return FALSE;
		}
		return TRUE;

	case 11:
	case 12:
	case 13:								//11-13代表设计题
		if(Buffer[SOCKHEAD-1] == 1)			//1代表标题 复制到堆上 给theApp对象的相应指针
		{
			theApp.design[Buffer[SOCKHEAD-2]-11] = new char[strlen(Buffer)+ADDBUFFER];
			::lstrcpy(theApp.design[Buffer[SOCKHEAD-2]-11],&Buffer[SOCKHEAD]);
		//	AfxMessageBox(theApp.design[Buffer[SOCKHEAD-2]-11]);
		}
		else if(Buffer[SOCKHEAD-1] == 2)   //2代表试题内容 需存入文件
		{
             if(InputFile(&Buffer[SOCKHEAD],Buffer[SOCKHEAD-2]) == FALSE)
				 return FALSE;
		}
		return TRUE;

	default:
		AfxMessageBox("信息标志异常！");
		return FALSE;


	}
}

BOOL CTestManage::InputFile(char* Buffer,int MajorFlag)
{
	//将文件名路径填充完整
	CString strFilePath = this->m_szAppPath;
	strFilePath = strFilePath + "\\Test"; //当前程序路径加上文件夹名 获得文件夹路径

	CString strFileName; //文件名
	if(MajorFlag == 5||MajorFlag == 6||MajorFlag == 7)
		strFileName.Format("\\Fill%d.cpp",MajorFlag-5);	
	else if(MajorFlag == 8||MajorFlag == 9||MajorFlag == 10)
		strFileName.Format("\\Modify%d.cpp",MajorFlag-8);		
	else if(MajorFlag == 11||MajorFlag == 12||MajorFlag == 13)
        strFileName.Format("\\Design%d.cpp",MajorFlag-11);											
	else
	{
		AfxMessageBox("文件标志异常！");
		return FALSE;
	}                            //根据不同的标志 格式化文件名

	
	strFilePath = strFilePath + strFileName; //获得完整文件名

	try
	{
		CFile outFile(strFilePath,CFile::modeReadWrite|CFile::modeCreate);
		outFile.Write(Buffer,strlen(Buffer));
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