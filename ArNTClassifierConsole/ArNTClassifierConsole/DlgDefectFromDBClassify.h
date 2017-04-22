#pragma once
#include "HDBOper.h"
#include "HFile.h"
#include "afxwin.h"
#include "afxcmn.h"

#define WM_THREADMSG1 WM_USER+1
#define WM_THREADMSG2 WM_USER+2
#define WM_THREADMSG3 WM_USER+3
#define WM_THREADMSG4 WM_USER+4
#define WM_THREADMSG5 WM_USER+5
#define WM_THREADMSG6 WM_USER+6
#define WM_THREADMSG7 WM_USER+7
#define WM_THREADMSG8 WM_USER+8

typedef struct tagClassifyConfig
{
	bool bIsNorm;
	int iImgWidth;
	int iImgHeight;
	CString strFeatName[64];
	CString strClassifierFileName;
}ClassifyConfig,*PClassifyConfig;

// DlgDefectFromDBClassify 对话框

class DlgDefectFromDBClassify : public CDialog
{
	DECLARE_DYNAMIC(DlgDefectFromDBClassify)

public:
	DlgDefectFromDBClassify(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgDefectFromDBClassify();

// 对话框数据
	enum { IDD = IDD_DIALOG_DEFECTCLASSIFY };

public:
	HThread		m_hThread[16];
	HThread		m_hDetectConfig;
	HFile_ini	m_FileIniOper;
	CString		m_strAppPath;
	CListCtrl	*m_listDBData[10];

	ClassifyConfig	m_ClassifyConfig;

	void InitInfo();
	LRESULT OnMsgFunc1(WPARAM,LPARAM);
	LRESULT OnMsgFunc2(WPARAM,LPARAM);
	LRESULT OnMsgFunc3(WPARAM,LPARAM);
	LRESULT OnMsgFunc4(WPARAM,LPARAM);
	LRESULT OnMsgFunc5(WPARAM,LPARAM);
	LRESULT OnMsgFunc6(WPARAM,LPARAM);
	LRESULT OnMsgFunc7(WPARAM,LPARAM);
	LRESULT OnMsgFunc8(WPARAM,LPARAM);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboDefectDBIP;
	CComboBox m_ComboDefectImgIP;
	CComboBox m_ComboDBType;
	CListBox m_listBoxShowLoadInfo;
	afx_msg void OnBnClickedButtonConnectDb();
	virtual BOOL OnInitDialog();
	CListCtrl m_listDBData1;
	CListCtrl m_listDBData2;
	CListCtrl m_listDBData3;
	CListCtrl m_listDBData4;
	CListCtrl m_listDBData5;
	CListCtrl m_listDBData6;
	CListCtrl m_listDBData7;
	CListCtrl m_listDBData8;
};
