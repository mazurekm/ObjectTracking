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
	void operator()(cv::Mat &frame);
};

class RgbToGray : public CImageTransform
{
public:
	void operator()(cv::Mat &frame);
};

class MedianBlur : public CImageTransform
{
public:
	void operator()(cv::Mat &frame);
};

class Dilate : public CImageTransform
{
public:
	Dilate(int size, int type);
	void operator()(cv::Mat &frame);
private:
	cv::Mat m_structEl;
};

class Erode : public CImageTransform
{
public:
	Erode(int size, int type);
	void operator()(cv::Mat &frame);
private:
	cv::Mat m_structEl;
};

class GaussianBlur : public CImageTransform
{
public:
	GaussianBlur(int width, int height, double sigmaX, double sigmaY);
   	void operator()(cv::Mat &frame);	
private:
	int m_width;
	int m_height;
	double m_sigmaX;
	double m_sigmaY;
};


#endif
