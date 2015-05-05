#ifndef IMAGE_TRANSFORM
#define IMAGE_TRANSFORM

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


class CImageTransform
{
public:
	virtual void operator()(cv::Mat &frame) = 0;
};

class RgbToHsv : public CImageTransform
{
public:
	void operator()(cv::Mat &frame)
	{
		cv::Mat oldFrame = frame.clone();
		cv::cvtColor(oldFrame, frame, CV_RGB2HSV);
	}	
};

class RgbToGray : public CImageTransform
{
public:
	void operator()(cv::Mat &frame)
	{
		cv::Mat oldFrame = frame.clone();
		cv::cvtColor(oldFrame, frame, CV_RGB2GRAY);
	}	
};


#endif
