#include "State.h"
#include <FrameProcessing/ImageMarker.h>

State::State() {
}

State::~State() {
}

MarkState::MarkState() {
}

MarkState::~MarkState() {
}

std::shared_ptr<State> MarkState::handle(CVideoLoader & loader, CAbstractAlgorithm & algorithm) {
    cv::Mat frame;
    std::shared_ptr<State> retPtr( new TrackState() );
    std::vector<std::pair<cv::Point, cv::Mat>> imgVec = CImageMarker::getInstance().getImgVec();
    while(0 == imgVec.size()) {
        if(false == CImageMarker::getInstance().isMarkerActive()) {
            frame = loader.getNextFrame();
            //m_container.perform(frame);
            CImageMarker::getInstance().setFrame( frame );
            cv::imshow("bbb", frame);
        }
        else {
            cv::imshow("bbb", CImageMarker::getInstance().getFrame() );
        }

        imgVec = CImageMarker::getInstance().getImgVec(); 

        /*if(imgVec.size() > 0) {
            cv::namedWindow("aaa", CV_WINDOW_AUTOSIZE);
            cv::imshow("aaa",*imgVec.begin());      
        }*/

        if(cv::waitKey(20) == 27) {
            retPtr = nullptr;
            break;
        }   
    }
    return retPtr;
}

TrackState::TrackState() {
}

TrackState::~TrackState() {
}

std::shared_ptr<State> TrackState::handle(CVideoLoader & loader, CAbstractAlgorithm & algorithm) {
    algorithm.perform(loader);
    return nullptr; 
}