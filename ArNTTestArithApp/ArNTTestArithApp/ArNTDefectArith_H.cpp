/////////////////////////////////////////////////
#include "ArNTDefectArith_H.h"
#include <ipps.h>
#include <ippi.h>
#include <ippcv.h>
#include <ippm.h>
#include <math.h>
#include "CommonFunc.h"
#include "H_DefectDetectInterface.h"
//构造函数

ArNTDefectArith_H::ArNTDefectArith_H()
{

}

ArNTDefectArith_H::~ArNTDefectArith_H()
{

}

bool ArNTDefectArith_H::_Initial(int camaraIndex)
{
	ReadArithSetInfo();
	return true;
}

//主算法函数
int  ArNTDefectArith_H::_DetectImgDefect(unsigned char* srcImg,int srcImgWidth,int srcImgHeight,PH_DefectSet pSet,int SteelNo,int ImgIndex,int CameralNo,unsigned char* dstImg)
{
	//double T_start = (double)cv::getTickCount();
	PH_DefectSet pH_DefectSet=new H_DefectSet;
	pH_DefectSet->iItemNum=0;

	pSet->iItemNum=0;
	m_imgSrcWidth=srcImgWidth;
	m_imgSrcHeight=srcImgHeight;

	m_ConfigurationInfo.tSteelInfo.iSquence=SteelNo;
	m_ConfigurationInfo.tSteelInfo.iCamera=CameralNo;
	m_ConfigurationInfo.tSteelInfo.iImgIndex=ImgIndex;
	H_DefectDetectInterfaceFunc(m_ConfigurationInfo.iProductionLineNo,srcImg,srcImgWidth,srcImgHeight,m_ConfigurationInfo,pH_DefectSet);

	for(int n=0;n<pH_DefectSet->iItemNum;n++)
	{
		if(false==m_ConfigurationInfo.bClassDetect[pH_DefectSet->Items[n].iDefectClass])
		{
			continue;
		}
		pSet->Items[pSet->iItemNum].iDefectClass=pH_DefectSet->Items[n].iDefectClass;
		pSet->Items[pSet->iItemNum].fConfidence=pH_DefectSet->Items[n].fConfidence;
		pSet->Items[pSet->iItemNum].iLeftInImage=pH_DefectSet->Items[n].iLeftInImage;
		pSet->Items[pSet->iItemNum].iRightInImage=pH_DefectSet->Items[n].iRightInImage;
		pSet->Items[pSet->iItemNum].iTopInImage=pH_DefectSet->Items[n].iTopInImage;
		pSet->Items[pSet->iItemNum].iBottomInImage=pH_DefectSet->Items[n].iBottomInImage;
		pSet->iItemNum++;
	}
	if(pH_DefectSet!= NULL)
	{
		delete pH_DefectSet;
	}
	return pSet->iItemNum;
}

//加日志文件
void ArNTDefectArith_H::AddLog(StrPointer strLogInfo)
{
	LONGSTR strAppName = {0};
	LONGSTR m_strLogPath = {0};
	LONGSTR m_strAppPath = {0};
	CCommonFunc::GetAppPath(m_strAppPath, STR_LEN(m_strAppPath));
	CCommonFunc::GetAppName(strAppName, STR_LEN(strAppName));
	CCommonFunc::SafeStringPrintf(m_strLogPath, STR_LEN(m_strLogPath), L"%s\\Log\\%s", m_strAppPath, strAppName);
	
	SYSTEMTIME NowTime;
	GetLocalTime(&NowTime);
	CCommonFunc::CreateDir(m_strLogPath);

	LONGSTR strLogFile = {0};
	CCommonFunc::SafeStringPrintf(strLogFile, STR_LEN(strLogFile), L"%s\\%d%02d%02d.txt", m_strLogPath, NowTime.wYear, NowTime.wMonth, NowTime.wDay);
	SHORTSTR strTime = {0};
	CCommonFunc::SafeStringPrintf(strTime, STR_LEN(strTime), L"%02d时%02d分%02d秒", NowTime.wHour, NowTime.wMinute, NowTime.wSecond);
	LONGSTR strTempLogInfo = {0};
	CCommonFunc::SafeStringPrintf(strTempLogInfo, STR_LEN(strTempLogInfo), L"[%s]:%s", strTime, strLogInfo);
	CCommonFunc::WriteStringToFile( strLogFile, strTempLogInfo);
}

