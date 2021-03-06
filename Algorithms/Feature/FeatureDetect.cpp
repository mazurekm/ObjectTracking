#include "FeatureDetect.h"

#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>

#include <FrameProcessing/PatternController.h>
#include <Algorithms/Utils/NNMatcher.h>

#include<algorithm>
#include<vector>
#include<functional>

#include<chrono>

CFeatureDetect::CFeatureDetect(const CTransformContainer &container, const std::string &winName) : CAbstractAlgorithm(container, winName)
{

}

CFeatureDetect::CFeatureDetect(const std::string &winName) : CAbstractAlgorithm(winName)
{
	m_container.addTransform(std::shared_ptr<CImageTransform>(new RgbToGray()));
}


void CFeatureDetect::perform(CVideoLoader &loader, std::unique_ptr<CMeasuredData> &data)
{
	CNNMatcher matcher;
	cv:: Mat frame;
	cv::namedWindow(m_winName, cv::WINDOW_AUTOSIZE );
	
	if(true == CPatternController::getInstance().getImgVec().empty())
	{
		return;
	}

	cv::Mat templ = CPatternController::getInstance().getImgVec().begin()->second;
	m_container.perform(templ);


	std::chrono::time_point<std::chrono::system_clock> start, end;			
	while(true)
	{
		frame = loader.getNextFrame();
		start = std::chrono::system_clock::now();	
		
		if(true == frame.empty())
		{
			break;
		}

		cv::Mat source = frame.clone();
		m_container.perform(source);
		auto points = matcher.getMatchedPoints(source, templ);
		cv::Rect rect = matcher.getRectangle(points, templ.cols, templ.rows);
		cv::rectangle(frame, rect, cv::Scalar(255,0,0), 2, 8);

		end = std::chrono::system_clock::now();	
		std::chrono::duration<double> elapsedTime = end-start;

		if(nullptr != data)
		{
			data->addComputeTime( elapsedTime.count() );
			data->addPredictPoints(cv::Point(rect.x, rect.y), 
							cv::Point(rect.x+rect.width, rect.y+rect.height));
		}

		cv::imshow(m_winName, frame);

		if(true == loader.interval(20)) break;

	}
}

