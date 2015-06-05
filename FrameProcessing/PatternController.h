#ifndef IMAGE_MARKER
#define IMAGE_MARKER


#include<opencv2/opencv.hpp>

#include<vector>
#include<iostream>
#include<cmath>
#include<memory>
#include <utility>


//void onMouse(int event, int x, int y, int flags, void *param);

class CPatternController
{
public:
	
	static CPatternController& getInstance()
	{
		static CPatternController marker;
		return marker;
	}

	std::vector<std::pair<cv::Point, cv::Mat>> getImgVec() const;

	void setFrame(const cv::Mat &img);
	
	void drawArea(int x, int y, int px, int py);

	cv::Mat getFrame() const;

	void addObject(int x, int y, int px, int py);
	void markerActivity(bool flag);
	bool isMarkerActive() const;
	void setWinName(const std::string &str);
	void removeAllPatterns();
	void saveTemplate(const std::string &filename);
	void addPattern(const cv::Mat &img, int x, int y);

private:
	CPatternController(const std::string &name);
	std::vector<std::pair<cv::Point, cv::Mat>> m_imgVec;
	std::string m_winName;
	bool m_isMarking = false;
	cv::Mat m_objToAdd;
	cv::Mat m_original;

	CPatternController();
	CPatternController(const CPatternController&) = delete;
	CPatternController(CPatternController &&) = delete;
	CPatternController & operator=(CPatternController &) = delete;
};

#endif 
