#include "TldOpenCVAlgorithm.h"
#include "opencv2/tracking/tracker.hpp"
#include <FrameProcessing/PatternController.h>
#include <iostream>

CTldOpenCVAlgorithm::CTldOpenCVAlgorithm(const CTransformContainer &container, const std::string &winName) : CAbstractAlgorithm(container, winName) 
{
    
}

void CTldOpenCVAlgorithm::perform(CVideoLoader &loader)
{
    cv::Point point = CPatternController::getInstance().getImgVec().begin()->first;
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

        if(true == loader.interval(20)) break;
    }
}

