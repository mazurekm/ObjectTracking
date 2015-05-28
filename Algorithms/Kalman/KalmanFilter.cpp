#include "KalmanFilter.h"
#include <FrameProcessing/PatternController.h>
#include <algorithm>
#include <Algorithms/Utils/NNMatcher.h>

CKalmanFilter::CKalmanFilter(const std::string &winName) : CAbstractAlgorithm(winName)
{
	m_container.addTransform(std::shared_ptr<CImageTransform>(new RgbToHsv()));
}

CKalmanFilter::CKalmanFilter(const CTransformContainer &container, const std::string &winName):
		CAbstractAlgorithm(container, winName)
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

	if(true == CPatternController::getInstance().getImgVec().empty())
	{
		return;
	}

	cv::Mat templ = CPatternController::getInstance().getImgVec().begin()->second;

	cv::TermCriteria criteria ( cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 20, 1 );	
	cv::Mat frame;
	cv::Mat_<float> measureFirst(2,1), measureSecond(2,1);	

	CNNMatcher matcher;
	
	while(true)
	{
		frame = loader.getNextFrame();
		if(true == frame.empty())
		{
			break;
		}

		cv::Rect window = templateMatching(templ, frame, 0);
		//auto points = matcher.getMatchedPoints(frame, iter->second);
		//cv::Rect window = matcher.getRectangle(points, iter->second.cols, iter->second.rows);

		if(false == m_filterPair.first.isInitialized() || false == m_filterPair.second.isInitialized() )
		{
			m_filterPair.first.init(window.x, window.y, -1, -1);
			m_filterPair.second.init(window.x+window.width, window.y+window.height, -1, -1);	
		}

		m_filterPair.first.predict();
		m_filterPair.second.predict();

		//cv::MatND back = calcBackProj(frame, 25);	
		//cv::Rect trackBox =  cv::CamShift(back, window, criteria).boundingRect();
		measureFirst(0) = window.x;
		measureFirst(1) = window.y;	

		measureSecond(0) = window.x + window.width;
		measureSecond(1) = window.y + window.height;

		cv::Mat firstPoint = m_filterPair.first.correct(measureFirst);
		cv::Mat secondPoint = m_filterPair.second.correct(measureSecond); 
				
		window.x = firstPoint.at<float>(0);
		window.y = firstPoint.at<float>(1);
		window.height = secondPoint.at<float>(1) - firstPoint.at<float>(1); 
		window.width = secondPoint.at<float>(0) - firstPoint.at<float>(0);  

		cv::rectangle(frame, window, cv::Scalar(255,0,0),2,8);				
		
		cv::imshow(m_winName, frame);
				
		if(true == loader.interval(20)) break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


COpenCVimpl::COpenCVimpl(int dynamParams, int measureParams, int controlParams, int type) :
		m_filter(dynamParams, measureParams, controlParams, type)
{
				
}


void COpenCVimpl::init(int x1Pos, int y1Pos, int, int)
{
	//noise
	cv::setIdentity(m_filter.processNoiseCov, cv::Scalar::all(1e-4));
	cv::setIdentity(m_filter.measurementNoiseCov, cv::Scalar::all(3));
	cv::setIdentity(m_filter.errorCovPost, cv::Scalar::all(.1));

	//transition
	m_filter.transitionMatrix = (cv::Mat_<float>(4, 4) << 1, 0, 2, 0, 
														  0, 1, 0, 2, 
														  0, 0, 1, 0, 
														  0, 0, 0, 1);
	m_filter.statePre.at<float>(0) = x1Pos;
	m_filter.statePre.at<float>(1) = y1Pos;
	m_filter.statePre.at<float>(2) = 0;
	m_filter.statePre.at<float>(3) = 0;
	m_filter.statePre.at<float>(4) = 0;
	m_filter.statePre.at<float>(5) = 0;

	
	//measure
	cv::setIdentity(m_filter.measurementMatrix);
	
}

cv::Mat COpenCVimpl::correct(const cv::Mat &measurement)
{
	return m_filter.correct(measurement);	
}

cv::Mat COpenCVimpl::predict()
{
	return m_filter.predict();
}



