#include "TldAlgorithm.h"
#include <FrameProcessing/ImageMarker.h>

CTldAlgorithm::CTldAlgorithm(const CTransformContainer &container, const std::string &winName) : CAbstractAlgorithm(container, winName) 
{
	
}

void CTldAlgorithm::perform(CVideoLoader &loader)
{
	/*cv::namedWindow(m_winName, CV_WINDOW_AUTOSIZE);
	CImageMarker::getInstance()->setWinName(m_winName);	

	cv::Mat frame;
	while(true)
	{
		if(false == CImageMarker::getInstance()->isMarkerActive())
		{	
			frame = loader.getNextFrame();
			//m_container.perform(frame);
			CImageMarker::getInstance()->setFrame( frame );
			cv::imshow(m_winName, frame);
		}
		else
		{
			cv::imshow(m_winName, CImageMarker::getInstance()->getFrame() );
		}

		std::vector<cv::Mat> imgVec = CImageMarker::getInstance()->getImgVec();
		

		if(imgVec.size() > 0)
		{
			cv::namedWindow("aaa", CV_WINDOW_AUTOSIZE);
			cv::imshow("aaa",*imgVec.begin());		
		}

		if(cv::waitKey(20) == 27)
		{
			break;
		}	
	}
	*/	
}

