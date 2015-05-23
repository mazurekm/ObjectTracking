#include "KalmanFilter.h"
#include <FrameProcessing/PatternController.h>

CKalmanFilter::CKalmanFilter(const std::string &winName) : CAbstractAlgorithm(winName)
{
	m_container.addTransform(std::shared_ptr<CImageTransform>(new RgbToHsv()));
}

CKalmanFilter::CKalmanFilter(const CTransformContainer &container, const std::string &winName):
		CAbstractAlgorithm(container, winName)
{
	
}

CKalmanFilter::~CKalmanFilter()
{
}

void CKalmanFilter::perform(CVideoLoader &loader)
{
	cv::namedWindow(m_winName, CV_WINDOW_AUTOSIZE);
    CPatternController::getInstance().setWinName(m_winName);
  
	cv::Mat frame;

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
		
			
			for(auto iter = imgVec.begin(); iter != imgVec.end(); ++iter)
			{
				
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

