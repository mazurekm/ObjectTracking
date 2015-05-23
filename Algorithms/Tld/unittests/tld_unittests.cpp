#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/Tld/TldAlgorithm.h>
#include <FrameProcessing/TransformContainer.h>
#include <FrameProcessing/ImageTransform.h>
#include <FrameProcessing/State.h>

BOOST_AUTO_TEST_CASE(PassTest)
{
	CTransformContainer container;
	container.addTransform( std::shared_ptr<CImageTransform>(new RgbToHsv()));
	container.addTransform( std::shared_ptr<CImageTransform>(new MedianBlur()));
	CTldAlgorithm tld(container, "tld");

    std::string path = "Tests/bin/sample1.avi";

    CVideoLoader loader(path);

    std::shared_ptr<State> state( new MarkState() );
    while (nullptr != state) {
        state = state->handle(loader, tld);
    }

	BOOST_CHECK(1);
}

