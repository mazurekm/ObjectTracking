#include "PointContainer.h"
#include <fstream>

void CPointContainer::toFile(const std::string &file)
{
	std::ofstream stream(file);
	for(auto iter = m_pointList.begin(); iter != m_pointList.end(); ++iter)
	{
		stream <<iter->first.x <<";" <<iter->first.y <<";" <<iter->second.x <<";" <<iter->second.y << std::endl;			
	}	
	stream.close();

}

void CPointContainer::addPoint(const cv::Point &p1, const cv::Point &p2)
{
	m_pointList.push_back( std::make_pair(p1,p2) );
}

