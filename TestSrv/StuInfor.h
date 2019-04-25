/////////////////////////////////////////////////////////////////////
//类名：CStuInfor
//说明：考生信息类
//功能：储存单个考生的所有信息和对这些信息的操作     
//作者：郭承(gc5084@163.com)
//组织：图形图像研究所
//日期：2009.03
//////////////////////////////////////////////////////////////////////
class CStuInfor
{
public:

	char*   strNum;//学号
									
	char*   strName;//姓名
									
	int     nState;//状态 ：0未登录 1在线 2交卷 3异常 4该考生被设为禁止考试        
									
	SOCKET  sock;//学生对应套接字  
										
//	int     nRandFill[3];//学生随机抽题填空题的随机数
									
//	int     nRandModify[3];//学生随机抽题改错题的随机数
									
//	int     nRandDesign[3];//学生随机抽题设计题的随机数
	int		testPackIndex; //考生随机试题包序号

	int		passTime;   //考生剩余时间
									
	char*   StuAnswerFill[3];//学生上交的填空题答案

	char*   StuAnswerModify[3];//学生上交的改错题答案

	char*   StuAnswerDesign[3];//学生上交的设计题答案

	int     StuCorrectFill[3];//学生填空题上交答案是否正确标志    1是正确 2是错误 0是没有试题
    
	int     StuCorrectModify[3];//学生改错题上交答案是否正确标志

	int     StuCorrectDesign[3];//学生设计题上交答案是否正确标志

	int     nAllPoint; //记录学生的总分
protected:
	CString m_strTemp;//临时字符串 用于储存组合的检测答案 跨越不同的函数
	char*   m_szPath;  //保存当前路径
public:
	CStuInfor();

	void ReState(); //重置状态

	void CheckAllAnswer();

	BOOL CheckOne(int nTestClass,int nTestNum);

	BOOL CheckOne(char* czAnswer,char* czCheck,char* czCheckOut);

	char* GetTestStr(int nTest,int nIndex,int Item);

	BOOL AnswerCorrect(char* czCheckOut);

	BOOL ReadTestFile();

	

protected:

    BOOL ComboAnswer(char* czAnswer,char* czCheck);
	void MakeAllPoint();
	


};