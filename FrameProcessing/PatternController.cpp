#include "PatternController.h"


void onMouse(int event, int x, int y, int flags, void *param)
{
	static int px = 0, py = 0; 
	static bool isClicked = false;

	if( event == cv::EVENT_LBUTTONDOWN )
	{
		px = x;
		py = y;
		isClicked = true;
		CPatternController::getInstance().markerActivity(true);	
	}
	else if(event == cv::EVENT_MOUSEMOVE)
	{
		if(true == isClicked)
		{
			CPatternController::getInstance().drawArea(x, y, px, py);					
		}
	}
	else if(event == cv::EVENT_LBUTTONUP )
	{
		CPatternController::getInstance().addObject(x, y, px, py);		

		CPatternController::getInstance().markerActivity(false);
		isClicked = false;	
	}
}


void CPatternController::removeAllPatterns()
{
	m_imgVec.clear();	
}


CPatternController::CPatternController()
{

}



std::vector<std::pair<cv::Point, cv::Mat>> CPatternController::getImgVec() const
{
	return m_imgVec;
}

void CPatternController::setFrame(const cv::Mat &img)
{
	m_objToAdd = img.clone();
	m_original = img.clone();
}


void CPatternController::addPattern(const cv::Mat &img, int x, int y)
{
	m_imgVec.push_back( std::make_pair(cv::Point(x,y),img) );
}

void CPatternController::drawArea(int x, int y, int px, int py)
{
	m_objToAdd = m_original.clone();
	if(x == px || y == py)
	{
		return;
	}

	if(x > px && y > py)
	{
		cv::rectangle(m_objToAdd, cv::Point(px, py), cv::Point(x, y), cv::Scalar(255, 0, 0), 2);	
	}
	else if(x < px)
	{
		cv::rectangle(m_objToAdd, cv::Point(x, py), cv::Point(px, y), cv::Scalar(255, 0, 0), 2);	
	}
	else if(y < py)
	{
		cv::rectangle(m_objToAdd, cv::Point(px, y), cv::Point(x, py), cv::Scalar(255, 0, 0), 2);	
	}
	else
	{
		cv::rectangle(m_objToAdd, cv::Point(x, y), cv::Point(px, py), cv::Scalar(255, 0, 0), 2);	
	}
}

cv::Mat CPatternController::getFrame() const
{
	return m_objToAdd;
}

void CPatternController::addObject(int x, int y, int px, int py)
{
	if(x == px || y == py)
	{
		return;
	}

	if(x > px && y > py)
	{
		cv::Rect roi(cv::Point(px+2, py+2), cv::Point(x-2, y-2));
		m_imgVec.push_back( std::make_pair(cv::Point(px+2, py+2), m_objToAdd(roi)) );	
	}
	else if(x < px)
	{
		cv::Rect roi(cv::Point(x+2, py+2), cv::Point(px-2, y-2));
		m_imgVec.push_back( std::make_pair(cv::Point(x+2, py+2), m_objToAdd(roi)) );	
	}
	else if(y < py)
	{
		cv::Rect roi(cv::Point(px+2, y+2), cv::Point(x-2, py-2));
		m_imgVec.push_back( std::make_pair(cv::Point(px+2, y+2), m_objToAdd(roi)) );	
	}
	else
	{
		cv::Rect roi(cv::Point(x+2, y+2), cv::Point(px-2, py-2));
		m_imgVec.push_back( std::make_pair(cv::Point(x+2, y+2), m_objToAdd(roi)) );	
	}
}

void CPatternController::saveTemplate(const std::string &filename)
{
	if(false == m_imgVec.empty() )
	{
		cv::imwrite(filename, m_imgVec.begin()->second);	
	}	
}

void CPatternController::markerActivity(bool flag)
{
	m_isMarking = flag;	
}

bool CPatternController::isMarkerActive() const
{
	return m_isMarking;
}

void CPatternController::setWinName(const std::string &str)
{
	m_winName = str;	
	cv::setMouseCallback(m_winName.c_str(), onMouse, 0 );
}
