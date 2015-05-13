#include <FrameProcessing/VideoLoader.h>
#include <FrameProcessing/TransformContainer.h>
#include <FrameProcessing/ImageMarker.h>
#include <cassert>
#include <iostream>

int main(int argc, char **argv)
{
	if(1 >= argc)
	{
		assert(0&&"Wrong input parameter");
	}

	CVideoLoader loader(argv[1]);

	CTransformContainer container;
	container.addTransform( std::shared_ptr<CImageTransform>(new MedianBlur () ) );


	cv::namedWindow("bbb", CV_WINDOW_AUTOSIZE);
	CImageMarker::getInstance().setWinName("bbb");	

	cv::Mat frame;
	while(true)
	{
		if(false == CImageMarker::getInstance().isMarkerActive())
		{	
			frame = loader.getNextFrame();
			//m_container.perform(frame);
			CImageMarker::getInstance().setFrame( frame );
			cv::imshow("bbb", frame);
		}
		else
		{
			cv::imshow("bbb", CImageMarker::getInstance().getFrame() );
		}

		std::vector<cv::Mat> imgVec = CImageMarker::getInstance().getImgVec();
		

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
}
