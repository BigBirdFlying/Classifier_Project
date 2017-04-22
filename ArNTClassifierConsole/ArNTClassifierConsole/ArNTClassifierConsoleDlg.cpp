// ArNTClassifierConsoleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ArNTClassifierConsole.h"
#include "ArNTClassifierConsoleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ConfigInfo CArNTClassifierConsoleDlg::m_ConfigInfo={L"",L""};
ConfigClassSet CArNTClassifierConsoleDlg::m_ConfigClassSet={0,0,""};
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CArNTClassifierConsoleDlg 对话框




CArNTClassifierConsoleDlg::CArNTClassifierConsoleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CArNTClassifierConsoleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CArNTClassifierConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_MainTab);
}

BEGIN_MESSAGE_MAP(CArNTClassifierConsoleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CArNTClassifierConsoleDlg::OnTcnSelchangeTabMain)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CArNTClassifierConsoleDlg 消息处理程序

BOOL CArNTClassifierConsoleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码 
	CRect mainTabRect;   // 标签控件客户区的位置和大小 
	m_MainTab.GetClientRect(&mainTabRect);    // 获取标签控件客户区Rect   
	mainTabRect.left += 1;                  
	mainTabRect.right -= 1;   
	mainTabRect.top += 22;   
	mainTabRect.bottom -= 1;
	//
	InitLoadConfig();
	//

	//通过命令行确定手动自动模式
	CString strCommandLine=::GetCommandLine();
	CString strCommand=L"-Mod";
	int iPosCommand=strCommandLine.Find(strCommand);
	if(iPosCommand>0)
	{
		CString strCommandOffset=L"";
		CString strCommandValue=L"";
		strCommandOffset = strCommandLine.Right(strCommandLine.GetLength()-iPosCommand-strCommand.GetLength()-1);
		int iPosCommandCut=strCommandOffset.Find(L"-");
		if(iPosCommandCut>0)
		{
			strCommandValue = strCommandOffset.Left(iPosCommandCut-1);
		}
		else
		{
			strCommandValue = strCommandLine.Right(strCommandLine.GetLength()-iPosCommand-strCommand.GetLength()-1);
		}

		int a=strCommandValue.Compare(L"collect");
		int b=strCommandValue.Compare(L"train");
		int c=strCommandValue.Compare(L"classify");
		if(0==strCommandValue.Compare(L"collect"))
		{
			m_DlgSampleCollection.SetWindowPos(NULL, mainTabRect.left, mainTabRect.top, mainTabRect.Width(), mainTabRect.Height(), SWP_SHOWWINDOW);   
			m_DlgClassifier.SetWindowPos(NULL, mainTabRect.left, mainTabRect.top, mainTabRect.Width(), mainTabRect.Height(), SWP_HIDEWINDOW);  
			m_DlgDefectClassify.SetWindowPos(NULL, mainTabRect.left, mainTabRect.top, mainTabRect.Width(), mainTabRect.Height(), SWP_HIDEWINDOW); 
		}
		else if(0==strCommandValue.Compare(L"train"))
		{
			m_DlgSampleCollection.SetWindowPos(NULL, mainTabRect.left, mainTabRect.top, mainTabRect.Width(), mainTabRect.Height(), SWP_HIDEWINDOW);   
			m_DlgClassifier.SetWindowPos(NULL, mainTabRect.left, mainTabRect.top, mainTabRect.Width(), mainTabRect.Height(), SWP_SHOWWINDOW);  
			m_DlgDefectClassify.SetWindowPos(NULL, mainTabRect.left, mainTabRect.top, mainTabRect.Width(), mainTabRect.Height(), SWP_HIDEWINDOW); 
		}
		else if(0==strCommandValue.Compare(L"classify"))
		{
			m_DlgDefectClassify.Create(IDD_DIALOG_DEFECTCLASS, &m_MainTab);
			
			m_MainTab.InsertItem(0, _T("缺陷在线分类"));  
			m_DlgDefectClassify.SetWindowPos(NULL, mainTabRect.left, mainTabRect.top, mainTabRect.Width(), mainTabRect.Height(), SWP_SHOWWINDOW); 
		}
	}
	else
	{
		m_MainTab.InsertItem(0, _T("缺陷样本采集"));  
		m_MainTab.InsertItem(1, _T("分类器设计训练")); 
		m_MainTab.InsertItem(2, _T("缺陷在线分类")); 
		m_MainTab.InsertItem(3, _T("系统在线帮助")); 

		m_DlgSampleCollection.Create(IDD_DIALOG_SAMPLE_COLLECTION, &m_MainTab);
		m_DlgClassifier.Create(IDD_DIALOG_CLASSIFIER, &m_MainTab); 
		m_DlgDefectClassify.Create(IDD_DIALOG_DEFECTCLASS, &m_MainTab);
		m_DlgHelp.Create(IDD_DIALOG_HELP, &m_MainTab);
 
		m_DlgSampleCollection.SetWindowPos(NULL, mainTabRect.left, mainTabRect.top, mainTabRect.Width(), mainTabRect.Height(), SWP_SHOWWINDOW);   
		m_DlgClassifier.SetWindowPos(NULL, mainTabRect.left, mainTabRect.top, mainTabRect.Width(), mainTabRect.Height(), SWP_HIDEWINDOW);  
		m_DlgDefectClassify.SetWindowPos(NULL, mainTabRect.left, mainTabRect.top, mainTabRect.Width(), mainTabRect.Height(), SWP_HIDEWINDOW); 
		m_DlgHelp.SetWindowPos(NULL, mainTabRect.left, mainTabRect.top, mainTabRect.Width(), mainTabRect.Height(), SWP_HIDEWINDOW); 
	}

	//添加标题
	CString strTime=L"";
	CTime CurTime = CTime::GetCurrentTime();
	strTime.Format(L"%04d-%02d-%02d %02d:%02d:%02d",CurTime.GetYear(),CurTime.GetMonth(),CurTime.GetDay(),CurTime.GetHour(),CurTime.GetMinute(),CurTime.GetSecond());
	CString strTitle=L"";
	strTitle.Format(L"在线检测系统缺陷提取分类控制台---程序开始运行时间为：%s  （北京科技大学设计研究院有限公司）",strTime);
	SetWindowText(strTitle);

	//测试
	//string str;
	//for(int i=0;i<10;i++)
	//{
	//	str=format("D:\\Works\\C++练习\\分类器算法结构\\样本集\\%d.bmp",i);
	//	int a=0;
	//}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CArNTClassifierConsoleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CArNTClassifierConsoleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CArNTClassifierConsoleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CArNTClassifierConsoleDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CRect tabRect; 
    // 获取标签控件客户区Rect，并对其调整，以适合放置标签页   
    m_MainTab.GetClientRect(&tabRect);   
    tabRect.left += 1;   
    tabRect.right -= 1;   
    tabRect.top += 22;   
    tabRect.bottom -= 1;   
  
    switch (m_MainTab.GetCurSel())   
    {    
    case 0:   
        m_DlgSampleCollection.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);   
        m_DlgClassifier.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);  
		m_DlgDefectClassify.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_DlgHelp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
        break;    
    case 1:   
        m_DlgSampleCollection.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
        m_DlgClassifier.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);  
		m_DlgDefectClassify.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_DlgHelp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
        break; 
	case 2:   
        m_DlgSampleCollection.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
        m_DlgClassifier.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);  
		m_DlgDefectClassify.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_DlgHelp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
        break; 
	case 3:   
        m_DlgSampleCollection.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
        m_DlgClassifier.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);  
		m_DlgDefectClassify.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_DlgHelp.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW); 
        break; 
    default:   
        break;   
    }   
}


