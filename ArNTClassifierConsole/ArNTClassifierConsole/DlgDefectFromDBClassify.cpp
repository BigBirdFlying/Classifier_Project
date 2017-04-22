// DlgDefectFromDBClassify.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ArNTClassifierConsole.h"
#include "DlgDefectFromDBClassify.h"
#include "ArNTClassifierConsoleDlg.h"
#include "HThread.h"
#include "ArNTInteractionFunc.h"

HDBOper					g_hDBOper[16];
SteelDefectInfoSet		g_tDefectSet[16];
long					g_iDefectMaxIndex[16];

UINT ThreadProc(LPVOID pParam)
{
	ThreadParam* pThreadParam = (ThreadParam*)pParam;
	while (!pThreadParam->bExit)
	{
		
		CString strDBName=L"";
		strDBName.Format(L"ClientDefectDB%d",pThreadParam->index);
		CString strDefectImgIP;
		for(int i=0;i<CArNTClassifierConsoleDlg::m_ConfigInfo.iDefectImgIP;i++)
		{
			CString strImgPath;
			strImgPath.Format(L"\\\\%s\\CamDefectImage%d",CArNTClassifierConsoleDlg::m_ConfigInfo.strDefectImgIP[i],pThreadParam->index);
			int IsExist=PathFileExists(strImgPath);
			if(IsExist)
			{
				strDefectImgIP=CArNTClassifierConsoleDlg::m_ConfigInfo.strDefectImgIP[i];
			}
		}
		switch(pThreadParam->index)
		{
		case 1:
			ReadDefectRecordFromDB(g_hDBOper[pThreadParam->index],CArNTClassifierConsoleDlg::m_ConfigInfo.strDefectDBIP,strDBName,L"SqlSever",L"",g_iDefectMaxIndex[pThreadParam->index],g_tDefectSet[pThreadParam->index]);
			//д���б�
			::PostMessage(pThreadParam->hWnd, WM_THREADMSG1, 0, 0);
			//
			if(g_tDefectSet[pThreadParam->index].iItemNum>0)
			{
				GetDefectImgAndClassify(g_hDBOper[pThreadParam->index],g_tDefectSet[pThreadParam->index],strDefectImgIP,pThreadParam->index,CArNTClassifierConsoleDlg::m_ConfigInfo.iImgWidth,CArNTClassifierConsoleDlg::m_ConfigInfo.iImgHeight);
			}
			break;
		case 2:
			ReadDefectRecordFromDB(g_hDBOper[pThreadParam->index],CArNTClassifierConsoleDlg::m_ConfigInfo.strDefectDBIP,strDBName,L"SqlSever",L"",g_iDefectMaxIndex[pThreadParam->index],g_tDefectSet[pThreadParam->index]);
			//д���б�
			::PostMessage(pThreadParam->hWnd, WM_THREADMSG2, 0, 0);
			//
			if(g_tDefectSet[pThreadParam->index].iItemNum>0)
			{
				GetDefectImgAndClassify(g_hDBOper[pThreadParam->index],g_tDefectSet[pThreadParam->index],strDefectImgIP,pThreadParam->index,CArNTClassifierConsoleDlg::m_ConfigInfo.iImgWidth,CArNTClassifierConsoleDlg::m_ConfigInfo.iImgHeight);
			}
			break;
		case 3:
			ReadDefectRecordFromDB(g_hDBOper[pThreadParam->index],CArNTClassifierConsoleDlg::m_ConfigInfo.strDefectDBIP,strDBName,L"SqlSever",L"",g_iDefectMaxIndex[pThreadParam->index],g_tDefectSet[pThreadParam->index]);
			//д���б�
			::PostMessage(pThreadParam->hWnd, WM_THREADMSG3, 0, 0);
			//
			if(g_tDefectSet[pThreadParam->index].iItemNum>0)
			{
				GetDefectImgAndClassify(g_hDBOper[pThreadParam->index],g_tDefectSet[pThreadParam->index],strDefectImgIP,pThreadParam->index,CArNTClassifierConsoleDlg::m_ConfigInfo.iImgWidth,CArNTClassifierConsoleDlg::m_ConfigInfo.iImgHeight);
			}
			break;
		case 4:
			ReadDefectRecordFromDB(g_hDBOper[pThreadParam->index],CArNTClassifierConsoleDlg::m_ConfigInfo.strDefectDBIP,strDBName,L"SqlSever",L"",g_iDefectMaxIndex[pThreadParam->index],g_tDefectSet[pThreadParam->index]);
			//д���б�
			::PostMessage(pThreadParam->hWnd, WM_THREADMSG4, 0, 0);
			//
			if(g_tDefectSet[pThreadParam->index].iItemNum>0)
			{
				GetDefectImgAndClassify(g_hDBOper[pThreadParam->index],g_tDefectSet[pThreadParam->index],strDefectImgIP,pThreadParam->index,CArNTClassifierConsoleDlg::m_ConfigInfo.iImgWidth,CArNTClassifierConsoleDlg::m_ConfigInfo.iImgHeight);
			}
			break;
		case 5:
			//ReadDefectRecordFromDB(pThreadParam->index,L"ClientDefectDB5",L"SqlSever",L"",g_tDefectSet[pThreadParam->index]);
			break;
		case 6:
			//ReadDefectRecordFromDB(pThreadParam->index,L"ClientDefectDB6",L"SqlSever",L"",g_tDefectSet[pThreadParam->index]);
			break;
		case 7:
			//ReadDefectRecordFromDB(pThreadParam->index,L"ClientDefectDB7",L"SqlSever",L"",g_tDefectSet[pThreadParam->index]);
			break;
		case 8:
			//ReadDefectRecordFromDB(pThreadParam->index,L"ClientDefectDB8",L"SqlSever",L"",g_tDefectSet[pThreadParam->index]);
			break;
		case 100:
			if(CArNTClassifierConsoleDlg::m_ConfigInfo.bIsEnd==true)
			{
				if(true==CArNTClassifierConsoleDlg::m_ConfigInfo.bAutoClassify)
				{
					::PostMessage(pThreadParam->hWnd, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CONNECT_DB, BN_CLICKED), 0);
				}
				pThreadParam->bExit=true;
			}
			break;
		default:break;
		}
		
		Sleep(2000);
		//if(pThreadParam->index==1)
		//{
		//	//pThreadParam->nData++;
		//	//::PostMessage(pThreadParam->hWnd, WM_THREADMSG1, 0, 0);
		//	
		//	int s=0;
		//}
		//if(pThreadParam->index==2)
		//{
		//	pThreadParam->nData++;
		//	//::PostMessage(pThreadParam->hWnd, WM_THREADMSG2, 0, 0);
		//}
	}
	return 0;
}
// DlgDefectFromDBClassify �Ի���

