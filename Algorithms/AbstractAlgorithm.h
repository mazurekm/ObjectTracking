#include<FrameProcessing/TransformContainer.h>
#include<FrameProcessing/VideoLoader.h>
#include<string>

class CAbstractAlgorithm
{
public:
	CAbstractAlgorithm(const CTransformContainer &container, const std::string &winName) : m_winName(winName), m_container(container)
	{
	}

	virtual void perform(CVideoLoader &loader) = 0;

protected:
	std::string m_winName;
	CTransformContainer m_container;

};
