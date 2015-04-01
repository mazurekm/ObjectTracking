#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <memory>

int main()
{
	std::shared_ptr<cv::VideoCapture> cap(new cv::VideoCapture(0));
	if(false == cap->isOpened())
	{
		return -1;
	}


	cv::namedWindow("Video", CV_WINDOW_AUTOSIZE);

	while(true)
	{
		cv::Mat frame;
		cap->read(frame);
		cv::imshow("Video", frame);

		if(cv::waitKey(30) == 27)
		{
			break;
		}	
	}
	return 0;	
}
