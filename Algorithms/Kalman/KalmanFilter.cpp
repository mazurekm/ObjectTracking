#include "KalmanFilter.h"
#include <FrameProcessing/PatternController.h>
#include <algorithm>

#include <opencv2/video/tracking.hpp>
#include <opencv2/videoio.hpp>


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


cv::MatND CKalmanFilter::calcBackProj(cv::Mat &img, int bins)
{

	cv::Mat hue, hsv = img.clone();
	m_container.perform(hsv);		
	hue.create(hsv.size(), hsv.depth());
	int ch[] = {0,0};

	cv::mixChannels(&hsv, 1, &hue, 1, ch, 1);

	cv::Mat hist;
	
	int histSize = std::max(bins, 2);
	float hueRange [] = {0, 180};
	const float *ranges [] = {hueRange};
	
	cv::calcHist(&hue, 1, 0, cv::Mat(), hist, 1, &histSize, ranges, true, false);
	cv::normalize(hist, hist, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());
	
	cv::MatND backProj;
	cv::calcBackProject(&hue, 1, 0, hist, backProj, ranges, 1, true);

	return backProj;
}


cv::Rect CKalmanFilter::templateMatching(cv::Mat& templ, cv::Mat &source, int method)
{
	int resCols = source.cols - templ.cols + 1;
	int resRows = source.rows - templ.rows + 1;
	
	cv::Mat result;
	result.create(resRows, resCols, CV_32FC1);

	cv::matchTemplate(source, templ, result, method );
	cv::normalize( result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );

	double minVal=0,  maxVal=0; 
	cv::Point minLoc, maxLoc;
	cv::Point matchLoc;

	cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );

	if(method  == CV_TM_SQDIFF || method == CV_TM_SQDIFF_NORMED )
	{ 
		matchLoc = minLoc;
	}
	else
	{ 
		matchLoc = maxLoc; 
	}

	cv::Rect rect(matchLoc, cv::Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ) );
	return rect;
}

void CKalmanFilter::perform(CVideoLoader &loader)
{
	cv::namedWindow(m_winName, CV_WINDOW_AUTOSIZE);
    CPatternController::getInstance().setWinName(m_winName);
  

	cv::TermCriteria criteria ( cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 10, 1 );	
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
				cv::Rect window = templateMatching(iter->second, frame, 0);
				cv::MatND back = calcBackProj(frame, 25);	
				cv::RotatedRect trackBox = cv::CamShift(back, window, criteria);
				cv::rectangle(frame, trackBox.boundingRect(), cv::Scalar(255,0,0),2,8);				
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

