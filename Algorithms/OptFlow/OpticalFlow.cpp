#include "OpticalFlow.h"

COpticalFlow::COpticalFlow(const CTransformContainer &container, const std::string &winName) : CAbstractAlgorithm(container, winName) {
}

COpticalFlow::COpticalFlow(const std::string &winName) : CAbstractAlgorithm(winName) {
}

void COpticalFlow::perform(CVideoLoader &loader) {
}
