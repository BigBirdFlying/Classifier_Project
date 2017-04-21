#include "H_ClassifierRelation.h"

H_ClassifierRelation::H_ClassifierRelation(void)
{
}

H_ClassifierRelation::~H_ClassifierRelation(void)
{
}

void H_ClassifierRelation::GetSobelFeat(Mat srcimg,vector<float>& feat)
{
 	int ddepth=CV_16S;
	int delta=0;
	int scale=1;

	Mat srcimg_down1;
	pyrDown(srcimg,srcimg_down1,cv::Size(srcimg.rows/2,srcimg.cols/2));
	Mat dstimg2_1,dstimg2_2,dstimg2_3;
	Mat grad_x2, grad_y2;
	Mat abs_grad_x2, abs_grad_y2;
	Sobel( srcimg_down1, grad_x2, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
	convertScaleAbs( grad_x2, abs_grad_x2 );
	Sobel( srcimg_down1, grad_y2, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
	convertScaleAbs( grad_y2, abs_grad_y2 );
	addWeighted( abs_grad_x2, 0.5, abs_grad_y2, 0.5, 0, dstimg2_1 );
	addWeighted( abs_grad_x2, 0.5, abs_grad_x2, 0.5, 0, dstimg2_2 );
	addWeighted( abs_grad_y2, 0.5, abs_grad_y2, 0.5, 0, dstimg2_3 );
	
	double minVal2_1,maxVal2_1;
	cv::minMaxLoc(dstimg2_1,&minVal2_1,&maxVal2_1);
	double minVal2_2,maxVal2_2;
	cv::minMaxLoc(dstimg2_2,&minVal2_2,&maxVal2_2);
	double minVal2_3,maxVal2_3;
	cv::minMaxLoc(dstimg2_3,&minVal2_3,&maxVal2_3);
	for(int i=0;i<dstimg2_1.rows;i++)
	{
		for(int j=0;j<dstimg2_1.cols;j++)
		{
			float temp=0;
			temp=(dstimg2_1.at<uchar>(i,j)-minVal2_1)/(maxVal2_1-minVal2_1);
			feat.push_back(temp);
			temp=(dstimg2_2.at<uchar>(i,j)-minVal2_2)/(maxVal2_2-minVal2_2);
			feat.push_back(temp);
			temp=(dstimg2_3.at<uchar>(i,j)-minVal2_3)/(maxVal2_3-minVal2_3);
			feat.push_back(temp);
		}
	}

	Mat srcimg_down2;
	pyrDown(srcimg_down1,srcimg_down2,cv::Size(srcimg_down1.rows/2,srcimg_down1.cols/2));
	Mat dstimg3_1,dstimg3_2,dstimg3_3;
	Mat grad_x3, grad_y3;
	Mat abs_grad_x3, abs_grad_y3;
	Sobel( srcimg_down2, grad_x3, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
	convertScaleAbs( grad_x3, abs_grad_x3 );
	Sobel( srcimg_down2, grad_y3, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
	convertScaleAbs( grad_y3, abs_grad_y3 );
	addWeighted( abs_grad_x3, 0.5, abs_grad_y3, 0.5, 0, dstimg3_1 );
	addWeighted( abs_grad_x3, 0.5, abs_grad_x3, 0.5, 0, dstimg3_2 );
	addWeighted( abs_grad_y3, 0.5, abs_grad_y3, 0.5, 0, dstimg3_3 );
	
	double minVal3_1,maxVal3_1;
	cv::minMaxLoc(dstimg3_1,&minVal3_1,&maxVal3_1);
	double minVal3_2,maxVal3_2;
	cv::minMaxLoc(dstimg3_2,&minVal3_2,&maxVal3_2);
	double minVal3_3,maxVal3_3;
	cv::minMaxLoc(dstimg3_3,&minVal3_3,&maxVal3_3);
	
	for(int i=0;i<dstimg3_1.rows;i++)
	{
		for(int j=0;j<dstimg3_1.cols;j++)
		{
			float temp=0;
			temp=(dstimg3_1.at<uchar>(i,j)-minVal3_1)/(maxVal3_1-minVal3_1);
			feat.push_back(temp);
			temp=(dstimg3_2.at<uchar>(i,j)-minVal3_2)/(maxVal3_2-minVal3_2);
			feat.push_back(temp);
			temp=(dstimg3_3.at<uchar>(i,j)-minVal3_3)/(maxVal3_3-minVal3_3);
			feat.push_back(temp);
		}
	}

}

void H_ClassifierRelation::GetLBPFeat(Mat srcimg,vector<float>& feat)
{
	Mat src,dst;
	Mat _dst;
	srcimg.copyTo(src);
    _dst.create(src.rows-2, src.cols-2, CV_8UC1);  
	_dst.copyTo(dst);  
    dst.setTo(0);  
  
    for(int i=1;i<src.rows-1;i++) {  

        for(int j=1;j<src.cols-1;j++) {  
              
            char center = src.at<char>(i,j);  

            unsigned char code = 0;  
            code |= (src.at<char>(i-1,j-1) >= center) << 7;  
            code |= (src.at<char>(i-1,j  ) >= center) << 6;  
            code |= (src.at<char>(i-1,j+1) >= center) << 5;  
            code |= (src.at<char>(i  ,j+1) >= center) << 4;  
            code |= (src.at<char>(i+1,j+1) >= center) << 3;  
            code |= (src.at<char>(i+1,j  ) >= center) << 2;  
            code |= (src.at<char>(i+1,j-1) >= center) << 1;  
            code |= (src.at<char>(i  ,j-1) >= center) << 0;  
  
            dst.at<unsigned char>(i-1,j-1) = code;  
        }  
    }
	double minVal,maxVal;
	cv::minMaxLoc(dst,&minVal,&maxVal);
	for(int i=0;i<dst.rows;i++)
	{
		for(int j=0;j<dst.cols;j++)
		{
			float temp=(dst.at<uchar>(i,j)-minVal)/(maxVal-minVal);
			feat.push_back(temp);
		}
	}	
}


void H_ClassifierRelation::Classifier_BP(const Mat& trainData,const Mat& trainLabels,int iClassNum,ClassifierParam tClassifierParam)
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

void H_ClassifierRelation::Classifier_BP_Predict(const Mat& testData,Mat& perLabels,int iClassNum,ClassifierParam tClassifierParam)
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

void H_ClassifierRelation::Classifier_SVM(const Mat& trainData,const Mat& trainLabels,int iClassNum,ClassifierParam tClassifierParam)
{
	//CvSVMParams Params;
	//Params.svm_type    = SVM::C_SVC;
	//Params.C           = 1;//0.1
	//Params.kernel_type = SVM::RBF; //SVM::LINEAR;
	//Params.gamma = 0.01;
	//Params.term_crit   = TermCriteria(CV_TERMCRIT_ITER, tClassifierParam.iMaxIter, tClassifierParam.fEpsilon);

	//CvSVM svm;
	//svm.train(trainData, trainLabels, Mat(), Mat(), Params);
	//svm.save(tClassifierParam.fileName);

	///
	CvSVMParams param;    
	param.svm_type = CvSVM::EPS_SVR;    
	param.kernel_type = CvSVM::RBF;    
	param.C = 1;  //给参数赋初始值  
	param.p = 5e-3;  //给参数赋初始值  
	param.gamma = 0.01;  //给参数赋初始值  
	param.term_crit = cvTermCriteria(CV_TERMCRIT_EPS, 100, 5e-3);   
	//对不用的参数step设为0  
	CvParamGrid nuGrid = CvParamGrid(1,1,0.0);  
	CvParamGrid coeffGrid = CvParamGrid(1,1,0.0);  
	CvParamGrid degreeGrid = CvParamGrid(1,1,0.0);  

	CvSVM regressor;  
	regressor.train_auto(trainData,trainLabels,Mat(), Mat(),param,  
	10,  
	regressor.get_default_grid(CvSVM::C),  
	regressor.get_default_grid(CvSVM::GAMMA),  
	regressor.get_default_grid(CvSVM::P),  
	nuGrid,  
	coeffGrid,  
	degreeGrid);
	regressor.save(tClassifierParam.fileName);
}

void H_ClassifierRelation::Classifier_SVM_Predict(const Mat& testData,Mat& perLabels,int iClassNum,ClassifierParam tClassifierParam)
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