#include <FrameProcessing/VideoLoader.h>
#include <FrameProcessing/TransformContainer.h>
#include <FrameProcessing/PatternController.h>
#include <FrameProcessing/State.h>
#include <Algorithms/Tld/TldAlgorithm.h>
#include <Algorithms/OptFlow/OpticalFlow.h>
#include <cassert>
#include <iostream>

int main(int argc, char **argv)
{
	CVideoLoader loader;
	COpticalFlow flow("Flow");
	flow.perform(loader);
	return 0;
}
