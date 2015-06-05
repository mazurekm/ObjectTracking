#include "TldAlgorithm.h"
#include "opencv2/tracking/tracker.hpp"
#include "tld/TLD.h"
#include <FrameProcessing/PatternController.h>
#include <iostream>
#include <Algorithms/Utils/PointContainer.h>
#include <chrono>

CTldAlgorithm::CTldAlgorithm(const CTransformContainer &container, const std::string &winName) : CAbstractAlgorithm(container, winName) 
{
	
}

CTldAlgorithm::CTldAlgorithm(const std::string &winName) : CAbstractAlgorithm(winName)
{
	m_container.addTransform( std::shared_ptr<CImageTransform>(new RgbToHsv()));
	m_container.addTransform( std::shared_ptr<CImageTransform>(new MedianBlur()));
}

void CTldAlgorithm::perform(CVideoLoader &loader, std::unique_ptr<CMeasuredData> &data)
{
	cv::Mat templ = CPatternController::getInstance().getImgVec().begin()->second;
	CPointContainer points;
    tld::TLD tracker;
    tracker.trackerEnabled = trackerEnabled;
	tracker.alternating = alternating;
	tracker.learningEnabled = learningEnabled;
	bool isInitialized = false;
	cv::Rect rect;
	cv::Mat frame, frameGray;
	int frameCount = 1;
	std::chrono::time_point<std::chrono::system_clock> start, end;			

	while(true)
	{
		frame = loader.getNextFrame();
		if(true == frame.empty())
		{
			break;
		}

		start = std::chrono::system_clock::now();	
		if(false == isInitialized)
		{
			isInitialized = true;
			rect = templateMatching(templ, frame, 0); 
			frameGray = frame.clone();	
			cv::cvtColor(frame, frameGray, CV_BGR2GRAY);

			tracker.detectorCascade->imgWidth = frameGray.cols;
			tracker.detectorCascade->imgHeight = frameGray.rows;
			tracker.detectorCascade->imgWidthStep = frameGray.step;
			tracker.detectorCascade->varianceFilter->enabled = varianceFilterEnabled;
			tracker.detectorCascade->ensembleClassifier->enabled = ensembleClassifierEnabled;
			tracker.detectorCascade->nnClassifier->enabled = nnClassifierEnabled;
			tracker.detectorCascade->nnClassifier->thetaTP = thetaTP;
			tracker.detectorCascade->nnClassifier->thetaFP = thetaFP;
			tracker.detectorCascade->useShift = useShift;
			tracker.detectorCascade->shift = shift;
			tracker.detectorCascade->minScale = minScale;
			tracker.detectorCascade->maxScale = maxScale;
			tracker.detectorCascade->minSize = minSize;
			tracker.detectorCascade->numTrees = numTrees;

			tracker.selectObject(frameGray, &rect);
		}

		if (1 == frameCount % 2) 
		{
				tracker.processImage(frame);
		}

		if (tracker.currBB != NULL) {
				
			if(nullptr != data)
			{
				points.addPoint(tracker.currBB->tl(),tracker.currBB->br());
				data->addPredictPoints(tracker.currBB->tl(),tracker.currBB->br());
			}
			cv::rectangle(frame,tracker.currBB->tl(),tracker.currBB->br(),cv::Scalar(255, 0, 0),2, 8);
		}
		else if(nullptr != data)
		{
		//	points.addPoint(cv::Point(-1, -1), cv::Point(-1, -1));
			data->addPredictPoints(cv::Point(-1, -1), cv::Point(-1, -1));
		}
	
		end = std::chrono::system_clock::now();	

		std::chrono::duration<double> elapsedTime = end-start;
		if(nullptr != data)
		{
			data->addComputeTime( elapsedTime.count() );
		}

		cv::imshow(m_winName, frame);

		if(true == loader.interval(20)) break;
		frameCount = (frameCount + 1) % 2;
	}
	//points.toFile(m_winName);
	tracker.release();
}

