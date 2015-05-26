#ifndef OPTICAL_FLOW
#define OPTICAL_FLOW

#include "../AbstractAlgorithm.h"
#include<vector>

class COpticalFlow : public CAbstractAlgorithm 
{
public:
    COpticalFlow(const CTransformContainer &container, const std::string &winName);
    COpticalFlow(const std::string &winName);
    
    void perform(CVideoLoader &loader);
private:
	std::vector<cv::Point2f> initOpticalFlow(cv::Mat &source, int fNum, float qLevel, int minDist);
};

#endif
