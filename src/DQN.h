#ifndef DQN_H
#define DQN_H

#include <torch/torch.h>
#include <memory>
#include <string>
#include <vector>
#include "ChessLogic.h" // use the same enum PieceColor

// enum class PieceColor { White, Black };

// RL net
struct NetImpl : torch::nn::Module {
    torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr};

    NetImpl(int inSize, int h1, int h2, int outSize);
    torch::Tensor forward(const torch::Tensor& x);
};
TORCH_MODULE(Net);

struct Transition {
    std::vector<float> state;  
    int action;
    float reward;
    std::vector<float> nextState;
    bool done;
    PieceColor moveColor; // which side moved
};

// forward declare
class ReplayBuffer;

class DQN {
public:
    DQN(int inputSize, int hidden1, int hidden2, int outputSize, float lr);

    // link external replay buffer
    void setReplay(ReplayBuffer* rep);

    // predict Q-values
    torch::Tensor predict(const std::vector<float>& input);

    // train batch
    void trainBatch(const std::vector<Transition>& batch, float gamma);

    // sync netOnline => netTarget
    void updateTarget();

    // fully implement: calls replay->addRewardToColor(...)
    void addRewardToColor(PieceColor color, float rewardDelta);

    // save/load
    void save(const std::string& path);
    void load(const std::string& path);

private:
    Net netOnline = nullptr; 
    Net netTarget = nullptr; 
    std::unique_ptr<torch::optim::Optimizer> optimizer;
    int inSize, outSize;

    ReplayBuffer* replay_;
};

#endif