IMPLEMENT_DYNAMIC(DlgDefectFromDBClassify, CDialog)

DlgDefectFromDBClassify::DlgDefectFromDBClassify(CWnd* pParent /*=NULL*/)
	: CDialog(DlgDefectFromDBClassify::IDD, pParent)
{

}

DlgDefectFromDBClassify::~DlgDefectFromDBClassify()
{
}

void DlgDefectFromDBClassify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEFECT_DB_IP, m_ComboDefectDBIP);
	DDX_Control(pDX, IDC_COMBO_DEFECT_IMG_IP, m_ComboDefectImgIP);
	DDX_Control(pDX, IDC_COMBO_DB_TYPE, m_ComboDBType);
	DDX_Control(pDX, IDC_LIST_SHOW_LOAD_INFO, m_listBoxShowLoadInfo);
	DDX_Control(pDX, IDC_LIST_DBDATA_1, m_listDBData1);
	DDX_Control(pDX, IDC_LIST_DBDATA_2, m_listDBData2);
	DDX_Control(pDX, IDC_LIST_DBDATA_3, m_listDBData3);
	DDX_Control(pDX, IDC_LIST_DBDATA_4, m_listDBData4);
	DDX_Control(pDX, IDC_LIST_DBDATA_5, m_listDBData5);
	DDX_Control(pDX, IDC_LIST_DBDATA_6, m_listDBData6);
	DDX_Control(pDX, IDC_LIST_DBDATA_7, m_listDBData7);
	DDX_Control(pDX, IDC_LIST_DBDATA_8, m_listDBData8);
}


