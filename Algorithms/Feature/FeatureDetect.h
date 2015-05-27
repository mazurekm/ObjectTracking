#ifndef FEATURE_DETECT
#define FEATURE_DETECT

#include "../AbstractAlgorithm.h"

class CFeatureDetect : public CAbstractAlgorithm
{
public:
	CFeatureDetect(const CTransformContainer &container, const std::string &winName);
	CFeatureDetect(const std::string &winName);
	
	~CFeatureDetect()
	{
	}

	void perform(CVideoLoader &loader);

private:
	void featureDetect(const cv::Mat &source, const cv::Mat &templ, cv::Mat &frame);
};


#endif
