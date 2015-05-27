#include "TldAlgorithm.h"
#include "opencv2/tracking/tracker.hpp"
#include "tld/TLD.h"
#include <FrameProcessing/PatternController.h>
#include <iostream>

CTldAlgorithm::CTldAlgorithm(const CTransformContainer &container, const std::string &winName) : CAbstractAlgorithm(container, winName) 
{
	
}

void CTldAlgorithm::perform(CVideoLoader &loader)
{
	cv::namedWindow(m_winName, CV_WINDOW_AUTOSIZE);
    CPatternController::getInstance().setWinName(m_winName);

    tld::TLD tracker;
	bool isInitialized = false;
	cv::Rect rect;
	cv::Mat frame, frameGray;
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
				cv::Mat tmp = frame.clone();
				m_container.perform(tmp);
				if(false == isInitialized)
				{
					isInitialized = true;
					rect.x = iter->first.x; 
					rect.y = iter->first.y;
					rect.width = iter->second.cols;
				   	rect.height = iter->second.rows;
				   	frameGray = frame.clone();	
					cv::cvtColor(frame, frameGray, CV_BGR2GRAY);
				   	tracker.selectObject(frameGray, &rect);
				}
				cv::rectangle(frame,tracker.currBB->tl(),tracker.currBB->br(),cv::Scalar(255, 0, 0),2, 8);
			}
		
			cv::imshow(m_winName, frame);
				
		}
		else
		{
            cv::imshow(m_winName, CPatternController::getInstance().getFrame() );
		}

		if(true == interval(20)) break;
	}

	tracker.release();

	/*cv::Point point = CPatternController::getInstance().getImgVec().begin()->first;
    cv::Rect2d rect(
        point,
        cv::Point(
            point.x + CPatternController::getInstance().getImgVec().begin()->second.cols,
            point.y + CPatternController::getInstance().getImgVec().begin()->second.rows
        )
    );

	cv::Ptr<cv::TrackerTLD> tracker = cv::TrackerTLD::createTracker();
	cv::Mat frame = loader.getNextFrame();
	m_container.perform(frame);
	tracker.get()->init(frame, rect);
	std::cout << "tracker created" << std::endl;

	
	int frameCount = 1;
	while(true)
	{
		frame = loader.getNextFrame();

		if(true == frame.empty())
		{
			break;
		}

		cv::Mat frameForUpdate = frame.clone();
		m_container.perform(frameForUpdate);
		
        if (0 == frameCount) {
	      tracker.get()->update(frameForUpdate, rect);
	    }

	    cv::rectangle(frame,
           rect.tl(),
           rect.br(),
           cv::Scalar(255, 0, 0),
           2, 8
        );

		cv::imshow(m_winName, frame);
		frameCount = (25 == frameCount) ? 0 : frameCount+1;

		if(true == interval(20)) break;
	}*/
}

