#include "ImageTransform.h"


void RgbToHsv::operator()(cv::Mat &frame)
{
	cv::Mat oldFrame = frame.clone();
	cv::cvtColor(oldFrame, frame, CV_BGR2HSV);
}

void RgbToGray::operator()(cv::Mat &frame)
{
	cv::Mat oldFrame = frame.clone();
	cv::cvtColor(oldFrame, frame, CV_RGB2GRAY);
}

void MedianBlur::operator()(cv::Mat &frame)
{
	cv::Mat oldFrame = frame.clone();
	cv::medianBlur(oldFrame, frame, 3);
}

Dilate::Dilate(int size, int type = 0)
{
	int dilation_type = 0;
	
	if(0 == type )
	{	
		dilation_type = cv::MORPH_RECT; 
	}
    else if( 1 == type)
	{ 
		dilation_type = cv::MORPH_CROSS; 
	}
    else if( 2 == type) 
	{ 
		dilation_type = cv::MORPH_ELLIPSE; 
	}
	m_structEl = getStructuringElement( dilation_type,
					                    cv::Size( 2*size + 1, 2*size+1 ),
										cv::Point( size, size ) );
}

void Dilate::operator()(cv::Mat &frame)
{
	cv::Mat copy = frame.clone();
	cv::dilate( copy, frame, m_structEl );	
}

Erode::Erode(int size, int type)
{
	
	int erosion_type = 0;
	
	if(0 == type )
	{	
		erosion_type = cv::MORPH_RECT; 
	}
    else if( 1 == type)
	{ 
		erosion_type = cv::MORPH_CROSS; 
	}
    else if( 2 == type) 
	{ 
		erosion_type = cv::MORPH_ELLIPSE; 
	}
	m_structEl = getStructuringElement( erosion_type,
					                    cv::Size( 2*size + 1, 2*size+1 ),
										cv::Point( size, size ) );
}

void Erode::operator()(cv::Mat &frame)
{
	cv::Mat copy = frame.clone();
	cv::erode( copy, frame, m_structEl );	
}

GaussianBlur::GaussianBlur(int width, int height,  double sigmaX, double sigmaY) : 
		m_width(width), m_height(height), m_sigmaX(sigmaX), m_sigmaY(sigmaY)
{
}

void GaussianBlur::operator()(cv::Mat &frame)
{
	cv::Mat copy = frame.clone();
	cv::GaussianBlur(copy, frame, cv::Size(m_width, m_height), m_sigmaX, m_sigmaY);
}



