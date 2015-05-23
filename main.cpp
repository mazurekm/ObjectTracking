#include <FrameProcessing/VideoLoader.h>
#include <FrameProcessing/TransformContainer.h>
#include <FrameProcessing/PatternController.h>
#include <FrameProcessing/State.h>
#include <Algorithms/Tld/TldAlgorithm.h>
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
	CPatternController::getInstance().setWinName("bbb");	
	CTldAlgorithm tldAlgorithm(container, "tld");

	std::shared_ptr<State> state( new MarkState() );
	while (nullptr != state) {
		state = state->handle(loader, tldAlgorithm);
	}
}