BEGIN_MESSAGE_MAP(DlgDefectFromDBClassify, CDialog)
	ON_MESSAGE(WM_THREADMSG1, OnMsgFunc1)
	ON_MESSAGE(WM_THREADMSG2, OnMsgFunc2)
	ON_MESSAGE(WM_THREADMSG3, OnMsgFunc3)
	ON_MESSAGE(WM_THREADMSG4, OnMsgFunc4)
	ON_MESSAGE(WM_THREADMSG5, OnMsgFunc5)
	ON_MESSAGE(WM_THREADMSG6, OnMsgFunc6)
	ON_MESSAGE(WM_THREADMSG7, OnMsgFunc7)
	ON_MESSAGE(WM_THREADMSG8, OnMsgFunc8)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT_DB, &DlgDefectFromDBClassify::OnBnClickedButtonConnectDb)
END_MESSAGE_MAP()


// DlgDefectFromDBClassify ��Ϣ�������
BOOL DlgDefectFromDBClassify::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ComboDefectDBIP.InsertString(0,L"192.168.0.100");
	m_ComboDefectDBIP.InsertString(1,L"192.168.0.1");
	m_ComboDefectDBIP.InsertString(2,L"192.168.0.101");
	m_ComboDefectDBIP.InsertString(3,L"192.168.1.100");
	m_ComboDefectDBIP.InsertString(4,L"192.169.0.100");
	m_ComboDefectDBIP.SetCurSel(0);
	//
	m_ComboDefectImgIP.InsertString(0,L"192.168.0.100");
	m_ComboDefectImgIP.InsertString(1,L"192.168.0.101");
	m_ComboDefectImgIP.InsertString(2,L"192.168.0.102");
	m_ComboDefectImgIP.InsertString(3,L"192.168.1.101");
	m_ComboDefectImgIP.InsertString(4,L"192.169.0.100");
	m_ComboDefectImgIP.SetCurSel(1);
	//
	m_ComboDBType.InsertString(0,L"Access");
	m_ComboDBType.InsertString(1,L"SqlSever");
	m_ComboDBType.InsertString(2,L"Oracle");
	m_ComboDBType.InsertString(3,L"Mysql");
	m_ComboDBType.SetCurSel(1);

	CRect rectStateDBDataInfo;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С 
    //GetDlgItem(IDC_STATIC_DBDATAINFO)->GetClientRect(&rectStateDBDataInfo);    // ��ȡ��ǩ�ؼ��ͻ���Rect  
	GetDlgItem(IDC_STATIC_DBDATAINFO)->GetWindowRect(&rectStateDBDataInfo);    // ��ȡ��ǩ�ؼ��ͻ���Rect 
	
	m_listDBData[1]=&m_listDBData1;
	m_listDBData[2]=&m_listDBData2;
	m_listDBData[3]=&m_listDBData3;
	m_listDBData[4]=&m_listDBData4;
	m_listDBData[5]=&m_listDBData5;
	m_listDBData[6]=&m_listDBData6;
	m_listDBData[7]=&m_listDBData7;
	m_listDBData[8]=&m_listDBData8;
	for(int i=1;i<=8;i++)
	{
		int height_mean=(rectStateDBDataInfo.Height()/CArNTClassifierConsoleDlg::m_ConfigInfo.iCameraNum)*2;
		int width_mean=rectStateDBDataInfo.Width()/2;
		int left=rectStateDBDataInfo.Width()*0.01;
		int top=rectStateDBDataInfo.Height()*0.05;
		if(i<=CArNTClassifierConsoleDlg::m_ConfigInfo.iCameraNum)
		{
			m_listDBData[i]->ShowWindow(true);
			if(i%2==1)
			{
				m_listDBData[i]->MoveWindow(rectStateDBDataInfo.left+left,top+height_mean*(i/2),width_mean*0.9,height_mean*0.85);
			}
			else
			{
				m_listDBData[i]->MoveWindow(rectStateDBDataInfo.left+left+width_mean,top+height_mean*(i/2-1),width_mean*0.9,height_mean*0.85);
			}
			CRect rect;    
			m_listDBData[i]->GetClientRect(&rect);  
			m_listDBData[i]->InsertColumn(0, _T("ȱ�ݺ�"), LVCFMT_CENTER, rect.Width()/5, 0);   
			m_listDBData[i]->InsertColumn(1, _T("�ְ��"), LVCFMT_CENTER, rect.Width()/5, 1);   
			m_listDBData[i]->InsertColumn(2, _T("�����"), LVCFMT_CENTER, rect.Width()/5, 2); 
			m_listDBData[i]->InsertColumn(3, _T("ԭ���"), LVCFMT_CENTER, rect.Width()/5, 3); 
			m_listDBData[i]->InsertColumn(4, _T("ʶ�����"), LVCFMT_CENTER, rect.Width()/5, 4); 
		}
		else
		{
			m_listDBData[i]->ShowWindow(false);
		}
	}

	//��������ļ��Ƿ�������ɹ�
	m_hDetectConfig.m_ThreadParam.hWnd=m_hWnd;
	m_hDetectConfig.m_ThreadParam.nData=0;
	m_hDetectConfig.m_ThreadParam.index=100;
	m_hDetectConfig.m_ThreadParam.bExit=false;
	m_hDetectConfig.BeginThread(ThreadProc);
	m_hDetectConfig.ResumeThread();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void DlgDefectFromDBClassify::OnBnClickedButtonConnectDb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	InitInfo();
	//
	//m_listDBData1.MoveWindow(
	//
	for(int i=1;i<=CArNTClassifierConsoleDlg::m_ConfigInfo.iCameraNum;i++)
	{
		m_hThread[i].m_ThreadParam.hWnd=m_hWnd;
		m_hThread[i].m_ThreadParam.nData=0;
		m_hThread[i].m_ThreadParam.index=i;
		m_hThread[i].m_ThreadParam.bExit=false;
		m_hThread[i].BeginThread(ThreadProc);
		m_hThread[i].ResumeThread();
	}
	m_hDetectConfig.EndThread();
	GetDlgItem(IDC_BUTTON_CONNECT_DB)->EnableWindow(false);
}

