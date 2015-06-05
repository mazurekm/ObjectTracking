#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/TldOpenCV/TldOpenCVAlgorithm.h>
#include <FrameProcessing/TransformContainer.h>
#include <FrameProcessing/ImageTransform.h>
#include <Algorithms/Utils/State.h>
#include <boost/filesystem.hpp>
#include <Algorithms/Utils/MeasuredData.h>
#include <iostream>

BOOST_AUTO_TEST_CASE(sample1_test)
{
	
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);
	path+="/";

	cv::Mat templ = cv::imread(path+"Tests/bin/temp1.png");
	CPatternController::getInstance().addPattern(templ,-1,-1);
	std::unique_ptr<CMeasuredData> ptr (new CMeasuredData(path+"Tests/bin/sample1.ref") );
	
	path += "Tests/bin/sample_1.wmv";
	CVideoLoader loader(path);	

	CTldOpenCVAlgorithm alg("sample1.ref");

	std::unique_ptr<State> state( new MarkState() );

	while (nullptr != state) 
	{
		state = state->handle(loader, alg, ptr);	 	
	}

	auto qual = ptr->getAvgMark();
	std::cout << ptr->getAvgTime() <<" " <<qual.first <<" " <<qual.second << std::endl; 
}


BOOST_AUTO_TEST_CASE(sample2_test)
{
	
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);
	path+="/";

	cv::Mat templ = cv::imread(path+"Tests/bin/temp2.png");
	CPatternController::getInstance().addPattern(templ,-1,-1);

	std::unique_ptr<CMeasuredData> ptr (new CMeasuredData(path+"Tests/bin/sample2.ref") );
	path += "Tests/bin/sample_2.wmv";
	CVideoLoader loader(path);	

	CTldOpenCVAlgorithm alg("sample2.csv");
	std::unique_ptr<State> state( new MarkState() );

	while (nullptr != state) 
	{
		state = state->handle(loader, alg, ptr);	 	
	}
	auto qual = ptr->getAvgMark();
	std::cout << ptr->getAvgTime() <<" " <<qual.first <<" " <<qual.second << std::endl; 

}

BOOST_AUTO_TEST_CASE(sample3_test)
{
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);
	path+="/";

	cv::Mat templ = cv::imread(path+"Tests/bin/temp3.png");
	CPatternController::getInstance().addPattern(templ,-1,-1);

	std::unique_ptr<CMeasuredData> ptr (new CMeasuredData(path+"Tests/bin/sample3.ref") );
	path += "Tests/bin/sample_3.wmv";
	CVideoLoader loader(path);	

	CTldOpenCVAlgorithm alg("sample3.csv");

	std::unique_ptr<State> state( new MarkState() );
	
	while (nullptr != state) 
	{
		state = state->handle(loader, alg, ptr);	 	
	}

	auto qual = ptr->getAvgMark();
	std::cout << ptr->getAvgTime() <<" " <<qual.first <<" " <<qual.second << std::endl; 

}

BOOST_AUTO_TEST_CASE(sample4_test)
{
	std::stringstream sst;
	sst << boost::filesystem::current_path();

	std::string path = sst.str();
	path.erase(path.begin());
	path.erase(path.end()-1);
	path+="/";

	cv::Mat templ = cv::imread(path+"Tests/bin/temp4.png");
	CPatternController::getInstance().addPattern(templ,-1,-1);

	std::unique_ptr<CMeasuredData> ptr (new CMeasuredData(path+"Tests/bin/sample4.ref") );
	path += "Tests/bin/sample_4.wmv";
	CVideoLoader loader(path);	

	CTldOpenCVAlgorithm alg("sample4.csv");

	std::unique_ptr<State> state( new MarkState() );

	while (nullptr != state) 
	{
		state = state->handle(loader, alg, ptr);	 	
	}
	
	auto qual = ptr->getAvgMark();
	std::cout << ptr->getAvgTime() <<" " <<qual.first <<" " <<qual.second << std::endl; 
}
