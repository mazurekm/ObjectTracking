#include "TldAlgorithm.h"
#include "opencv2/tracking/tracker.hpp"
#include <FrameProcessing/ImageMarker.h>
#include <iostream>

CTldAlgorithm::CTldAlgorithm(const CTransformContainer &container, const std::string &winName) : CAbstractAlgorithm(container, winName) 
{
	
}

void CTldAlgorithm::perform(CVideoLoader &loader)
{
	//cv::namedWindow(m_winName, CV_WINDOW_AUTOSIZE);
    cv::Point point = CImageMarker::getInstance().getImgVec().begin()->first;
    cv::Rect2d rect(
        point,
        cv::Point(
            point.x + CImageMarker::getInstance().getImgVec().begin()->second.cols,
            point.y + CImageMarker::getInstance().getImgVec().begin()->second.rows
        )
    );

	cv::Ptr<cv::TrackerTLD> tracker = cv::TrackerTLD::createTracker();
	tracker.get()->init(loader.getNextFrame(), rect);
	std::cout << "tracker created" << std::endl;

	
	int frameCount = 1;
	while(true)
	{
		cv::Mat frame = loader.getNextFrame();
		m_container.perform(frame);
		
        if (0 == frameCount) {
	      tracker.get()->update(frame, rect);
	    }

	    cv::rectangle(frame,
           rect.tl(),
           rect.br(),
           cv::Scalar(255, 255, 255),
           2, 8
        );

		cv::imshow(m_winName, frame);
		frameCount = (25 == frameCount) ? 0 : frameCount+1;

		if(cv::waitKey(10) == 27)
		{
			break;
		}	
	}
}

