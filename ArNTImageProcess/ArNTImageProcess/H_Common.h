#pragma once
#include <windows.h>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\nonfree\features2d.hpp> // ����surf�õ�
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp> // Hough������
#include <opencv2\gpu\gpu.hpp>

#include <iostream>
#include <fstream>
#include <vector> 
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <windows.h>
#include <string>
#include <sstream>	//�ַ���������ȥ��
using namespace std;
using namespace cv;
#define NTRAINING_SAMPLES   100         // Number of training samples per class
#define FRAC_LINEAR_SEP     0.9f        // Fraction of samples which compose the linear separable part
#define MAX_CLUSTERS (8)  

#define GLCM_DIS 3  //�Ҷȹ��������ͳ�ƾ���  
#define GLCM_CLASS 16 //����Ҷȹ��������ͼ��Ҷ�ֵ�ȼ���  
#define GLCM_ANGLE_HORIZATION 0  //ˮƽ  
#define GLCM_ANGLE_VERTICAL   1  //��ֱ  
#define GLCM_ANGLE_DIGONAL    2  //�Խ�  
#define PI 3.1415926


