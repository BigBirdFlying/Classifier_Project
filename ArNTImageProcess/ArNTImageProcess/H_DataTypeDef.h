#pragma once

#define MAX_NUM_CLASS  64
//缺陷数据结构体定义
typedef struct tagH_Defect
{	
	int		iLeftInImage;		//缺陷所在图像的左坐标位置
	int		iRightInImage;		//缺陷所在图像的右坐标位置
	int		iTopInImage;		//缺陷所在图像的顶坐标位置
	int		iBottomInImage;		//缺陷所在图像的底坐标位置
	float	fConfidence;
	int		iDefectClass;
}*PH_Defect, H_Defect;

typedef struct tagH_DefectSet
{
	enum {MAX_ITEMNUM = 1024};
	H_Defect Items[MAX_ITEMNUM];
	int iItemNum;
}H_DefectSet, *PH_DefectSet;

typedef struct tagClassifierParam
{
	int iMaxIter;
	float fEpsilon;
	int iHideNode;
	char fileName[128];
}ClassifierParam,*PClassifierParam;

typedef struct tagSteelInfo
{
	int iSquence;
	int iCamera;
	int iImgIndex;
}SteelInfo, *PSteelInfo;
typedef struct tagConfigurationInfo
{
	int iProductionLineNo;

	int iDefectMaxNum;
	int iEdgeNoDetect;
	int iFilterThreshold;
	int iAreaThreshold;
	int iSegmentationThreshold;
	int iDefectDetectGrade;

	enum {MAX_CAMERA_NUM = 16};
	int iCameraIndex;
	int iCameraNo[MAX_CAMERA_NUM];
	int iLeftEdgeLimit[MAX_CAMERA_NUM];
	int iRightEdgeLimit[MAX_CAMERA_NUM];
	
	enum {MAX_CLASS_NUM = 64};
	int iClassIndex;
	int iClassNo[MAX_CLASS_NUM];
	bool bClassDetect[MAX_CLASS_NUM];
	float fClassThreshold[MAX_CLASS_NUM];

	SteelInfo tSteelInfo;
}ConfigurationInfo, *PConfigurationInfo;

typedef struct tagConfigClass
{	
	int iInternalClassNo;
	int iExternalClassNo;
	char strClassName[128];
}*PConfigClass, ConfigClass;

typedef struct tagConfigClassSet
{
	enum {MAX_ITEMNUM = 1024};
	ConfigClass Items[MAX_ITEMNUM];
	int iItemNum;
}ConfigClassSet, *PConfigClassSet;

