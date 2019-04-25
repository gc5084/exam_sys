// TestDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestData.h"
#include "TestDataDlg.h"
#include "FillDlg.h"
#include "Base.h"
#include "Fill.h"
#include "Modify.h"
#include "Design.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDataDlg dialog

CTestDataDlg::CTestDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDataDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDataDlg)
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_bmExit);
	DDX_Control(pDX, IDC_BUTTON_LINK, m_bmLink);
	DDX_Control(pDX, IDC_BUTTON_CUT, m_bmCut);
	DDX_Control(pDX, IDC_BUTTON_FILL, m_bmFill);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_bmModify);
	DDX_Control(pDX, IDC_BUTTON_DESIGN, m_bmDesign);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDataDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDataDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LINK, OnButtonLink)
	ON_BN_CLICKED(IDC_BUTTON_CUT, OnButtonCut)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_FILL, OnButtonFill)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DESIGN, OnButtonDesign)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDataDlg message handlers

BOOL CTestDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here


    m_bmFill.LoadBitmaps(IDB_FILLU,IDB_FILLD,IDB_FILLF,IDB_FILLX);
    m_bmFill.SizeToContent();
                                   //加载填空题位图
	m_bmModify.LoadBitmaps(IDB_MODIFYU,IDB_MODIFYD,IDB_MODIFYF,IDB_MODIFYX);
    m_bmModify.SizeToContent();
									//加载改错题位图
	m_bmDesign.LoadBitmaps(IDB_DESIGNU,IDB_DESIGND,IDB_DESIGNF,IDB_DESIGNX);
    m_bmDesign.SizeToContent();
									//加载设计题位图
	m_bmCut.LoadBitmaps(IDB_CUTU,IDB_CUTD,IDB_CUTF,IDB_CUTX);
    m_bmCut.SizeToContent();
									//断开数据库按钮位图加载
    m_bmLink.LoadBitmaps(IDB_LINKU,IDB_LINKD,IDB_LINKF,IDB_LINKX);
    m_bmLink.SizeToContent();
									//链接按钮位图加载
	m_bmExit.LoadBitmaps(IDB_EXITU,IDB_EXITD,IDB_EXITF);
    m_bmExit.SizeToContent();    
									//退出按钮无禁止状态

	((CButton*)this->GetDlgItem(IDC_BUTTON_CUT))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_FILL))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_DESIGN))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDataDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDataDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDataDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/*
 关联ID为IDC_BUTTON_LINK的链接数据库按钮
 点击按钮后该函数完成链接数据库操作
*/
void CTestDataDlg::OnButtonLink() 
{
	CString str;
	str.Format("Provider=SQLOLEDB.1;Persist Security Info=False;\
		Integrated Security=SSPI;DataSource=.;database=TestData");
	try
	{
		::CoInitialize(NULL);
		//初始化com环境
		m_pConnection.CreateInstance(__uuidof(Connection));
		//初始化链接对象
		m_pConnection->Open((_bstr_t)str,"","",adModeUnknown);
		
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	((CButton*)this->GetDlgItem(IDC_BUTTON_CUT))->EnableWindow(TRUE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_FILL))->EnableWindow(TRUE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_DESIGN))->EnableWindow(TRUE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(TRUE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_LINK))->EnableWindow(FALSE);

	MessageBox("链接成功！");
}
/*
  与ID为IDC_BUTTON_CUT的按钮关联
  功能数据库断开连接
*/
void CTestDataDlg::OnButtonCut() 
{
   	try
	{
		m_pConnection->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return;
	}
	
	MessageBox("已断开与数据库的链接！");
	((CButton*)this->GetDlgItem(IDC_BUTTON_CUT))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_FILL))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_DESIGN))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
	((CButton*)this->GetDlgItem(IDC_BUTTON_LINK))->EnableWindow(TRUE);
}

/*
  与ID为IDC_BUTTON_EXIT的按钮关联
  功能退出程序，先尝试关闭数据库
  放在try中如果数据库已关闭也可以容错
  然后返送WM_CLOSE消息退出程序
*/
void CTestDataDlg::OnButtonExit() 
{
	try
	{
		m_pConnection->Close();
	}
	catch(_com_error e)
	{
	}
    PostMessage(WM_CLOSE);

	
}

void CTestDataDlg::OnButtonFill() 
{
	m_pB = new CFill(m_pConnection);
	CFillDlg dlg(this);
	dlg.DoModal();
	delete m_pB;
}


void CTestDataDlg::OnButtonModify() 
{
	m_pB = new CModify(m_pConnection);
	CFillDlg dlg(this);
	dlg.DoModal();
	delete m_pB;
}

void CTestDataDlg::OnButtonDesign() 
{
	m_pB = new CDesign(m_pConnection);
	CFillDlg dlg(this);
	dlg.DoModal();
	delete m_pB;
}

void CTestDataDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

//	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CTestDataDlg::OnOK()
{
}

void CTestDataDlg::OnCancel()
{
	try
	{
		m_pConnection->Close();
	}
	catch(_com_error e)
	{
	}
	CDialog::OnCancel();

}


