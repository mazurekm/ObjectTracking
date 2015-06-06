#include "OpticalFlow.h"
#include <Algorithms/Utils/NNMatcher.h>

#include <FrameProcessing/PatternController.h>
#include<algorithm>

#include <cassert>
#include <chrono>

COpticalFlow::COpticalFlow(const CTransformContainer &container, const std::string &winName) : 
		CAbstractAlgorithm(container, winName) 
{
	
}

COpticalFlow::COpticalFlow(const std::string &winName) : CAbstractAlgorithm(winName) 
{
	m_container.addTransform(std::shared_ptr<CImageTransform>(new RgbToGray()));	
}


std::vector<cv::Point2f> COpticalFlow::initOpticalFlow(cv::Mat &source, int fNum, float qLevel, int minDist)
{
	std::vector<cv::Point2f> feature;
	cv::goodFeaturesToTrack(source, feature, fNum, qLevel, minDist);	
  	return feature;	
}


void COpticalFlow::perform(CVideoLoader &loader, std::unique_ptr<CMeasuredData> &data) 
{
	cv::Mat templ = CPatternController::getInstance().getImgVec().begin()->second;
	m_container.perform(templ);

	cv:: Mat prevImg, nextImg;
	CNNMatcher matcher;

	std::vector<cv::Point2f> fPrev, fNext;
	bool isInitialized = false;
	cv::Mat frame;	
	cv::Rect rect;	

	std::chrono::time_point<std::chrono::system_clock> start, end;			
	while(true)
	{
		prevImg = nextImg.clone();
		nextImg = loader.getNextFrame();
		
		start = std::chrono::system_clock::now();	
		frame = nextImg.clone();

		if(true == nextImg.empty())
		{
			break;
		}

		m_container.perform(nextImg);
		
		if(false == isInitialized)
		{
			isInitialized = true;
			cv::Mat src = frame.clone();
			m_container.perform(src);
			fNext = matcher.getMatchedPoints(src, templ);
		}
		else
		{
			fPrev = fNext;
			std::vector<uchar> found;
			cv::Mat err;
			cv::calcOpticalFlowPyrLK(prevImg, nextImg, fPrev, fNext, found, err);	
		}
			
			
		if(false == fNext.empty())
		{
			rect = matcher.getRectangle(fNext, templ.cols, templ.rows);
			cv::rectangle(frame, rect, cv::Scalar(255,0,0), 2, 8);
		}
		else
		{
			assert(0&&"No points matching pattern found!");
		}
		
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
