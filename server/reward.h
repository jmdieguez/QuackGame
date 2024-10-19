#ifndef SERVER_REWARD_H
#define SERVER_REWARD_H

#include <string>

#include "common_reward_id.h"

class Reward {
public:
    RewardID id;
    std::string name;
    Reward(const RewardID& an_id, const std::string& a_name): id(an_id), name(a_name) {}
    Reward(): id(RewardID::Undefined), name("Undefined") {}
    ~Reward() = default;
};

#endif  // SERVER_REWARD_H
