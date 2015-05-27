#ifndef TLD_ALGORITHM
#define TLD_ALGORITHM

#include "../AbstractAlgorithm.h"

class CTldAlgorithm : public CAbstractAlgorithm
{
public:
	CTldAlgorithm(const CTransformContainer &container, const std::string &winName);

	~CTldAlgorithm()
	{
	}
	
	void perform(CVideoLoader &loader);
};

#endif
