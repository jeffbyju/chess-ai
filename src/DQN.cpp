#include "DQN.h"
#include "ReplayBuffer.h"
#include <torch/serialize/archive.h>
#include <iostream>
#include <sstream>

static void copyWeights(Net& src, Net& dst) {
    // 1) Create an OutputArchive, save `src` into it
    torch::serialize::OutputArchive outArc;
    src->save(outArc);

    // 2) Write that archive to a memory buffer
    std::stringstream buffer;
    outArc.save_to(buffer);

    // 3) Create an InputArchive, read from that buffer, then load into `dst`
    torch::serialize::InputArchive inArc;
    inArc.load_from(buffer);
    dst->load(inArc);
}

NetImpl::NetImpl(int inSize, int h1, int h2, int outSize)
{
    fc1 = register_module("fc1", torch::nn::Linear(inSize, h1));
    fc2 = register_module("fc2", torch::nn::Linear(h1, h2));
    fc3 = register_module("fc3", torch::nn::Linear(h2, outSize));
}

torch::Tensor NetImpl::forward(const torch::Tensor& x)
{
    auto h1 = torch::relu(fc1->forward(x));
    auto h2 = torch::relu(fc2->forward(h1));
    return fc3->forward(h2);
}

DQN::DQN(int inputSize, int hidden1, int hidden2, int outputSize, float lr)
: inSize(inputSize), outSize(outputSize), replay_(nullptr)
{
    netOnline = Net(inputSize, hidden1, hidden2, outputSize);
    netTarget = Net(inputSize, hidden1, hidden2, outputSize);

    netOnline->to(torch::kCPU);
    netTarget->to(torch::kCPU);

    // copy netOnline => netTarget
    {
        torch::NoGradGuard noGrad;
        copyWeights(netOnline, netTarget);
    }

    optimizer = std::make_unique<torch::optim::Adam>(netOnline->parameters(), lr);
}

void DQN::setReplay(ReplayBuffer* rep)
{
    replay_ = rep;
}

torch::Tensor DQN::predict(const std::vector<float>& input)
{
    auto inT = torch::from_blob((void*)input.data(), {1,(long)inSize}, torch::kFloat32);
    return netOnline->forward(inT);
}

void DQN::trainBatch(const std::vector<Transition>& batch, float gamma)
{
    for(const auto& t : batch){
        auto sT= torch::from_blob((void*)t.state.data(), {1,(long)inSize}, torch::kFloat32);
        auto outOnline= netOnline->forward(sT);

        float predQ= outOnline[0][ t.action ].item<float>();

        auto nxt= torch::from_blob((void*)t.nextState.data(), {1,(long)inSize}, torch::kFloat32);
        auto outTarg= netTarget->forward(nxt);

        float maxNext=0.f;
        if(!t.done){
            float* dt= outTarg.data_ptr<float>();
            maxNext= dt[0];
            for(int i=1; i< outSize; i++){
                if(dt[i]>maxNext) maxNext= dt[i];
            }
        }
        float targetQ= t.reward + (t.done? 0.f : gamma*maxNext);

        auto copy= outOnline.clone().detach();
        copy[0][ t.action ]= targetQ;

        auto loss= torch::mse_loss(outOnline, copy);
        optimizer->zero_grad();
        loss.backward();
        optimizer->step();
    }
}

void DQN::updateTarget()
{
    torch::NoGradGuard noGrad;
    copyWeights(netOnline, netTarget);
}

// fully implement
void DQN::addRewardToColor(PieceColor color, float rewardDelta)
{
    if(!replay_){
        std::cerr<<"[DQN] No replay set; cannot addRewardToColor.\n";
        return;
    }
    replay_->addRewardToColor(color, rewardDelta);
}

void DQN::save(const std::string& path)
{
    torch::serialize::OutputArchive arc;
    netOnline->save(arc);
    arc.save_to(path);
    std::cout<<"[C++] DQN saved => "<<path<<"\n";
}

void DQN::load(const std::string& path)
{
    torch::serialize::InputArchive inArc;
    inArc.load_from(path);
    netOnline->load(inArc);
    // sync netTarget
    {
        torch::NoGradGuard noGrad;
        copyWeights(netOnline, netTarget);
    }
    std::cout<<"[C++] DQN loaded => "<<path<<"\n";
}

