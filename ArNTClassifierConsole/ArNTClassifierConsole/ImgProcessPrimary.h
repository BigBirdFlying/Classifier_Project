#pragma once

class ImgProcessPrimary
{
public:
	ImgProcessPrimary(void);
	~ImgProcessPrimary(void);

	static void GetSobelFeat(Mat srcimg,vector<float>& feat);
	static void GetLBPFeat(Mat srcimg,vector<float>& feat);
};