void DlgDefectFromDBClassify::InitInfo()
{
	//��ȡӦ�ó���·��
	TCHAR szFileName[MAX_PATH];
	::GetModuleFileName(NULL, szFileName, MAX_PATH);
	CString strFileName = szFileName;
	int nIndex = strFileName.ReverseFind('\\');
	m_strAppPath = strFileName.Left(nIndex);

	//�õ�ini�����ļ�·��
	m_FileIniOper.m_strFileName.Format(L"%s\\ClassifierInteraction.ini",m_strAppPath);
	CString strValue=L"";
	m_FileIniOper.Read(L"ImgSize",L"Norm",strValue);
	m_ClassifyConfig.bIsNorm=_ttoi(strValue);
	m_FileIniOper.Read(L"ImgSize",L"Width",strValue);
	m_ClassifyConfig.iImgWidth=_ttoi(strValue);
	m_FileIniOper.Read(L"ImgSize",L"Height",strValue);
	m_ClassifyConfig.iImgHeight=_ttoi(strValue);
	for(int i=0;i<64;i++)
	{
		CString strKey=L"";
		strKey.Format(L"Feat%d",i);
		if(0==m_FileIniOper.Read(L"Feats",strKey,strValue))
		{
			break;
		}
		else
		{
			m_ClassifyConfig.strFeatName[i]=strValue;
		}
	}
	m_FileIniOper.Read(L"Classifier",L"ClassifierFileName",strValue);
	m_ClassifyConfig.strClassifierFileName=strValue;
	//
	//��ʾ��Ϣ
	CString strInfo=L"";
	strInfo.Format(L"ȱ�����ݿ�λ�ã�%s",CArNTClassifierConsoleDlg::m_ConfigInfo.strDefectDBIP);
	m_listBoxShowLoadInfo.AddString(strInfo);
	for(int i=0;i<CArNTClassifierConsoleDlg::m_ConfigInfo.iDefectImgIP;i++)
	{
		strInfo.Format(L"ȱ��ͼ��λ�ã�%s",CArNTClassifierConsoleDlg::m_ConfigInfo.strDefectImgIP[i]);
		m_listBoxShowLoadInfo.AddString(strInfo);
	}
	strInfo.Format(L"������������%d",CArNTClassifierConsoleDlg::m_ConfigInfo.iCameraNum);
	m_listBoxShowLoadInfo.AddString(strInfo);
	strInfo.Format(L"���ͼ���ȣ�%d",CArNTClassifierConsoleDlg::m_ConfigInfo.iImgWidth);
	m_listBoxShowLoadInfo.AddString(strInfo);
	strInfo.Format(L"���ͼ��߶ȣ�%d",CArNTClassifierConsoleDlg::m_ConfigInfo.iImgHeight);
	m_listBoxShowLoadInfo.AddString(strInfo);

	if(true==m_ClassifyConfig.bIsNorm)
	{
		strInfo.Format(L"����ͼ���Ƿ�淶������");
	}
	else
	{
		strInfo.Format(L"����ͼ���Ƿ�淶������");
	}	
	m_listBoxShowLoadInfo.AddString(strInfo);
	strInfo.Format(L"ͼ��淶����ȣ�%d",m_ClassifyConfig.iImgWidth);
	m_listBoxShowLoadInfo.AddString(strInfo);
	strInfo.Format(L"ͼ��淶���߶ȣ�%d",m_ClassifyConfig.iImgHeight);
	m_listBoxShowLoadInfo.AddString(strInfo);
	for(int i=0;i<64;i++)
	{
		if(m_ClassifyConfig.strFeatName[i]!=L"")
		{
			strInfo.Format(L"ѡȡ������%s",m_ClassifyConfig.strFeatName[i]);
			m_listBoxShowLoadInfo.AddString(strInfo);
		}
		else
		{
			break;
		}
	}
	strInfo.Format(L"�������ļ���%s",m_ClassifyConfig.strClassifierFileName);
	m_listBoxShowLoadInfo.AddString(strInfo);
}

