#ifndef KALMAN_FILTER
#define KALMAN_FILTER

#include "../AbstractAlgorithm.h"

class CKalmanFilter : public CAbstractAlgorithm
{
public:
	CKalmanFilter(const std::string &winName );
	CKalmanFilter(const CTransformContainer &container, const std::string &winName);
	~CKalmanFilter();

	void perform(CVideoLoader &loader);


};


#endif
