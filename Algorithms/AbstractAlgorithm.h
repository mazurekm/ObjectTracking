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

protected:
	CTransformContainer m_container;

};

#endif