void CArNTClassifierConsoleDlg::InitLoadConfig()
{
	m_ConfigInfo.bIsEnd=false;
	HFile_xml hFileXml;
	int iJudge=hFileXml.LoadFile(L"ArNTClassifierConsole.xml");
	if(1==iJudge)
	{
		CString strValue;

		hFileXml.Read(L"//分类器控制台//在线分类模块//启用自动搜索分类",strValue);
		if(_ttoi(strValue)>0)
		{
			m_ConfigInfo.bAutoClassify=true;
		}
		else
		{
			m_ConfigInfo.bAutoClassify=false;
		}

		hFileXml.Read(L"//分类器控制台//在线分类模块//缺陷数据库//服务器IP地址",strValue);
		m_ConfigInfo.strDefectDBIP.Format(L"%s",strValue);

		hFileXml.Read(L"//分类器控制台//在线分类模块//缺陷图像存储目录//服务器数量",strValue);
		m_ConfigInfo.iDefectImgIP=_ttoi(strValue);

		for(int i=0;i<m_ConfigInfo.iDefectImgIP;i++)
		{
			CString strKey;
			strKey.Format(L"//分类器控制台//在线分类模块//缺陷图像存储目录//服务器IP地址%d",i);
			hFileXml.Read(strKey,strValue);
			m_ConfigInfo.strDefectImgIP[i].Format(L"%s",strValue);
		}

		hFileXml.Read(L"//分类器控制台//在线分类模块//相机个数",strValue);
		m_ConfigInfo.iCameraNum=_ttoi(strValue);

		hFileXml.Read(L"//分类器控制台//在线分类模块//图像原始尺寸//图像宽度",strValue);
		m_ConfigInfo.iImgWidth=_ttoi(strValue);

		hFileXml.Read(L"//分类器控制台//在线分类模块//图像原始尺寸//图像高度",strValue);
		m_ConfigInfo.iImgHeight=_ttoi(strValue);
	}
	else
	{
		AfxMessageBox(TEXT("配置文件ArNTClassifierConsole.xml加载失败！"));
	}

	//
	iJudge=hFileXml.LoadFile(L"ArNTClassTable.xml");
	if(1==iJudge)
	{
		m_ConfigClassSet.iItemNum=0;
		CString strValue;
		hFileXml.Read(L"//缺陷类别表//缺陷类别//类别总数",strValue);
		int iClassTotal=_ttoi(strValue);
		for(int i=0;i<iClassTotal;i++)
		{
			CString strNode=L"";
			
			strNode.Format(L"//缺陷类别表//缺陷类别//类别%d//内部编号",i);
			hFileXml.Read(strNode,strValue);
			m_ConfigClassSet.Items[m_ConfigClassSet.iItemNum].iInternalClassNo=_ttoi(strValue);
			
			strNode.Format(L"//缺陷类别表//缺陷类别//类别%d//名称",i);
			hFileXml.Read(strNode,strValue);
			int iLength = WideCharToMultiByte(CP_ACP, 0, strValue, -1, NULL, 0, NULL, NULL);  
			WideCharToMultiByte(CP_ACP, 0, strValue, -1, m_ConfigClassSet.Items[m_ConfigClassSet.iItemNum].strClassName, iLength, NULL, NULL);

			strNode.Format(L"//缺陷类别表//缺陷类别//类别%d//外部编号",i);
			hFileXml.Read(strNode,strValue);
			m_ConfigClassSet.Items[m_ConfigClassSet.iItemNum].iExternalClassNo=_ttoi(strValue);

			m_ConfigClassSet.iItemNum++;
		}
	}
	else
	{
		AfxMessageBox(TEXT("配置文件ArNTClassTable.xml加载失败！"));
	}

	//
	m_ConfigInfo.bIsEnd=true;
}
void CArNTClassifierConsoleDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HANDLE hself=GetCurrentProcess();
	TerminateProcess(hself,0);

	CDialog::OnClose();
}
