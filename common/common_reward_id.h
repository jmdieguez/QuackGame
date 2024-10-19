#ifndef COMMON_REWARD_ID_H
#define COMMON_REWARD_ID_H

#include <cstdint>

enum class RewardID : uint8_t {
    Undefined = 0x0,
    BazookaReward = 0x10,
    ChainsawReward,
    DeathRayReward,
    ShotgunReward
};

#endif  // COMMON_REWARD_ID_H
