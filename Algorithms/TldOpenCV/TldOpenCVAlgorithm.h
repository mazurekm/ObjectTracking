#ifndef TLD_OPENCV_ALGORITHM
#define TLD_OPENCV_ALGORITHM

#include "../AbstractAlgorithm.h"

class CTldOpenCVAlgorithm : public CAbstractAlgorithm
{
public:
    CTldOpenCVAlgorithm(const CTransformContainer &container, const std::string &winName);
	CTldOpenCVAlgorithm(const std::string &winName);
    ~CTldOpenCVAlgorithm()
    {
    }
    
    void perform(CVideoLoader &loader, std::unique_ptr<CMeasuredData> &data);
};

#endif
