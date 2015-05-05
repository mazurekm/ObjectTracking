#ifndef VIDEO_LOADER
#define VIDEO_LOADER

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<string>

class CVideoLoader
{
public:
	CVideoLoader( const std::string &path );
	CVideoLoader();
	~CVideoLoader();

	cv::Mat getNextFrame();
	cv::Mat getCurrentFrame();	

private:
	std::string m_path;
	cv::VideoCapture m_capture;
	cv::Mat m_current;
};

#endif 
