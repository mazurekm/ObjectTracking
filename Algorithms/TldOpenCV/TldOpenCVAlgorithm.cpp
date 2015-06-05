#include "TldOpenCVAlgorithm.h"
#include "opencv2/tracking/tracker.hpp"
#include <FrameProcessing/PatternController.h>
#include <iostream>
#include <chrono>

CTldOpenCVAlgorithm::CTldOpenCVAlgorithm(const CTransformContainer &container, const std::string &winName) : CAbstractAlgorithm(container, winName) 
{
    
}

CTldOpenCVAlgorithm::CTldOpenCVAlgorithm(const std::string &winName) : CAbstractAlgorithm(winName)
{
	m_container.addTransform( std::shared_ptr<CImageTransform>(new RgbToHsv()));
	m_container.addTransform( std::shared_ptr<CImageTransform>(new MedianBlur()));	
}

void CTldOpenCVAlgorithm::perform(CVideoLoader &loader, std::unique_ptr<CMeasuredData> &data)
{
		
   	/*cv::Rect2d rect(
        point,
        cv::Point(
            point.x + CPatternController::getInstance().getImgVec().begin()->second.cols,
            point.y + CPatternController::getInstance().getImgVec().begin()->second.rows
        )
    );*/
	
	cv::Mat templ = CPatternController::getInstance().getImgVec().begin()->second; 
	cv::Ptr<cv::TrackerTLD> tracker = cv::TrackerTLD::createTracker();
    cv::Mat frame = loader.getNextFrame();
    
	cv::Rect rect = templateMatching(templ, frame, 0);
	cv::Rect2d rect2d(rect.x, rect.y, rect.width, rect.height);
	m_container.perform(frame);

    tracker.get()->init(frame, rect2d);
    std::cout << "tracker created" << std::endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;			
    while(true)
    {
        frame = loader.getNextFrame();
		
		start = std::chrono::system_clock::now();	
        if(true == frame.empty())
        {
            break;
        }

        cv::Mat frameForUpdate = frame.clone();
        m_container.perform(frameForUpdate);
        
        tracker.get()->update(frameForUpdate, rect2d);
				

        cv::rectangle(frame,
           rect2d.tl(),
           rect2d.br(),
           cv::Scalar(255, 0, 0),
           2, 8
        );
		
		end = std::chrono::system_clock::now();	
		std::chrono::duration<double> elapsedTime = end-start;

		if(nullptr != data)
		{
			data->addPredictPoints(rect2d.tl(), rect2d.br());
			data->addComputeTime( elapsedTime.count() );
		}

        cv::imshow(m_winName, frame);

        if(true == loader.interval(20)) break;
    }
}

