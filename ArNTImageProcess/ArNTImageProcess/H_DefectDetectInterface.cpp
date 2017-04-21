#include "H_DefectDetectInterface.h"
#include "H_CommonImageProcess.h"
#include "H_RZ_DingXin_1780X_ImageProcess.h"
#include "H_ClassifierRelation.h"
#include "H_LB_XinJiangZhongHe_1X_ImageProcess.h"

//�������
H_CommonImageProcess							m_CommonImageProcess;
H_RZ_DingXin_1780X_ImageProcess					m_H_RZ_DingXin_1780X_ImageProcess;
H_LB_XinJiangZhongHe_1X_ImageProcess			m_H_LB_XinJiangZhongHe_1X_ImageProcess;

int  __stdcall  H_DefectDetectInterfaceFunc(int iIDMark,unsigned char* pImgData,int iImgWidth,int iImgHeight,ConfigurationInfo& tConfigurationInfo,PH_DefectSet pH_DefectSet,bool IsDebug)
{
	switch(iIDMark)
	{
		case TY_Common_0X:
			m_CommonImageProcess.K_ImageProcessInterfaceFunc(iIDMark,pImgData,iImgWidth,iImgHeight,tConfigurationInfo,pH_DefectSet,IsDebug);
			break;
		case BP_ChongGang_1X:
			break;
		case BP_ChongGang_2X:
			break;
		case BP_ChongGang_3X:
			break;
		case BP_BeiHaiChengDe_1X:
			break;
		case BP_BeiHaiChengDe_2X:
			break;
		case BP_LiuGang_1X:
			break;
		case KHB_NanGang_5000X:
			break;
		case KHB_XiangTan_3800X:
			break;
		case KHB_XiangTan_5000X:
			break;
		case KHB_ChongGang_4100X:
			break;
		case KHB_XingChengTeGang_1X:
			break;
		case RZ_ChongGang_1780X:
			break;
		case RZ_DingXin_1780X:
			break;
		case RZ_DingXin_850X:
			m_H_RZ_DingXin_1780X_ImageProcess.K_ImageProcessInterfaceFunc(iIDMark,pImgData,iImgWidth,iImgHeight,tConfigurationInfo,pH_DefectSet);
			break;
		case RZ_LiuGang_1450X:
			break;
		case GR_BeiHaiChengDe_1X:
			break;
		case GR_BeiHaiChengDe_2X:
			break;
		case GR_BeiHaiChengDe_3X:
			break;
		case LZ_TianChengBuXiu_1X:
			break;
		case LB_XiNanLv_1X:
			break;
		case LB_XinJiangZhongHe_1X:
			m_H_LB_XinJiangZhongHe_1X_ImageProcess.K_ImageProcessInterfaceFunc(iIDMark,pImgData,iImgWidth,iImgHeight,tConfigurationInfo,pH_DefectSet,IsDebug);
			break;
		case BC_HuaiGangBangCai_1X:
			break;
		default:
			break;
	}
	return 0;
}

int  __stdcall  H_GetFeats(const cv::Mat& src,vector<float>& feat,int FeatNameNum,char*strFeat,...)
{
	va_list argp;													/* ���屣�溯�������Ľṹ */    												/* ��¼�������� */    
    char *para;														/* ���ȡ�����ַ������� */                                            
    va_start( argp, FeatNameNum);									/* argpָ����ĵ�һ����ѡ����,msg�����һ��ȷ���Ĳ��� */          
    while (1)   
    {    
        para = va_arg( argp, char *);								/* ȡ����ǰ�Ĳ���������Ϊchar *. */    
		if(para != NULL)
		{															/* ���ÿմ�ָʾ����������� */    
            break; 
		}
        if (strcmp( para, "LBP") == 1)  
		{
			H_ClassifierRelation::GetLBPFeat(src,feat);
		}
		else if(strcmp( para, "Sobel") == 1) 
		{
			H_ClassifierRelation::GetSobelFeat(src,feat);
		}
		else
		{
			break;
		}
    }    
    va_end( argp );   
	return 0;
}

int  __stdcall  H_GetFeat(const cv::Mat& src,vector<float>& feat,char*strFeat)
{	
    if (strcmp( strFeat, "LBP����") == 0)  
	{
		H_ClassifierRelation::GetLBPFeat(src,feat);
	}
	else if(strcmp( strFeat, "Sobel����") == 0) 
	{
		H_ClassifierRelation::GetSobelFeat(src,feat);
	}
  
	return 0;
}

int  __stdcall  H_ClassifierTrain(char* strClassifierName,const cv::Mat& trainData,const cv::Mat& trainLabels,int iClassNum,ClassifierParam tClassifierParam)
{
	if (strcmp( strClassifierName, "BP������") == 0)  
	{
		H_ClassifierRelation::Classifier_BP(trainData,trainLabels,iClassNum,tClassifierParam);
	}
	else if(strcmp( strClassifierName, "SVM������") == 0)
	{
		H_ClassifierRelation::Classifier_SVM(trainData,trainLabels,iClassNum,tClassifierParam);
	}
	return 0;
}

int  __stdcall  H_ClassifierPredict(char* strClassifierName,const cv::Mat& testData,const cv::Mat& testLabels,cv::Mat& preLabels,int iClassNum,ClassifierParam tClassifierParam)
{
	if (strcmp( strClassifierName, "BP������") == 0)  
	{
		H_ClassifierRelation::Classifier_BP_Predict(testData,preLabels,iClassNum,tClassifierParam);
	}
	else if(strcmp( strClassifierName, "SVM������") == 0)
	{
		H_ClassifierRelation::Classifier_SVM_Predict(testData,preLabels,iClassNum,tClassifierParam);
	}
	return 0;
}