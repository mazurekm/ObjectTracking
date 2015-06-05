#ifndef OPTICAL_FLOW
#define OPTICAL_FLOW

#include "../AbstractAlgorithm.h"
#include<vector>

class COpticalFlow : public CAbstractAlgorithm 
{
public:
    COpticalFlow(const CTransformContainer &container, const std::string &winName);
    COpticalFlow(const std::string &winName);
    
	~COpticalFlow()
	{
	}

    void perform(CVideoLoader &loader, std::unique_ptr<CMeasuredData> &data);
private:
	std::vector<cv::Point2f> initOpticalFlow(cv::Mat &source, int fNum, float qLevel, int minDist);
};

#endif
