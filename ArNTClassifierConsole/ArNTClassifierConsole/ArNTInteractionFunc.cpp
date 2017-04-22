#include "stdafx.h"
#include "ArNTInteractionFunc.h"
#include "H_DefectDetectInterface.h"

void ReadDefectRecordFromDB(HDBOper& hDBOper,CString strIP,CString strDBName,CString strType,CString strSQLCondition,long& iDefectMaxIndex, SteelDefectInfoSet& DefectSet)
{
	if(hDBOper.m_bConnected==false)
	{
		hDBOper.ConnectDB(strIP,strDBName,L"ARNTUSER",L"ARNTUSER",strType);
		hDBOper.GetDefectMaxNum(iDefectMaxIndex,L"select top 1 * from Defect order by ID desc");
	}
	CString strSQL=L"";
	strSQL.Format(L"select * from Defect where DefectNo>%d and Class=%d",iDefectMaxIndex,0);
	hDBOper.SearchDefect(DefectSet,iDefectMaxIndex,strSQL);
}

void GetDefectImgAndClassify(HDBOper& hDBOper,const SteelDefectInfoSet& DefectSet,CString strIP,int iCamIndex,int iImgWidth,int iImgHeight)
{
	for(int i=0;i<DefectSet.iItemNum;i++)
	{
		cv::Mat src;
		GetDefectImg(strIP,iCamIndex,DefectSet.Items[i].iSteelNo,DefectSet.Items[i].iImageIndex,iImgWidth,iImgHeight,src);
		cv::Rect rect(DefectSet.Items[i].iLeftInImg,DefectSet.Items[i].iTopInImg,abs(DefectSet.Items[i].iRightInImg-DefectSet.Items[i].iLeftInImg),abs(DefectSet.Items[i].iBottomInImg-DefectSet.Items[i].iTopInImg));
		cv::Mat src_ROI;
		if(src.rows>0&&src.cols>0)
		{
			GetDefectImgROI(src,rect,src_ROI);
			///进入分类器
			CString strInfo=L"";
			strInfo.Format(L"相机号：%d  缺陷号：%d  当前类别：%d",iCamIndex,DefectSet.Items[i].iDefectNo,DefectSet.Items[i].iClass);
			AddLog(strInfo);
				
			cv::resize(src_ROI,src_ROI,cv::Size(64,64));
			vector<float> vFeat;
			H_GetFeat(src_ROI,vFeat,"Sobel特征");
			cv::Mat testData=cvCreateMat(1,vFeat.size(),CV_32FC1);
			Mat OneImgFeat(vFeat); 
			Mat OneImgFeatT=OneImgFeat.reshape(0,1).clone();
			OneImgFeatT.copyTo(testData.row(0));
			Mat testLabels= cvCreateMat(1, 1, CV_32FC1);
			Mat perLabels= cvCreateMat(1, 1, CV_32FC1); 
			ClassifierParam			tClassifierParam;
			tClassifierParam.fEpsilon=0.0001;
			strcpy(tClassifierParam.fileName,"SVM_Classifier.xml");
			//tClassifierParam.fileName="SVM_Classifier.xml";
			tClassifierParam.iHideNode=30;
			tClassifierParam.iMaxIter=10000;
			H_ClassifierPredict("SVM分类器",testData,testLabels,perLabels,6,tClassifierParam);
			int perClass=(int)perLabels.at<float>(0,0);
			///分类后的类别写入数据库
			WriteDefectClassToDB(hDBOper,perClass,DefectSet.Items[i].iDefectNo);
		}
	}
}

void GetDefectImg(CString strIP,int iCamIndex,int iSquence,int iImgIndex,int iImgWidth,int iImgHeight,cv::Mat& image)
{
	CString strImgPath=L"";
	strImgPath.Format(L"\\\\%s\\CamDefectImage%d\\%d\\%04d.img",strIP,iCamIndex,iSquence,iImgIndex);

	FILE *fp=NULL;
	USES_CONVERSION;
	const char * imgpath=T2A(strImgPath.GetBuffer(0));
	fp=fopen(imgpath,"rb");

	if(fp==NULL)
	{
		AfxMessageBox(L"文件打开失败");
		return;
	}
	fseek(fp,0,SEEK_END); //定位到文件末 
	long nFileLen = ftell(fp); //文件长度
	char* Data = (char*)malloc(sizeof(char) * nFileLen);
	memset(Data, 0, sizeof(char) * nFileLen);
	fseek(fp,0,SEEK_SET); //定位到文件头
	while(!feof(fp))
	{
		fread(Data,nFileLen,1,fp);
	}
	fclose(fp);

	int offset=nFileLen-iImgWidth*iImgHeight;
	char *img=NULL;
	//img = (char*)malloc(sizeof(char) * iImgWidth*iImgHeight);
	//memset(img, 0, sizeof(char) * iImgWidth*iImgHeight);
	img=Data+offset;
	cv::Mat src = cv::Mat(iImgHeight,iImgWidth,CV_8UC1,img);

	//
	cv::Mat map_x,map_y;
	map_x.create( src.size(), CV_32FC1 );
	map_y.create( src.size(), CV_32FC1 );
	for( int i = 0; i < src.rows; i++ )
	{ 
		for( int j = 0; j < src.cols; j++ )
		{
			map_x.at<float>(i,j) = j ;
			map_y.at<float>(i,j) = src.rows - i ;
		}
	}
	remap( src, image, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0,0));
	//
	//cv::imwrite("1.bmp",src);
	//cv::imwrite("2.bmp",image);
	//free(img);
	free(Data);
	
}

void GetDefectImgROI(const cv::Mat& src,cv::Rect rect,cv::Mat& dst)
{
	src(rect).copyTo(dst);
}

//加日志文件
void AddLog(CString strInfo)
{
	TCHAR szFileName[MAX_PATH];
	if (::GetModuleFileName(NULL, szFileName, MAX_PATH))
	{
		//去掉文件名
		CString strFileName = szFileName;
		int nIndex = strFileName.ReverseFind('\\');
		CString strDirectory = strFileName.Left(nIndex);
		CString strText = _T("");
	}

	USES_CONVERSION;
	const char * info=T2A(strInfo.GetBuffer(0));
	TXTFILE_OPEN_START("log.txt")
		TXTFILE_ADD("提示",info)//TXTFILE_ADD("图像索引",(float)ImgIndex)
	TXTFILE_CLOSE_END
}

void WriteDefectClassToDB(HDBOper& hDBOper,int iperClass,int iDefectNo)
{
	if(hDBOper.m_bConnected==true)
	{
		CString strSQL=L"";
		strSQL.Format(L"update Defect set Class=%d where DefectNo=%d",iperClass,iDefectNo);
		hDBOper.UpdateDefectClass(strSQL);
	}
}