#include "NNMatcher.h"

#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>

std::vector<cv::Point2f> CNNMatcher::getMatchedPoints(const cv::Mat &source, const cv::Mat &templ)
{
	cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create( m_minHessian );

	std::vector<cv::KeyPoint> keypointsObject, keypointsScene;
	cv::Mat descriptorsObject, descriptorsScene;

	detector->detectAndCompute( templ, cv::noArray(), keypointsObject, descriptorsObject );
	detector->detectAndCompute( source, cv::noArray(), keypointsScene, descriptorsScene ); 

	cv::FlannBasedMatcher matcher;
	std::vector< cv::DMatch > matches;
	matcher.match( descriptorsObject, descriptorsScene, matches );

	auto predicate = [](cv::DMatch i, cv::DMatch j) { return i.distance < j.distance;}; 

	auto minElIter = std::min_element(matches.begin(), matches.end(), predicate);

	double min = 100;	
	if(matches.end() != minElIter)
	{
		min = minElIter->distance;
	}

	std::vector< cv::DMatch > goodMatches;
			
	auto cond =  [&min](cv::DMatch el) {return el.distance <= std::max(2*min, 0.02);};
	std::copy_if(matches.begin(), matches.end(), std::back_inserter(goodMatches), cond);


	std::vector<cv::Point2f> result;
	for( size_t i = 0; i < goodMatches.size(); i++ )
	{
		result.push_back(keypointsScene[ goodMatches[i].trainIdx ].pt );
	}
	return result;
}

cv::Rect CNNMatcher::getRectangle(const std::vector<cv::Point2f> &points)
{
	return cv::Rect();
}	
