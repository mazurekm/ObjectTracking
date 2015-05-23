#ifndef ABSTRACT_ALGORITHM
#define ABSTRACT_ALGORITHM

#include<FrameProcessing/TransformContainer.h>
#include<FrameProcessing/VideoLoader.h>
#include<string>

class CAbstractAlgorithm
{
public:
    std::string m_winName;
	CAbstractAlgorithm(const CTransformContainer &container, const std::string &winName) : m_winName(winName), m_container(container)
	{
	}

	CAbstractAlgorithm(const std::string &winName) : m_winName(winName)
	{
	}

	virtual void perform(CVideoLoader &loader) = 0;
	
	bool interval(int miliSec)
	{
		int key = cv::waitKey(miliSec);
		if(1048603 == key || 27 == key)
		{
			return true;
		}		

		return false;
	}

protected:
	CTransformContainer m_container;

};

#endif
