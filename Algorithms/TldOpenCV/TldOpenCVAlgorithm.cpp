#include "TldOpenCVAlgorithm.h"
#include "opencv2/tracking/tracker.hpp"
#include <FrameProcessing/PatternController.h>
#include <iostream>

CTldOpenCVAlgorithm::CTldOpenCVAlgorithm(const CTransformContainer &container, const std::string &winName) : CAbstractAlgorithm(container, winName) 
{
    
}

void CTldOpenCVAlgorithm::perform(CVideoLoader &loader)
{
    cv::namedWindow(m_winName, CV_WINDOW_AUTOSIZE);
    CPatternController::getInstance().setWinName(m_winName);

    cv::Ptr<cv::TrackerTLD> tracker = cv::TrackerTLD::createTracker();
    bool isInitialized = false;
    cv::Rect2d rect;
    cv::Mat frame;
    int frameCount = 1;
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
                    tracker.get()->init(frame, rect);
                }
                if (1 == frameCount % 2) {
                    tracker.get()->update(tmp, rect);
                }
                cv::rectangle(frame,rect.tl(),rect.br(),cv::Scalar(255, 0, 0),2, 8);
            }
        
            cv::imshow(m_winName, frame);
                
        }
        else
        {
            cv::imshow(m_winName, CPatternController::getInstance().getFrame() );
        }

        if(true == interval(20)) break;
        frameCount = (frameCount + 1) % 2;
    }

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