LRESULT DlgDefectFromDBClassify::OnMsgFunc1(WPARAM,LPARAM)
{
	int n=1;
	m_listDBData[n]->DeleteAllItems();
	for(int i=0;i<g_tDefectSet[n].iItemNum;i++)
	{
		CString strValue;
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iDefectNo);
		m_listDBData[n]->InsertItem(i, strValue);
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iSteelNo);
		m_listDBData[n]->SetItemText(i, 1, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iCameraNo);
		m_listDBData[n]->SetItemText(i, 2, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iClass);
		m_listDBData[n]->SetItemText(i, 3, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iGrade);
		m_listDBData[n]->SetItemText(i, 4, strValue); 
	}
	return 1;
}

LRESULT DlgDefectFromDBClassify::OnMsgFunc2(WPARAM,LPARAM)
{
	int n=2;
	m_listDBData[n]->DeleteAllItems();
	for(int i=0;i<g_tDefectSet[n].iItemNum;i++)
	{
		CString strValue;
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iDefectNo);
		m_listDBData[n]->InsertItem(i, strValue);
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iSteelNo);
		m_listDBData[n]->SetItemText(i, 1, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iCameraNo);
		m_listDBData[n]->SetItemText(i, 2, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iClass);
		m_listDBData[n]->SetItemText(i, 3, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iGrade);
		m_listDBData[n]->SetItemText(i, 4, strValue); 
	}
	return 1;
}
LRESULT DlgDefectFromDBClassify::OnMsgFunc3(WPARAM,LPARAM)
{
	int n=3;
	m_listDBData[n]->DeleteAllItems();
	for(int i=0;i<g_tDefectSet[n].iItemNum;i++)
	{
		CString strValue;
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iDefectNo);
		m_listDBData[n]->InsertItem(i, strValue);
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iSteelNo);
		m_listDBData[n]->SetItemText(i, 1, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iCameraNo);
		m_listDBData[n]->SetItemText(i, 2, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iClass);
		m_listDBData[n]->SetItemText(i, 3, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iGrade);
		m_listDBData[n]->SetItemText(i, 4, strValue); 
	}
	return 1;
}

