#ifndef KALMAN_FILTER
#define KALMAN_FILTER

#include "../AbstractAlgorithm.h"

class CKalmanFilter : public CAbstractAlgorithm
{
public:
	CKalmanFilter(const std::string &winName );
	CKalmanFilter(const CTransformContainer &container, const std::string &winName);
	~CKalmanFilter();

	void perform(CVideoLoader &loader);
	
private:
	cv::MatND calcBackProj(cv::Mat &img, int bins);
	cv::Rect templateMatching(cv::Mat& templ, cv::Mat &source, int method);

};


#endif
