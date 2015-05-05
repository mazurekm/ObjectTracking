#include "VideoLoader.h"
#include <cassert>

CVideoLoader::CVideoLoader(const std::string &path) : m_capture(path)
{
	getNextFrame();
}

CVideoLoader::CVideoLoader() : m_capture(0)
{	
}


CVideoLoader::~CVideoLoader()
{
	m_capture.release();
}

cv::Mat CVideoLoader::getCurrentFrame()
{
	return m_current;
}

cv::Mat CVideoLoader::getNextFrame()
{
	if(true == m_capture.isOpened())
	{
		m_capture.read(m_current);
		return m_current;
	}

	assert(0 && "Video not loaded!");

	return cv::Mat();
}	
