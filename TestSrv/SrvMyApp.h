/////////////////////////////////////////////////////////////////////
//类名：CMyApp
//说明：应用程序类
//功能：承载应用程序的生死         
//作者：郭承(gc5084@163.com)
//组织：图形图像研究所
//日期：2009.03
//////////////////////////////////////////////////////////////////////
#ifndef MYAPP_H_
#define MYAPP_H_

class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	WSADATA wsaData;

};

/////////////////////////////////////////////////////////////////////
//类名：MemoryData
//说明：试题类
//功能：保存试题信息        
//作者：郭承(gc5084@163.com)
//组织：图形图像研究所
//日期：2009.03
//////////////////////////////////////////////////////////////////////

class MemoryData
{
public:
	MemoryData(){TestTitle = NULL;TestContent = NULL;}
	char* TestTitle;
									//试题标题指针
	char* TestContent;
									//试题内容指针
	char* Check;

	char* PrimaryKey;

	char* CorrectAnswer;

	char* CheckOut;

	char* Remark;
};

/////////////////////////////////////////////////////////////////////
//SendTestData
//说明：分配试题信息类
//功能：保存分配试题序号        
//作者：郭承(gc5084@163.com)
//组织：
//日期：2010.05
//////////////////////////////////////////////////////////////////////
class SendTestData
{
public:
	SendTestData() //构建器很重要 -1代表没有出这个试题
	{
		int n;
		for(n=0;n<3;n++)
		{
			nRandFill[n] = -1;
			nRandModify[n] = -1;
			nRandDesign[n] = -1;
		}
	};

	int nRandFill[3];
	int nRandModify[3];
	int nRandDesign[3];
};

#endif