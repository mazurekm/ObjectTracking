#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/TldOpenCV/TldOpenCVAlgorithm.h>
#include <FrameProcessing/TransformContainer.h>
#include <FrameProcessing/ImageTransform.h>
#include <FrameProcessing/State.h>
#include <boost/filesystem.hpp>


BOOST_AUTO_TEST_CASE(sample0_test)
{
	CTransformContainer container;
	container.addTransform( std::shared_ptr<CImageTransform>(new RgbToHsv()));
	container.addTransform( std::shared_ptr<CImageTransform>(new MedianBlur()));
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample_0.avi";
	CVideoLoader loader(path);	

    CTldOpenCVAlgorithm alg(container,"tld");
	
	std::unique_ptr<State> state( new MarkState() );
	
	while (nullptr != state) 
	{
		state = state->handle(loader, alg);	 	
	}
	
}

BOOST_AUTO_TEST_CASE(sample1_test)
{
	CTransformContainer container;
	container.addTransform( std::shared_ptr<CImageTransform>(new RgbToHsv()));
	container.addTransform( std::shared_ptr<CImageTransform>(new MedianBlur()));

	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample_1.wmv";
	CVideoLoader loader(path);	

    CTldOpenCVAlgorithm alg(container,"tld");
	
	std::unique_ptr<State> state( new MarkState() );
	
	while (nullptr != state) 
	{
		state = state->handle(loader, alg);	 	
	}
	
}

BOOST_AUTO_TEST_CASE(sample2_test)
{
	CTransformContainer container;
	container.addTransform( std::shared_ptr<CImageTransform>(new RgbToHsv()));
	container.addTransform( std::shared_ptr<CImageTransform>(new MedianBlur()));

	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample_2.wmv";
	CVideoLoader loader(path);	

    CTldOpenCVAlgorithm alg(container,"tld");

	std::unique_ptr<State> state( new MarkState() );
	
	while (nullptr != state) 
	{
		state = state->handle(loader, alg);	 	
	}
}

BOOST_AUTO_TEST_CASE(sample3_test)
{
	CTransformContainer container;
	container.addTransform( std::shared_ptr<CImageTransform>(new RgbToHsv()));
	container.addTransform( std::shared_ptr<CImageTransform>(new MedianBlur()));

	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample_3.wmv";
	CVideoLoader loader(path);	

    CTldOpenCVAlgorithm alg(container,"tld");
	
	std::unique_ptr<State> state( new MarkState() );
	
	while (nullptr != state) 
	{
		state = state->handle(loader, alg);	 	
	}
	
}

BOOST_AUTO_TEST_CASE(sample4_test)
{
	CTransformContainer container;
	container.addTransform( std::shared_ptr<CImageTransform>(new RgbToHsv()));
	container.addTransform( std::shared_ptr<CImageTransform>(new MedianBlur()));

	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);

	path = "Tests/bin/sample_4.wmv";
	CVideoLoader loader(path);	

    CTldOpenCVAlgorithm alg(container,"tld");
	
	std::unique_ptr<State> state( new MarkState() );
	
	while (nullptr != state) 
	{
		state = state->handle(loader, alg);	 	
	}
	
}
