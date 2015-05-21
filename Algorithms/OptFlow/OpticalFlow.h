#ifndef OPTICAL_FLOW
#define OPTICAL_FLOW

#include "../AbstractAlgorithm.h"

class COpticalFlow : public CAbstractAlgorithm {
    COpticalFlow(const CTransformContainer &container, const std::string &winName);
    COpticalFlow(const std::string &winName);
    
    void perform(CVideoLoader &loader);
};

#endif