LRESULT DlgDefectFromDBClassify::OnMsgFunc4(WPARAM,LPARAM)
{
	int n=4;
	m_listDBData[n]->DeleteAllItems();
	for(int i=0;i<g_tDefectSet[n].iItemNum;i++)
	{
		CString strValue;
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iDefectNo);
		m_listDBData[n]->InsertItem(i, strValue);
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iSteelNo);
		m_listDBData[n]->SetItemText(i, 1, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iCameraNo);
		m_listDBData[n]->SetItemText(i, 2, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iClass);
		m_listDBData[n]->SetItemText(i, 3, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iGrade);
		m_listDBData[n]->SetItemText(i, 4, strValue); 
	}
	return 1;
}
LRESULT DlgDefectFromDBClassify::OnMsgFunc5(WPARAM,LPARAM)
{
	int n=5;
	m_listDBData[n]->DeleteAllItems();
	for(int i=0;i<g_tDefectSet[n].iItemNum;i++)
	{
		CString strValue;
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iDefectNo);
		m_listDBData[n]->InsertItem(i, strValue);
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iSteelNo);
		m_listDBData[n]->SetItemText(i, 1, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iCameraNo);
		m_listDBData[n]->SetItemText(i, 2, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iClass);
		m_listDBData[n]->SetItemText(i, 3, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iGrade);
		m_listDBData[n]->SetItemText(i, 4, strValue); 
	}
	return 1;
}

LRESULT DlgDefectFromDBClassify::OnMsgFunc6(WPARAM,LPARAM)
{
	int n=6;
	m_listDBData[n]->DeleteAllItems();
	for(int i=0;i<g_tDefectSet[n].iItemNum;i++)
	{
		CString strValue;
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iDefectNo);
		m_listDBData[n]->InsertItem(i, strValue);
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iSteelNo);
		m_listDBData[n]->SetItemText(i, 1, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iCameraNo);
		m_listDBData[n]->SetItemText(i, 2, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iClass);
		m_listDBData[n]->SetItemText(i, 3, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iGrade);
		m_listDBData[n]->SetItemText(i, 4, strValue); 
	}
	return 1;
}
LRESULT DlgDefectFromDBClassify::OnMsgFunc7(WPARAM,LPARAM)
{
	int n=7;
	m_listDBData[n]->DeleteAllItems();
	for(int i=0;i<g_tDefectSet[n].iItemNum;i++)
	{
		CString strValue;
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iDefectNo);
		m_listDBData[n]->InsertItem(i, strValue);
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iSteelNo);
		m_listDBData[n]->SetItemText(i, 1, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iCameraNo);
		m_listDBData[n]->SetItemText(i, 2, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iClass);
		m_listDBData[n]->SetItemText(i, 3, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iGrade);
		m_listDBData[n]->SetItemText(i, 4, strValue); 
	}
	return 1;
}

LRESULT DlgDefectFromDBClassify::OnMsgFunc8(WPARAM,LPARAM)
{
	int n=8;
	m_listDBData[n]->DeleteAllItems();
	for(int i=0;i<g_tDefectSet[n].iItemNum;i++)
	{
		CString strValue;
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iDefectNo);
		m_listDBData[n]->InsertItem(i, strValue);
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iSteelNo);
		m_listDBData[n]->SetItemText(i, 1, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iCameraNo);
		m_listDBData[n]->SetItemText(i, 2, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iClass);
		m_listDBData[n]->SetItemText(i, 3, strValue); 
		strValue.Format(L"%d",g_tDefectSet[n].Items[i].iGrade);
		m_listDBData[n]->SetItemText(i, 4, strValue); 
	}
	return 1;
}