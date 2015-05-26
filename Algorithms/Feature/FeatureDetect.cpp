#include "FeatureDetect.h"


#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>

#include <FrameProcessing/PatternController.h>
#include <Algorithms/Utils/NNMatcher.h>

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


void CFeatureDetect::perform(CVideoLoader &loader)
{
	CNNMatcher matcher;
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
				auto points = matcher.getMatchedPoints(source, templ);
				for(auto pt = points.begin(); pt != points.end(); ++pt)
				{
					cv::circle(frame, *pt, 7, cv::Scalar(255,0,0), -1); 
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

