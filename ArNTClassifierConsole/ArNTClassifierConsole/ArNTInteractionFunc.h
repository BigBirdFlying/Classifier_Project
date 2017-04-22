#pragma once
#include "H_Common.h"
#include "HDBOper.h"
#include "HFile.h"

void ReadDefectRecordFromDB(HDBOper& hDBOper,CString strIP,CString strDBName,CString strType,CString strSQLCondition,long& iDefectMaxIndex, SteelDefectInfoSet& DefectSet);
void GetDefectImgAndClassify(HDBOper& hDBOper,const SteelDefectInfoSet& DefectSet,CString strIP,int iCamIndex,int iImgWidth,int iImgHeight);
void GetDefectImg(CString strIP,int iCamIndex,int iSquence,int iImgIndex,int iImgWidth,int iImgHeight,cv::Mat& image);
void GetDefectImgROI(const cv::Mat& src,cv::Rect rect,cv::Mat& dst);

void WriteDefectClassToDB(HDBOper& hDBOper,int iperClass,int iDefectNo);

void AddLog(CString strInfo);