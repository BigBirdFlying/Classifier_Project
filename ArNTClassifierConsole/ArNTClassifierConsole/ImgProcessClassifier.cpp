#include "StdAfx.h"
#include "ImgProcessClassifier.h"

ImgProcessClassifier::ImgProcessClassifier(void)
{
}

ImgProcessClassifier::~ImgProcessClassifier(void)
{
}

void ImgProcessClassifier::Classifier_BP(const Mat& trainData,const Mat& trainLabels,int iClassNum,ClassifierParam tClassifierParam)
{
	Mat testLabels_BP = cv::Mat::zeros(trainData.rows, iClassNum, CV_32FC1); 
	for(int i=0;i<testLabels_BP.rows;i++)
	{
		for(int j=0;j<testLabels_BP.cols;j++)
		{
			if(j==(int)trainLabels.at<float>(i,0))
			{
				testLabels_BP.at<float>(i,j)=1;
			}
		}
	}
	int iFeatDims=trainData.cols;
	int iLabelNum=testLabels_BP.cols;
	Mat layerSizes=(Mat_<int>(1,3)<<iFeatDims,tClassifierParam.iHideNode,iLabelNum);
	CvANN_MLP mlp;
	mlp.create(layerSizes);
	CvANN_MLP_TrainParams params;
	params.term_crit=cvTermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS,tClassifierParam.iMaxIter,tClassifierParam.fEpsilon);
	mlp.train(trainData, testLabels_BP, Mat(),Mat(), params);  
	mlp.save(tClassifierParam.fileName);
}

void ImgProcessClassifier::Classifier_BP_Predict(const Mat& testData,const Mat& testLabels,int iClassNum,ClassifierParam tClassifierParam,Mat& perLabels)
{
	int iDataNumCorrect=0;
	int iDataNum=testData.rows;
	int iLabelNum=iClassNum;
	Mat nearest(iDataNum, iLabelNum, CV_32FC1, Scalar(0));

	CvANN_MLP neuralNetwork;
	neuralNetwork.load(tClassifierParam.fileName);
	neuralNetwork.predict(testData, nearest);
	for(int i=0;i<nearest.rows;i++)
	{
		float fConfMax=0;
		int ipre=0;
		for(int j=0;j<nearest.cols;j++)
		{
			if(nearest.at<float>(i,j)>fConfMax)
			{
				fConfMax=nearest.at<float>(i,j);
				ipre=j;
			}			
		}
		perLabels.at<float>(i,0)=ipre;
	}
}

void ImgProcessClassifier::Classifier_SVM(const Mat& trainData,const Mat& trainLabels,int iClassNum,ClassifierParam tClassifierParam)
{
	CvSVMParams Params;
    Params.svm_type    = SVM::C_SVC;
    Params.C           = 1;//0.1
    Params.kernel_type = SVM::LINEAR;
	Params.term_crit   = TermCriteria(CV_TERMCRIT_ITER, tClassifierParam.iMaxIter, tClassifierParam.fEpsilon);

    CvSVM svm;
    svm.train(trainData, trainLabels, Mat(), Mat(), Params);
	svm.save(tClassifierParam.fileName);	
}

void ImgProcessClassifier::Classifier_SVM_Predict(const Mat& testData,const Mat& testLabels,int iClassNum,ClassifierParam tClassifierParam,Mat& perLabels)
{
	int iDataNumCorrect=0;
	int iDataNum=testData.rows;
	CvSVM svm;
	svm.load(tClassifierParam.fileName);
	for(int i=0;i<testData.rows;i++)
	{
		float ipre = svm.predict(testData.row(i));
		perLabels.at<float>(i,0)=ipre;
	}
}