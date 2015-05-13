#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/Tld/TldAlgorithm.h>
#include <FrameProcessing/TransformContainer.h>
#include <FrameProcessing/ImageTransform.h>

BOOST_AUTO_TEST_CASE(PassTest)
{
	CTransformContainer container;
	container.addTransform( std::shared_ptr<CImageTransform>(new RgbToGray () ) );
	CTldAlgorithm tld(container, "tld");

	BOOST_CHECK(1);
}

