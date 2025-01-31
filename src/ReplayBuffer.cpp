#include "ReplayBuffer.h"
#include <random>
#include <iostream>

static std::random_device rd;
static std::mt19937 gen(rd());

ReplayBuffer::ReplayBuffer(size_t maxSize)
: max_size(maxSize)
{}

void ReplayBuffer::add(const Transition& t)
{
    if(buffer.size()>= max_size){
        buffer.erase(buffer.begin());
    }
    buffer.push_back(t);
}

Transition ReplayBuffer::sample()
{
    if(buffer.empty()){
        Transition tr;
        tr.done=true;
        return tr;
    }
    std::uniform_int_distribution<size_t> dist(0, buffer.size()-1);
    size_t idx= dist(gen);
    return buffer[idx];
}

void ReplayBuffer::addRewardToColor(PieceColor color, float rewardDelta)
{
    for(int i= (int)buffer.size()-1; i>=0; i--){
        if(!buffer[i].done && buffer[i].moveColor== color){
            buffer[i].reward += rewardDelta;
            buffer[i].done=true; // mark it done
            break;
        }
    }
}
