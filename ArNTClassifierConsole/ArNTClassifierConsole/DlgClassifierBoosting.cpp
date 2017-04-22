// DlgClassifierBoosting.cpp : 实现文件
//

#include "stdafx.h"
#include "ArNTClassifierConsole.h"
#include "DlgClassifierBoosting.h"


// DlgClassifierBoosting 对话框

IMPLEMENT_DYNAMIC(DlgClassifierBoosting, CDialog)

DlgClassifierBoosting::DlgClassifierBoosting(CWnd* pParent /*=NULL*/)
	: CDialog(DlgClassifierBoosting::IDD, pParent)
{

}

DlgClassifierBoosting::~DlgClassifierBoosting()
{
}

void DlgClassifierBoosting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgClassifierBoosting, CDialog)
END_MESSAGE_MAP()


// DlgClassifierBoosting 消息处理程序
