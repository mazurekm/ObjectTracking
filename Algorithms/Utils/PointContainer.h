#ifndef POINT_CONTAINER
#define POINT_CONTAINER

#include<list>
#include<utility>
#include<opencv2/core/core.hpp>

class CPointContainer
{
public:
	CPointContainer() = default;
	void toFile(const std::string &file);
	void addPoint(const cv::Point &p1, const cv::Point &p2);

private:
	std::list<std::pair<cv::Point, cv::Point> > m_pointList;
};

#endif
