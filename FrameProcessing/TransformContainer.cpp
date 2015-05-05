#include "TransformContainer.h"

void CTransformContainer::addTransform(const std::shared_ptr<CImageTransform> &obj)
{
	m_transformVec.push_back(obj);
}

void CTransformContainer::perform(cv::Mat &frame)
{
	for(auto iter = m_transformVec.begin(); iter != m_transformVec.end(); ++iter)
	{
		(**iter)(frame);
	}
}

