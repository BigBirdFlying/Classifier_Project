#pragma once
#include "h_baseimageprocess.h"

class H_ClassifierRelation
{
public:
	H_ClassifierRelation(void);
	~H_ClassifierRelation(void);

	static void GetSobelFeat(Mat srcimg,vector<float>& feat);
	static void GetLBPFeat(Mat srcimg,vector<float>& feat);

	static void Classifier_BP(const Mat& trainData,const Mat& trainLabels,int iClassNum,ClassifierParam tClassifierParam);
	static void Classifier_SVM(const Mat& trainData,const Mat& trainLabels,int iClassNum,ClassifierParam tClassifierParam);

	static void Classifier_SVM_Predict(const Mat& testData,Mat& perLabels,int iClassNum,ClassifierParam tClassifierParam);
	static void Classifier_BP_Predict(const Mat& testData,Mat& perLabels,int iClassNum,ClassifierParam tClassifierParam);
};

