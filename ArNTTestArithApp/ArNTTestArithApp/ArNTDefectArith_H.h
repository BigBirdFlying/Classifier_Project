/////////////////////////////////////////////////
#pragma once
//#include "ArNTDefectDetectInterface.h"
#include "ArNTGrayBmp.h"
#include "H_DataTypeDef.h"

//��
class ArNTDefectArith_H	
{
public:
	ArNTDefectArith_H();
	~ArNTDefectArith_H(void);

public:
	ConfigurationInfo	m_ConfigurationInfo;

	int					m_imgSrcWidth;
	int					m_imgSrcHeight;

public:
	bool _Initial(int camaraIndex=0);
	//����⺯��
	int _DetectImgDefect( unsigned char* srcImg,int srcImgWidth,int srcImgHeight,PH_DefectSet pSet,int SteelNo=0,int ImgIndex=0,int CameralNo=0,unsigned char* dstImg=NULL);
	//���ܺ���
	void AddLog(StrPointer strLogInfo);
	bool ReadArithSetInfo();
};
