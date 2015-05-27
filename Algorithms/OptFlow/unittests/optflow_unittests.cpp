#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/OptFlow/OpticalFlow.h>
#include <FrameProcessing/TransformContainer.h>
#include <FrameProcessing/ImageTransform.h>

#include <string>
#include <sstream>
#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_CASE(sample1_test)
{
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample1.avi";
	CVideoLoader loader(path);	

	COpticalFlow alg("optflow");
	alg.perform(loader);

}

BOOST_AUTO_TEST_CASE(sample2_test)
{
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample2.wmv";
	CVideoLoader loader(path);	


	COpticalFlow alg("optflow");
	alg.perform(loader);

	BOOST_CHECK(1);
}
