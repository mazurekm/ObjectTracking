#ifndef KALMAN_FILTER
#define KALMAN_FILTER

#include <opencv2/video/tracking.hpp>
#include <opencv2/videoio.hpp>

#include "../AbstractAlgorithm.h"
#include<utility>

class COpenCVimpl
{
public:
	COpenCVimpl(int dynamParams=4, int measureParams=2, int controlParams=0, int type=CV_32F);
	void init(int x1Pos, int y1Pos, int x2Pos, int y2Pos);
	cv::Mat correct(const cv::Mat &measurement);
	cv::Mat predict();
	bool isInitialized() const
	{
		return m_isInitialized;
	}

private:
	cv::KalmanFilter m_filter;
	bool m_isInitialized = false;
		
};


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
	std::pair<COpenCVimpl, COpenCVimpl> m_filterPair = std::make_pair(COpenCVimpl(), COpenCVimpl());
};


#endif
