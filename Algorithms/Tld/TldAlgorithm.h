#ifndef TLD_ALGORITHM
#define TLD_ALGORITHM

#include "../AbstractAlgorithm.h"

class CTldAlgorithm : public CAbstractAlgorithm
{
public:
	CTldAlgorithm(const CTransformContainer &container, const std::string &winName);
	void perform(CVideoLoader &loader);
};

#endif
