#include <FrameProcessing/VideoLoader.h>
#include <FrameProcessing/PatternController.h>
#include <Algorithms/Utils/State.h>
#include <Algorithms/Tld/TldAlgorithm.h>
#include <Algorithms/OptFlow/OpticalFlow.h>

int main(int argc, char **argv)
{
	CVideoLoader loader;
	std::unique_ptr<CMeasuredData> dataPtr;

	std::unique_ptr<State> state( new MarkState() );

	CTldAlgorithm alg("Tld");
	while (nullptr != state) 
	{
		state = state->handle(loader, alg, dataPtr);	 	
	}

	return 0;
}
