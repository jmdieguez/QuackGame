#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "server_reward.h"

#define BAZOOKA_RESPAWN_TIMER 15
#define CHAINSAW_RESPAWN_TIMER 5
#define DEATHRAY_RESPAWN_TIMER 20
#define SHOTGUN_RESPAWN_TIMER 10

class Item {
private:
    bool picked_up = false;
    int respawn_timer_start;
    int remaining_iterations;
    std::string name = "Undefined";
    RewardID reward_id = RewardID::Undefined;

public:
    explicit Item(const int& n_iterations, const char* gun_name, const RewardID& r_id):
            respawn_timer_start(n_iterations),
            remaining_iterations(0),
            name(gun_name),
            reward_id(r_id) {}
    virtual ~Item() = default;

    bool decrease_timer() {
        if (picked_up) {
            if (--remaining_iterations == 0) {
                picked_up = false;
                return true;  // respawned
            }
        }
        return false;  // hasn't respawned or wasn't picked up in the first place
    }

    Reward pickup() {
        if (!picked_up && remaining_iterations == 0) {
            remaining_iterations = respawn_timer_start;
            picked_up = true;
            return Reward(reward_id, name);
        }
        return Reward();  // invalid reward
    }
};

class Bazooka: public Item {
public:
    Bazooka(): Item(BAZOOKA_RESPAWN_TIMER, "Bazooka", RewardID::BazookaReward) {}
};

class Chainsaw: public Item {
public:
    Chainsaw(): Item(CHAINSAW_RESPAWN_TIMER, "Chainsaw", RewardID::ChainsawReward) {}
};

class DeathRay: public Item {
public:
    DeathRay(): Item(DEATHRAY_RESPAWN_TIMER, "Death ray", RewardID::DeathRayReward) {}
};

class Shotgun: public Item {
public:
    Shotgun(): Item(SHOTGUN_RESPAWN_TIMER, "Shotgun", RewardID::ShotgunReward) {}
};
