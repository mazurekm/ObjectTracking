#ifndef STATE
#define STATE

#include <memory>
#include <FrameProcessing/VideoLoader.h>
#include <Algorithms/AbstractAlgorithm.h>

class State {
    
public:
    State();
    ~State();
    virtual std::unique_ptr<State> handle(CVideoLoader &, CAbstractAlgorithm &) = 0;
};

class MarkState : public State {
    
public:
    MarkState();
    ~MarkState();
    std::unique_ptr<State> handle(CVideoLoader &, CAbstractAlgorithm &);
};

class TrackState : public State {
    
public:
    TrackState();
    ~TrackState();
    std::unique_ptr<State> handle(CVideoLoader &, CAbstractAlgorithm &);
};

#endif
