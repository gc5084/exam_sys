/////////////////////////////////////////////////////////////////////
//类名：CMainWindow
//说明：程序主窗口类
//功能：创建程序主窗口 响应窗口内的所用事件
//      响应菜单 接受消息 程序的核心类        
//作者：郭承(gc5084@163.com)
//组织：图形图像研究所
//日期：2009.03
//////////////////////////////////////////////////////////////////////
#ifndef MAINWND_H_
#define MAINWND_H_

class CMainWindow : public CWnd
{
public:
	CMainWindow();
				  //主窗口窗口句柄 保存为静态是因为其他线程要用
				  //本场考试时长
   static int     nFlag;
	             //标志位
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpcreatestruct);
	afx_msg void OnStart();
	afx_msg void OnPaint(); 
	afx_msg void OnClose();
	afx_msg void OnPerson();
	afx_msg BOOL OnSetTime();
	afx_msg void OnConCheck();
	afx_msg void OnConStuInfo();
	afx_msg void OnConForbid();
	afx_msg void OnConRestate();
	afx_msg void OnConSend();


	afx_msg void OnInforPaint(WPARAM wParam, LPARAM lParam);
	afx_msg void OnReset();
	afx_msg void OnExitTest();
	afx_msg BOOL OnLoadStu();
	afx_msg void OnRePaint();
	afx_msg void OnForbid();
	afx_msg void OnSendInfor();
	afx_msg void OnCheckAll();
	afx_msg void OnCheckSave();
	afx_msg void OnCheckShow();
	afx_msg void OnHelpAbout();
	afx_msg void OnLock();
	afx_msg void OnOutExcel();
	afx_msg void OnToolData();

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
protected:
	BOOL  InitMySocket();
	void  DrawInfor(CDC* pDC);
	void  DrawClient(CDC* pDC);
//	BOOL  LoadStuInfor();
	BOOL  LoadTestFirst();
	void  SetStartTime();
	void  RandStu();
	void  ReStart();
protected:
	int				m_cxChar;						  //主字体宽度
	int				m_cyChar;			              //主字体高度
	CRect			m_rcClient;                       // 仅消息客户区
	CRect           m_rcInfor;                        //提示信息客户区
	CRect			m_rcPaint;                        //整个重绘客户区
	SOCKET			m_LisSock;						  //监听套接字描述符
	CFont			m_fontMain;                       //主字体  
	CRect			Arect[80];						  //80个在信息区的矩形区域
	CWinThread*     m_threadAccept;					  //接受连接线程的句柄
	CWinThread*     m_threadSelect;					  //Select线程的句柄
	int             PassedRect;                       //记录上一个当前格

public:

	int             nRightDown;						  //记录当右键按下时所在的区域
	CMyDataBase     m_DataBase;						  //数据库类
	int             nMuchTest[3];                     //记录当次考试每题各出几个
	CString         Password;                         //存储锁定应用程序的密码





DECLARE_MESSAGE_MAP()
};

#endif