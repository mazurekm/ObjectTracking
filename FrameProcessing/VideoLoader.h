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
	
	bool interval(int miliSec)
	{
		int key = cv::waitKey(miliSec);
		if(1048603 == key || 27 == key)
		{
			return true;
		}		

		return false;
	}

private:
	std::string m_path;
	cv::VideoCapture m_capture;
	cv::Mat m_current;
	cv::VideoCapture cap;
};

#endif 
