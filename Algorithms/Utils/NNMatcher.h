#ifndef NNMatcher
#define NNMatcher

#include <opencv2/core/core.hpp>
#include <vector>

class CNNMatcher
{
public:
	CNNMatcher(int minHessian = 400) : m_minHessian(minHessian)
	{

	}

	std::vector<cv::Point2f> getMatchedPoints(const cv::Mat &source, const cv::Mat &templ);
	cv::Rect getRectangle(const std::vector<cv::Point2f> &points, int width, int height);	
	
private:
	int m_minHessian;
};


#endif
