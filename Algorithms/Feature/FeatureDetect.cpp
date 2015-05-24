#include "FeatureDetect.h"


#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>

#include <FrameProcessing/PatternController.h>

#include<algorithm>
#include<vector>
#include<functional>

CFeatureDetect::CFeatureDetect(const CTransformContainer &container, const std::string &winName) : CAbstractAlgorithm(container, winName)
{

}

CFeatureDetect::CFeatureDetect(const std::string &winName) : CAbstractAlgorithm(winName)
{
	m_container.addTransform(std::shared_ptr<CImageTransform>(new RgbToGray()));
}



void CFeatureDetect::featureDetect(const cv::Mat &source, const cv::Mat &templ, cv::Mat &frame)
{
	int minHessian = 400;
	cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create( minHessian );

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

	cv::Mat imgMatches;
	if(false == goodMatches.empty())
	{
		drawMatches( templ, keypointsObject, frame, keypointsScene,
					goodMatches, imgMatches, cv::Scalar::all(-1), cv::Scalar::all(-1),
					std::vector<char>(), 2 );
		frame = imgMatches.clone();	
	}
}


void CFeatureDetect::perform(CVideoLoader &loader)
{
	cv:: Mat frame;
	cv::namedWindow(m_winName, cv::WINDOW_AUTOSIZE );
	CPatternController::getInstance().setWinName(m_winName);
	
	while(true)
	{
		
		if(false == CPatternController::getInstance().isMarkerActive()) 
		{
			frame = loader.getNextFrame();

			if(true == frame.empty())
			{
				break;
			}

            CPatternController::getInstance().setFrame( frame );

			auto imgVec = CPatternController::getInstance().getImgVec();
	
			cv::Mat source = frame.clone(); 
			m_container.perform(source);

			for(auto iter = imgVec.begin(); iter != imgVec.end(); ++iter)
			{
				cv::Mat templ = iter->second.clone();
				m_container.perform(templ);
				featureDetect(source, templ, frame);
			}	

			cv::imshow(m_winName, frame);
        }
		else
		{
            cv::imshow(m_winName, CPatternController::getInstance().getFrame() );
		}	

		if(true == interval(20)) break;

	}
}

