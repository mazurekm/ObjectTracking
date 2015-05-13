#include "TldAlgorithm.h"

CTldAlgorithm::CTldAlgorithm(const CTransformContainer &container, const std::string &winName) : CAbstractAlgorithm(container, winName) 
{
	
}


void CTldAlgorithm::perform(CVideoLoader &loader)
{
	cv::namedWindow(m_winName, CV_WINDOW_AUTOSIZE);
	
	while(true)
	{
		cv::Mat frame = loader.getNextFrame();
		m_container.perform(frame);
		cv::imshow(m_winName, frame);

		if(cv::waitKey(30) == 27)
		{
			break;
		}	
	}
		
}

