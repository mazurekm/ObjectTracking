#include <FrameProcessing/VideoLoader.h>
#include <FrameProcessing/TransformContainer.h>

int main(int argc, char **argv)
{
	CVideoLoader loader(argv[1]);
	CTransformContainer container;

	container.addTransform( std::shared_ptr<CImageTransform>(new RgbToGray () ) );

	cv::namedWindow( "w", CV_WINDOW_AUTOSIZE);
	
	while(true)
	{

		cv::Mat frame = loader.getNextFrame();
		container.perform(frame);
		cv::imshow("w", frame);

		if(cv::waitKey(30) == 27)
		{
			break;
		}	
	}
	cv::waitKey(0);
}
