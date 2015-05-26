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
					fNext = matcher.getMatchedPoints(frame, iter->second);

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
					cv::Rect rect = matcher.getRectangle(fNext, iter->second.cols, iter->second.rows);
					cv::rectangle(frame, rect, cv::Scalar(255,0,0), 2, 8);
				}
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
