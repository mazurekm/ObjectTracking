#ifndef TLD_ALGORITHM
#define TLD_ALGORITHM

#include "../AbstractAlgorithm.h"

class CTldAlgorithm : public CAbstractAlgorithm
{
    const bool alternating = false;
    const bool trackerEnabled = true;
    const bool learningEnabled = true;

    const bool varianceFilterEnabled = true;
    const bool ensembleClassifierEnabled = true;
    const bool nnClassifierEnabled = true;
    const bool useShift = true;
    const float shift = 0.1;
    const int minScale = -10;
    const int maxScale = 10;
    const int minSize = 25;
    const int numTrees = 10;
    const int numFeatures = 13;
    const float thetaTP = 0.65;
    const float thetaFP = 0.5;

public:
	CTldAlgorithm(const CTransformContainer &container, const std::string &winName);
	CTldAlgorithm(const std::string &winName);

	~CTldAlgorithm()
	{
	}
	
	void perform(CVideoLoader &loader, std::unique_ptr<CMeasuredData> &data);
};

#endif
