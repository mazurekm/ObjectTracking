#ifndef MEASURED_DATA
#define MEASURED_DATA

#include<list>
#include<utility>
#include <opencv2/core/core.hpp>

struct Result
{
	Result(double w, double h, double dist) : width(w), height(h), distance(dist)
	{

	}

	double width;
	double height;
	double distance;
};

class CMeasuredData
{
public:
	CMeasuredData(const std::string &file, const std::string &delim = ";");
	void addPredictPoints(const cv::Point &p1, const cv::Point &p2);
	void addComputeTime(double time);
	double getAvgTime();
	Result getAvgMark();	

private:

	std::string m_file;
	std::list<double> m_timeList;
	std::list<std::pair<cv::Point, cv::Point> > m_predictList;
	std::list<std::pair<cv::Point, cv::Point> > m_referenceList;
};

#endif
