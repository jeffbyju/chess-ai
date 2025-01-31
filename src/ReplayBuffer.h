#ifndef REPLAYBUFFER_H
#define REPLAYBUFFER_H

#include <vector>
#include "DQN.h" // for Transition, PieceColor

class ReplayBuffer {
public:
    ReplayBuffer(size_t maxSize);

    void add(const Transition& t);
    Transition sample();

    // modifies the last transition for that color which isn't done yet
    void addRewardToColor(PieceColor color, float rewardDelta);

    size_t size() const { return buffer.size(); }

private:
    std::vector<Transition> buffer;
    size_t max_size;
};

#endif
