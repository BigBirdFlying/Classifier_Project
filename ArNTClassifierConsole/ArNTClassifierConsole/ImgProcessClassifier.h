#pragma once
//#include "H_Common.h"
//#include "H_DataTypeDef.h"
//typedef struct tagClassifierParam
//{
//	int iMaxIter;
//	float fEpsilon;
//	int iHideNode;
//	char fileName[128];
//}ClassifierParam,PClassifierParam;

class ImgProcessClassifier
{
public:
	ImgProcessClassifier(void);
	~ImgProcessClassifier(void);

	static void Classifier_BP(const Mat& trainData,const Mat& trainLabels,int iClassNum,ClassifierParam tClassifierParam);
	static void Classifier_SVM(const Mat& trainData,const Mat& trainLabels,int iClassNum,ClassifierParam tClassifierParam);

	static void Classifier_SVM_Predict(const Mat& testData,const Mat& testLabels,int iClassNum,ClassifierParam tClassifierParam,Mat& perLabels);
	static void Classifier_BP_Predict(const Mat& testData,const Mat& testLabels,int iClassNum,ClassifierParam tClassifierParam,Mat& perLabels);
};
