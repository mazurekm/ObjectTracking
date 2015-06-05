#ifndef ABSTRACT_ALGORITHM
#define ABSTRACT_ALGORITHM

#include<FrameProcessing/TransformContainer.h>
#include<FrameProcessing/VideoLoader.h>
#include<FrameProcessing/PatternController.h>
#include<Algorithms/Utils/MeasuredData.h>
#include<string>
#include<iostream>
#include<memory>

class CAbstractAlgorithm
{
public:
    std::string m_winName;
	CAbstractAlgorithm(const CTransformContainer &container, const std::string &winName) : m_winName(winName), m_container(container)
	{
	}

	CAbstractAlgorithm(const std::string &winName) : m_winName(winName)
	{
	}

	virtual ~CAbstractAlgorithm()
	{
		cv::destroyWindow(m_winName);
		CPatternController::getInstance().removeAllPatterns();
	}

	virtual void perform(CVideoLoader &loader, std::unique_ptr<CMeasuredData> &data) = 0;

	virtual cv::Rect templateMatching(cv::Mat& templ, cv::Mat &source, int method)
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

protected:
	CTransformContainer m_container;

};

#endif
