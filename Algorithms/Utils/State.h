#ifndef STATE
#define STATE

#include <memory>
#include <FrameProcessing/VideoLoader.h>
#include <Algorithms/AbstractAlgorithm.h>
#include <Algorithms/Utils/MeasuredData.h>

class State {
    
public:
    State();
    ~State();
    virtual std::unique_ptr<State> handle(CVideoLoader &, CAbstractAlgorithm &, std::unique_ptr<CMeasuredData> &data) = 0;
};

class MarkState : public State {
    
public:
    MarkState();
    ~MarkState();
    std::unique_ptr<State> handle(CVideoLoader &, CAbstractAlgorithm &, std::unique_ptr<CMeasuredData> &data);
};

class TrackState : public State {
    
public:
    TrackState();
    ~TrackState();
    std::unique_ptr<State> handle(CVideoLoader &, CAbstractAlgorithm &, std::unique_ptr<CMeasuredData> &data);
};

#endif
