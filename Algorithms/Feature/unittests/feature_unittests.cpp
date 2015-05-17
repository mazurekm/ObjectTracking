#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/Feature/FeatureDetect.h>
#include <FrameProcessing/TransformContainer.h>
#include <FrameProcessing/ImageTransform.h>
#include <string>
#include <sstream>
#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_CASE(first_test)
{
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample1.avi";
	CVideoLoader loader(path);	

	CFeatureDetect alg("Feature");
	alg.perform(loader);
}
