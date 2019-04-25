#include <afxwin.h>         // MFC 基础头文件
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <afxcmn.h>         // MFC support for Windows Common Controls 有进度条控件
#include <afxmt.h>			// MFC 临界对象所需头文件
#include <Afxsock.h>		// MFC 套接字库头文件
#include <Afxtempl.h>       // 模板头文件 使用CList类时需用
#include "resource.h"       // 本地资源头文件


#import "msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","adoBOF")

#include "MyDataBase.h"
#define ID_TIME       1     //timer时钟ID 设为1
#define WM_INFORPAINT (WM_USER + 101)
							//连接中断消息 由于主窗口的重绘

const int FLAG_TEST  = 1;    //考试试题是否加载标志
const int FLAG_STU   = 2;    //考生名单是否加载
const int FLAG_TIME  = 4;    //考试时间是否设置
const int FLAG_START = 8;    //考试是否已启动
const int FLAG_OVER  = 16;   //考试是否结束
const int FLAG_SAVE  = 32;   //考试信息是否保存了
const int FLAG_MUCHNUM = 64; //考试题数已出
const int FLAG_TIMEGO= 128;  //考生开始计时

const int MAXNUM    = 80;   //最大人数
const int LINEW     = 5;    //基础线宽 用于提示信息和表格之间的宽度
const int ROWCOUNT  = 8;    //一共有8行
const int COLCOUNT  = 10;   //一共有10列
const int CELLWIDTH = 16;   //每一个方格宽最多宥15个字符 留出16个字符宽度
const int CELLHIGH  = 5;    //每一个方格高最多有3个字符  留出5个字符高度

const int SOCKHEAD = 4;     //socket报文头长度
const int ADDBUFFER	= 4;	//防止字符串越界 凡是new的字符串统一多出

///////////////////////////////////服务器客户端消息对于const
const int Mess_TestPackIndex = 20;
const int Mess_Time = 15;
const int Mess_ConfirmNumber = 2;
const int Mess_TestOver = 3;