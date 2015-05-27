#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/Feature/FeatureDetect.h>
#include <FrameProcessing/TransformContainer.h>
#include <FrameProcessing/ImageTransform.h>
#include <FrameProcessing/State.h>
#include <string>
#include <sstream>
#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_CASE(sample0_test)
{
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample_0.avi";
	CVideoLoader loader(path);	

	CFeatureDetect alg("Feature");

	std::unique_ptr<State> state( new MarkState() );
	
	while (nullptr != state) 
	{
		state = state->handle(loader, alg);	 	
	}
}

BOOST_AUTO_TEST_CASE(sample1_test)
{
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample_1.wmv";
	CVideoLoader loader(path);	

	CFeatureDetect alg("Feature");

	std::unique_ptr<State> state( new MarkState() );
	
	while (nullptr != state) 
	{
		state = state->handle(loader, alg);	 	
	}
}


BOOST_AUTO_TEST_CASE(sample2_test)
{
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "tests/bin/sample_2.wmv";
	CVideoLoader loader(path);	

	CFeatureDetect alg("feature");
	std::unique_ptr<State> state( new MarkState() );
	
	while (nullptr != state) 
	{
		state = state->handle(loader, alg);	 	
	}
}

BOOST_AUTO_TEST_CASE(sample3_test)
{
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample_3.wmv";
	CVideoLoader loader(path);	

	CFeatureDetect alg("Feature");

	std::unique_ptr<State> state( new MarkState() );
	
	while (nullptr != state) 
	{
		state = state->handle(loader, alg);	 	
	}
}

BOOST_AUTO_TEST_CASE(sample4_test)
{
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample_4.wmv";
	CVideoLoader loader(path);	

	CFeatureDetect alg("Feature");

	std::unique_ptr<State> state( new MarkState() );
	
	while (nullptr != state) 
	{
		state = state->handle(loader, alg);	 	
	}
}
