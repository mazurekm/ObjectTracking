#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


int main()
{
	cv::VideoCapture cap(0);
	if(false == cap.isOpened())
	{
		return -1;
	}


	double fps = cap.get(CV_CAP_PROP_FPS);
	cv::namedWindow("Video", CV_WINDOW_AUTOSIZE);

	while(true)
	{
		cv::Mat frame;
		cap.read(frame);
		cv::imshow("Video", frame);

		if(cv::waitKey(30) == 27)
		{
			break;
		}	
	}
	return 0;	
}
