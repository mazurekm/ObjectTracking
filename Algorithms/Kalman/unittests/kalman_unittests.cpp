#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/Kalman/KalmanFilter.h>
#include <FrameProcessing/TransformContainer.h>
#include <FrameProcessing/ImageTransform.h>
#include <boost/filesystem.hpp>


BOOST_AUTO_TEST_CASE(PassTest)
{
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample1.avi";
	CVideoLoader loader(path);	

	CKalmanFilter alg("kalman");
	alg.perform(loader);

	BOOST_CHECK(1);
}
