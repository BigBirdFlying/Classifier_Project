///opencv引用文件
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\nonfree\features2d.hpp> // 这是surf用的
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp> // Hough在这里
#include <opencv2\gpu\gpu.hpp>

///halcon引用文件
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
#include <sstream>	//字符串串来串去用
using namespace std;
//using namespace HalconCpp;
//using namespace cv;


#define uchar unsigned char

