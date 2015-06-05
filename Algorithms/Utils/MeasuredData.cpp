#include "MeasuredData.h"

#include<numeric>
#include<fstream>
#include<boost/algorithm/string/split.hpp>
#include<boost/algorithm/string/classification.hpp>
#include<boost/lexical_cast.hpp>
#include<vector>
#include<algorithm>
#include<cassert>
#include<cmath>


CMeasuredData::CMeasuredData(const std::string &file, const std::string &delim) : m_file(file)
{
	std::ifstream stream(m_file);
	std::vector<std::string> strVec;
	std::string line;
	
	while( std::getline(stream, line) )
	{
		boost::split(strVec, line, boost::is_any_of(delim) );
		
		if(4 != strVec.size())
		{
			assert(0&&"Incorrect data format");
		}


		try
		{
			cv::Point p1(boost::lexical_cast<double>(strVec[0]), boost::lexical_cast<double>(strVec[1]));
			cv::Point p2(boost::lexical_cast<double>(strVec[2]), boost::lexical_cast<double>(strVec[3]));		
			m_referenceList.push_back(std::make_pair(p1,p2));
		}
		catch(boost::bad_lexical_cast &)
		{
			assert(0&&"Incorrect data !");
		}

	}
	stream.close();
}


void CMeasuredData::addPredictPoints(const cv::Point &p1, const cv::Point &p2)
{
	m_predictList.push_back( std::make_pair(p1, p2) );
}

void CMeasuredData::addComputeTime(double time)
{
	m_timeList.push_back(time);
}

double CMeasuredData::getAvgTime()
{

	return std::accumulate(m_timeList.begin(), m_timeList.end(), 0.0) / (double) m_timeList.size();
}

std::pair<double, double> CMeasuredData::getAvgMark()
{
	auto refIter = m_referenceList.begin();
	auto predIter = m_predictList.begin();
	
	double avgXdiff = 0, avgYdiff = 0, areaDiff = 0;

	for(size_t i = 0; i<m_predictList.size(); ++i)
	{
		if(-1 != refIter->first.x)
		{
			double xRefVec = abs(refIter->first.x - refIter->second.x);
	   		double yRefVec = abs(refIter->first.y - refIter->second.y);
	
			double xPredVec = abs(predIter->first.x - predIter->second.x);
		   	double yPredVec = abs(predIter->first.y - predIter->second.y);

			areaDiff += abs(xRefVec * yRefVec - xPredVec * yPredVec); 

			avgXdiff += abs(refIter->first.x - predIter->first.x);
			avgYdiff += abs(refIter->first.y - predIter->first.y);	
			++predIter;
			++refIter;
		}	
	}	

	avgXdiff /= m_predictList.size();
	avgYdiff /= m_predictList.size();

	areaDiff /= m_predictList.size();

	return std::make_pair(sqrt(avgXdiff * avgXdiff + avgYdiff * avgYdiff), areaDiff);
}	

