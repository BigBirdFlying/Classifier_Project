///opencv�����ļ�
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\nonfree\features2d.hpp> // ����surf�õ�
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp> // Hough������
#include <opencv2\gpu\gpu.hpp>

///halcon�����ļ�
//#include "halconcpp.h"
//#include "halcon.h"
//#ifndef HC_LARGE_IMAGES
//#include <HALCONCpp/HalconCpp.h>
//#include <HALCONCpp/HDevThread.h>
//#  else
//#    include <HALCONCppxl/HalconCpp.h>
//#    include <HALCONCppxl/HDevThread.h>
//#  endif

#include <iostream>
#include <string>
#include <sstream>	//�ַ���������ȥ��
using namespace std;
//using namespace HalconCpp;
//using namespace cv;


#define uchar unsigned char

