#include "OpticalFlow.h"
#include <FrameProcessing/PatternController.h>

COpticalFlow::COpticalFlow(const CTransformContainer &container, const std::string &winName) : 
		CAbstractAlgorithm(container, winName) 
{
	
}

COpticalFlow::COpticalFlow(const std::string &winName) : CAbstractAlgorithm(winName) 
{
	
}

void COpticalFlow::perform(CVideoLoader &loader) 
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
