#include "OpticalFlow.h"
#include <Algorithms/Utils/NNMatcher.h>

#include <FrameProcessing/PatternController.h>
#include<algorithm>

#include <cassert>

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


void COpticalFlow::perform(CVideoLoader &loader) 
{

	cv::namedWindow(m_winName, cv::WINDOW_AUTOSIZE );
	
	if(true == CPatternController::getInstance().getImgVec().empty())
	{
		return;
	}

	cv::Mat templ = CPatternController::getInstance().getImgVec().begin()->second;
	m_container.perform(templ);

	cv:: Mat prevImg, nextImg;
	CNNMatcher matcher;

	std::vector<cv::Point2f> fPrev, fNext;
	bool isInitialized = false;
	cv::Mat frame;	
			
	while(true)
	{
		prevImg = nextImg.clone();
		nextImg = loader.getNextFrame();
		frame = nextImg.clone();
		m_container.perform(nextImg);

		if(true == nextImg.empty())
		{
			break;
		}

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
			cv::Rect rect = matcher.getRectangle(fNext, templ.cols, templ.rows);
			cv::rectangle(frame, rect, cv::Scalar(255,0,0), 2, 8);
		}
		else
		{
			assert(0&&"No points matching pattern found!");
		}

		cv::imshow(m_winName, frame);

		if(true == loader.interval(20)) break;

	}
}
