#include <FrameProcessing/VideoLoader.h>
#include <FrameProcessing/TransformContainer.h>
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

	CTldAlgorithm tld(container, "tld");
	tld.perform(loader);

}
