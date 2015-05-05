#ifndef TRANSFORM_CONTAINER
#define TRANSFORM_CONTAINER

#include <vector>
#include <memory>
#include "ImageTransform.h"


class CTransformContainer
{
public:
	CTransformContainer() {}
	void addTransform(const std::shared_ptr<CImageTransform> &obj);
	void perform(cv::Mat &frame);

private:
	std::vector<std::shared_ptr<CImageTransform> > m_transformVec;	
};

#endif
