#include "OpticalFlow.h"
#include <Algorithms/Utils/NNMatcher.h>

#include <FrameProcessing/PatternController.h>
#include<algorithm>

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
	cv:: Mat prevImg, nextImg;
	cv::namedWindow(m_winName, cv::WINDOW_AUTOSIZE );
	CPatternController::getInstance().setWinName(m_winName);
	CNNMatcher matcher;

	std::vector<cv::Point2f> fPrev, fNext;
	bool isInitialized = false;
	cv::Mat frame;	
			
	while(true)
	{
		if(false == CPatternController::getInstance().isMarkerActive()) 
		{
			prevImg = nextImg.clone();
			nextImg = loader.getNextFrame();
			frame = nextImg.clone();
			m_container.perform(nextImg);

			if(true == nextImg.empty())
			{
				break;
			}

            CPatternController::getInstance().setFrame( frame );

			auto imgVec = CPatternController::getInstance().getImgVec();
	
			for(auto iter = imgVec.begin(); iter != imgVec.end(); ++iter)
			{
				if(false == isInitialized)
				{
					isInitialized = true;
					cv::Mat src = iter->second.clone();
					m_container.perform(src);
					fNext = matcher.getMatchedPoints(nextImg, iter->second);
				}
				else
				{
					fPrev = fNext;
					std::vector<uchar> found;
					cv::Mat err;
					cv::calcOpticalFlowPyrLK(prevImg, nextImg, fPrev, fNext, found, err);	
				}
			}
			
			auto pointComp1 = [](const cv::Point2f &p1, const cv::Point2f &p2) {return p1.x < p2.x;};
			auto pointComp2 = [](const cv::Point2f &p1, const cv::Point2f &p2) {return p1.y < p2.y;};

			auto maxX = std::max_element(fNext.begin(), fNext.end(), pointComp1);
			auto maxY = std::max_element(fNext.begin(), fNext.end(), pointComp2);	
			
			auto minX = std::min_element(fNext.begin(), fNext.end(), pointComp1);
			auto minY = std::min_element(fNext.begin(), fNext.end(), pointComp2);	
			
			if(false == fNext.empty())
			{
				for(auto pt = fNext.begin(); pt != fNext.end(); ++pt)
				{
					cv::circle(frame, cv::Point(pt->x, pt->y), 5, cv::Scalar(255,0,0), CV_FILLED, 8, 0);
				}
				cv::rectangle(frame, cv::Point2f(minX->x, minY->y), cv::Point2f(maxX->x, maxY->y), cv::Scalar(255,0,0),2,8);		
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