//读取所有参数到结构中
bool ArNTDefectArith_H::ReadArithSetInfo()
{
	m_ConfigurationInfo.iDefectDetectGrade=0;
	
	LONGSTR strAppPath;
	CCommonFunc::GetAppPath(strAppPath, STR_LEN(strAppPath));
	wchar_t  strFilePath[256];
	CCommonFunc::SafeStringPrintf(strFilePath,STR_LEN(strFilePath), L"%s\\ArNTProcessParam.xml",strAppPath);

	LONGSTR strInfo={0};
	ArNTXMLOperator	m_XMLOperator;
	if(m_XMLOperator.LoadXML(strFilePath))
	{
		LONGSTR strValue = {0};	
		LONGSTR strName = {0};
		if(m_XMLOperator.GetValueByString(L"ArNTProcessParam#ProductionLineNumber", strValue))
		{
			m_ConfigurationInfo.iProductionLineNo=_wtoi(strValue);
		}
		if(m_XMLOperator.GetValueByString(L"ArNTProcessParam#All#DefectMaxNumForEvery", strValue))
		{
			m_ConfigurationInfo.iDefectMaxNum=_wtoi(strValue);
		}
		if(m_XMLOperator.GetValueByString(L"ArNTProcessParam#All#EdgeNoDetectPixel", strValue))
		{
			m_ConfigurationInfo.iEdgeNoDetect=_wtoi(strValue);		
		}
		if(m_XMLOperator.GetValueByString(L"ArNTProcessParam#All#FilterThreshold", strValue))
		{
			m_ConfigurationInfo.iFilterThreshold=_wtoi(strValue);		
		}
		if(m_XMLOperator.GetValueByString(L"ArNTProcessParam#All#AreaThreshold", strValue))
		{
			m_ConfigurationInfo.iAreaThreshold=_wtoi(strValue);		
		}
		if(m_XMLOperator.GetValueByString(L"ArNTProcessParam#All#SegmentationThreshold", strValue))
		{
			m_ConfigurationInfo.iSegmentationThreshold=_wtoi(strValue);		
		}
		if(m_XMLOperator.GetValueByString(L"ArNTProcessParam#All#DefectDetectGrade", strValue))
		{
			m_ConfigurationInfo.iDefectDetectGrade=_wtoi(strValue);
		}

		m_ConfigurationInfo.iCameraIndex=0;
		while(ArNT_TRUE)
		{
			CCommonFunc::SafeStringPrintf(strName, STR_LEN(strName), L"ArNTProcessParam#Edge#Camera%d", m_ConfigurationInfo.iCameraIndex);
			if(m_XMLOperator.GetValueByString(strName, strValue))
			{
				m_ConfigurationInfo.iCameraIndex++;
			}else
			{
				break;
			}
		}
		for(ShortInt i = 0; i < m_ConfigurationInfo.iCameraIndex; i++)
		{
			CCommonFunc::SafeStringPrintf(strName, STR_LEN(strName), L"ArNTProcessParam#Edge#Camera%d#CameraNum", i);
			if(m_XMLOperator.GetValueByString(strName, strValue))
			{
				m_ConfigurationInfo.iCameraNo[i]=_wtoi(strValue);
			}
			CCommonFunc::SafeStringPrintf(strName, STR_LEN(strName), L"ArNTProcessParam#Edge#Camera%d#LeftEdgeValue", i);
			if(m_XMLOperator.GetValueByString(strName, strValue))
			{
				m_ConfigurationInfo.iLeftEdgeLimit[m_ConfigurationInfo.iCameraNo[i]]=_wtof(strValue);
			}
			CCommonFunc::SafeStringPrintf(strName, STR_LEN(strName), L"ArNTProcessParam#Edge#Camera%d#RightEdgeValue", i);
			if(m_XMLOperator.GetValueByString(strName, strValue))
			{
				m_ConfigurationInfo.iRightEdgeLimit[m_ConfigurationInfo.iCameraNo[i]]=_wtof(strValue);
			}
		}
		
		m_ConfigurationInfo.iClassIndex=0;
		while(ArNT_TRUE)
		{
			CCommonFunc::SafeStringPrintf(strName, STR_LEN(strName), L"ArNTProcessParam#Class#Class%d", m_ConfigurationInfo.iClassIndex);
			if(m_XMLOperator.GetValueByString(strName, strValue))
			{
				m_ConfigurationInfo.iClassIndex++;
			}else
			{
				break;
			}
		}
		for(ShortInt i = 0; i < m_ConfigurationInfo.iClassIndex; i++)
		{
			CCommonFunc::SafeStringPrintf(strName, STR_LEN(strName), L"ArNTProcessParam#Class#Class%d#ClassName", i);
			if(m_XMLOperator.GetValueByString(strName, strValue))
			{
				m_ConfigurationInfo.iClassNo[i]=_wtoi(strValue);
			}
			CCommonFunc::SafeStringPrintf(strName, STR_LEN(strName), L"ArNTProcessParam#Class#Class%d#ClassDetect", i);
			if(m_XMLOperator.GetValueByString(strName, strValue))
			{
				int temp=_wtoi(strValue);
				if(temp>0)
				{
					m_ConfigurationInfo.bClassDetect[i]=true;
				}
				else
				{
					m_ConfigurationInfo.bClassDetect[i]=false;
				}
			}
			CCommonFunc::SafeStringPrintf(strName, STR_LEN(strName), L"ArNTProcessParam#Class#Class%d#ClassThreshold", i);
			if(m_XMLOperator.GetValueByString(strName, strValue))
			{
				m_ConfigurationInfo.fClassThreshold[i]=_wtof(strValue);
			}
		}
		AddLog(L"载入ArNTProcessParam.xml成功！");
		return true;
	}
	else
	{
		return false;
	}	
}
