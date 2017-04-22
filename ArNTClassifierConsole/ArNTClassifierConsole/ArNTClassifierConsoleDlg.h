// ArNTClassifierConsoleDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "DlgClassifier.h"
#include "DlgDefectFromDBClassify.h"
#include "DlgSampleCollection.h"
#include "DlgHelp.h"
#include "HFile.h"

typedef struct tagConfigInfo
{
	bool	bAutoClassify;
	CString strDefectDBIP;
	int		iDefectImgIP;
	CString strDefectImgIP[8];
	int		iCameraNum;
	int		iImgWidth;
	int		iImgHeight;

	bool	bIsEnd;
}ConfigInfo,*PConfigInfo;

// CArNTClassifierConsoleDlg 对话框
class CArNTClassifierConsoleDlg : public CDialog
{
// 构造
public:
	CArNTClassifierConsoleDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ARNTCLASSIFIERCONSOLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
//对话框对象
public:
	DlgDefectFromDBClassify		m_DlgDefectClassify;
	DlgSampleCollection		m_DlgSampleCollection;
	DlgClassifier			m_DlgClassifier;
	DlgHelp					m_DlgHelp;

public:
	static ConfigInfo			m_ConfigInfo;
	static ConfigClassSet		m_ConfigClassSet;
	void InitLoadConfig();

//函数

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CTabCtrl m_MainTab;
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
};
