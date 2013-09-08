#ifndef STAT_H
#define STAT_H

#include <memory>

template <class entity_type>
class State
{
public:
    //this will execute when the state is entered
    virtual void Enter(entity_type*)=0;
    //this is called by the miner’s update function each update step
    virtual void Execute(entity_type*)=0;
    //this will execute when the state is exited
    virtual void Exit(entity_type*)=0;
};

#endif 