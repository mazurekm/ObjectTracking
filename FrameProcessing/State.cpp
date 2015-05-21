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
    cv::namedWindow(algorithm.m_winName, CV_WINDOW_AUTOSIZE);
    CImageMarker::getInstance().setWinName(algorithm.m_winName);
    std::shared_ptr<State> retPtr( new TrackState() );
    std::vector<std::pair<cv::Point, cv::Mat>> imgVec = CImageMarker::getInstance().getImgVec();
    while(0 == imgVec.size()) {
        if(false == CImageMarker::getInstance().isMarkerActive()) {
            frame = loader.getNextFrame();
            CImageMarker::getInstance().setFrame( frame );
            cv::imshow(algorithm.m_winName, frame);
        }
        else {
            cv::imshow(algorithm.m_winName, CImageMarker::getInstance().getFrame() );
        }

        imgVec = CImageMarker::getInstance().getImgVec(); 

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
